#include <carte.h>
#include <arbre.h>

void affichage_liste_destinations(ville * liste)
{
	for(int i=0;i<23;i++)
	{
		printf("%s\n",(liste+i)->nom);

		element_connexion * temp = ((liste+i)->liste_connexions);
		while(temp!=NULL)
		{
			connexion * temp_co = temp -> contenu;
			printf("	%s %d %d\n",(temp_co->destination)->nom,temp_co->distance,temp_co->duree_trajet);
			temp = temp->next;
		}
	}
}

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

int main(int argc, char **argv)
{
	ville * liste = import_villes();
	import_destination(liste);
	//affichage_liste_destinations(liste);
	
	ville * Lille = get_ville(liste,"Lille");
	ville * Bayonne = get_ville(liste,"Bayonne");
	
	noeud * arbre = construction_arbre(liste,Lille,Bayonne,8);
	
	
	//printf("\n\n");
	//affichage_arbre(arbre,0);
	
	printf("\n");
	tous_trajet(arbre,Bayonne,0);
	
	printf("\n");
	int est_trouve = 0;
	//premier_trajet(arbre,Bayonne,&est_trouve);
	
	liberer_arbre(arbre);
	
	liberer_villes(liste,23);
	return 0;
}
