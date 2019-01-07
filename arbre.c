#include <arbre.h>

//******************************************************************************
// Fonctions de construction de l'arbre
//******************************************************************************

noeud * construction_arbre(ville * liste, ville * depart, ville * arrivee,int hauteur)
{
	noeud * noeud_initial = allouer_noeud(depart);
	*(noeud_initial->villes_visitees+indice_ville(liste,depart))=1;
	
	noeud_initial->liste_villes_visitees = (element_ville*) malloc(sizeof(element_ville));
	noeud_initial->liste_villes_visitees->contenu = depart;
	noeud_initial->liste_villes_visitees->next =NULL;
	
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
	nouveau_noeud->liste_villes_visitees = NULL;
	
	return nouveau_noeud;
}

element_noeud * ajouter_fils(ville * liste, noeud * parent,ville * ville_ajoutee)
{
	element_noeud * nouveau_element = (element_noeud *) malloc(sizeof(element_noeud));
	nouveau_element->contenu = allouer_noeud(ville_ajoutee);
	
	nouveau_element->next =parent->liste_fils;
	parent->liste_fils = nouveau_element;
	
	for(int i=0; i<23;i++)
	{
		*(nouveau_element->contenu->villes_visitees+i) =*(parent->villes_visitees+i);
	}
	*(nouveau_element->contenu->villes_visitees+indice_ville(liste,ville_ajoutee))=1;
	
	nouveau_element ->contenu->liste_villes_visitees = NULL;
	ajouter_ville_visitee(parent,nouveau_element);
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
				element_noeud * nouveau_fils = ajouter_fils(liste,parent,temp->contenu->destination);
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

void tous_trajet(noeud * arbre, ville * arrivee,int est_trouve)
{
	if(arbre->ville_noeud == arrivee && est_trouve==0)
	{
		affichage_trajet_trouve(arbre,0);
		printf("\n\n");
		est_trouve==1;
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			tous_trajet(temp->contenu,arrivee,est_trouve);
			temp = temp->next;
		}
	}
}

void premier_trajet(noeud * arbre, ville * arrivee,int *est_trouve)
{
	if(arbre->ville_noeud == arrivee && *est_trouve==0)
	{
		affichage_trajet_trouve(arbre,0);
		printf("\n");
		*est_trouve=1;
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			premier_trajet(temp->contenu,arrivee,est_trouve);
			temp = temp->next;
		}
	}
}

void affichage_trajet_trouve(noeud * arbre, int option)
{
	element_ville * temp = arbre->liste_villes_visitees;
	int somme_distance=0;
	int somme_duree=0;
	while(temp!=NULL)
	{
		printf("%s ", temp->contenu->nom);
		
		element_connexion * temp_co = temp->contenu->liste_connexions;
		while(temp->next!=NULL && temp_co!=NULL && temp_co->contenu->destination!=temp->next->contenu)
		{
			temp_co = temp_co->next;
		}
		if(temp->next!=NULL)
		{
			printf("-> %dkm %dmin : ",temp_co->contenu->distance,temp_co->contenu->duree_trajet);
			somme_distance+=temp_co->contenu->distance;
			somme_duree+= temp_co->contenu->duree_trajet;
		}
		temp= temp->next;
	}
	printf(" == %dkm %dmin", somme_distance,somme_duree);
}

void ajouter_ville_visitee(noeud * parent, element_noeud * noeud_act)
{
	element_ville * temp_parent = parent->liste_villes_visitees;
	element_ville * temp=(element_ville*) malloc(sizeof(element_ville));
	noeud_act->contenu->liste_villes_visitees = temp;
	
	while(temp_parent !=NULL)
	{
		temp->contenu = temp_parent->contenu;
		temp->next = (element_ville*) malloc(sizeof(element_ville));
		temp = temp->next;
		temp_parent = temp_parent->next;
	}
	temp->contenu = noeud_act->contenu->ville_noeud;
	temp->next =NULL;
}

