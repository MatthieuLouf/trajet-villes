#include <carte.h>
#include <arbre.h>

//******************************************************************************
// Demander nombre ou string
//******************************************************************************

int demander_nb(int min, int max)
{
	int nb=-1;
	while(nb<min || (nb>max && max!=-1))
	{
		scanf("%d",&nb);
	}
	return nb;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
	//viderBuffer();
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin)!= NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

char * demander_str()
{
	char * chaine2 = (char *) malloc(sizeof(char)*100);
	lire(chaine2,100);
	return chaine2;
}

//******************************************************************************
// Menu
//******************************************************************************

void menu()
{
	char * chaine = NULL;
	int choix =0;
	int est_trouve=0;
	int trouve = 0;
	int hauteur;
	ville * liste = import_villes();
	import_destination(liste);
	
	printf("Entrez le nom de la ville de depart : ");
	chaine = demander_str();
	ville* depart = get_ville(liste,chaine);
	
	printf("Entrez le nom de la ville d'arrivee : ");
	chaine = demander_str();
	ville* arrive = get_ville(liste,chaine);
	
	printf("Entrez la hauteur de l'arbre : ");
	hauteur = demander_nb(1,23);
	
	noeud * arbre = construction_arbre(liste,depart, arrive,hauteur);
	nb_trajet(arbre,arrive,&est_trouve);
	
	while (choix!=7)
	{
		system("cls");
		printf("\n	Programme de recherche de trajets \n\n");
		
		printf("	-> Entre %s et %s, %d trajets trouves! \n\n",depart->nom, arrive->nom,est_trouve);
		printf("	1. Un trajet	2. Tous les trajets \n\n 	3. Trajet le plus court    4. Trajet le plus rapide	\n\n	5. Arbre des trajets \n	6. Changer de trajet	7. Quitter \n\n	Choix: ");
		choix = demander_nb(1,7);
		
		switch(choix)
		{
			case 1:
				trouve = 0;
				premier_trajet(arbre,arrive,&trouve);
				break;
				
			case 2:
				tous_trajet(arbre,arrive,0);
				break;
				
			case 3:
				trajet_petite_distance(arbre,arrive);
				break;
				
			case 4:
				trajet_petite_duree(arbre,arrive);
				break;
				
			case 5:
				affichage_arbre(arbre,0);
				break;
			
			case 6:
				viderBuffer();
				printf("Entrez le nom de la ville de depart : ");
				chaine = demander_str();
				depart = get_ville(liste,chaine);
				printf("Entrez le nom de la ville d'arrivee : ");
				chaine = demander_str();
				arrive = get_ville(liste,chaine);
				printf("Entrez la hauteur de l'arbre : ");
				hauteur = demander_nb(1,23);
				arbre = construction_arbre(liste,depart, arrive,hauteur);
				est_trouve=0;
				nb_trajet(arbre,arrive,&est_trouve);
				break;
		}
		
		if(choix!=7)
		{
			printf("\n");
			viderBuffer();
			printf("\n Appuyez sur Entree pour continuer:");
			char suite =' ';
			scanf("%c",&suite);
		}
	}
	liberer_arbre(arbre);
	liberer_villes(liste,23);
}

int main(int argc, char **argv)
{
	menu();
	return 0;
}
