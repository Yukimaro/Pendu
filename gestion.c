#include<stdio.h>
#include<stdlib.h>
#include "gestion.h"


void testOption(int *difficulteSelectionnee, int *themeSelectionnee)
{
  if(*difficulteSelectionnee>DIFFICILE)
  {
   *difficulteSelectionnee = FACILE;
  }
  else if(*difficulteSelectionnee<FACILE)
  {
   *difficulteSelectionnee = DIFFICILE;
  }

  if(*themeSelectionnee>DISNEY)
  {
   *themeSelectionnee = BASE;
  }
  else if(*themeSelectionnee<BASE)
  {
   *themeSelectionnee = DISNEY;
  }
}

//-------------------------------------------------------------------------------------------------------------------------------

void selectionTheme(const short selecTheme, char nameTheme[])
{
 char allTheme[][20]={"base", "manga", "informatique", "jeu", "graveleux", "disney"};
 int i=0, j=selecTheme;

 //ON AFFECTE LE NOM DU THEME A CHARGER
 do
 {
  nameTheme[i] = allTheme[j][i];
  i++;
 }while(allTheme[j][i]!='\0');
 nameTheme[i] = allTheme[j][i];
}

//-------------------------------------------------------------------------------------------------------------------------------

void initMotUtilisateur(char chaineAInit[], int longeurChaine)
{
 int i=0;

 while(i < longeurChaine)
 {
  chaineAInit[i] = '-';
  i++;
 }
 chaineAInit[i] = '\0';
}

//-------------------------------------------------------------------------------------------------------------------------------

_Bool testeLettre(char motMystere[], char lettreSaisie[], char motUser[], char lettreErronee[], int *j, int *tentativeRestante)
{
 int i=0;
 _Bool matchingLetter=0;

 //RECHERCHE LETTRE DANS LE MOT MYSSTERE
 while(motMystere[i] != '\0')
 {
  if(*lettreSaisie == motMystere[i])
  {
   motUser[i] = motMystere[i];
   matchingLetter = 1;
  }

  i++;
 }

 //SI PAS DE CORRESPONDANCE TROUVE ON DECREMENTE LE NOMBRE DE TENTATIVE
 if(!matchingLetter)
 {
  *tentativeRestante = *tentativeRestante - 1;
  lettreErronee[*j] = *lettreSaisie;
 }

 //REINITIALISATION DE LA LETTRE PROPOSE
 *lettreSaisie = '_';

 return matchingLetter;
}

//-------------------------------------------------------------------------------------------------------------------------------

int testeGameOver(_Bool *gagne, _Bool *perdu, char motMystere[], char motUser[], int nombreEssai)
{
 int i=0;
 _Bool matchingMot=1;

 //TESTE SI LE NOMBRE DE TENTATIVE EST ATTEINT
 if(nombreEssai == 0)
 {
  *perdu = 1;
  return 1;
 }

 //TESTE SI LE MOT UTILISATEUR CORRESPOND AU MOT MYSTERE
 while(motMystere[i] != '\0')
 {
  if(motUser[i] != motMystere[i])
  {
   matchingMot=0;
   break;
  }
  else
  {
   i++;
  }
 }
 if(matchingMot)
 {
  *gagne = 1;
  return 1;
 }

 //SI PAS GAGNE OU PERDU LA PARTIE CONTINUE EN RETOURNANT 0
 return 0;
}

