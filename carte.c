#include <carte.h>

//******************************************************************************
// Fonctions d'importation des villes et connexions
//******************************************************************************

ville * import_villes()
{
	char nom_fichier[] = "villes.csv";
	FILE* fichier_ville = fopen(nom_fichier,"r"); 		// ouverture en lecture (read)
	
	int nb_villes = 23; 
	ville * liste_villes = (ville *)malloc(sizeof(ville)*nb_villes);
	
	if( fichier_ville != NULL )
	{
		int MAX_STRING_LEN = 100;
		char* ma_ville = (char*)malloc(MAX_STRING_LEN*sizeof(char));

		fscanf(fichier_ville, "%s", ma_ville); //affiche sur la console la 1ere ligne du fichier mais faut pas le mettre dans la liste
		
		for (int k=0; k<nb_villes;k++)
		{
			fscanf(fichier_ville, "%s", ma_ville);
			
			(liste_villes+k)->nom = (char*)malloc(MAX_STRING_LEN*sizeof(char));
			strcpy((liste_villes+k)->nom,ma_ville);
			(liste_villes+k)->liste_connexions = NULL;
		}
		fclose(fichier_ville);
		free(ma_ville);
	}
	else
	{
		printf("Problème lors de l'ouverture du fichier %s\n", nom_fichier);
	}
	return liste_villes;
}

void import_destination(ville * liste)
{
	char nom_fichier[] = "connexions.csv";
	FILE* fichier_dest = fopen(nom_fichier,"r"); // ouverture en lecture (read)
	
	if( fichier_dest != NULL )
	{
		int MAX_STRING_LEN = 100;
		char* nom_ville = (char*)malloc(MAX_STRING_LEN*sizeof(char));
		char* dest = (char*)malloc(MAX_STRING_LEN*sizeof(char));
		int dist = 0;
		int heures = 0;
		int minutes = 0;
		char osef= '\n';
		//int k=0;
		
		fscanf(fichier_dest,"%s",nom_ville);
		
		for (int k = 0; k<72; k++)
		{
			fscanf(fichier_dest, "%c%[^,],%[^,],%d,%d:%d", &osef,nom_ville, dest, &dist, &heures, &minutes);
			
			//printf("\n%s %s %d %d %d \n",nom_ville, dest, dist, heures, minutes);
			new_connexion(get_ville(liste,nom_ville),get_ville(liste,dest),dist,conversion_en_min(heures,minutes));
		}
		fclose(fichier_dest); // fermeture du fichier_dest
	}
	else
	{
		printf("Problème lors de l'ouverture du fichier_dest %s\n", nom_fichier);
	}
}

ville * get_ville(ville * liste, char * nom_ville)
{
	int i =0;
	while(strcmp((liste+i)->nom,nom_ville)!=0)
	{
		i++;
	}
	return (liste+i);
}

void new_connexion(ville * depart, ville * destination, int distance, int duree)
{
	element_connexion * elem = (element_connexion *) malloc(sizeof(element_connexion));

	elem -> contenu = (connexion *) malloc(sizeof(connexion));
	elem -> contenu -> destination =destination;
	elem -> contenu -> distance= distance;
	elem -> contenu -> duree_trajet = duree;
	
	elem -> next = depart -> liste_connexions;
	depart -> liste_connexions = elem;
}

int conversion_en_min(int heures, int minutes)
{
	int tmp_minu = heures*60+minutes;
	return tmp_minu;
}

//******************************************************************************
// Fonction de libération des villes et de leurs structures internes
//******************************************************************************

void liberer_villes(ville * liste, int taille)
{
	for(int i =0;i<taille;i++)
	{
		free((liste+i)->nom);
		
		element_connexion * temp = ((liste+i)->liste_connexions);
		while(temp!=NULL)
		{
			element_connexion * temp_co = temp;
			temp = temp->next;
			free(temp_co->contenu);
			free(temp_co);
		}
		free((liste+i)->liste_connexions);
	}
	free(liste);
}

//******************************************************************************
// Fonction d'affichage de la liste de villes et de leurs connexions
//******************************************************************************

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