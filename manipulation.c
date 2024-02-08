#include "manipulation.h"
#include "machine_abs.h"
#include "creation.h"
#include <string.h>
// Function to initialize the header with default values
void INIT_Entete(FILE* F) {
    index_entete entt;
    entt.nmbr_bloc = 0;
    entt.nmbr_eff = 0;
    entt.nmbr_enrg = 0;
    fseek(F, 0, SEEK_SET);
    fwrite(&entt, sizeof(index_entete), 1, F);
}
// The file :
void INIT(FILE** F, const char nom[], char mode) {
    if (mode == 'N') {
        *F = fopen(nom, "wb+");
        INIT_Entete(*F);
    } else if (mode == 'A') {
        *F = fopen(nom, "rb+");
        if (*F == NULL) {
            *F = fopen(nom, "wb");
            if (*F == NULL) {
                perror("Error opening file");
            }
        }
    }
}
// Function to read a block from the index file
bool liredire_index(FILE* F, int i, indexbuffer* Buf) {
    if (F == NULL || i <= 0 || fseek(F, (i - 1) * sizeof(indexbuffer) + sizeof(index_entete), SEEK_SET) != 0) {
        return false;
    }

    if (fread(Buf, sizeof(indexbuffer), 1, F) != 1) {
        return false;  // Check if the read was successful
    }

    return true;
}

// Function to write a block to the index file
bool ecriredir_index(FILE* F, int i, indexbuffer* Buf) {
    if (F == NULL || i <= 0 || fseek(F, (i - 1) * sizeof(indexbuffer) + sizeof(index_entete), SEEK_SET) != 0) {
        return false;
    }

    if (fwrite(Buf, sizeof(indexbuffer), 1, F) != 1) {
        return false;  // Check if the write was successful
    }

    return true;
}
// Function to retrieve header information
int entete_index(FILE* F, int i) {
    if (F != NULL) {
        index_entete entt;
        fseek(F, 0, SEEK_SET);
        fread(&entt, sizeof(index_entete), 1, F);
        if (i == 1) return entt.nmbr_bloc;
        if (i == 2) return entt.nmbr_enrg;
        if (i == 3) return entt.nmbr_eff;
    }
    return -1;  // Return an error value if the file is not open
}
// Function to update header information
void aff_enteteindex(FILE* F, int Nb, int i) {
    if (F != NULL) {
        index_entete entt;
        fseek(F, 0, SEEK_SET);
        fread(&entt, sizeof(index_entete), 1, F);
        if (i == 1) entt.nmbr_bloc = Nb;
        if (i == 2) entt.nmbr_enrg = Nb;
        if (i == 3) entt.nmbr_eff = Nb;
        fseek(F, 0, SEEK_SET);
        fwrite(&entt, sizeof(index_entete), 1, F);
    }
}

/**insertion dans la table d'index **/
void InsertKeySorted(index **IndexTable, int *totalIndex, int newKey, int blockNumber, int recordIndex) {
    // Allocate memory for a new index table with one additional element
    index *newIndexTable = (index *)malloc((*totalIndex + 1) * sizeof(index));

    if (newIndexTable == NULL) {
        perror("Memory allocation error");
    }

    // Find the position to insert the new key in the sorted index table
    int position = 0;
    while (position < *totalIndex && (*IndexTable)[position].matricule < newKey) {
        position++;
    }

    // Shift elements to make space for the new key
    for (int i = 0; i < position; i++) {
        newIndexTable[i] = (*IndexTable)[i];
    }

    // Insert the new key at the correct position
    newIndexTable[position].matricule = newKey;
    newIndexTable[position].nbloc = blockNumber;
    newIndexTable[position].depl = recordIndex;

    // Copy the remaining elements
    for (int i = position + 1; i <= *totalIndex; i++) {
        newIndexTable[i] = (*IndexTable)[i - 1];
    }

    // Free the old index table
    free(*IndexTable);

    // Update the pointer to the new index table
    *IndexTable = newIndexTable;

    // Increment the total number of elements in the index table
    (*totalIndex)++;
}
/** creation du fichier index **/
// Function to load initial data into the file
void Chargement_indexfile(FILE* F, int n, indexbuffer* Buf, index* index) {
    int i = 1, j = 0;
    for (int k = 0; k < n; k++) {
        if (j < B) {
            Buf->TAB[j].idx.matricule = index[k].matricule;
            Buf->TAB[j].idx.nbloc = index[k].nbloc;
            Buf->TAB[j].idx.depl = index[k].depl;
            Buf->TAB[j].eff = 0;
            j++;
        } else {
            Buf->NB = j;
            ecriredir_index(F, i, Buf);
            Buf->TAB[0].idx.matricule = index[k].matricule;
            Buf->TAB[0].idx.nbloc = index[k].nbloc;
            Buf->TAB[0].idx.depl = index[k].depl;
            Buf->TAB[0].eff = 0;
            i++;
            j = 1;
        }
    }
    Buf->NB = j;
    ecriredir_index(F, i, Buf);
    aff_enteteindex(F, i, 1);
    aff_enteteindex(F, n, 2);
}

////////////////////////////////////////////
void Recherch_Dicho_ind(index *dex, int key, int totalIndex, int *posi,bool *trouv) {
    int inf = 0, sup = totalIndex-1 ;
    *trouv = false;

    int j = 0;

    while (inf <= sup && !*trouv) {
        j = (int)(sup + inf) / 2;

        if (dex[j].matricule == key) {
            *trouv = true;
        } else {
            if (key > dex[j].matricule) {
                inf = j + 1;
            } else {
                sup = j - 1;
            }
        }
    }

    if (!*trouv) {
        j = inf-1;
    }

    *posi = j;
}
////////////////////////////////////////////
//chargement de la table d'index du fichier index
 void chargement_table_index(FILE *fichierIndex, index **tableIndex, int *totalIndex, indexbuffer *Buf2) {
    *totalIndex = entete_index(fichierIndex, 2);
    // Allocate memory for the table d'index
    index *tindex = (index *)malloc((*totalIndex + 1) * sizeof(index));

    if (tindex == NULL) {
        perror("Memory allocation error");
    }
    int dex = 0;

    // Traverse the blocks in the fichier d'index
    for (int i = 1; i <= entete(fichierIndex, 1); i++) {
        // Read the block into the buffer
        liredire_index(fichierIndex, i, Buf2);

        // Traverse the keys in the block
        for (int j = 0; j < Buf2->NB; j++) {
            // Add the key to the table d'index
            if( !Buf2->TAB[j].eff )
            {
            tindex[dex].matricule = Buf2->TAB[j].idx.matricule;
            tindex[dex].nbloc = Buf2->TAB[j].idx.nbloc;
            tindex[dex].depl = Buf2->TAB[j].idx.depl;
            dex++;
            }

        }

    }


    // Free the existing memory of *tableIndex
    // free(*tableIndex);
    // Update *tableIndex with the new memory address
    *tableIndex = tindex;
    *totalIndex = dex;

}
/////////////////////////////////////////////////////////
void sauvegarde_indexfile(FILE* F, int n,indexbuffer* Buf2, index* dex) {
    int i = 1, j = 0;
    for (int k = 0; k < n; k++) {
        if (j < B) {
            Buf2->TAB[j].idx.matricule = dex[k].matricule;
            Buf2->TAB[j].idx.nbloc=dex[k].nbloc;
            Buf2->TAB[j].idx.depl=dex[k].depl ;
            j++;
        } else {
            Buf2->NB = j;
            ecriredir_index(F, i, Buf2);
            Buf2->TAB[0].idx.matricule = dex[k].matricule;
            Buf2->TAB[0].idx.nbloc=dex[k].nbloc;
            Buf2->TAB[0].idx.depl=dex[k].depl ;
            i++;
            j = 1;
        }
    }
    Buf2->NB = j;
    ecriredir_index(F, i, Buf2);
    aff_enteteindex(F, i, 1);
    aff_enteteindex(F, n, 2);
    int l = entete_index(F,1);
    l = entete_index(F,2);
    printf(" --> Index est sauvegarde \n");
}
//////////////////////////////////////////////
void Insertion_fichier_de_donnes(elem e, FILE* F, buffer* Buf,int *bloc,int *depl) {
    int i, j;
    i = entete(F,1);
    LireDir(F,i,Buf);
    j=Buf->NB;
        if (Buf->NB < b) {
            Buf->tab[j] = e;
            Buf->NB++;
        } else {
            Buf->tab[0] = e;
            Buf->NB = 1;
            i++;
        }
    EcrireDir(F, i, Buf);
    Aff_entete(F, 1, i);
    Aff_entete(F, 2, entete(F, 2) + 1);
    *bloc = i;
    *depl = entete(F,2);
}
//////////////////////////////////////////////////////
void Insertion_table(index **table, int *totalElements, int newKey, int blockNumber, int recordIndex) {
    index *newTable = (index *)malloc((*totalElements + 1) * sizeof(index));

    if (newTable == NULL) {
        perror("Memory allocation error");
    }

    int position = 0;
    while (position < *totalElements && (*table)[position].matricule < newKey) {
        position++;
    }

    for (int i = 0; i < position; i++) {
        newTable[i] = (*table)[i];
    }

    newTable[position].matricule = newKey;
    newTable[position].nbloc = blockNumber;
    newTable[position].depl = recordIndex;

    for (int i = position + 1; i <= *totalElements; i++) {
        newTable[i] = (*table)[i - 1];
    }

    free(*table);

    *table = newTable;

    *totalElements = *totalElements+1;
}

////////////////////////////////////////////////////////
void supp(int c, FILE* F, buffer* Buf,index *dex,int taille_index,bool *trouve) {
    int i, j, k,x;
    elem e;
    Recherch_Dicho_ind(dex,c,taille_index,&x,trouve);
    i = dex[x].nbloc;
    j = dex[x].depl;
    if (*trouve) {
        k = entete(F, 1);  // Get the total number of blocks
    LireDir(F, k, Buf);  // Read the last block

        e = Buf->tab[Buf->NB - 1];  // Get the last record in the last block
        Buf->NB--;
        EcrireDir(F, k, Buf);  // Write back the modified last block
        LireDir(F, i, Buf);
        Buf->tab[j] = e;
        EcrireDir(F, i, Buf);
        Aff_entete(F, 2, entete(F, 2) - 1);

        //supression fichier index :
        FILE *f;
        INIT(&f,"MATRICULE_INDEX.idx",'A');
        i = x/1024 +1; // 1024 est la taille du bloc
        j = x%1024;
        indexbuffer buf2;
        liredire_index(f,i,&buf2);
        buf2.TAB[j].eff = true;
        ecriredir_index(f,i,&buf2);
/*
for (int i = 1; i <= k; i++) {
  LireDir(F, i, Buf);
            printf("Block %d:\n", i);
            for (int j = 0; j < Buf->NB; j++) {
                printf("    Key: %d\n", Buf->tab[j].matricule);
            }

    }*/
    }else {        printf("\033[1;31m  -->matricule non trouve \n");}
}
///////////////////////////////////////////////////////////////////
void modification(FILE* dataFile, int key, char newValue[20], buffer* dataBuffer, index* tableindex, int totalIndex)
 {
    int position;
    bool trouve;
    Recherch_Dicho_ind(tableindex, key, totalIndex, &position,&trouve);
    if(trouve)
    {
       if (position >= 0 && position < totalIndex && tableindex[position].matricule == key) {
        // Read the block containing the record from the data file
        if (LireDir(dataFile, tableindex[position].nbloc, dataBuffer)) {
            // Modify the field
            strcpy(dataBuffer->tab[tableindex[position].depl].Region_militaire,newValue);

            // Write the updated block back to the data file
            EcrireDir(dataFile, tableindex[position].nbloc, dataBuffer);

            printf("Field modified successfully.\n");
        } else {
            //printf("Error reading block %d\n", tableindex[position].nbloc);
        }
     } else {
        printf("Key not found in the index.\n");
     }
    }else{
    printf("Key not found in the index.\n");
    }
    printf("position dans index %d.\n",position);

}
///////////////////////////////////////////////////////////////////7
void Requete_a_intervalle(index *tableindex, int startKey, int endKey, int totalIndex, FILE *dataFile, buffer *dataBuffer) {
    int startPos, endPos;
    bool trouve;
    // Perform binary search to find positions in the index for startKey and endKey
    Recherch_Dicho_ind(tableindex, startKey, totalIndex, &startPos,&trouve);
    Recherch_Dicho_ind(tableindex, endKey, totalIndex, &endPos,&trouve);
    printf("\nRecords in the range [start pos %d, end pos%d]:\n", startPos, endPos);

    for (int i = startPos; i <= endPos; i++) {
        // Read the block containing the record from the data file
        if (LireDir(dataFile, tableindex[i].nbloc, dataBuffer)) {
            // Display the keys within the specified range
                    if ((tableindex[i].matricule >= startKey) && (tableindex[i].matricule <= endKey))
                  {
        printf("\n\033[1;33m  la matricule est \033[1;34m %d\n",dataBuffer->tab[tableindex[i].depl].matricule);
        printf("\033[1;33m  le nom :\033[1;34m '%s' \n\033[1;33m  le prenom :\033[1;34m '%s' \n",dataBuffer->tab[tableindex[i].depl].nom,dataBuffer->tab[tableindex[i].depl].prenom);
        printf("\033[1;33m  date de naissance :\033[1;34m %d-%d-%d \n",dataBuffer->tab[tableindex[i].depl].date_naissance.day,dataBuffer->tab[tableindex[i].depl].date_naissance.month,dataBuffer->tab[tableindex[i].depl].date_naissance.year);
        printf("\033[1;33m  Du wilaya :\033[1;34m %s",dataBuffer->tab[tableindex[i].depl].wilaya);
        printf("\033[1;33m  le groupe sanguin :\033[1;34m %s ",dataBuffer->tab[tableindex[i].depl].Groupe_sanguin);
        printf("\033[1;33m le grade :\033[1;34m %s ",dataBuffer->tab[tableindex[i].depl].Grade);
        printf("\033[1;33m la force armee :\033[1;34m  %s ",dataBuffer->tab[tableindex[i].depl].Force_Armee);
        printf("\033[1;33m la region militaire :\033[1;34m %s ",dataBuffer->tab[tableindex[i].depl].Region_militaire);
        printf("\n\033[1;0m------------------------------------------------------------------------------------------------------\n");
                  }
                }

         else {
            printf("Error reading block %d\n", tableindex[i].nbloc);
        }
    }
}
