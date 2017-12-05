#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <wait.h>
#include <unistd.h>


void fctserveur (int sockdescr){
	// Fonction qui lit dans la socket une chaine de caractères (en fait un
	// bloc d'octets) et l'affiche à l'écran comme une chaine de caractères
	// ...
	int i;
	read(sockdescr, &i, sizeof(&i));
    printf("Recu %i\n",i);
}


void finfils(int sig){
	wait(&sig);
	printf("Fermeture du fils (serveur.c:finfils)\n");
}


int main(int argc, char **argv){
	// structures pour la socket d'écoute et la socket de service :
	struct sockaddr_in serveur_ad, client_ad;
	// déclarations des autres variables nécessaires :

	//nombre de requète maxi en attente
	int nb = 10;

	//numéro de port choisi ou 3 par défaut
	int port = 4200;
	if(argv[1] == NULL){
		printf("Port non précisé, il aura pour valeur 4200\n");
	}
	else { port = atoi(argv[1]); }

	// préparation de la variable serveur_ad de type 'struct sockaddr_in'
	serveur_ad.sin_family = AF_INET;
	serveur_ad.sin_port = htons(port);
	(serveur_ad.sin_addr).s_addr = htonl(INADDR_ANY);

	// préparation de la variable signal de type 'struct sigaction'
	struct sigaction signal;
	signal.sa_handler = finfils;
	signal.sa_flags = SA_RESTART;


	// Serveur :
	// récupère le numéro de port en argument (si présent !), se met en état de
	// recevoir des requêtes de clients, et sert chaque requête grâce à la
	// fonction fctserveur
	
	int sock_ecoute = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_ecoute == -1){printf("Erreur à la création de la socket (serveur.c:main)\n");}


	if (bind(sock_ecoute, (struct sockaddr *)&serveur_ad, sizeof(serveur_ad)) == -1) {
		printf("Erreur à la création du bind (serveur.c:main) \n");
		//printf("(struct sockaddr *) &serveur_ad = %i \n", (struct sockaddr *) &serveur_ad);
		printf("sock_ecoute = %i \n", sock_ecoute);
		printf("sizeof(serveur_ad) = %lu \n", sizeof(serveur_ad));
	}

	if (listen(sock_ecoute, nb) == -1) {printf("Erreur à l'ouverture du service (serveur.c:main:listen)\n");}


	while(1) {
		printf("En attente de requète client\n");	
		//création client par accept()
		int size_struct = sizeof(client_ad);
		int sock_client = accept(sock_ecoute, (struct sockaddr*) &client_ad, &size_struct);


		switch(fork()){
			case 0 :
				printf("Service de client\n");
				// service du client puis fermeture de son socket
				fctserveur(sock_client);
				close(sock_client);
				finfils(sigaction(SIGCHLD, &signal, NULL));
			default :
				break;
		}
	}

	return 0;
}
