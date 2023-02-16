/*
Nom : VAUDRY
Prenom : Pierre
Classse : AERO 3PSA-1
Groupe : A1
Exercice :EXERXICE 4
Version : v3_max
Date : 25/01/2023 | seance 3 (cours-TP)
Description :
	Biblio pour le programme de saisie des notes d'un etudiant et affichage de cet etudiant
*/

//------------------------------------
//           Define
//------------------------------------
#define CMDTEXT1 "\nCommand /> "
#define CMDTEXT2 "\nLa saisie de la commande comporte une erreur..."
#define CMDTEXT3 "\nUn entier entre 0 et 6 est demande."

#define IDTEXT1 "\nDonner l'id de l'etudiants : "
#define IDTEXT2 "\nLa saisie de l'id etudiants comporte une erreur..."
#define IDTEXT3 "\nUn entier entre 0 et X est demande."

#define NBTEXT1 "\nDonner le nombre d'etudiants : "
#define NBTEXT2 "\nLa saisie du nombre d'etudiants comporte une erreur..."
#define NBTEXT3 "\nUn entier entre 0 et 100 est demande."

#define ANNEETEXT1 "\nAnnee : "
#define ANNEETEXT2 "\nLa saisie de l'annee comporte une erreur..."
#define ANNEETEXT3 "\nUne annee est entre 1950 et 2000."

#define MOISTEXT1 "\nMois : "
#define MOISTEXT2 "\nLa saisie du mois comporte une erreur..."
#define MOISTEXT3 "\nUn mois est entre 1 et 12."

#define JOURTEXT1 "\nJour : "
#define JOURTEXT2 "\nLa saisie du jour comporte une erreur..."
#define JOURTEXT3 "\nUn mois est entre 1 et 30."

#define JSONDATA "etudiants.json"

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
    //struct Etudiant* suivant;
}Etudiant;

//------------------------------------
//            Fonction
//------------------------------------
int saisir_int(char text1[100], char text2[100], char text3[100],int min_nb, int max_nb)
{
    int n = 0;
    do {
        printf("%s", text1);
        if ((scanf("%d", &n)) != 1) // vérifie si la saisie est invalide
        {
            printf(text2);
            printf(text3);
            fflush(stdin); // vide le tampon d'entrée
            n = -1; // affecte -1 pour que la boucle continue
        }
        else if (n < min_nb || n > max_nb) // vérifie si le nombre est hors limites
        {
            printf(text2);
            printf(text3);
            n = -1; // affecte -1 pour que la boucle continue
        }
    }while (n < min_nb);
}
//------------------------------------
void saisir_date(date *d)
{
    printf("Entrez le jour de naissance : ");
    scanf("%d", d->jour);
    printf("Entrez le mois de naissance : ");
    scanf("%d", d->mois);
    printf("Entrez l'annee de naissance : ");
    scanf("%d", d->annee);
}
//------------------------------------
void afficher_date(date d)
{
    printf("\n     DDN : %02d/%02d/%d", d.jour, d.mois, d.annee);
}
//------------------------------------
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
    printf("\nSaisir la date de naissance au format : jour/mois/annee");
    DateDeNaissance.jour = saisir_int(JOURTEXT1,JOURTEXT2,JOURTEXT3,1, 30);
    DateDeNaissance.mois = saisir_int(MOISTEXT1,MOISTEXT2,MOISTEXT3,1, 12);
    DateDeNaissance.annee = saisir_int(ANNEETEXT1,ANNEETEXT2,ANNEETEXT3,1950, 2024);
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

//------------------------------------
void afficher_1_etudiant(Etudiant e, int i )
{
    /*
    Fonction qui permet d'afficher les informations d'1 etudiant(e)
    */
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
void  afficher_n_etudiant(Etudiant *e, int nb_etudiants)
{
    for (int i = 0 ; i < nb_etudiants ; i++ )
    {
        afficher_1_etudiant(*(e+i), i);
    }
}
//------------------------------------
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
void supprimer_etudiant(int etudiantASupprimer, Etudiant *e, int *nb_etudiant)
{
    int i, j = nb_etudiant;

    for(i = etudiantASupprimer -1; i < j - 1; i++)
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
int sauvegarder_etudiants(Etudiant* e, int n) {
    // Définissez une chaîne de caractères qui contiendra les données JSON
    char jsonString[1000] = "";

    // Ajoutez la chaîne d'ouverture d'objet JSON "{"
    strcat(jsonString, "{\n");

    // Ajoutez le champ "personnes" avec sa valeur, qui sera un tableau d'objets JSON
    strcat(jsonString, "  \"etudiant_\": [\n");
    for (int i = 0; i < n; i++) {
        // Ajoutez l'indentation pour le nouvel objet JSON
        strcat(jsonString, "    ");

        // Ajoutez la chaîne d'ouverture d'objet JSON "{"
        strcat(jsonString, "{");

        // Ajoutez le champ "nom" avec sa valeur en utilisant la fonction sprintf
        char nomField[100];
        sprintf(nomField, "\"nom\": \"%s\"", (e+i)->nom);
        strcat(jsonString, nomField);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "prenom" avec sa valeur en utilisant la fonction sprintf
        char prenomField[100];
        sprintf(prenomField, "\"prenom\": \"%s\"", (e+i)->prenom);
        strcat(jsonString, prenomField);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "ddn" avec sa valeur en utilisant la fonction sprintf
        char ddnField[100];
        sprintf(ddnField, "\"ddn\": \"%02d/%02d/%d\"", (e+i)->ddn.jour, (e+i)->ddn.mois, (e+i)->ddn.annee);
        strcat(jsonString, ddnField);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note1" avec sa valeur en utilisant la fonction sprintf
        char note1Field[100];
        sprintf(note1Field, "\"Note1\": %f", (e+i)->note1);
        strcat(jsonString, note1Field);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note2" avec sa valeur en utilisant la fonction sprintf
        char note2Field[100];
        sprintf(note2Field, "\"Note2\": %f", (e+i)->note2);
        strcat(jsonString, note2Field);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "note3" avec sa valeur en utilisant la fonction sprintf
        char note3Field[100];
        sprintf(note3Field, "\"Note3\": %f", (e+i)->note3);
        strcat(jsonString, note3Field);

        // Ajoutez une virgule pour séparer les champs dans l'objet JSON
        strcat(jsonString, ", ");

        // Ajoutez le champ "moyenne" avec sa valeur en utilisant la fonction sprintf
        char moyenneField[100];
        sprintf(moyenneField, "\"moyenne\": %f", (e+i)->moyenne);
        strcat(jsonString, moyenneField);

        // Ajoutez la chaîne de fermeture d'objet JSON "}"
        strcat(jsonString, "}");

        // Ajoutez une virgule pour séparer les objets dans le tableau JSON
        if (i < n - 1) {
            strcat(jsonString, ",\n");
        }
    }
    strcat(jsonString, "\n  ]\n");

    // Ajoutez la chaîne de fermeture d'objet JSON "}"
    strcat(jsonString, "}\n");

    // Ouvrez un fichier en écriture
    FILE *fichier = fopen("etudiants.json", "w");

    // Écrivez les données JSON dans le fichier en utilisant la fonction fprintf
    fprintf(fichier, "%s", jsonString);

    // Fermez le fichier
    fclose(fichier);
    return 0;
}
//------------------------------------
Etudiant* charger_etudiants(char* filename, int* n) {
    // Ouvrir le fichier en lecture
    FILE* fichier = fopen(filename, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Compter le nombre d'étudiants dans le fichier
    *n = 0;
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '{') {
            (*n)++;
        }
    }

    // Allouer de la mémoire pour le tableau d'étudiants
    Etudiant* etudArray = (Etudiant*)malloc(sizeof(Etudiant) * (*n));

    // Revenir au début du fichier
    fseek(fichier, 0, SEEK_SET);

    // Lire les données et remplir le tableau d'étudiants
    int i = 0;
    while (i < (*n)) {
        // Ignorer les caractères de ponctuation
        char c;
        while ((c = fgetc(fichier)) != '{' && c != EOF) {}

        // Lire les champs de l'étudiant
        char nom[20], prenom[20];
        int jour, mois, annee;
        float note1, note2, note3;
        fscanf(fichier, "\"prenom\": \"%[^\"]\",", prenom);
        fscanf(fichier, "\"nom\": \"%[^\"]\",", nom);
        fscanf(fichier, "\"ddn\": { \"jour\": %d, \"mois\": %d, \"annee\": %d },", &jour, &mois, &annee);
        fscanf(fichier, "\"note1\": %f,", &note1);
        fscanf(fichier, "\"note2\": %f,", &note2);
        fscanf(fichier, "\"note3\": %f", &note3);

        // Stocker les champs dans le tableau d'étudiants
        strncpy(etudArray[i].nom, nom, 20);
        strncpy(etudArray[i].prenom, prenom, 20);
        etudArray[i].ddn.jour = jour;
        etudArray[i].ddn.mois = mois;
        etudArray[i].ddn.annee = annee;
        etudArray[i].note1 = note1;
        etudArray[i].note2 = note2;
        etudArray[i].note3 = note3;
        etudArray[i].moyenne = (note1 + note2 + note3) / 3.0;
        i++;
    }

    // Fermer le fichier et renvoyer le tableau d'étudiants
    fclose(fichier);
    return etudArray;
}

//------------------------------------
//Printf du titre du programme, du menu, de la description du programme
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
    printf("* > Afficher la fiche etudiant | cmd : 3          *\n");
    printf("* > Supprimer la fiche etudiant| cmd : 4          *\n");
    printf("* > Sauvegarder la liste       | cmd : 5          *\n");
    printf("* > Charger sur le programme   | cmd : 6          *\n");
    printf("* > Aide sur le programme      | cmd : 7          *\n");
    printf("* > Quiter le programme        | cmd : 0          *\n");
    printf("*                                                 *\n");
    printf("*#################################################*\n");
}
//------------------------------------
void description()
{
    printf("\n[Information generale] : ");
    printf("\n\tNom : VAUDRY\n\tPrenom : Pierre\n\tClassse : AERO 3PSA-1\n\tGroupe : A1\n\tExercice :EXERXICE 4\n\tVersion : v1\n\tDate : 25/01/2023 | seance 3 (cours-TP)");
    printf("\n");
    printf("\n[DESCRIPTION] :\tBienvenu dans le programme de gestion d'etudiant.");
    printf("\nCe programme permet de gerer une liste d'etudiant.");
    printf("\nOn peut :\n\t- ajouter un(e) etudiant(e)s dans la liste | nom, prenom, date de naissance, 3 note, moyenne.\n\t- afficher la liste des etudiant(e)s\n\t- afficher une fiche etudiant(e)s\n\t- supprimer une fiche etudiant(e)s\n\t- sauvegarder la liste au format json\n\t- une aide pour l'utilisation de ce programme\n\t- quitter le programme");
    printf("\nLe langage de ce programme est le C ! Un langage puissant et tres utilise.\n");
}
//------------------------------------
void screen_separator(char sep, int nb)
{
    for (int i = 0; i < nb; i++) {
            printf("%s", sep);
    }
}
