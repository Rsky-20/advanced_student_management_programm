/*
Nom : VAUDRY
Prenom : Pierre
Classse : AERO 3PSA-1
Groupe : A1
Exercice :EXERXICE 4
Version : v3_max
Date : 25/01/2023 | seance 3 (cours-TP)
Description :
	Programme de gestion d'etudiant.
	Creation d'une fiche etudiante / Suppression d'une fiche etudiante / Affichage d'une fiche etudiante
	Recherche d'un(e) ou plusieurs etudiant(e)(s) / Sauvegarde via un fichier json / Chargement via un fichier json
*/

//------------------------------------
//             En-tete
//------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lib/ex3_lib.h"

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
        user_cmd = saisir_int(CMDTEXT1, CMDTEXT2, CMDTEXT3, 0, 8);

        switch (user_cmd)
        {
            case 0:
                system("cls");
                afficher_titre();
                printf("\n\n\t\t\t\t   Merci d'avoir utilise le programme etudiant !!!");
                printf("\n\t\t\t\t\t      ######## END ########\n");
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
                printf("\n######## Suppression Etudiant ########\n");

                if(N == 0)
                {
                    printf("\nIl n'y a aucun etudiant a supprimer");
                    system("pause");
                }
                else
                {
                    supprimer_etudiant(e, N);
                    N--;
                    printf("\nL'etudiant(e) a ete supprime avec succes !!!");
                    system("pause");
                }
                break;
            case 5:
                system("cls");
                printf("\n######## Modification Etudiant ########\n");

                if(N == 0)
                {
                    printf("\nIl n'y a aucun etudiant a modifier");
                    system("pause");
                }
                else
                {
                    modifier_etudiant(e, N);
                    printf("\nL'etudiant(e) a ete modifie avec succes !!!");
                    system("pause");
                }
                break;
            case 6:
                system("cls");
                printf("\n######## Sauvegarder Etudiants ########\n");
                int s = sauvegarder_etudiants(e, N);
                printf("\nLa liste d'etudiant a ete sauvegarde avec succes !!!");
                system("pause");
                break;
            case 7:
                system("cls");
                printf("\n######## Charger Etudiants ######## [dev in progree]\n");
                int nbEtudiants;
                nbEtudiants = 0;
                e = charger_etudiants(JSONDATA, &nbEtudiants);
                N = nbEtudiants;
                printf("\nLa liste d'etudiant a ete chargee avec succes !!!");
                system("pause");
                break;
            case 8:
                system("cls");
                printf("\n######## AIDE | Help ########\n");
                aide();
                system("pause");
                break;
            default:
                printf("\nERREUR !!! Choix invalide.\n");
                break;
        }
    }while(user_cmd != 0);
    free(e);
}
