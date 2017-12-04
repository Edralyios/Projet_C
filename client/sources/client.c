//***** Programme client *****
//Il demande une connexion avec le serveur, puis saisit une ligne au clavier et l'envoie au serveur.
void fctclient (int sockdescr){
 // Fonction qui saisit une chaine de caractères au clavier et l'envoie
 // dans la socket
 // ...
	char s[];
	scanf("%s", s);
	&sockdescr = atoi(s);
}
int main(int argc, char **argv){
 // Client :
 // récupère le nom du serveur et le numéro de port en arguments (si
 // présents !), demande la connexion au serveur, et effectue sa requête
 // grâce à la fonction fctclient
 // ...
 // ...
 return 0;
}