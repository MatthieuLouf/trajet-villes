#ifndef VILLE_H
#define VILLE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

//******************************************************************************
// Structure de base de chaque ville qui contient une liste chainée de connexions
//******************************************************************************
typedef struct
{
	char * nom ;
	struct _element_connexion * liste_connexions;
} ville;

//******************************************************************************
// Structure contenant les éléments de connexion, qui est ensuite stocké dans un élément_connexion
//******************************************************************************
typedef struct _connexion{
	ville * destination;
	int distance;
	int duree_trajet; //en minutes
} connexion ;

//******************************************************************************
// Structure d'un element_connexion qui servira de base à la liste chainée de chaque ville
//******************************************************************************
typedef struct _element_connexion{
	connexion * contenu;
	struct _element_connexion * next;
} element_connexion;

//******************************************************************************
// Fonctions d'importation des villes et connexions
//******************************************************************************

/*
 * Fonction qui importe une liste de villes à partir du fichier villes.csv dans /Debug
 * Fonctions appelées : fopen, fclose, malloc, fscanf, strcpy
 * Return : le tableau de ville créée
 */
ville* import_villes();

/*
 * Fonction qui importe les connexions pour chaque ville à partir du fichier connexions.csv dans /Debug
 * Paramètre liste : tableau des villes précédemment importées, auxquelles on ajoute une liste chainée de connexions
 * Fonctions appelées : fopen, fclose, malloc, fscanf, strcpy + new_connexion(),get_ville(), conversion_en_min()
 * Void : liste modifiée par pointeurs
 */
void import_destination(ville * liste);

/*
 * Fonction qui convertit deux valeurs en heures et minutes en minutes
 * Paramètre heures : nombres d'heures
 * Paramètre minutes : nombres de minutes
 * Return : la valeur équivalente en minutes
 */
int conversion_en_min(int heures, int minutes);

/*
 * Fonction qui récupère l'objet ville à partir de son nom en string
 * Paramètre liste : tableau de villes où la ville est recherchée
 * Paramètre nom_ville : nom en string de la ville recherchée
 * Return : ville * du nom de la ville en entrée
 */
ville * get_ville(ville * liste, char * nom_ville);

/*
 * Fonction qui crée une nouvelle connexion dans la liste chainée de la ville courante
 * Paramètre depart : ville à laquelle ajouter la connexion
 * Paramètre destination : ville qu'on ajoute en connexion à "départ"
 * Paramètre distance : distance qu'on ajoute à cette connexion de "départ"
 * Paramètre duree : duree qu'on ajoute à cette connexion de "départ"
 * Void : modifie par pointeur la ville départ
 */
void new_connexion(ville * depart, ville * destination, int distance, int duree);

//******************************************************************************
// Fonction de libération des villes et de leurs structures internes
//******************************************************************************

/*
 * Fonction qui libère les pointeurs crées dans la liste de villes
 * Paramètre liste : tableau des villes à libérer
 * Paramètre taille : taille du tableau liste
 * Void
 */
void liberer_villes(ville * liste, int taille);

//******************************************************************************
// Fonction d'affichage de la liste de villes et de leurs connexions
//******************************************************************************

/*
 * Fonction qui affiche la liste de villes et leurs villes connectées
 * Paramètre liste : tableau de villes à afficher
 * Void
 */
void affichage_liste_destinations(ville * liste);

#endif