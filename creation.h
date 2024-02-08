#ifndef CREATION_H_INCLUDED
#define CREATION_H_INCLUDED

// Declaration et fonction necessaire pour verifier que la matricule est unique :
struct maillon
{
    int val;
    struct maillon *suivant;

};

typedef struct maillon node;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// LES FONCTIONS ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int randomnumb(int min, int max);
bool unique(node *tete,int val);
node* allouer(); //LLC
void matricule(elem *enrg,node **tete,node **queue, int *min,int *oldmin,int *j,int *oldj);
void nom(elem *e,int min);
void prenom(elem *e,int min);
void date_birth(elem *e,int min);
void wilaya(elem *e,int min);
void Groupe_sanguin(elem *e,int min);
void grade(elem *e,int min);
void Force_Armee(elem *e,int min);
void Region_militaire(elem *e,int min);
void chargement(char nomfich[20], int nmbr_enrg);

#endif // CREATION_H_INCLUDED
