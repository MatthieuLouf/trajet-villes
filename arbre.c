#include <arbre.h>

//******************************************************************************
// Fonctions de construction de l'arbre
//******************************************************************************

noeud * construction_arbre(ville * liste, ville * depart, ville * arrivee,int hauteur)
{
	noeud * noeud_initial = allouer_noeud(depart);
	*(noeud_initial->villes_visitees+indice_ville(liste,depart))=1;
	noeud_initial->distance_previous_noeud=0;
	noeud_initial->duree_previous_noeud=0;
	
	remplir_arbre(liste,noeud_initial,arrivee,hauteur,0);
	
	return noeud_initial;
}

noeud * allouer_noeud(ville * ville_ajoutee)
{
	noeud * nouveau_noeud = (noeud *) malloc(sizeof(noeud));
	nouveau_noeud->ville_noeud = ville_ajoutee;
	nouveau_noeud->liste_fils = NULL;
	nouveau_noeud->villes_visitees = (int*) malloc(sizeof(int)*23);
	
	for(int i=0;i<23;i++)
	{
		*(nouveau_noeud->villes_visitees+i) = 0;
	}
	
	return nouveau_noeud;
}

element_noeud * ajouter_fils(ville * liste, noeud * parent,ville * ville_ajoutee,int duree,int distance)
{
	element_noeud * nouveau_element = (element_noeud *) malloc(sizeof(element_noeud));
	nouveau_element->contenu = allouer_noeud(ville_ajoutee);
	nouveau_element->contenu->distance_previous_noeud = distance;
	nouveau_element->contenu->duree_previous_noeud = duree;
	
	nouveau_element->next =parent->liste_fils;
	parent->liste_fils = nouveau_element;
	
	for(int i=0; i<23;i++)
	{
		*(nouveau_element->contenu->villes_visitees+i) =*(parent->villes_visitees+i);
	}
	*(nouveau_element->contenu->villes_visitees+indice_ville(liste,ville_ajoutee))=1;
	
	return nouveau_element;
}

int indice_ville(ville *liste,ville * cherchee)
{
	int i=0;
	while(liste+i!=cherchee)
	{
		i++;
	}
	return i;
}

void remplir_arbre(ville* liste,noeud * parent,ville * arrivee, int hauteur_limite,int hauteur)
{
	if( (hauteur<hauteur_limite) && (parent->ville_noeud!=arrivee) )
	{
		element_connexion * temp =parent->ville_noeud->liste_connexions;
		while(temp!=NULL)
		{
			if(*(parent->villes_visitees+indice_ville(liste,temp->contenu->destination)) == 0)
			{
				element_noeud * nouveau_fils = ajouter_fils(liste,parent,temp->contenu->destination,temp->contenu->duree_trajet,temp->contenu->distance);
				remplir_arbre(liste,nouveau_fils->contenu,arrivee,hauteur_limite,hauteur+1);
			}
			temp = temp->next;
		}
	}
}

void liberer_arbre(noeud * arbre)
{
	if(arbre!=NULL)
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			liberer_arbre(temp->contenu);
			element_noeud *temp_next = temp->next;
			free(temp->contenu->villes_visitees);
			free(temp->contenu->liste_fils);
			free(temp->contenu);
			temp = temp_next;
		}
		free(arbre->villes_visitees);
		free(arbre->liste_fils);
		free(arbre);
	}
}

//******************************************************************************
// Fonctions de recherche dans l'arbre
//******************************************************************************

void premier_trajet(noeud * arbre, ville * arrivee, char * chaine,int * est_trouve)
{
	if(arbre->ville_noeud == arrivee)
	{
		*est_trouve =1;
	}
	else if(*est_trouve==0)
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			//printf("%s\n",temp->contenu->ville_noeud->nom);
			premier_trajet(temp->contenu,arrivee,chaine,est_trouve);
			temp = temp->next;
		}
	}
	
	//printf("\n");
	if(*est_trouve ==1)
	{
		strcat(chaine,arbre->ville_noeud->nom);
		//printf("%s\n",arbre->ville_noeud->nom);
	}
}

void affichage_premier_trajet(noeud * arbre, ville * arrivee)
{
	char * chaine = (char *) malloc(sizeof(char)*1000);
	*chaine='\0';
	int * est_trouve = (int *) malloc(sizeof(int));
	*est_trouve=0;
	premier_trajet(arbre,arrivee,chaine,est_trouve);
	printf("%s", chaine);
}
