# OUTIL GESTION ETUDIANT

## __Introduction__
Ce programme a pour but de comprendre et d'apprendre le langage C.
Le but principale du programme est de permettre un administratif (utilisateur) de gérer une liste d'etudiant.

### __Cahier des charges__

    Menu 
    ---------------------------

    1- Saisir étudiants 

    2- Afficher étudiants

    3- Rechercher étudiants 

    4- Supprimer étudiant

    5- Fin

    ---------------------------

* En tapant : 1 l'utilisateur peux rentrer des étudiants en utilisant malloc une première fois et peux resaisir des étudiants par realloc les fois d'après et reviens au menu.

* En tapant 2 : La machine affiche à l'utilisateur l'ensemble des coordonnées de tous les étudiants dans la base et reviens au menu.



* En tapant 3 : La machine recherche le ou les étudiants selon :

     - leur nom 

     - leur prénom 

     - leur année de naissance. 

    les affiches et reviens au menu.

* En tapant 4 : Le programme demande à l'utilisateur le nom de l'étudiant à supprimer puis le supprime de la liste des étudiants ainsi le nombre d'étudiant diminue de 1 et reviens au menu. 

* En tapant 5 : Le programme s'arrête et ne revient pas au menu et affiche Merci et à bientôt. 

### __Information sur le programme__

Nom : VAUDRY

Prenom : Pierre

Classse : AERO Groupe : A1

Exercice :EXERXICE 4

Version : Date : 25/01/2023 | seance 3 (cours-TP)

### __[DESCRIPTION] : Bienvenu dans le programme de gestion d'etudiant.__


    Ce programme permet de gerer une liste d'etudiant.
    On peut :
        - ajouter un(e) etudiant(e)s dans la liste | nom, prenom, date de naissance, 3 note, moyenne.
        - afficher la liste des etudiant(e)s
        - afficher une fiche etudiant(e)s
        - supprimer/modifier une fiche etudiant(e)s
        - sauvegarder/charger la liste d'etudiant a partir d'un fichier JSON
        - une aide pour l'utilisation de ce programme
        - quitter le programme");

    Le langage de ce programme est le C ! Un langage puissant et tres utilise.

------------------------------------------------------------------

## __Fonctionnalités & menu__

---
### __1. Ajouter un etudiant__

Cette fonctionnalite permet a l'utilisateur d'ajouter un 
etudiant dans la liste du programme.
Dans un premier temps, on demande la saisie du nombre d'etudiant qu'on souhaite inscrire dans le programme. 
Si on tape 0, on ressort de la fonctionnalité sans rajouter d'etudiant. Sinon, X etudiant seront a saisir.
		
L'id de l'etudiant s'affiche et le programme demande les
informations de l'etudiant : 
- nom
- prenom
- la date de naissance dans le format jj/mm/aaaa. 
    Il faut d'abord rentrer l'annee, le mois puis
    le jour pour verifier si le mois de fevrier 
    prend 28 ou 29 jours au maximum
- la note 1 a 3

---
### __2. Afficher etudiants__

Cette fonctionnalite permet a l'utilisateur d'afficher la liste des etudiants disponible dans le programme.
Aucune action de l'utilisateur n'est attendue pour cette fonctionnalite. 
Lors de l'affichage des fiches etudiants, toutes les informations sont presentees. 
Chaque etudiant a un id correspondant a sont emplacement relative dans la liste du programme.

---
### __3. Rechercher un etudiant__

Cette fonctionnalite permet a l'utilisateur de rechercher un etudiant dans la liste du programme.
Afin de rechercer l'etudiant, il faut saisir au choix : 
    - l'annee de naissance
    - le nom
    - le prenom


__/!\ A savoir /!\\__

Si plusieurs etudiant ont : 
- la meme annee de naissance
- le meme nom
- le meme prenom

Ils seront afficher les un apres les autres. 

La recherche necessite de connaitre au moins l'une des informations demandees. Sans quoi il n'est pas possible de rechercher un etudiant.

Une fonctionnalite interressante serait de rechercher des etudiants  selon la moyenne. Cependant, elle n'est pas disponible a ce jours.
~~Dans une autre version du programme (v3_max), on peut rechercher l'étudiant via son identifiant simplifié (correspondant à l'INE).~~

---
### __4. Supprimer un etudiant__

Ce programme permet également la suppréssion de la fiche d'un étudiant.
Pour cela il faut renseigner :
- le nom
- le prénom
Ces deux informations sont éssentielles. 
Car deux étudiants peuvent avoir le même nom ou le même prénom mais pas les deux simultannément (sauf cas rare).

---
### __5. Quitter le programme__

Une fois l'utilisation terminée, l'utilisateur a le choix de quitter le programme avec un message de fin.

Le programme sauvegarde la liste d'étudiant dans un fichier JSON.


## Evolution et code source

Ce programme sera ammené à évoluer. 

__[EVOLUTION & AJOUT] :__
- Système de trie des élèves en fonction de leurs moyennes (classement).
- Ajout d'un gestionnaire des notes/matières/code matières/professeurs.
- Portage du programme sur les listes chainées.
- Portage du programme en anglais (nom variable / documentation).
- Interface graphique ?

Vous trouverez différentes version de ce code : 

    - version 3 min (sans documentation et sans les fonctionnalités de modification / sauvegarde manuelle / chargement manuel)
    - version 3 max (avec documentation et avec les fonctionnalités de modification / choix sauvegarde / choix chargement)

Les différents codes sources sont disponibles sur [Github](https://github.com/Rsky-20/advanced_student_management_programm)