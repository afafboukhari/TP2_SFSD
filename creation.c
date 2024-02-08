#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "machine_abs.h"
#include "creation.h"


int randomnumb(int min,int max) {
    /* lors de l'appel de cette procedure il est important de varier le min et le max
    dans un intervalle pour ne pas avoir des plusieurs valeurs qui repetent souvent
    Aussi, avant la boucle il faut appeler   srand(time(NULL));    */
    long long r;
    r = rand() ;
    r = abs(r);
    if (r==0)
    {
        r=1;
    }

    r=(r*min)%max;
    r = abs(r);

        while (r<min)
        {
            r = r+max-min;
        }

    return r;

}

bool unique(node *tete,int val)
{   bool boo = true;
    if (tete == NULL) { return boo;}
    while (tete->suivant != NULL && boo == true )
    {
        if(tete->val == val)
        {boo = false;
         }else{
            tete = tete->suivant;
         }
    }
    return boo;
}

node* allouer()
{
    node* pointer = (node*)malloc(sizeof(node));
    pointer->suivant = NULL;
    return pointer;
}


void matricule(elem *enrg,node **tete,node **queue, int *min,int *oldmin,int *j,int *oldj)
{
    int randomval;
    /* ce traitement f prgrm principal
    int j=1;
    int oldj=1;
    int *min = 111111;
    int oldmin = 111111;
    */
    node *q;
    srand(time(NULL));
    randomval = randomnumb(*min,999999);
        q = allouer();
        q->val = randomval;
        if (*tete == NULL)
        {
        *tete = q;
        }else{
        (*queue)->suivant = q;
        }
        *queue = q;
        *min = *min + *j ;
        *j++;
        // tester si la matricule is toujour unique
        if (unique(*tete,randomval))
        {
            enrg->matricule = randomval;
         }
         //mise a jour du min pour avoir des valeurs aleatoires a chaque iteration(Methode bizzare)
        if (*min >= 999999)
        {
           *min = *oldmin + *oldj +1;
           *oldj = *oldj +1;
           *j = *oldj;
           *oldmin=*min;
        }
        /* ce traitement f prgrm principal
        p = *tete;
        while (p != NULL)
       {
         q = p;
         p = p->suivant;
         free(q);
        }*/
}
void nom(elem *e,int min)
{
    int nmbr_car;
    while(min>=29)
    {
        min = min%29 +4;
    }
    srand(time(NULL));
    nmbr_car = randomnumb(min,29);
    for (int i = 0; i <= nmbr_car; i++)
     {
        if (min >= 25)
        {
           min = 1;
        }
         (*e).nom[i] = randomnumb(min,26)+97;
         min++;
        }
        (*e).nom[nmbr_car] = '\0';

}

void prenom(elem *e,int min)
{
    int nmbr_car;
        while(min>=30)
    {
        min = min%30+7;
    }
    srand(time(NULL));
    nmbr_car = randomnumb(min,30);
    for (int i = 0; i <= nmbr_car; i++)
     {
         if (min >= 25)
        {
           min = 1;
        }
         (*e).prenom[i] = randomnumb(min,26)+97;
         min++;
        }
    (*e).prenom[nmbr_car] = '\0';

}

void date_birth(elem *e,int min)
{
    while(min<=1942 || min >=2005)
    {
        min = min%2005 + 1942;
        if (min==0){ min =1; }
    }
    int maxday;
    srand(time(NULL));
    int year = randomnumb(min,2005);
    (*e).date_naissance.year = year;
    min = min%12;
    if (min==0){ min =1; }
        int month = randomnumb(min,12);
        (*e).date_naissance.month = month;
        min=(min*10)%28;
        if (min==0){ min =1; };
        if (month == 2)
        {
            if (year%4 == 0) // si l'année est bissextile
            {
                maxday = 29;
            }else{
                maxday =28;
            }
        }else{
            if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                maxday = 30;
            }else{
                maxday = 31;
            }
            }
        (*e).date_naissance.day = randomnumb(min,maxday);
}

void wilaya(elem *e,int min)
{
    while(min >= 58)
    {
        min = min%58;
        if (min==0){ min =1; }
    }
    int max=58;
    int random;
    srand(time(NULL));
    random = randomnumb(min,max);
    FILE *F;
    F=fopen("wilayas.txt","r");
    char wil[20];
    for (int j = 1; j <= random; j++)
    {
        fgets(wil,sizeof(wil),F);
    }
    strcpy((*e).wilaya,wil);
    fermer(F);
}
///////////////////////////////
void Groupe_sanguin(elem *e,int min)
{
    while(min >= 8)
    {
        min = min%8;
        if (min==0){ min =1; }
    }
    int max=8;
    int random;
    srand(time(NULL));
    random = randomnumb(min,max);
    FILE *F;
    F=fopen("groupe_sanguin.txt","r");
    char wil[5];
    for (int j = 1; j <= random; j++)
    {
        fgets(wil,sizeof(wil),F);
    }
    strcpy((*e).Groupe_sanguin,wil);
    fermer(F);
}
//////////////////////////////////////////////
void grade(elem *e,int min)
{
    while(min >= 19)
    {
        min = min%19;
        if (min==0){ min =1; }
    }
    int max=19;
    int random;
    srand(time(NULL));
    random = randomnumb(min,max);
    FILE *F;
    F=fopen("grade.txt","r");
    char wil[30];
    for (int j = 1; j <= random; j++)
    {
        fgets(wil,sizeof(wil),F);
    }
    strcpy((*e).Grade,wil);
    fermer(F);
}
/////////////////////////////////////7
void Force_Armee(elem *e,int min)
{
    while(min >= 8)
    {
        min = min%8;
        if (min==0){ min =1; }
    }
    int max=8;
    int random;
    srand(time(NULL));
    random = randomnumb(min,max);
    FILE *F;
    F=fopen("force_armee.txt","r");
    char wil[50];
    for (int j = 1; j <= random; j++)
    {
        fgets(wil,sizeof(wil),F);
    }
    strcpy((*e).Force_Armee,wil);
    fermer(F);
}
//////////////////////////////////////////7
void Region_militaire(elem *e,int min)
{
    while(min >= 6)
    {
        min = min%6;
        if (min==0){ min =1; }
    }
    int max=6;
    int random;
    srand(time(NULL));
    random = randomnumb(min,max);
    FILE *F;
    F=fopen("region_militare.txt","r");
    char wil[20];
    for (int j = 1; j <= random; j++)
    {
        fgets(wil,sizeof(wil),F);
    }
    strcpy((*e).Region_militaire,wil);
    fermer(F);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////CHARGEMENT INITIAL :


void chargement(char nomfich[20], int nmbr_enrg)
{   if (nmbr_enrg == 0)
        return;
    node *p,*q,*tete;
    int j=1;
    int oldj=1;
    int min = 111111;
    int oldmin = 111111;
    int min2 = 1;
    int bloc ;
    int val = nmbr_enrg;
    p=NULL;
    q=NULL;
    tete = NULL;
    FILE *f;
    ouvrire(&f,nomfich,'N');
    buffer buf;
    bloc = nmbr_enrg/b +1;
    int oldbloc = bloc;
    do{
    if (bloc>1){ val = b;
                }else{ val=nmbr_enrg%b; } //remplire le dernier bloc avec ce que rest
    for ( int i=0; i < val ; i++)
    {
    matricule(&(buf.tab[i]),&tete,&p,&min,&oldmin,&j,&oldj);
    nom(&(buf.tab[i]),min2);
    prenom(&(buf.tab[i]),min2);
    date_birth(&(buf.tab[i]),min2);
    wilaya(&(buf.tab[i]),min2);
    Groupe_sanguin(&(buf.tab[i]),min2);
    grade(&(buf.tab[i]),min2);
    Force_Armee(&(buf.tab[i]),min2);
    Region_militaire(&(buf.tab[i]),min2);
    min2++;
    }
    buf.NB = val;
    EcrireDir(f,oldbloc-bloc+1,&buf);
    bloc--;
    }while( bloc != 0 );
    Aff_entete(f,1,nmbr_enrg/b +1);
    Aff_entete(f,2,val-1);
    fermer(f);

        p = tete;
while (p != NULL)
{
    q = p;
    p = p->suivant;
    free(q);
}
}

















