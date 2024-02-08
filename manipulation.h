#ifndef MANIPULATION_H_INCLUDED
#define MANIPULATION_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define B 1024
#include "machine_abs.h"

// declaration necessaire pour le fichier index :

typedef struct {
  int matricule;
  int nbloc;
  int depl;
}index ;

typedef struct {
index idx;
bool eff;
} indexenrg;

typedef struct {
indexenrg TAB[B];
int NB;
}indexbloc,indexbuffer;

typedef struct {
int nmbr_bloc;
int nmbr_enrg;
int nmbr_eff;
}index_entete;


/** FONCTIONS **/
// machine abstraite du fichier TOF (index) :
void INIT_Entete(FILE* F);
void INIT(FILE** F, const char nom[], char mode);
bool liredire_index(FILE* F, int i, indexbuffer* Buf);
bool ecriredir_index(FILE* F, int i, indexbuffer* Buf);
int  entete_index(FILE* F, int i);
void aff_enteteindex(FILE* F, int Nb, int i);
/////////////////////////////////////////////////////////////
void InsertKeySorted(index **IndexTable, int *totalIndex, int newKey, int blockNumber, int recordIndex);
void Chargement_indexfile(FILE* F, int n, indexbuffer* Buf, index* index);
void rech(int c, char nom[20],int *i,int *j,bool *trouve);
void chargement_table_index(FILE *fichierIndex, index **tableIndex, int *totalIndex, indexbuffer *Buf2);
void sauvegarde_indexfile(FILE* F, int n,indexbuffer* Buf2, index* dex);
void Recherch_Dicho_ind(index *dex, int key, int totalIndex, int *posi,bool *trouv);
void Insertion_fichier_de_donnes(elem e, FILE* F, buffer* Buf,int *bloc,int *depl);
void Insertion_table(index **table, int *totalElements, int newKey, int blockNumber, int recordIndex);
void supp(int c, FILE* F, buffer* Buf,index *dex,int taille_index,bool *trouv);
void modification(FILE* dataFile, int key, char newValue[20], buffer* dataBuffer, index* tableindex, int totalIndex);
void Requete_a_intervalle(index *tableindex, int startKey, int endKey, int totalIndex, FILE *dataFile, buffer *dataBuffer);

#endif // MANIPULATION_H_INCLUDED
