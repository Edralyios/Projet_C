include <stdio.h>
include <stdlib.h>



 // Fonction qui lit dans la socket une chaine de caractères (en fait un
 // bloc d'octets) et l'affiche à l'écran comme une chaine de caractères
 // ...
void fctserveur (int sockdescr);

 // Handler pour la réception de SIGCHLD
 // ...
void finfils(int sig);
int main(int argc, char **argv);
void fctclient (int sockdescr);
int main(int argc, char **argv);