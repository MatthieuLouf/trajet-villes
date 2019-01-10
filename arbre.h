#ifndef ARBRE_H
#define ARBRE_H

#include <carte.h>
#include <windows.h>//gestion couleurs
#include <string.h>

//******************************************************************************
// Stucture de base d'un noeud contenant la liste des fils
//******************************************************************************
typedef struct _noeud {
	ville * ville_noeud;
	int * villes_visitees;
	
	struct _element_ville * liste_villes_visitees; //villes parentes du noeud

	struct _element_noeud * liste_fils;
} noeud;

//******************************************************************************
// Structure element_noeud pour construire la liste des noeuds fils
//******************************************************************************
typedef struct _element_noeud {
	noeud * contenu;
	struct _element_noeud * next;
}element_noeud;

//******************************************************************************
// Structure element_ville pour construire la liste des villes parentes du noeud
//******************************************************************************
typedef struct _element_ville{
	ville * contenu;
	struct _element_ville * next;
} element_ville;

//******************************************************************************
// Fonctions de construction de l'arbre
//******************************************************************************

/*
 * Fonction de base de la construction de l'arbre, qui initialise le noeud de la ville départ et construit sa descendance
 * Paramètre liste : tableau des villes à ajouter aux noeuds de l'arbre
 * Paramètre depart : ville de départ avec laquelle on initialise le premier noeud
 * Paramètre arrivee : ville d'arrivée pour laquelle on arrête la construction de l'arbre
 * Paramètre hauteur : limite de la taille de l'arbre
 * Fonctions appelées : allouer_noeud, indice_ville, remplir_arbre
 * Return noeud * : le noeud parent de tout l'arbre créé
 */
noeud * construction_arbre(ville * liste, ville * depart, ville * arrivee, int hauteur);

/*
 * Fonction pour allouer un noeud et l'initialiser avec la ville voulue
 * Paramètre ville_ajoutee : ville avec laquelle initialiser le noeud alloué
 * Return noeud * : le noeud alloué et initialisé
 */
noeud * allouer_noeud(ville * ville_ajoutee);

/*
 * Fonction d'ajout d'un fils avec une ville donnée au noeud parent rentré
 * Paramètre liste : tableau des villes existantes
 * Paramètre parent : noeud auquel ajouter un nouveau fils
 * Paramètre ville_ajoutee : ville à ajouter comme fils au noeud parent
 * Fonctions appelées : allouer_noeud, indice_ville, ajouter_ville_visitee
 * Return element_noeud * : le element_noeud pour compléter la liste des fils
 */
element_noeud * ajouter_fils(ville * liste, noeud * parent, ville * ville_ajoutee);

/*
 * Fonction qui calcule l'indice dans la liste de villes d'une ville recherchée
 * Paramètre liste : tableau des villes existantes
 * Paramètre cherchee : ville cherchée dans la liste
 * Return : l'indice de la ville trouvée
 */
int indice_ville(ville * liste,ville * cherchee);

/*
 * Fonction récursive qui parcourt les noeuds et crée les suivants, en vérifiant si l'arrivee n'est pas atteinte et la hauteur de l'arbre dépassée 
 * Paramètre liste : tableau des villes existantes
 * Paramètre parent : noeud actuel dont l'on crée les fils et vérifie la ville
 * Paramètre arrivee : ville d'arrivée qui sert à vérifier que la branche ne l'a pas atteint 
 * Paramètre hauteur_limite : constante qui est la hauteur maximale à ne pas dépasser
 * Paramètre hauteur : entier qui compte la hauteur actuelle de l'arbre en train d'être créé
 * Fonctions appelées : indice_ville, ajouter_fils et remplir_arbre
 * Void
 */
void remplir_arbre(ville* liste,noeud * parent,ville * arrivee, int hauteur_limite,int hauteur);

/*
 * Fonction récursive qui libère noeud par noeud l'arbre
 * Paramètre arbre : noeud parent de l'arbre à libérer
 * Fonctions appelées : liberer_arbre
 * Void
 */
void liberer_arbre(noeud * arbre);

/*
 * Fonction qui créer la liste des villes précédemment visitées au noeud actif à partir de son noeud parent
 * Paramètre parent : noeud parent à partir duquel on copie les villes visitées
 * Paramètre noeud_act : noeud dont l'on crée la liste des villes visitées, en ajoutant sa propre ville
 * Void
 */
void ajouter_ville_visitee(noeud * parent, element_noeud * noeud_act);

//******************************************************************************
// Fonctions de recherche dans l'arbre
//******************************************************************************

/*
 * Fonction récursive qui recherche et affiche tous les trajets trouvés dans l'arbre 
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche tous les trajets
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Fonctions appelées : affichage_trajet_trouve et tous_trajet
 * Void
 */
void tous_trajet(noeud * arbre, ville * arrivee);

/*
 * Fonction récursive qui recherche et affiche le premier noeud trouvé dans l'arbre
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet
 * Paramètre arrivee : ville à atteindre dans la recherche du trajet
 * Paramètre est_trouve : pointeur dont l'entier passe à 1 quand on atteind pour la première fois la ville d'arrivée
 * Fonctions appelées : affichage_trajet_trouve et premier_trajet
 * Void
 */
void premier_trajet(noeud * arbre, ville * arrivee,int * est_trouve);

/*
 * Fonction récursive qui compte le nombre de trajet trouvés dans l'arbre
 * Paramètre arbre : noeud parent de l'arbre dans lequel on compte tous les trajets
 * Paramètre arrivee : on compte le nombre de fois où cette ville est atteinte
 * Paramètre compt : pointeur dont l'entier compteur s'incrémente à chaque fois que la ville d'arrivée est trouvée
 * Fonctions appelées : nb_trajet
 * Void
 */
void nb_trajet(noeud * arbre, ville * arrivee,int *compt);

//******************************************************************************
// Trajet plus court
//******************************************************************************

/*
 * Fonction qui trouve le trajet de plus petite durée puis l'affiche
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus rapide
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Fonctions appelées : nb_trajet, indice_petite_duree et affichage_petite_duree
 * Void
 */
void trajet_petite_duree(noeud * arbre, ville * arrivee);

/*
 * Fonction récursive qui trouve le trajet le moins long et stocke sa position dans l'arbre
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus court
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Paramètre compt : compteur qui suit la position des villes à atteindre dans l'arbre, pour pouvoir la stocker dans ind_plus_court
 * Paramètre ind_plus_court : entier qui stocke la position de la branche la moins longue
 * Paramètre plus_court : entier qui stocke la valeur de la durée la plus courte trouvée actuelle, pour la comparer aux trajets suivants
 * Fonctions appelées : duree_trajet et indice_petite_duree
 * Void
 */
void indice_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court);

/*
 * Fonction récursive qui parcourt l'arbre jusqu'à retrouver la branche identifiée comme plus rapide, pour l'afficher
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus court
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Paramètre compt : compteur qui suit la position des villes à atteindre dans l'arbre, pour pouvoir s'arrêter quand on atteint le trajet le plus court
 * Paramètre ind_plus_court : entier qui indique la position de la branche la plus rapide
 * Fonctions appelées : affichage_petite_duree et affichage_trajet_trouve
 * Void
 */
void affichage_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court);

/*
 * Fonction qui calcule la duree d'un trajet à partir de la liste des villes parcourues d'une feuille de l'arbre
 * Paramètre arrivee : premier element de la liste des villes utilisée
 * Fonctions appelées : affichage_petite_duree et affichage_trajet_trouve
 * Void
 */
int duree_trajet(element_ville * arrivee);

//******************************************************************************
// Trajet petite distance
//******************************************************************************

/*
 * Fonction qui trouve le trajet de plus petite distance puis l'affiche
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus court
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Fonctions appelées : nb_trajet, indice_petite_distance et affichage_petite_distance
 * Void
 */
void trajet_petite_distance(noeud * arbre, ville * arrivee);

/*
 * Fonction récursive qui trouve le trajet avec la plus petite distance et stocke sa position dans l'arbre
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus court
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Paramètre compt : compteur qui suit la position des villes à atteindre dans l'arbre, pour pouvoir la stocker dans ind_plus_court
 * Paramètre ind_plus_court : entier qui stocke la position de la branche la moins longue
 * Paramètre plus_court : entier qui stocke la valeur de la distance la plus courte trouvée actuelle, pour la comparer aux trajets suivants
 * Fonctions appelées : distance_trajet et indice_petite_distance
 * Void
 */
void indice_petite_distance(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court);

/*
 * Fonction récursive qui parcourt l'arbre jusqu'à retrouver la branche identifiée comme plus courte, pour l'afficher
 * Paramètre arbre : noeud parent de l'arbre dans lequel on recherche le trajet le plus court
 * Paramètre arrivee : ville à atteindre dans la recherche de trajets
 * Paramètre compt : compteur qui suit la position des villes à atteindre dans l'arbre, pour pouvoir s'arrêter quand on atteint le trajet le plus court
 * Paramètre ind_plus_court : entier qui indique la position de la branche la plus courte
 * Fonctions appelées : affichage_petite_distance et affichage_trajet_trouve
 * Void
 */
int distance_trajet(element_ville * arrivee);

/*
 * Fonction qui calcule la distance d'un trajet à partir de la liste des villes parcourues d'une feuille de l'arbre
 * Paramètre arrivee : premier element de la liste des villes utilisées
 * Fonctions appelées : affichage_petite_distance et affichage_trajet_trouve
 * Void
 */
void affichage_petite_distance(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court);

//******************************************************************************
// Affichage trajet et arbre
//******************************************************************************

/*
 * Fonction qui affiche int decalage fois une tabulation
 * Paramètre decalage : nombre de tabulations à afficher
 * Void
 */
void ajout_decalage(int decalage);

/*
 * Fonction récursive qui affiche l'arbre entier à l'horizontale
 * Paramètre parent : noeud parent de l'arbre à afficher
 * Paramètre decalage : nombre de tabulations à ajouter avant d'afficher la ville du noeud
 * Fonctions appelées : ajout_decalage, affichage_arbre + printf
 * Void
 */
void affichage_arbre(noeud * parent, int decalage);

/*
 * Fonction qui affiche un trajet, en indiquant les distance et durées entre chaque ville et leurs valeurs totales
 * Paramètre arbre : noeud dont l'on affiche la liste des villes parcourues
 * Fonctions appelées : color + printf
 * Void
 */
void affichage_trajet_trouve(noeud * arbre);

/*
 * Fonction qui change la couleur de l'affichage dans la console // fonction récupérée du site OpenClassroom
 * Paramètre t : entier entre 1 et 15 représentant la couleur de la typographie
 * Paramètre f : entier entre 1 et 15 représentant la couleur du fond de la console
 * Fonctions appelées : SetConsoleTextAttribute et GetStdHandle
 * Void
 */
void color(int t,int f);


#endif