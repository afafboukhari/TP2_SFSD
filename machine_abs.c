#include <stdio.h>
#include <stdlib.h>
#include "machine_abs.h"


int entete(FILE* F, int i) {
    /*if (F == NULL || i != 1 || i != 2) {
        perror("error in entete");
        return -1;  // si y a une erreur
    }else{*/
        type_entete header;
        fseek(F, 0, SEEK_SET);
        fread(&header, sizeof(type_entete), 1, F);
        if (i == 1) return header.nmbr_bloc ;
        if (i == 2) return header.pos_dernier ;
   // }
     return 0;
}
//---------------------------------------------------------
void Aff_entete(FILE *f, int i, int val)
{
if (f == NULL ||( i != 1 && i != 2))
{       perror("error in aff_entete");
        return ;  // si y a une erreur
    }else{
        type_entete header;
        fseek(f, 0, SEEK_SET);
        fread(&header, sizeof(type_entete), 1, f);
        if (i == 1) { header.nmbr_bloc = val; } ;
        if (i == 2) { header.pos_dernier = val; } ;
        fseek(f,0, SEEK_SET);
        fwrite(&header,sizeof(type_entete),1,f);
    }
}
//---------------------------------------------------------
bool LireDir(FILE *f, int i,buffer *BUFFER)
{
    if (f == NULL || i <= 0 || fseek(f, ((i-1) * sizeof(buffer) + 8 ), SEEK_SET) != 0) { //8 est la taille de l'entete
        return false;
    }else{
     if (fread(BUFFER, sizeof(buffer), 1, f) != 1) {
        return false;  // Check if the read was successful
    }
     return true;
    }
}
//---------------------------------------------------------
bool EcrireDir(FILE *f, int i, buffer *BUFFER)
{
    if (f == NULL || i <= 0 || fseek(f, ((i-1) * sizeof(buffer) + 8 ), SEEK_SET) != 0) { //8 est la taille de l'entete
        return false;
    }else{
     if (fwrite(BUFFER, sizeof(buffer), 1, f) != 1) {
        return false;  // Check if the read was successful
    }
     return true;
    }
}
//---------------------------------------------------------
void ouvrire(FILE **f,char *nomfich, char mode)
{
 if ( f == NULL)
 {
    perror("file not found");
    return; }
 else{
    switch (mode)
    {
    case 'A':
        *f = fopen(nomfich, "rb+");
        break;
    case 'N':
        *f = fopen(nomfich, "wb+");
        Aff_entete(*f,1,0);
        Aff_entete(*f,2,0);
        break;
    default :
    perror("mode not detected");
    break;
    }
 }
}
//---------------------------------------------------------
void fermer(FILE *f)
{
    fclose(f);
}
//---------------------------------------------------------
int alloc_bloc(FILE *f)
{
 return 0;
}
//---------------------------------------------------------
void display(char* nomfich)
{
    FILE *f;
    ouvrire(&f,nomfich,'A');
    buffer buf;
    for(int i=1; i<=entete(f,1) ; i++ )
    {
        LireDir(f,i,&buf);
        int j=0;
        for(j ; j< buf.NB ;j++)
    {   printf("\033[1;33m  la matricule est \033[1;34m %d\n",buf.tab[j].matricule);
        printf("\033[1;33m  le nom :\033[1;34m '%s' \n\033[1;33m  le prenom :\033[1;34m '%s' \n",buf.tab[j].nom,buf.tab[j].prenom);
        printf("\033[1;33m  date de naissance :\033[1;34m %d-%d-%d \n",buf.tab[j].date_naissance.day,buf.tab[j].date_naissance.month,buf.tab[j].date_naissance.year);
        printf("\033[1;33m  Du wilaya :\033[1;34m %s",buf.tab[j].wilaya);
        printf("\033[1;33m  le groupe sanguin :\033[1;34m %s ",buf.tab[j].Groupe_sanguin);
        printf("\033[1;33m le grade :\033[1;34m %s ",buf.tab[j].Grade);
        printf("\033[1;33m la force armee :\033[1;34m  %s ",buf.tab[j].Force_Armee);
        printf("\033[1;33m la region militaire :\033[1;34m %s ",buf.tab[j].Region_militaire);
        printf("\033[1;0m------------------------------------------------------------------------\n ------------------------------------------------------------------------\n");
    }
    }
    fermer(f);
}
