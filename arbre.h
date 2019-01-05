#ifndef ARBRE_H
#define ARBRE_H

#include <carte.h>

typedef struct _noeud {
	ville * ville_noeud;
	int * villes_visitees;
	
	int duree_previous_noeud;
	int distance_previous_noeud;
	
	struct _element_noeud * liste_fils;
} noeud;

typedef struct _element_noeud {
	noeud * contenu;
	struct _element_noeud * next;
}element_noeud;

noeud * construction_arbre(ville * liste, ville * depart, ville * arrivee,int hauteur);
noeud * allouer_noeud(ville * ville_ajoutee);
element_noeud * ajouter_fils(ville * liste, noeud * parent,ville * ville_ajoutee,int duree,int distance);

int indice_ville(ville *liste,ville * cherchee);

void remplir_arbre(ville* liste,noeud * parent,ville * arrivee, int hauteur_limite,int hauteur);

void liberer_arbre(noeud * arbre);

void premier_trajet(noeud * arbre, ville * arrivee, char * chaine,int * est_trouve);
void affichage_premier_trajet(noeud * arbre, ville * arrivee);

#endif