#ifndef VILLE_H
#define VILLE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef struct
{
	char * nom ;
	struct _element_connexion * liste_connexions;
} ville ;

typedef struct _connexion{
	ville * destination;
	int distance;
	int duree_trajet; //en minutes
} connexion ;

typedef struct _element_connexion{
	connexion * contenu;
	struct _element_connexion * next;
} element_connexion;


ville* import_villes();
void import_destination(ville * liste);

int conversion_en_min(int heures, int minutes);

ville * get_ville(ville * liste, char * nom_ville);
void new_connexion(ville * depart, ville * destination, int distance, int duree);

void liberer_villes(ville * liste, int taille);

#endif