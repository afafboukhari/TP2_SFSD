#ifndef MACHINE_ABS_H_INCLUDED
#define MACHINE_ABS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#define b 1024



//declaration de l'enregistrement :
struct date
{
    int day;
    int month;
    int year;
};


struct Soldat
{   int matricule;
    char nom[29];
    char prenom[30];
    struct date date_naissance;
    char wilaya[20];
    char Groupe_sanguin[5];
    char Grade[30];
    char Force_Armee[50];
    char Region_militaire[20];
};


typedef struct Soldat elem;


//declaration des bloc du fichier et buffer
typedef struct BLOC_fichier
{
    elem tab[b];
    int NB; //nombre d'enreg dans le bloc
} bloc, buffer ;


//L'entete :
struct Entete
{
    int nmbr_bloc;
    int pos_dernier; //nombre d'enreg dans le dernier bloc
};

typedef struct Entete type_entete ;



// LES MODULES :

int entete(FILE* F, int i);
void Aff_entete(FILE *f, int i, int val);
bool LireDir(FILE *f, int i,buffer *BUFFER);
bool EcrireDir(FILE *f, int i, buffer *BUFFER);
void ouvrire(FILE **f,char *nomfich, char mode);
void fermer(FILE *f);
int alloc_bloc(FILE *f);
void display(char *nomfich);




#endif // MACHINE_ABS_H_INCLUDED
