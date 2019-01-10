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

//******************************************************************************
// Fonctions de recherche dans l'arbre
//******************************************************************************

void tous_trajet(noeud * arbre, ville * arrivee)
{
	if(arbre->ville_noeud == arrivee)
	{
		affichage_trajet_trouve(arbre);
		printf("\n\n");
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			tous_trajet(temp->contenu,arrivee);
			temp = temp->next;
		}
	}
}

void premier_trajet(noeud * arbre, ville * arrivee,int *est_trouve)
{
	if(arbre->ville_noeud == arrivee && *est_trouve==0)
	{
		affichage_trajet_trouve(arbre);
		printf("\n");
		*est_trouve=1;
	}
	else if (* est_trouve== 0)
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			premier_trajet(temp->contenu,arrivee,est_trouve);
			temp = temp->next;
		}
	}
}

void nb_trajet(noeud * arbre, ville * arrivee,int *compt)
{
	if(arbre->ville_noeud == arrivee)
	{
		*compt =*compt+1;
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			nb_trajet(temp->contenu,arrivee,compt);
			temp = temp->next;
		}
	}
}

//******************************************************************************
// Trajet plus court
//******************************************************************************

void trajet_petite_duree(noeud * arbre, ville * arrivee)
{
	int  nb_trajets = 0;
	nb_trajet(arbre,arrivee,&nb_trajets);
	int nb_trajets2=0;
	int distance_min = 100000;
	int indice_distance_min = -1;
	indice_petite_duree(arbre,arrivee,&nb_trajets2,&indice_distance_min,&distance_min);
	int nb_trajets3=0;
	affichage_petite_duree(arbre,arrivee,&nb_trajets3,&indice_distance_min);
}

void indice_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court)
{
	if(arbre->ville_noeud == arrivee)
	{
		*compt =*compt+1;
		if(duree_trajet(arbre->liste_villes_visitees)<*plus_court)
		{
			*plus_court= duree_trajet(arbre->liste_villes_visitees);
			*ind_plus_court = *compt;
		}
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			indice_petite_duree(temp->contenu,arrivee,compt,ind_plus_court,plus_court);
			temp = temp->next;
		}
	}
}

void affichage_petite_duree(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court)
{
	if(arbre->ville_noeud == arrivee)
	{
		*compt =*compt+1;
		if(*compt==*ind_plus_court)
		{
			affichage_trajet_trouve(arbre);
		}
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			affichage_petite_duree(temp->contenu,arrivee,compt,ind_plus_court);
			temp = temp->next;
		}
	}
}

int duree_trajet(element_ville * arrivee)
{
	element_ville * temp = arrivee;
	int somme_duree=0;
	while(temp!=NULL)
	{
		element_connexion * temp_co = temp->contenu->liste_connexions;
		while(temp->next!=NULL && temp_co!=NULL && temp_co->contenu->destination!=temp->next->contenu)
		{
			temp_co = temp_co->next;
		}
		if(temp->next!=NULL)
		{
			somme_duree+= temp_co->contenu->duree_trajet;
		}
		temp= temp->next;
	}
	return somme_duree;
}

//******************************************************************************
// Trajet petite distance
//******************************************************************************

void trajet_petite_distance(noeud * arbre, ville * arrivee)
{
	int  nb_trajets = 0;
	nb_trajet(arbre,arrivee,&nb_trajets);
	int nb_trajets2=0;
	int distance_min = 100000;
	int indice_distance_min = -1;
	indice_petite_distance(arbre,arrivee,&nb_trajets2,&indice_distance_min,&distance_min);
	int nb_trajets3=0;
	affichage_petite_distance(arbre,arrivee,&nb_trajets3,&indice_distance_min,&distance_min);
}

void indice_petite_distance(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court)
{
	if(arbre->ville_noeud == arrivee)
	{
		*compt =*compt+1;
		if(distance_trajet(arbre->liste_villes_visitees)<*plus_court)
		{
			*plus_court= distance_trajet(arbre->liste_villes_visitees);
			*ind_plus_court = *compt;
		}
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			indice_petite_distance(temp->contenu,arrivee,compt,ind_plus_court,plus_court);
			temp = temp->next;
		}
	}
}

void affichage_petite_distance(noeud * arbre, ville * arrivee,int *compt, int * ind_plus_court, int * plus_court)
{
	if(arbre->ville_noeud == arrivee)
	{
		*compt =*compt+1;
		if(*compt==*ind_plus_court)
		{
			affichage_trajet_trouve(arbre);
		}
	}
	else
	{
		element_noeud * temp =arbre->liste_fils;
		while(temp!=NULL)
		{
			affichage_petite_distance(temp->contenu,arrivee,compt,ind_plus_court,plus_court);
			temp = temp->next;
		}
	}
}

int distance_trajet(element_ville * arrivee)
{
	element_ville * temp = arrivee;
	int somme_distance=0;
	while(temp!=NULL)
	{
		element_connexion * temp_co = temp->contenu->liste_connexions;
		while(temp->next!=NULL && temp_co!=NULL && temp_co->contenu->destination!=temp->next->contenu)
		{
			temp_co = temp_co->next;
		}
		if(temp->next!=NULL)
		{
			somme_distance+= temp_co->contenu->distance;
		}
		temp= temp->next;
	}
	return somme_distance;
}

//******************************************************************************
// Affichage trajet
//******************************************************************************

void ajout_decalage(int decalage)
{
	for(int i=0;i<decalage;i++)
	{
		printf("	");
	}
}

void affichage_arbre(noeud * parent, int decalage)
{
	if(parent!=NULL)
	{
		ajout_decalage(decalage);
		printf("|-%s\n", parent->ville_noeud->nom);
		
		element_noeud * temp =parent->liste_fils;
		while(temp!=NULL)
		{
			affichage_arbre(temp->contenu,decalage+1);
			temp = temp->next;
		}
	}
}

void affichage_trajet_trouve(noeud * arbre)
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
			color(8,0);
			printf("-> %dkm",temp_co->contenu->distance);
			afficher_conversion_heures(temp_co->contenu->duree_trajet);
			printf(" :");
			color(15,0);
			somme_distance+=temp_co->contenu->distance;
			somme_duree+= temp_co->contenu->duree_trajet;
		}
		temp= temp->next;
	}
	color(3,0);
	printf(" == %dkm", somme_distance);
	afficher_conversion_heures(somme_duree);
	color(15,0);
}

void color(int t,int f)
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,f*16+t);
}

void afficher_conversion_heures(int minutes)
{
	int heures = minutes / 60;
	minutes = minutes % 60;
	printf(" %dh%dmin",heures,minutes);
}