#include <stdio.h>
#include <stdlib.h>
#include <string.h>









typedef struct typeDuBien typeDuBien;
struct typeDuBien
{
    char  *code;
    char  *libelle;
    float prix;









};









typedef struct receipt receipt;
struct receipt
{
char receiptLibelle[20], receiptCode[6];
float receiptPrix,S;
int minSupp;
receipt *suiv;
};













typedef struct Liste
        {
                struct receipt *premier;
        } Liste ;








Liste *initialisation()
{
    Liste *liste = malloc(sizeof(struct Liste));








    if (liste == NULL )
    {
        exit(EXIT_FAILURE);
    }
  liste->premier = NULL;







    return liste;
}









void insertion(Liste *liste,receipt element)
{
    /* Création du nouvel élément */
    receipt *nouveau = malloc(sizeof(receipt));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
        strcpy( nouveau->receiptLibelle, element.receiptLibelle);
        strcpy(nouveau->receiptCode, element.receiptCode);
        nouveau->receiptPrix = element.receiptPrix ;
        nouveau->S =element.S ;
        nouveau->minSupp = element.minSupp ;







    /* Insertion de l'élément au début de la liste */
    nouveau->suiv = liste->premier;
    liste->premier = nouveau;
}
//END LISTE








void afficherListe(Liste *liste,float ttlcost)
{
       FILE * bdt;    //file bdt
    FILE * idt;    //file identi
    FILE * rslt; //file resultat
    //files
   bdt = fopen ("Bdt.txt","a");  /* Bdt.txt*/ //"a" for contenu typing "w" for deleting and put new ligne
   idt = fopen ("identifiant.txt","a");  /* identifiant.txt*/
   rslt = fopen("resultat.txt","a");






    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }







    receipt *actuel = liste->premier;







    while (actuel != NULL)
    {









printf("%10s %10s %10.2f %10d %10.2f\n", actuel->receiptLibelle, actuel->receiptCode, actuel->receiptPrix, actuel->minSupp, actuel->S);
fprintf(idt,"%10s%10s%10.2f\n", actuel->receiptCode, actuel->receiptLibelle,  actuel->receiptPrix); //for identifiant
fprintf (bdt, "%10s\n",  actuel->receiptCode); //for Bdt
fprintf(rslt,"%10s %10s %10.2f %10d %10.2f\n", actuel->receiptLibelle, actuel->receiptCode, actuel->receiptPrix, actuel->minSupp, actuel->S); //for resultat







        actuel = actuel->suiv;
    }



    printf("_____________________________________\n\n");
printf("      MERCI DE VOTRE VISITE!     \n");
printf("_____________________________________\n");
printf("         Voici votre reçu:       \n\n");
printf("%s %20s %10s %10s %10s", " Libelle ", " Code "," Prix ", " QTT", " Supp\n");





printf("\n_____________________________________\n");
printf("          TOTALE:%.2f            \n", ttlcost);
fprintf(rslt,"TOTALE:%.2f\n", ttlcost); //for resultat
/* close  files*/



     fclose (idt);
   fclose(rslt);
   fclose(bdt);
}








void add_price(receipt element,Liste *liste)
{
     if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }







    receipt *actuel = liste->premier;







    while (actuel != NULL)
    {
        if(strcmp(actuel->receiptCode, element.receiptCode) == 0){
             actuel->receiptPrix +=element.receiptPrix;
             break;
        }
        actuel = actuel->suiv;
    }
}









static typeDuBien biens[] =
{
    { "1009", "creme_glacee",  3.56 },
    { "167", "fromage",  1.55 },
    { "123", "jus",  1.35 },
    { "500", "lait",  0.97 },
    { "890", "coca",  1.22 },
    { "654", "chocolat",  2.78 },
    { "763", "crevette",  33.62 },
    { "34", "serviette_papier",  0.87 },
};
static int bienstotal = sizeof(biens) / sizeof(biens[0]);
int main( void )









{
    //afficher table
    unsigned int i,j,minSupp;
//        int S;
    for (i = 0; i < bienstotal; i++ )
        printf( "%s %s %f\n", biens[i].code, biens[i].libelle, biens[i].prix );
        printf( "\n Nombres totales des biens: %d\n", bienstotal );











char tempCode[6]; //code entrer
receipt receipt[13];
 Liste *maListe = initialisation();











char stop[2] = {"F"}; //sorter du programme
float ttlcost = 0; //resultat final









unsigned int total = 0; //nbr de produit dans le tableaux








struct receipt element;









while ( strcmp(tempCode, stop) ){ //strcmp comparer entre 2 string
printf("\n Veuillez saisir le code article. Tapez F pour terminer: ");
scanf("%s", tempCode);
printf("Donner nombre de produits: ");
scanf("%d", &minSupp); //qtt








for (i = 0; i < bienstotal; ++i){
    if(strcmp(tempCode, biens[i].code) == 0){
        strcpy(element.receiptLibelle, biens[i].libelle); //strcpy copy
        strcpy(element.receiptCode, biens[i].code);
        element.receiptPrix = biens[i].prix ;
        element.S = biens[i].prix * minSupp ;
        element.minSupp = minSupp ;
        insertion(maListe,element);
         add_price(element,maListe);
        ttlcost += biens[i].prix;
        total++;
    }











}









}



afficherListe(maListe,ttlcost);




//   fprintf (bdt,);
   return 0;
}
