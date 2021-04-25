#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include <time.h>
#include <string.h>

void enregistrerParametre(Parametre *saveParametre)
{
 
 FILE* fichierParametre=NULL;
 
 fichierParametre=fopen("configuration/parametre/parametre.conf", "w+");

 if(fichierParametre!=NULL)
 {
  fputc(saveParametre->difficulteActuel, fichierParametre);
  fputc(saveParametre->themeActuel, fichierParametre);
 }

 else 
 {
  printf("PROBLEME OUVERTURE FICHIER"); 	 
 }

 fclose(fichierParametre);
}

//-------------------------------------------------------------------------------------------------------------------------------

void chargementParametre(Parametre *loadParametre)
{
 
 FILE* fichierParametre=NULL;

 fichierParametre=fopen("configuration/parametre/parametre.conf", "r");
 
 if(fichierParametre!=NULL)
 {
  loadParametre->difficulteActuel = fgetc(fichierParametre);
  loadParametre->themeActuel = fgetc(fichierParametre);
 }

 else 
 {
  printf("PROBLEME OUVERTURE FICHIER"); 	 
 }

 fclose(fichierParametre);

}

//-------------------------------------------------------------------------------------------------------------------------------

int chargementMotMystere(char dico[], char loadMotMystere[])
{
 FILE *fichierDico=NULL;
 int selectionMot;
 int nombreMot=0;
 int caractereLu=0;
 char cheminDico[50]={""};
 int nombreCaractereMotMystere=0;

 //DEFINIT LE CHEMIN DU DICO A CHARGER
 sprintf(cheminDico, "configuration/dictionnaire/%s.txt",dico);

 //OUVERTURE FICHIER AVEC TEST
 fichierDico = fopen(cheminDico, "r");
 if(fichierDico == NULL)
 {
  printf("\nPROBLEME OUVERTURE FICHIER");
  exit(EXIT_FAILURE);
 }

 //COMPTE LE NOMBRE DE MOT DANS LE DICTIONNAIRE
 do
 {
  caractereLu = fgetc(fichierDico);
  if(caractereLu == '\n')
  {
   nombreMot++;
  }

 }while(caractereLu != EOF);	  
 
 //ON GENERE UN NOMBRE ALEATOIRE POUR SELECTIONNER UN MOT
 srand(time(NULL));
 selectionMot = (rand() % nombreMot); 
 
 //REMBOBINAGE DU CURSEUR SUR LE FICHIER ET ON LE POSITIONNE SUR LA BONNE LIGNE
 rewind(fichierDico);
 while(selectionMot>0)
 {
  caractereLu = fgetc(fichierDico);
  if(caractereLu == '\n')
  {
   selectionMot--; 
  }
 }

 //ON PIOCHE LE MOT DE LA LIGNE SELECTIONNEE
 fgets(loadMotMystere, 100, fichierDico);
 
 //ON CALCULE LA TAILLE DU MOT MYSTERE
 nombreCaractereMotMystere = strlen(loadMotMystere) - 1;

 //SUPPRESSION DU CARATERE RETOUR CHARIO DU MOT CHARGE
 loadMotMystere[nombreCaractereMotMystere] = '\0';

 fclose(fichierDico);
 return nombreCaractereMotMystere;
}
