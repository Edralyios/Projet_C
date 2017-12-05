#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "../../doc/Trains.txt"
#define LENGTH 256


// type structuré trajet contenant tous les attributs d'un trajet en train selon notre BD.
typedef struct Trajet Trajet;
struct Trajet
{
        char depart[LENGTH];
        char arrivee[LENGTH];
        char heureDepart[6];
        char heureArrivee[6];
        char duree[6];
        char prix[7];
        char option[5];
};

int main(int argc, char **argv){
	FILE* fichier;
	char c;
	int swt = 0;

	fichier = fopen(PATH, "r");
	while (fichier == NULL){
		printf("Erreur lors de l'ouverture du fichier '%s'\n\nEntrez un nouveau chemin :", PATH);
		char s[LENGTH];
		scanf("%s", s);
		fichier = fopen(s, "r");
	}

	c = fgetc(fichier);
	while(c != EOF){
		
	}

	return 0;
}