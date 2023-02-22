/*
Nom : VAUDRY
Prenom : Pierre
Classse : AERO 3PSA-1
Groupe : A1
Exercice :EXERXICE 3
Version : v3_max
Date : 25/02/2023 | seance 3 (cours-TP)
Description :
	Biblio pour le programme de saisie des notes d'un etudiant et affichage de cet etudiant
*/

//------------------------------------
//           Define
//------------------------------------
#define CMDTEXT1 "\nCommand /> "
#define CMDTEXT2 "\nLa saisie de la commande comporte une erreur..."
#define CMDTEXT3 "\nUn entier entre 0 et 8 est demande."

#define IDTEXT1 "\nDonner l'id de l'etudiants : "
#define IDTEXT2 "\nLa saisie de l'id etudiants comporte une erreur..."
#define IDTEXT3 "\nUn entier entre 1 et X est demande."

#define NBTEXT1 "\nDonner le nombre d'etudiants : "
#define NBTEXT2 "\nLa saisie du nombre d'etudiants comporte une erreur..."
#define NBTEXT3 "\nUn entier entre 0 et 100 est demande."

#define ANNEETEXT1 "\nAnnee : "
#define ANNEETEXT2 "\nLa saisie de l'annee comporte une erreur..."
#define ANNEETEXT3 "\nUne annee est entre 1950 et 2100."

#define MOISTEXT1 "\nMois : "
#define MOISTEXT2 "\nLa saisie du mois comporte une erreur..."
#define MOISTEXT3 "\nUn mois est entre 1 et 12."

#define JOURTEXT1 "\nJour : "
#define JOURTEXT2 "\nLa saisie du jour comporte une erreur..."
#define JOURTEXT3 "\nLe jour est entre 1 et 30 (sauf f�vrier |28 ou 29 (bissextile))."

#define JSONDATA "etudiants.json"
#define TAILLE_MAX 1000

//------------------------------------
//           Structure
//------------------------------------
typedef struct {
    int jour, mois, annee; // jour de naissance // mois de naissance // annee de naissance
}date;
//------------------------------------
typedef struct {
    char prenom[20], nom[20];
    date ddn;
    float note1, note2, note3, moyenne;
}Etudiant;

//------------------------------------
//            Fonction
//------------------------------------
/**
 * @brief Saisir un entier sans erreur de boucle infini en cas de saisie d'un float, d'un char. Controle de la saisie utilisateur.
 *
 * @param text1[100] Tableau contenant le text d'affichage 1.
 * @param text2[100] Tableau contenant le text d'affichage 2.
 * @param text3[100] Tableau contenant le text d'affichage 3.
 * @param min_nb la borne inferieur.
 * @param max_nb la borne superieur.
 */
int saisir_int(char text1[100], char text2[100], char text3[100],int min_nb, int max_nb)
{
    int n = 0;
    do{
        printf("%s", text1);
        if ((scanf("%d", &n)) != 1) // v�rifie si la saisie est invalide
        {
            printf(text2);
            printf(text3);
            fflush(stdin); // vide le tampon d'entr�e
            n = -1; // affecte -1 pour que la boucle continue
        }
        else if (n < min_nb || n > max_nb) // v�rifie si le nombre est hors limites
        {
            printf(text2);
            printf(text3);
            n = -1; // affecte -1 pour que la boucle continue
        }
    }while (n < min_nb);
}
//------------------------------------
/**
 * @brief Saisir une date sans erreur de boucle infini en cas de saisie d'un float, d'un char.
 */
date saisir_date()
{
    date d;
    int bissextile = 0, annee;
    time_t t;
    // Renvoie l'heure actuelle
    time(&t);

    struct tm *local = localtime(&t);
    annee = local->tm_year + 1900;

    printf("\nSaisir la date de naissance au format : jj/mm/aaaa");
    printf("\nEntrez l'annee de naissance : ");
    d.annee = saisir_int(ANNEETEXT1, ANNEETEXT2, ANNEETEXT3, 1950, annee);

    if ((d.annee % 4 == 0 && d.annee % 100 != 0) || d.annee % 400 == 0)
    {
        bissextile = 1;
        printf("\nL'annee est bissextile.");
    }
    else
        printf("\nL'annee n'est pas bissextile.");

    printf("\nEntrez le mois de naissance : ");
    d.mois = saisir_int(MOISTEXT1, MOISTEXT2, MOISTEXT3, 1, 12);

    // Verifier si le mois de fevrier doit avoir 29 jours
    if(d.mois == 2)
    {
        // Verifier si l'annee est bissextile
        if(bissextile)
        {
            printf("\nLe mois de fevrier a 29 jours.");
            printf("\nEntrez le jour de naissance (1-29) : ");
            d.jour = saisir_int(JOURTEXT1, JOURTEXT2, JOURTEXT3,1 , 29);
        }
        else
        {
            printf("\nLe mois de fevrier a 28 jours.");
            printf("\nEntrez le jour de naissance (1-28) : ");
            d.jour = saisir_int(JOURTEXT1, JOURTEXT2, JOURTEXT3, 1, 28);
        }
    }
    else
    {
        if(d.mois == 1 || d.mois == 3 || d.mois == 5 || d.mois == 7 || d.mois == 8 || d.mois == 10 || d.mois == 12)
        {
            printf("\nEntrez le jour de naissance (1-31) : ");
            d.jour = saisir_int(JOURTEXT1, JOURTEXT2, JOURTEXT3, 1, 31);
        }
        if(d.mois == 4 || d.mois == 6 || d.mois == 8 || d.mois == 11)
        {
            printf("\nEntrez le jour de naissance (1-30) : ");
            d.jour = saisir_int(JOURTEXT1, JOURTEXT2, JOURTEXT3, 1, 30);
        }
    }
    return d;
}
//------------------------------------
/**
 * @brief Affiche la date selon le format standard jj/mm/aaaa.
 *
 * @param d Structure date.
 */
void afficher_date(date d)
{
    printf("\n     DDN : %02d/%02d/%04d", d.jour, d.mois, d.annee);
}
//------------------------------------
/**
 * @brief Extraire la date a partir du format standard jj/mm/aaaa.
 *
 * @param chaine chaine de charactere contenant la date.
 */
date extraire_date(char* chaine)
{
    date d;
    sscanf(chaine, "%d/%d/%d", &(d.jour), &(d.mois), &(d.annee));
    return d;
}
//------------------------------------
/**
 * @brief Saisir les informations d'un etudiant.
 *
 * @param i Position de l'etudiants a afficher.
 */
Etudiant saisir_1_etudiant(int i)
{
    Etudiant e;
    date DateDeNaissance;
    printf("\n ------------------");
    printf("\n   Etudiant %d  ", i+1);
    printf("\n ------------------");
    printf("\nNom : ");
    scanf("%s", &e.nom);

    printf("\nPrenom: ");
    scanf("%s", &e.prenom);

    DateDeNaissance = saisir_date();
    e.ddn = DateDeNaissance;
    printf("------------------");
    printf("\nSaisir les notes : ");
    do{
        printf("\nNote 1 : ");
        scanf("%f", &e.note1);
    }while(e.note1 < 0 || e.note1 > 20);

    do{
        printf("\nNote 2 : ");
        scanf("%f", &e.note2);
    }while(e.note2 < 0 || e.note2 > 20);

    do{
        printf("\nNote 3 : ");
        scanf("%f", &e.note3);
    }while(e.note3 < 0 || e.note3 > 20);

    e.moyenne = (e.note1 + e.note2 + e.note3) / 3;
    return(e);
}
//------------------------------------
/**
 * @brief saisir X etudiant.
 *
 * @param e Tableau d'etudiants contenant les informations a afficher.
 * @param ini Le nombre d'etudiants initiale.
 * @param fin Le nombre d'etudiants finale.
 */
void  saisir_n_etudiant(Etudiant *e, int ini ,int fin)
{
    for (int i = ini ; i < fin ; i++ )
    {
        *(e+i) = saisir_1_etudiant(i);
        system("pause");
        system("cls");
    }
}
//------------------------------------
/**
 * @brief Affiche les informations de tous les etudiants sous forme de liste.
 *
 * @param e Tableau d'�tudiants contenant les informations a afficher.
 * @param i Position de l'etudiants � afficher.
 */
void afficher_1_etudiant(Etudiant e, int i )
{
    printf("\n ---------------------");
    printf("\n      Etudiant %d  ", i+1);
    printf("\n ---------------------");
    printf("\n     Nom : %s", e.nom);
    printf("\n  Prenom : %s", e.prenom);
    afficher_date(e.ddn);
    printf("\n  Note 1 : %.2f/20", e.note1);
    printf("\n  Note 2 : %.2f/20", e.note2);
    printf("\n  Note 3 : %.2f/20", e.note3);
    printf("\n ---------------------");
    printf("\n Moyenne :  %.2f/20", e.moyenne);
    printf("\n ---------------------\n");
}
//------------------------------------
/**
 * @brief Affiche les informations de tous les �tudiants sous forme de liste.
 *
 * @param e Tableau d'�tudiants contenant les informations a afficher.
 * @param nb_etudiants Le nombre d'etudiants a afficher.
 */
void  afficher_n_etudiant(Etudiant *e, int nb_etudiants)
{
    for (int i = 0 ; i < nb_etudiants ; i++ )
    {
        afficher_1_etudiant(*(e+i), i);
    }
}
//------------------------------------
/**
 * @brief Affiche les informations de tous les etudiants sous forme de liste.
 *
 * @param e Tableau d'etudiants contenant les informations a rechercher.
 * @param nb_etudiants Le nombre d'etudiants a afficher.
 */
void rechercher_etudiants(Etudiant *e, int nb_etudiants)
{
    printf("Entrez le nom, prenom ou annee de naissance : ");
    char recherche[20];
    scanf("%s", recherche);
    int nb_trouves = 0;
    for (int i = 0; i < nb_etudiants; i++)
    {
        if (strcmp(recherche, e[i].nom) == 0 || strcmp(recherche, e[i].prenom) == 0 || atoi(recherche) == e[i].ddn.annee)
        {
            afficher_1_etudiant(e[i], i);
            nb_trouves++;
        }
    }
    if (nb_trouves == 0)
    {
        printf("Aucun etudiant trouve.\n");
    }
}
//------------------------------------
/**
 * @brief Supprimer la fiche d'un etudiant specifique.
 *
 * @param e Tableau d'etudiants contenant les informations a rechercher.
 * @param nb_etudiants Le nombre d'etudiants.
 */
void supprimer_etudiant(Etudiant *e, int *nb_etudiant)
{
    int i, id, j = nb_etudiant;
    printf("\n------------ /!\ IMPORTANT /!\ -------------");
    printf("\n- Saisissez l'id de l'etudiant a supprimer -");
    printf("\n--------------------------------------------");
    afficher_n_etudiant(e, nb_etudiant);
    printf("\n--------------------------------------------");
    id = saisir_int(IDTEXT1, IDTEXT2, IDTEXT3, 1, nb_etudiant);

    for(i = id -1; i < j - 1; i++)
    {
        if(i == 0 || i < j - 1 )
        {
            *(e+i) = *(e+i+1);
        }
        else
            break;
    }
    nb_etudiant--;
}
//------------------------------------
/**
 * @brief Supprimer la fiche d'un etudiant specifique.
 *
 * @param e Tableau d'etudiants contenant les informations a rechercher.
 * @param nb_etudiants Le nombre d'etudiants.
 */
void modifier_etudiant(Etudiant *e, int *nb_etudiant)
{
    int i, id, j = nb_etudiant;
    printf("\n------------ /!\ IMPORTANT /!\ -------------");
    printf("\n- Saisissez l'id de l'etudiant a modifier  -");
    printf("\n--------------------------------------------");
    afficher_n_etudiant(e, nb_etudiant);
    printf("\n--------------------------------------------");
    id = saisir_int(IDTEXT1, IDTEXT2, IDTEXT3, 1, nb_etudiant);

    for(i = id -1; i < j - 1; i++)
    {
        if(i == 0 || i < j - 1 )
        {
            *(e+i) = saisir_1_etudiant(i);
        }
        else
            break;
    }
    nb_etudiant--;
}
//------------------------------------
/**
 * @brief Sauvegarder les informations de tous les etudiants dans un fichier json.
 *
 * @param e Tableau d'etudiants contenant les informations a sauvegarder.
 * @param n Le nombre d'etudiants actuellement dans le programme.
 */
int sauvegarder_etudiants(Etudiant* e, int n)
{
    // D�finissez une cha�ne de caract�res qui contiendra les donn�es JSON
    char jsonString[1000] = "";

    // Ajoutez la cha�ne d'ouverture d'objet JSON "{"
    strcat(jsonString, "{\n");

    // Ajoutez le champ "personnes" avec sa valeur, qui sera un tableau d'objets JSON
    strcat(jsonString, "  \"etudiant_\": [\n");
    for (int i = 0; i < n; i++)
    {
        // Ajoutez l'indentation pour le nouvel objet JSON
        strcat(jsonString, "    ");

        // Ajoutez la cha�ne d'ouverture d'objet JSON "{"
        strcat(jsonString, "{");

        // Ajoutez le champ "nom" avec sa valeur en utilisant la fonction sprintf
        char nomField[100];
        sprintf(nomField, "\"#nom\": \"%s\"", (e+i)->nom);
        strcat(jsonString, nomField);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "prenom" avec sa valeur en utilisant la fonction sprintf
        char prenomField[100];
        sprintf(prenomField, "\"prenom\": \"%s\"", (e+i)->prenom);
        strcat(jsonString, prenomField);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "ddn" avec sa valeur en utilisant la fonction sprintf
        char ddnField[100];
        sprintf(ddnField, "\"ddn\": \"%02d/%02d/%d\"", (e+i)->ddn.jour, (e+i)->ddn.mois, (e+i)->ddn.annee);
        strcat(jsonString, ddnField);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note1" avec sa valeur en utilisant la fonction sprintf
        char note1Field[100];
        sprintf(note1Field, "\"note1\": %f", (e+i)->note1);
        strcat(jsonString, note1Field);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note2" avec sa valeur en utilisant la fonction sprintf
        char note2Field[100];
        sprintf(note2Field, "\"note2\": %f", (e+i)->note2);
        strcat(jsonString, note2Field);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note3" avec sa valeur en utilisant la fonction sprintf
        char note3Field[100];
        sprintf(note3Field, "\"note3\": %f", (e+i)->note3);
        strcat(jsonString, note3Field);

        // Ajoutez une virgule pour s�parer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "moyenne" avec sa valeur en utilisant la fonction sprintf
        char moyenneField[100];
        sprintf(moyenneField, "\"moyenne\": %f", (e+i)->moyenne);
        strcat(jsonString, moyenneField);

        // Ajoutez la cha�ne de fermeture d'objet JSON "}"
        strcat(jsonString, "}");

        // Ajoutez une virgule pour s�parer les objets dans le tableau JSON
        if (i < n - 1)
        {
            strcat(jsonString, ",\n");
        }
    }
    strcat(jsonString, "\n  ]\n");

    // Ajoutez la cha�ne de fermeture d'objet JSON "}"
    strcat(jsonString, "}\n");

    // Ouvrez un fichier en �criture
    FILE *fichier = fopen(JSONDATA, "w");

    // �crivez les donn�es JSON dans le fichier en utilisant la fonction fprintf
    fprintf(fichier, "%s", jsonString);

    // Fermez le fichier
    fclose(fichier);
    return 0;
}
//------------------------------------
/**
 * @brief Charge les informations de tous les �tudiants � partir d'un fichier JSON.
 *
 * @param filename Le nom du fichier JSON.
 * @param nbEtudiants Le nombre d'�tudiants � charger (r�cup�r� depuis le fichier JSON).
 * @return Un tableau d'�tudiants contenant les informations charg�es depuis le fichier JSON.
 */
Etudiant* charger_etudiants(char* filename, int* nbEtudiants)
{
    // Ouvrir le fichier en lecture
    FILE* fichier = fopen(filename, "r");
    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Compter le nombre d'�tudiants dans le fichier
    int n = 0;
    char c;
    while ((c = fgetc(fichier)) != EOF)
    {
        if (c == '#')
        {
            (n)++;
        }
    }
    *nbEtudiants = n;

    // Allouer de la m�moire pour le tableau d'�tudiants
    Etudiant* etudArray = (Etudiant*)malloc(sizeof(Etudiant)*(n));

    // Revenir au d�but du fichier
    fseek(fichier, 0, SEEK_SET);

    // Lire les donn�es et remplir le tableau d'�tudiants
    int i = 0;
    while ((c = fgetc(fichier)) != '{' && c != EOF) {}
    while (i < n)
    {
        // Ignorer les caract�res de ponctuation
        char c;
        while ((c = fgetc(fichier)) != '{' && c != EOF) {}

        // Lire les champs de l'�tudiant
        char nom[20], prenom[20], ddn[11];
        float note1, note2, note3, moyenne;

        fscanf(fichier, "\"#nom\": \"%[^\"]\", ", nom);
        fscanf(fichier, "\"prenom\": \"%[^\"]\", ", prenom);
        fscanf(fichier, "\"ddn\": \"%[^\"]\", ", ddn);
        fscanf(fichier, "\"note1\": %f, ", &note1);
        fscanf(fichier, "\"note2\": %f, ", &note2);
        fscanf(fichier, "\"note3\": %f, ", &note3);
        fscanf(fichier, "\"moyenne\": %f", &moyenne);

        // Stocker les champs dans le tableau d'�tudiants
        Etudiant e;
        e.ddn = extraire_date(ddn);
        strcpy(e.nom, nom);
        strcpy(e.prenom, prenom);
        e.note1 = note1;
        e.note2 = note2;
        e.note3 = note3;
        e.moyenne = moyenne;
        etudArray[i] = e;
        i++;
    }

    // Fermer le fichier et renvoyer le tableau d'�tudiants
    fclose(fichier);
    return etudArray;
}
//------------------------------------
/**
 * @brief Affichage du titre du programme.
 */
void afficher_titre()
{
    printf("\t----------------------------------------------------------------------------------------------\n");
    printf("\t-\t#######                                  #                      #####  #######\t     -\n");
    printf("\t-\t#       ##### #    # #####  ######      # #   #    # #####     #     # #     #\t     -\n");
    printf("\t-\t#         #   #    # #    # #          #   #  ##   # #    #    #       #     #\t     -\n");
    printf("\t-\t#####     #   #    # #    # #####     #     # # #  # #    #    #       #     #\t     -\n");
    printf("\t-\t#         #   #    # #    # #         ####### #  # # #    #    #       #     #\t     -\n");
    printf("\t-\t#         #   #    # #    # #         #     # #   ## #    #    #     # #     #\t     -\n");
    printf("\t-\t#######   #    ####  #####  ######    #     # #    # #####      #####  #######\t     -\n");
    printf("\t----------------------------------------------------------------------------------------------");
}
//------------------------------------
/**
 * @brief Affichage du menu du programme.
 */
void affiche_menu()
{
    printf("\n*#################################################*\n");
    printf("#                                                 #\n");
    printf("#   M       M    E E E    N       N    U     U    #\n");
    printf("#   M M   M M    E        N N     N    U     U    #\n");
    printf("#   M   M   M    E E E    N   N   N    U     U    #\n");
    printf("#   M       M    E        N     N N    U     U    #\n");
    printf("#   M       M    E E E    N       N     U U U     #\n");
    printf("#                                                 #\n");
    printf("*#################################################*\n");
    printf("*                                                 *\n");
    printf("* > Ajouter une fiche etudiant | cmd : 1          *\n");
    printf("* > Afficher Liste Etudiants   | cmd : 2          *\n");
    printf("* > Rechercher Etudiant        | cmd : 3          *\n");
    printf("* > Supprimer la fiche etudiant| cmd : 4          *\n");
    printf("* > Modifier la fiche etudiant | cmd : 5          *\n");
    printf("* > Sauvegarder la liste       | cmd : 6          *\n");
    printf("* > Charger sur le programme   | cmd : 7          *\n");
    printf("* > Aide sur le programme      | cmd : 8          *\n");
    printf("* > Quiter le programme        | cmd : 0          *\n");
    printf("*                                                 *\n");
    printf("*#################################################*\n");
}
//------------------------------------
/**
 * @brief Affichage de la description du programme.
 */
void description()
{
    printf("\n[Information generale] : ");
    printf("\n\tNom : VAUDRY\n\tPrenom : Pierre\n\tClassse : AERO 3PSA-1\n\tGroupe : A1\n\tExercice :EXERXICE 4\n\tVersion : v1\n\tDate : 25/01/2023 | seance 3 (cours-TP)");
    printf("\n");
    printf("\n[DESCRIPTION] :\tBienvenu dans le programme de gestion d'etudiant.");
    printf("\nCe programme permet de gerer une liste d'etudiant.");
    printf("\nOn peut :\n\t- ajouter un(e) etudiant(e)s dans la liste | nom, prenom, date de naissance, 3 note, moyenne.\n\t- afficher la liste des etudiant(e)s\n\t- afficher une fiche etudiant(e)s\n\t- supprimer/modifier une fiche etudiant(e)s\n\t- sauvegarder/charger la liste d'etudiant a partir d'un fichier JSON\n\t- une aide pour l'utilisation de ce programme\n\t- quitter le programme");
    printf("\nLe langage de ce programme est le C ! Un langage puissant et tres utilise.\n");
}
//------------------------------------
/**
 * @brief Affichage d'un separateur customisable.
 *
 * @param sep Le caractere separateur.
 * @param nb Le nombre de caractere pour la separation.
 */


void affichage_fichier(char filename[20])
{
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";

    fichier = fopen(filename, "r");

    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne re�oit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la cha�ne qu'on vient de lire
        }
        fclose(fichier);
    }
}
//------------------------------------
/**
 * @brief Affichage de l'aide pour les fonctionnalites du programme.
 */
void aide()
{

    int user_cmd;


    do{
        system("cls");
        printf("\n*#################################################*\n");
        printf("#                                                 #\n");
        printf("#           ####    #   ####    #####   #         #\n");
        printf("#          #    #   #   #   #   #       #         #\n");
        printf("#          ######   #   #   #   #####   #         #\n");
        printf("#          #    #   #   #   #   #                 #\n");
        printf("#          #    #   #   ####    #####   #         #\n");
        printf("#                                                 #\n");
        printf("*#################################################*\n");
        printf("\n\t~ Comment fonctionne le programme ?");
        printf("\n\tLe programme est compose de sous ensemble disponible dans le menu. ");
        printf("\nLe menu permet de naviguer a travers les differentes fonctionnalite. \n");
        printf("\nA chaque etape, on s'assure que la saisie de l'utilisateur est valide (notament");
        printf("\npour les entiers ou les flottants). Le temps que la saisie n'est pas conforme");
        printf("\n(exemple : si le mois n'est pas compris entre 1 et 12), les informations seront");
        printf("\ndemandees avec un message indiquand l'erreur possible.");
        printf("\nCette verification permet d'eviter les boucle infini lors de la saisie d'une");
        printf("\nchaine de caractere dans un emplacement reserve a un entier ou un flottant.\n");
        affiche_menu();
        user_cmd = saisir_int(CMDTEXT1, CMDTEXT2, CMDTEXT3, 0, 8);

        switch (user_cmd)
        {
            case 0:
                printf("\n######## Aide Quitter le programme ########\n");
                printf("\nPermet de quitter le programme. Ainsi que l'aide au programme.\n");
                return 0;
            case 1:
                system("cls");
                printf("\n######## Aide Ajout Etudiant ########\n\n");
                affichage_fichier("txt/ajouter.txt");
                printf("\n");
                system("pause");
                break;
            case 2:
                system("cls");
                printf("\n######## Aide Afficher Liste Etudiant ########\n\n");
                affichage_fichier("txt/afficher_liste.txt");
                printf("\n");
                system("pause");
                break;
            case 3:
                system("cls");
                printf("\n######## Aide Recherche Etudiant ########\n\n");
                affichage_fichier("txt/rechercher.txt");
                printf("\n");
                system("pause");
                break;
            case 4:
                system("cls");
                printf("\n######## Aide Suppression Etudiant ########\n\n");
                affichage_fichier("txt/supprimer.txt");
                printf("\n");
                system("pause");
                break;
            case 5:
                system("cls");
                printf("\n######## Aide Modification Etudiant ########\n\n");
                affichage_fichier("txt/modifier.txt");
                printf("\n");
                system("pause");
                break;
            case 6:
                system("cls");
                printf("\n######## Aide Sauvegarder Etudiants ########\n\n");
                affichage_fichier("txt/sauvegarder.txt");
                printf("\n");
                system("pause");
                break;
            case 7:
                system("cls");
                printf("\n######## Aide Charger Etudiants ########\n");
                affichage_fichier("txt/charger.txt");
                printf("\n");
                system("pause");
                break;
            case 8:
                system("cls");
                printf("\n######## AIDE | Help ########\n");
                printf("\nLa fonctionnalite ou vous vous trouver pour savoir comment utiliser le programme.\n");
                system("pause");
                break;
            default:
                printf("\nERREUR !!! Choix invalide.\n");
                break;
        }
    }while(user_cmd != 0);
}
