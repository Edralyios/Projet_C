#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <netdb.h>



//***** Programme client *****
//Il demande une connexion avec le serveur, puis saisit une ligne au clavier et l'envoie au serveur.
void fctclient (int sockdescr){
// Fonction qui saisit une chaine de caractères au clavier et l'envoie
// dans la socket
	char i = 42;
	write(sockdescr, &i, sizeof(i));
	printf("Envoyé %i\n",i);

}


int main(int argc, char **argv){
	// Client :
	// récupère le nom du serveur et le numéro de port en arguments (si
	// présents !), demande la connexion au serveur, et effectue sa requête
	// grâce à la fonction fctclient

	//numéro de port choisi ou 3 par défaut
	int port = 4200;
	if(argv[1] == NULL){
		printf("Port non précisé, il aura pour valeur 4200\n");
	}
	else { port = atoi(argv[1]); }

	// préparation de la variable host de type 'struct hosten*'
	//récupération des informations de la machine locale sous le nom 'localhost'
	struct hostent* host = gethostbyname("localhost");

	// préparation de la variable serveur_ad de type 'struct sockaddr_in'
	struct sockaddr_in serveur_ad;
	serveur_ad.sin_family = AF_INET;
	serveur_ad.sin_port = htons(port);
	// recopie des infos de localhost dans serveur_ad (remplace '(serveur_ad.sin_addr).s_addr = htonl(INADDR_ANY)')
	memcpy((void *)(&serveur_ad.sin_addr.s_addr), (const void*)host->h_addr, sizeof(host->h_addr));


	// création du socket du client
	int sock_ecoute = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_ecoute == -1){printf("Erreur à la création de la socket (client.c:main)\n");}



	// demande de connexion
	if (connect(sock_ecoute, (struct sockaddr *) &serveur_ad, sizeof(serveur_ad)) == -1){
		printf("Erreur à la demande de connexion (temps de connexion écoulé) (client.c:main)\n");
	}

	fctclient(sock_ecoute);


	return 0;
}