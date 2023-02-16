/*
Nom : VAUDRY
Prenom : Pierre
Classse : AERO 3PSA-1
Groupe : A1
Exercice :EXERXICE 4
Version : v3_max
Date : 25/01/2023 | seance 3 (cours-TP)
Description :
	Programme de saisie des notes d'un etudiant et affichage de cet etudiant
*/

//------------------------------------
//             En-tete
//------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lib/ex3_lib.h"
//#include"lib/json_lib.h"

//------------------------------------
//        Programme Principal
//------------------------------------
int main()
{
    //Variable global du programme
    Etudiant* e;
    int n, menu, N, user_cmd;
    N = 0;
    afficher_titre();
    description();
    system("pause");

    do{
        system("cls");
        affiche_menu();
        user_cmd = saisir_int(CMDTEXT1, CMDTEXT2, CMDTEXT3, 0, 7);

        switch (user_cmd)
        {
            case 0:
                printf("Merci d'avoir utilise le programme etudiant !!!");
                printf("\n######## END ########\n");
                return 0;
            case 1:
                system("cls");
                printf("\n######## Ajout Etudiant ########\n");
                n = saisir_int(NBTEXT1, NBTEXT2, NBTEXT3, 0, 100);
                if(N == 0)
                {
                    e = (Etudiant*)malloc( n*sizeof(Etudiant));
                }
                else
                {
                    e = (Etudiant*)realloc(e, (N+n)*sizeof(Etudiant));
                }
                saisir_n_etudiant(e, N, N + n);
                N = N + n;
                break;
            case 2:
                system("cls");
                printf("\n######## Afficher Liste Etudiant ########\n");
                afficher_n_etudiant(e, N);
                system("pause");
                break;
            case 3:
                system("cls");
                printf("\n######## Recherche Etudiant ########\n");
                rechercher_etudiants(e, N);
                system("pause");
                break;
            case 4:
                system("cls");
                printf("\n######## Suppression Etudiant ######## [dev in progree]\n");

                int id;
                if(N == 0)
                {
                    printf("\nIl n'y a aucun etudiant a supprimer");
                    system("pause");
                }
                else
                {
                    printf("\n------------ /!\ IMPORTANT /!\ -------------");
                    printf("\n- Saisissez l'id de l'etudiant a supprimer -");
                    printf("\n--------------------------------------------");
                    afficher_n_etudiant(e, N);
                    printf("\n--------------------------------------------");

                    id = saisir_int(IDTEXT1, IDTEXT2, IDTEXT3, 0, N);
                    supprimer_etudiant(id, e, N);
                    N--;
                    system("pause");
                }
                break;
            case 5:
                system("cls");
                printf("\n######## Sauvegarder Etudiants ########\n");
                int s = sauvegarder_etudiants(e, N);
                if(s)
                {
                    printf("\nLa liste d'etudiant a ete sauvegarde avec succes !!!");
                }
                else
                    printf("\n /!\ ERREUR etudiants.json /!\ \nUne erreur s'est produite lors de la sauvegarde du fichier .json ! \n Veuillez verifier que le fichier est au bon format et qu'il comporte des donnees valident.");

                system("pause");
                break;
            case 6:
                system("cls");
                printf("\n######## Charger Etudiants ######## [dev in progree]\n");
                e = charger_etudiants(JSONDATA, N);
                if(e)
                {
                    printf("\nLa liste d'etudiant a ete chargee avec succes !!!");
                }
                else
                    printf("\n /!\ ERREUR etudiants.json /!\ \nUne erreur s'est produite lors du chargement du fichier .json ! \n Veuillez verifier que le fichier est au bon format et qu'il comporte des donnees valident.");

                system("pause");
                break;
            case 7:
                system("cls");
                printf("\n######## AIDE | Help ########\n");
                description();
                system("pause");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }while(user_cmd != 0);
    free(e);
}
