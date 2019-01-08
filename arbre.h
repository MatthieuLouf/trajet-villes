#ifndef ARBRE_H
#define ARBRE_H

#include <carte.h>

typedef struct _noeud {
	ville * ville_noeud;
	int * villes_visitees;
	
	struct _element_ville * liste_villes_visitees;

	struct _element_noeud * liste_fils;
} noeud;

typedef struct _element_noeud {
	noeud * contenu;
	struct _element_noeud * next;
}element_noeud;

typedef struct _element_ville{
	ville * contenu;
	struct _element_ville * next;
} element_ville  ;

//******************************************************************************
// Fonctions de construction de l'arbre
//******************************************************************************

noeud * construction_arbre(ville * liste, ville * depart, ville * arrivee,int hauteur);
noeud * allouer_noeud(ville * ville_ajoutee);
element_noeud * ajouter_fils(ville * liste, noeud * parent,ville * ville_ajoutee);

int indice_ville(ville *liste,ville * cherchee);

void remplir_arbre(ville* liste,noeud * parent,ville * arrivee, int hauteur_limite,int hauteur);

void liberer_arbre(noeud * arbre);
void ajouter_ville_visitee(noeud * parent, element_noeud * noeud_act);

//******************************************************************************
// Fonctions de recherche dans l'arbre
//******************************************************************************

void tous_trajet(noeud * arbre, ville * arrivee,int est_trouve);
void premier_trajet(noeud * arbre, ville * arrivee,int * est_trouve);
void nb_trajet(noeud * arbre, ville * arrivee,int *compt);

//******************************************************************************
// Trajet plus court
//******************************************************************************

void trajet_petite_duree(noeud * arbre, ville * arrivee);
void indice_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court);
void affichage_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court);
int duree_trajet(element_ville * arrivee);

//******************************************************************************
// Trajet petite distance
//******************************************************************************

void trajet_petite_distance(noeud * arbre, ville * arrivee);
void trajet_petite_distance(noeud * arbre, ville * arrivee);
int distance_trajet(element_ville * arrivee);
int distance_trajet(element_ville * arrivee);

//******************************************************************************
// Affichage trajet
//******************************************************************************

void affichage_trajet_trouve(noeud * arbre);
#endif