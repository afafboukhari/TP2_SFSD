#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<time.h>
#include "machine_abs.h"
#include "creation.h"
#include "manipulation.h"




int main()
{
  int choice;
  int n;
  int min2=21548963;
  bool q1=false,q2=false;
  int total_index;
  do{
  system("cls");
  index *table_index;
  printf("******************************************* BIENVENUE ! ******************************************\n\n");
  printf("\033[1;34mVoici les choix possibles :\n\n[1]-\033[1;33mCreer le fichier PERSONNEL-ANP_DZ.dat de nouveau\n\033[1;34m[2]-\033[1;33mChargement de l index en MC à partir du fichier index nomme MATRICULE_INDEX.idx");
  printf("\n\033[1;34m[3]-\033[1;33mSauvegarde de l index dans MATRICULE_INDEX.idx.\n\033[1;34m[4]-\033[1;33mRecherche d un militaire par son matricule.\n\033[1;34m[5]-\033[1;33mInsertion d un nouvel enregistrement au fichier PERSONNEL-ANP_DZ.dat");
  printf("\n\033[1;34m[6]-\033[1;33mSuppression d un enregistrement donne par le matricule.\n\033[1;34m[7]-\033[1;33mModification de la region militaire d un enregistrement donne.\n\033[1;34m[8]-\033[1;33mAffichage ou consultation de tous militaires dont les matricules appartiennent à l intervalle [M1, M2].");
  printf("\n\033[1;34m[0]-\033[1;33mEXIT .");
  printf("\n\n\033[1;34mEntrer votre choix la ----->  \033[1;0m");
  scanf("%d",&choice);
  //display("PERSONNEL-ANP_DZ.dat");
    switch (choice)
  {
    case 1:
    { q1 = true;
      printf("\033[1;33m ****************Creer le fichier PERSONNEL-ANP_DZ.dat****************");
      printf("\n\033[1;34mCombien d'enregistrement voulez-vous creer ?  ");
      scanf("%d",&n);
      printf("\nPatienz un petit peu s'il vous plait , la creation peut prendre quelques instants~");
      chargement("PERSONNEL-ANP_DZ.dat",n);
      //creation de la table d'index :
      index *index = NULL;
      buffer buf;
      FILE *file;
        int indexSize = 0;
      ouvrire(&file,"PERSONNEL-ANP_DZ.dat",'A');
      for (int i = 1; i <= entete(file, 1); i++) {
        LireDir(file, i, &buf);
        for (int j = 0; j < buf.NB; j++) {

            InsertKeySorted(&index, &indexSize, buf.tab[j].matricule, i, j);
        }
          }
      //fin de la creation de la table d'index
      //cration de fichier index :
      FILE *g;
      indexbuffer buf2;
      INIT(&g,"MATRICULE_INDEX.idx",'N');
      Chargement_indexfile(g,indexSize,&buf2,index);
      //fin creation de fichier index
      printf("\n\n\033[1;32m   Operation fait avec succes !");
      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      free(index);
      fclose(g);
      getchar();
      getchar();
      break;
    }
    case 2:
    {   q2 = true;
        char answer;
        printf("\n\033[1;34m*************\033[1;33m Chargement de l index en MC à partir du fichier index nomme MATRICULE_INDEX.idx\033[1;34m*************");
        FILE *f;
        INIT(&f,"MATRICULE_INDEX.idx",'A');
        indexbuffer buf;
        printf("\nPatienz un petit peu s'il vous plait , la creation peut prendre quelques instants~");
        chargement_table_index(f,&table_index,&total_index,&buf);
        printf("\n\033[1;32m   Operation fait avec succes !\n");
        printf("\n \033[1;33mtotal %d\n",total_index);
        fclose(f);
        printf("\033[1;33m Voulez vous afficher le contenu ? (y/n) ");
        scanf("%c",&answer);
        scanf("%c",&answer); //on est besoin de 2 scanf á cause de getchar

        if(answer == 'y' || answer == 'Y')
        {
            display("PERSONNEL-ANP_DZ.dat");
            printf("\n Total : %d ",total_index);
           /*for(int x=0;x<total_index;x++)
        {
            printf("%d    \n",table_index[x].matricule);
        }*/
        }
        printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
        if(!q1) { n = total_index; }
        getchar();
        getchar();
        break;
    }
    case 3:
    {
        printf("\n\033[1;34m*************\033[1;33mSauvegarde de l index dans MATRICULE_INDEX.idx.\033[1;34m*************\n");
        if(!q2)
        {
            printf("\n\033[1;31m    traiter le 2eme choix d abord s il vous plait ~\n");
        }else{
        sauv :;
        FILE *f;
        int taille = n;
        ouvrire(&f,"MATRICULE_INDEX.idx",'N');
        indexbuffer buf2;
        if(total_index != 0)
        {
            taille = total_index;
        }
        sauvegarde_indexfile(f,taille,&buf2,table_index);
        printf("\n\n\033[1;32m   Operation fait avec succes !");
        }
        printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
        getchar();
        getchar();
        break;
    }
    case 4:
    {
      printf("\033[1;34m*************\033[1;33mRecherche d un militaire par son matricule.\033[1;34m*************");
      if(!q2)
      {
          printf("\n\n\033[1;31m   traiter le 2eme choix d abord s il vous plait ~\n");
      }else{
      printf("\n Donnez la matricule que vous voulez rechercher : ");
      int key;
      scanf("%d",&key);
      int i,j;
      bool trouve;
      Recherch_Dicho_ind(table_index,key,total_index,&j,&trouve);
      i = table_index[j].nbloc;
      j = table_index[j].depl;
      if(trouve)
      {
       FILE *g;
       ouvrire(&g,"PERSONNEL-ANP_DZ.dat",'A');
       buffer buf;
       LireDir(g,i,&buf);
        printf("\033[1;33m  la matricule est \033[1;34m %d\n",buf.tab[j].matricule);
        printf("\033[1;33m  le nom :\033[1;34m '%s' \n\033[1;33m  le prenom :\033[1;34m '%s' \n",buf.tab[j].nom,buf.tab[j].prenom);
        printf("\033[1;33m  date de naissance :\033[1;34m %d-%d-%d \n",buf.tab[j].date_naissance.day,buf.tab[j].date_naissance.month,buf.tab[j].date_naissance.year);
        printf("\033[1;33m  Du wilaya :\033[1;34m %s",buf.tab[j].wilaya);
        printf("\033[1;33m  le groupe sanguin :\033[1;34m %s ",buf.tab[j].Groupe_sanguin);
        printf("\033[1;33m le grade :\033[1;34m %s ",buf.tab[j].Grade);
        printf("\033[1;33m la force armee :\033[1;34m  %s ",buf.tab[j].Force_Armee);
        printf("\033[1;33m la region militaire :\033[1;34m %s ",buf.tab[j].Region_militaire);
      }else{
      printf("\n\033[1;31m desolee,la matricule que vous cherchez n'existe pas !\n");
      }
      }
      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      getchar();
      getchar();
      break;
    }
    case 5:
    {   FILE *f;
        printf("\n\033[1;34m*********\033[1;33mInsertion d un nouvel enregistrement au fichier PERSONNEL-ANP_DZ.dat\033[1;34m*********\n");
        if(!q2)
        {
            printf("\n\n\033[1;31m   traiter le 2eme choix d abord s il vous plait ~\n");
        }else
        {
        printf(" Donnez la cle que vous voulez inserer : ");
        int cle;
        scanf("%d",&cle);
        bool trouve;
        int x,j;
        Recherch_Dicho_ind(table_index,cle,total_index,&j,&trouve);
        if(!trouve)
        {
            ouvrire(&f,"PERSONNEL-ANP_DZ.dat",'A');
            buffer buf;
            elem e;
            e.matricule = cle;
            nom(&e,min2);
            prenom(&e,min2);
            date_birth(&e,min2);
            wilaya(&e,min2);
            Groupe_sanguin(&e,min2);
            grade(&e,min2);
            Force_Armee(&e,min2);
            Region_militaire(&e,min2);
            min2=min2%333 + 14;
            Insertion_fichier_de_donnes(e,f,&buf,&x,&j);
            Insertion_table(&table_index,&total_index,cle,x,j);
            goto sauv;
        }else{
        printf("\n\033[1;31m  --> matricule existe deja.\n");
        }

        }


      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      getchar();
      getchar();
      break;
    }
    case 6:
    {
      printf("\n\033[1;34m*************\033[1;33mSuppression d’un enregistrement donne par le matricule.\033[1;34m*************\n");
      if(!q2)
      {
          printf("\n\n\033[1;31m   traiter le 2eme choix d abord s il vous plait ~\n");
      }else{
          int key;
          printf("donnez le matricule a supprimer ");
          scanf("%d",&key);
          FILE *f;
          ouvrire(&f,"PERSONNEL-ANP_DZ.dat",'A');
          buffer buf;
          bool trouve;
          supp(key,f,&buf,table_index,total_index,&trouve);
          if(trouve)
          {
              printf("\n\n\033[1;32m   Operation fait avec succes !\n");
              INIT(&f,"MATRICULE_INDEX.idx",'A');
              indexbuffer buf;
              chargement_table_index(f,&table_index,&total_index,&buf);
          }
      }
      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      getchar();
      getchar();
      break;
    }
    case 7:
    {
      printf("\n\033[1;34m*************\033[1;33mModification de la region militaire d un enregistrement donne\033[1;34m*************\n");
      if(!q2)
      {
          printf("\n\n\033[1;31m   traiter le 2eme choix d abord s il vous plait ~\n");
      }else{
      printf("\n\033[1;33m entrez la matricule de l'enregistrement que vouz voulez modifier ");
      int key;
      scanf("%d",&key);
      printf("Donnez la nouvelle valeur :");
      char val[20];
      scanf("%s",val);
      FILE *f;
      ouvrire(&f,"PERSONNEL-ANP_DZ.dat",'A');
      buffer buff;
      modification(f,key,val,&buff,table_index,total_index);
      }
      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      getchar();
      getchar();
      break;
    }
    case 8:
    { printf("\n\033[1;34m*************\033[1;33mModification de la region militaire d un enregistrement donne\033[1;34m*************\n");
    if(!q2)
    {
        printf("\n\n\033[1;31m   traiter le 2eme choix d abord s il vous plait ~\n");
    }else{
      printf("Donnez le debut et la fin de l intervalle pour l'afficher : ");
      int star,end;
      scanf("%d",&star);
      scanf("%d",&end);
      FILE *file;
      ouvrire(&file,"PERSONNEL-ANP_DZ.dat",'A');
      buffer buff;
      Requete_a_intervalle(table_index,star,end,total_index,file,&buff);
    }
      printf("\n\033[1;33m   >>>>>Cliquez sur Entrer pour revenir au menu\n");
      getchar();
      getchar();
      break;
    }
    case 0:
    {
        return 0;
    }
    default :
        {
            printf(" \n Choix invalide ! Cliquez sue Entrer pour revenir au menu principal \n");
            getchar();
            getchar();
        }
  }

}while(choice != 0);

}
