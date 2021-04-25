#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

void introduction(SDL_Surface *ecran)
{

 //DECLARATION DES SURFACES ET DE LEUR POSITION
 //DE LA GESTION D'EVENEMENT ET  D'UN BOOLÉEN (mise en pause programme)
 SDL_Surface *imageDeFond = NULL;
 SDL_Rect positionFond;
 SDL_Event event;
 _Bool continuer=1;

 //AFFECTATION DES POSITIONS X, Y DU FOND ECRAN ET DES BOUTONS SUR LA FENETRE
 //(l'originie des coordonnées x=0, y =0 est situé sur le coin haut gauche de la fenetre)
 positionFond.x=0;
 positionFond.y=0;

 //CHARGEMENT DE L'IMAGE DE FOND PAGE INTRODUCTION
 imageDeFond=SDL_LoadBMP("picture/fondEcran/introduction/IntroStudioLudo.bmp");

 //COLLAGE DE L'IMAGE PRECEDEMENT CHARGEE SUR L'ECRAN
 SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

 //AFFICHAGE DE LA FENETRE AVEC LES CHANGEMENTS EFFECTUÉS
 SDL_Flip(ecran);

 //BOUCLE ATTENDANT UN EVENEMENT PRESSION SUR ECHAP OU CLIC CROIX FENETRE
 //OU UN DELAI DE 3s
 while(continuer)
 {
  SDL_PollEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
        continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
              continuer=0;
              break;
	}
	break;
  }
  //LANCEMENT DUN TIMER DE TEMPS DE 3s
  if(SDL_GetTicks()==5000)
  {
   continuer=0;
  }
 }

 SDL_FreeSurface(imageDeFond);
}

//-------------------------------------------------------------------------------------------------------------------------------

int menu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black,_Bool *continuer)
{
 SDL_Surface *bouton[NOMBRE_BOUTON_MENU] = {NULL};
 SDL_Surface *texteSubtitle = NULL;
 SDL_Surface *vignettePendu = NULL;
 SDL_Rect positionBouton[NOMBRE_BOUTON_MENU];
 SDL_Rect positionVignettePendu;
 SDL_Event event;
 int clicBoutonUp=40, clicBoutonDown=40;
 int tailleBoutonX[NOMBRE_BOUTON_MENU]={104,84,93};
 int tailleBoutonY[NOMBRE_BOUTON_MENU]={32,32,32};
 _Bool pause=1;


 //CHARGEMENT SOUS-TITRE
 texteSubtitle = TTF_RenderText_Blended(policeSubtitle, "(MENU)", *black);

 //CHARGEMENT WALLPAPER PENDU
 vignettePendu = IMG_Load("picture/fondEcran/menu/pendu.png");

 //DEFINITION DES POSITIONS DES ELEMENTS
 positionBouton[JOUER].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[JOUER]/2));
 positionBouton[OPTION].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[OPTION]/2));
 positionBouton[QUITTER].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[QUITTER]/2));
 positionBouton[JOUER].y = positionSubtitle->y + texteSubtitle->h + 10;
 positionBouton[OPTION].y = positionBouton[JOUER].y + tailleBoutonY[JOUER] + 10;
 positionBouton[QUITTER].y = ecran->h - 200;
 positionVignettePendu.x = (ecran->w/2) - (vignettePendu->w/2);
 positionVignettePendu.y = positionSubtitle->y;

 //CHARGEMENT  WALLPAPER
 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,239, 216, 7));

 //BLIT LES SURFACES STATIQUES
 SDL_BlitSurface(title,NULL,ecran,positionTitle);
 SDL_BlitSurface(texteSubtitle,NULL,ecran,positionSubtitle);
 SDL_BlitSurface(vignettePendu,NULL,ecran,&positionVignettePendu);

 while(*continuer && pause)
 {
  //CHARGEMENT DU BOUTON ACTIF
  switch(clicBoutonDown)
  {
   case QUITTER:
	bouton[QUITTER]=IMG_Load("picture/bouton/boutonQuitter_Actif.png");
	break;
   case JOUER:
	bouton[JOUER]=IMG_Load("picture/bouton/boutonJouer_Actif.png");
	break;
   case OPTION:
	bouton[OPTION]=IMG_Load("picture/bouton/boutonOption_Actif.png");
	break;
   default:
	bouton[QUITTER]=IMG_Load("picture/bouton/boutonQuitter.png");
	bouton[JOUER]=IMG_Load("picture/bouton/boutonJouer.png");
	bouton[OPTION]=IMG_Load("picture/bouton/boutonOption.png");
	break;
  }

  //BLIT LES BOUTONS
  SDL_BlitSurface(bouton[QUITTER],NULL,ecran,&positionBouton[QUITTER]);
  SDL_BlitSurface(bouton[JOUER],NULL,ecran,&positionBouton[JOUER]);
  SDL_BlitSurface(bouton[OPTION],NULL,ecran,&positionBouton[OPTION]);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //BOUCLE BLOQUANTE/GESTION EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
	*continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      *continuer=0;
     	       break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         clicBoutonDown=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_MENU);
	 clicBoutonUp=40;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 clicBoutonUp=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_MENU);
	 clicBoutonDown=40;
	}
	break;
  }

  //TEST SELECTION MENU / CLIC RELACHE
  if(clicBoutonUp!=40)
  {
   pause=0;
  }

 }

 //LIBERATION MEMOIRE
 SDL_FreeSurface(bouton[QUITTER]);
 SDL_FreeSurface(bouton[JOUER]);
 SDL_FreeSurface(bouton[OPTION]);
 SDL_FreeSurface(texteSubtitle);
 SDL_FreeSurface(vignettePendu);

 return clicBoutonUp;
}

//-------------------------------------------------------------------------------------------------------------------------------

_Bool option(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, Parametre *parametre, _Bool *continuer)
{
 SDL_Surface *boutonSelection[NOMBRE_BOUTON_OPTION]={NULL};
 SDL_Surface *texteSubtitle=NULL;
 SDL_Surface *texteSelection[2]={NULL};
 SDL_Surface *texteChoixDifficulte=NULL;
 SDL_Surface *texteChoixTheme=NULL;
 SDL_Rect positionBoutonSelection[NOMBRE_BOUTON_OPTION];
 SDL_Rect positionTexteSelection[2];
 SDL_Rect positionChoixDifficulte;
 SDL_Rect positionChoixTheme;
 TTF_Font *policeIntitule=NULL, *policeOption=NULL;
 SDL_Event event;
 int selectionBouton=40;
 int tailleBoutonX[NOMBRE_BOUTON_OPTION]={103,110, 50, 50, 50, 50};
 int tailleBoutonY[NOMBRE_BOUTON_OPTION]={32, 32, 50, 50, 50, 50};
 int themeSelection=parametre->themeActuel;
 int difficulteSelection=parametre->difficulteActuel;
 _Bool pause=1, changement=0, clic=0, clicRelache=0;

 //PREPARATION POLICE/STYLE DES TITRES DE SELECTIONS
 policeIntitule = TTF_OpenFont("font/RioGrande Striped.ttf", 25);
 TTF_SetFontStyle(policeIntitule, TTF_STYLE_NORMAL);
 policeOption = TTF_OpenFont("font/arial.ttf", 18);
 TTF_SetFontStyle(policeOption, TTF_STYLE_BOLD);

 //CHARGEMENT SOUS-TITRE DE LA PAGE
 texteSubtitle = TTF_RenderText_Blended(policeSubtitle, "(OPTION)", *black);

 //CHARGEMENT DES INTITULES DES OPTIONS
 texteSelection[0] = TTF_RenderText_Blended(policeIntitule, "Difficulte", *black);
 texteSelection[1] = TTF_RenderText_Blended(policeIntitule, "Theme", *black);

 //INITIALISATION TEXTE DES OPTIONS
 texteChoixDifficulte = TTF_RenderText_Blended(policeOption, "NORMAL", *black);
 texteChoixTheme = TTF_RenderText_Blended(policeOption, "MANGA", *black);

 //CHARGEMENT DES BOUTONS PASSIFS
 boutonSelection[SELECTION_DIFFICULTE_L] = IMG_Load("picture/bouton/flecheSelectionGauche.png");
 boutonSelection[SELECTION_DIFFICULTE_R] = IMG_Load("picture/bouton/flecheSelectionDroite.png");
 boutonSelection[SELECTION_THEME_L] = IMG_Load("picture/bouton/flecheSelectionGauche.png");
 boutonSelection[SELECTION_THEME_R] = IMG_Load("picture/bouton/flecheSelectionDroite.png");
 boutonSelection[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");
 boutonSelection[VALIDER]=IMG_Load("picture/bouton/boutonValider.png");

 //POSITIONNEMENT DES NOUVEAUX ELEMENTS DE CETTE PAGE
 positionTexteSelection[0].x = (ecran->w/2) - (texteSelection[0]->w/2);
 positionChoixDifficulte.x = (ecran->w/2) - (texteChoixDifficulte->w/2);
 positionBoutonSelection[SELECTION_DIFFICULTE_L].x = positionTexteSelection[0].x - tailleBoutonX[SELECTION_DIFFICULTE_L];
 positionBoutonSelection[SELECTION_DIFFICULTE_R].x = positionTexteSelection[0].x + texteSelection[0]->w;
 positionTexteSelection[1].x = (ecran->w/2) - (texteSelection[1]->w/2);
 positionChoixTheme.x = (ecran->w/2) - (texteChoixTheme->w/2);
 positionBoutonSelection[SELECTION_THEME_L].x = positionBoutonSelection[SELECTION_DIFFICULTE_L].x;
 positionBoutonSelection[SELECTION_THEME_R].x = positionBoutonSelection[SELECTION_DIFFICULTE_R].x;
 positionBoutonSelection[RETOUR].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[RETOUR]/2));
 positionBoutonSelection[VALIDER].x = positionBoutonSelection[SELECTION_THEME_R].x + tailleBoutonX[SELECTION_THEME_R];
 positionTexteSelection[0].y = positionSubtitle->y;
 positionBoutonSelection[SELECTION_DIFFICULTE_L].y = positionTexteSelection[0].y + texteSelection[0]->h;
 positionBoutonSelection[SELECTION_DIFFICULTE_R].y = positionBoutonSelection[SELECTION_DIFFICULTE_L].y;
 positionChoixDifficulte.y = positionBoutonSelection[SELECTION_DIFFICULTE_L].y + (tailleBoutonY[SELECTION_DIFFICULTE_L]/2 - texteChoixDifficulte->h/2);
 positionTexteSelection[1].y = positionBoutonSelection[SELECTION_DIFFICULTE_L].y + tailleBoutonY[SELECTION_DIFFICULTE_L] + 20;
 positionBoutonSelection[SELECTION_THEME_L].y = positionTexteSelection[1].y + texteSelection[1]->h;
 positionBoutonSelection[SELECTION_THEME_R].y = positionBoutonSelection[SELECTION_THEME_L].y;
 positionChoixTheme.y = positionBoutonSelection[SELECTION_THEME_L].y + (tailleBoutonY[SELECTION_DIFFICULTE_L]/2 - texteChoixTheme->h/2);
 positionBoutonSelection[RETOUR].y = ecran->h - 200;
 positionBoutonSelection[VALIDER].y = positionBoutonSelection[SELECTION_THEME_R].y + tailleBoutonY[SELECTION_THEME_R];

 while(*continuer && pause)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case SELECTION_DIFFICULTE_L:
	 boutonSelection[SELECTION_DIFFICULTE_L]=IMG_Load("picture/bouton/flecheSelectionGauche_Actif.png");
	 difficulteSelection--;
	 break;
    case SELECTION_DIFFICULTE_R:
	 boutonSelection[SELECTION_DIFFICULTE_R]=IMG_Load("picture/bouton/flecheSelectionDroite_Actif.png");
	 difficulteSelection++;
	 break;
    case SELECTION_THEME_L:
	 boutonSelection[SELECTION_THEME_L]=IMG_Load("picture/bouton/flecheSelectionGauche_Actif.png");
	 themeSelection--;
	 break;
    case SELECTION_THEME_R:
	 boutonSelection[SELECTION_THEME_R]=IMG_Load("picture/bouton/flecheSelectionDroite_Actif.png");
	 themeSelection++;
	 break;
    case RETOUR:
	 boutonSelection[RETOUR]=IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
    case VALIDER:
	 boutonSelection[VALIDER]=IMG_Load("picture/bouton/boutonValider_Actif.png");
	 break;
   }
   clic=0;
  }

  //AJUSTE LE DEFILEMENT DES PARAMETRES
  testOption(&difficulteSelection, &themeSelection);

  //AFFICHE LA DIFFICULTE SELECTIONNEE
  switch(difficulteSelection)
  {
   case FACILE:
 	texteChoixDifficulte = TTF_RenderText_Blended(policeOption, "FACILE", *black);
	break;
   case NORMAL:
 	texteChoixDifficulte = TTF_RenderText_Blended(policeOption, "NORMAL", *black);
	break;
   case DIFFICILE:
 	texteChoixDifficulte = TTF_RenderText_Blended(policeOption, "DIFFICILE", *black);
	break;
  }

  //AFFICHE LE THEME SELECTIONNEE
  switch(themeSelection)
  {
   case BASE:
 	texteChoixTheme = TTF_RenderText_Blended(policeOption, "BASE", *black);
	break;
   case MANGA:
 	texteChoixTheme = TTF_RenderText_Blended(policeOption, "MANGA", *black);
	break;
   case INFORMATIQUE:
 	texteChoixTheme = TTF_RenderText_Blended(policeOption, "INFORMATIQUE", *black);
	break;
   case JEU:
	texteChoixTheme = TTF_RenderText_Blended(policeOption, "JEU VIDEO", *black);
	break;
   case GRAVELEUX:
    texteChoixTheme = TTF_RenderText_Blended(policeOption, "GRAVELEUX", *black);
    break;
   case DISNEY:
 	texteChoixTheme = TTF_RenderText_Blended(policeOption, "DISNEY", *black);
	break;
  }

  //CHARGEMENT  WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,239, 216, 7));

  //BLIT LES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(texteSubtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(texteSelection[0],NULL,ecran,&positionTexteSelection[0]);
  SDL_BlitSurface(texteSelection[1],NULL,ecran,&positionTexteSelection[1]);
  SDL_BlitSurface(boutonSelection[SELECTION_DIFFICULTE_L],NULL,ecran,&positionBoutonSelection[SELECTION_DIFFICULTE_L]);
  SDL_BlitSurface(boutonSelection[SELECTION_DIFFICULTE_R],NULL,ecran,&positionBoutonSelection[SELECTION_DIFFICULTE_R]);
  SDL_BlitSurface(boutonSelection[SELECTION_THEME_L],NULL,ecran,&positionBoutonSelection[SELECTION_THEME_L]);
  SDL_BlitSurface(boutonSelection[SELECTION_THEME_R],NULL,ecran,&positionBoutonSelection[SELECTION_THEME_R]);
  SDL_BlitSurface(boutonSelection[RETOUR],NULL,ecran,&positionBoutonSelection[RETOUR]);
  SDL_BlitSurface(boutonSelection[VALIDER],NULL,ecran,&positionBoutonSelection[VALIDER]);
  SDL_BlitSurface(texteChoixDifficulte,NULL,ecran,&positionChoixDifficulte);
  SDL_BlitSurface(texteChoixTheme,NULL,ecran,&positionChoixTheme);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
	*continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      pause=0;;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonSelection, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_OPTION);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBoutonSelection, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_OPTION);
	 clicRelache=1;
	}
	break;
  }

  //GESTION DES SELECTION / RELACHEMENT CLIC / RECHARGE BOUTON PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 pause = 0;
	 break;
    case VALIDER:
	 changement=1;
         parametre->difficulteActuel=difficulteSelection;
	 parametre->themeActuel=themeSelection;
	 break;
   }

   boutonSelection[SELECTION_DIFFICULTE_L] = IMG_Load("picture/bouton/flecheSelectionGauche.png");
   boutonSelection[SELECTION_DIFFICULTE_R] = IMG_Load("picture/bouton/flecheSelectionDroite.png");
   boutonSelection[SELECTION_THEME_L] = IMG_Load("picture/bouton/flecheSelectionGauche.png");
   boutonSelection[SELECTION_THEME_R] = IMG_Load("picture/bouton/flecheSelectionDroite.png");
   boutonSelection[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");
   boutonSelection[VALIDER]=IMG_Load("picture/bouton/boutonValider.png");
   clicRelache=0;
  }

 }

 //LIBERATION MEMOIRE
 TTF_CloseFont(policeIntitule);
 TTF_CloseFont(policeOption);

 SDL_FreeSurface(boutonSelection[SELECTION_DIFFICULTE_L]);
 SDL_FreeSurface(boutonSelection[SELECTION_DIFFICULTE_R]);
 SDL_FreeSurface(boutonSelection[SELECTION_THEME_L]);
 SDL_FreeSurface(boutonSelection[SELECTION_THEME_R]);
 SDL_FreeSurface(boutonSelection[RETOUR]);
 SDL_FreeSurface(boutonSelection[VALIDER]);
 SDL_FreeSurface(texteSubtitle);
 SDL_FreeSurface(texteSelection[0]);
 SDL_FreeSurface(texteSelection[1]);
 SDL_FreeSurface(texteChoixDifficulte);
 SDL_FreeSurface(texteChoixTheme);

 return changement;
}

//-------------------------------------------------------------------------------------------------------------------------------

void jeu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, char themePendu[], char motMystere[], char motUtilisateur[], _Bool *continuer)
{
 SDL_Surface *vignette= NULL;
 SDL_Surface *texteSubtitle = NULL;
 SDL_Surface *texteTheme = NULL;
 SDL_Surface *texteInstruction = NULL;
 SDL_Surface *texteMotCache = NULL;
 SDL_Surface *texteLettre = NULL;
 SDL_Surface *texteErreur = NULL;
 SDL_Surface *texteExergueErreur = NULL;
 SDL_Surface *texteTentative = NULL;
 SDL_Surface *bordure = NULL;
 SDL_Surface *bouton[NOMBRE_BOUTON_JEU] = {NULL};
 SDL_Rect positionVignette;
 SDL_Rect positionTentative;
 SDL_Rect positionBouton[NOMBRE_BOUTON_JEU];
 SDL_Rect positionTheme;
 SDL_Rect positionInstruction;
 SDL_Rect positionMotCache;
 SDL_Rect positionLettre;
 SDL_Rect positionErreur;
 SDL_Rect positionExergueErreur;
 SDL_Rect positionBordure;
 SDL_Event event;
 SDL_Color violet = {136, 0, 136};
 SDL_Color white = {255, 255, 255};
 SDL_Color red = {255, 0, 0};
 TTF_Font *policeTheme= NULL;
 TTF_Font *policeInstruction = NULL;
 TTF_Font *policeMotCache = NULL;
 TTF_Font *policeLettre = NULL;
 int tailleBoutonX[NOMBRE_BOUTON_JEU]={103, 56};
 int tailleBoutonY[NOMBRE_BOUTON_JEU]={32, 32};
 int selectionBouton=40, tentativeRestante=TENTATIVE_MAX;
 int selectLettre=0;
 char themeAffiche[25]={""};
 char essaiRestant[23]={""};
 char propositionLettre[]= "_";
 char cheminVignette[42]={""};
 char listeErreur[11]={""};
 _Bool pause=1, gameOver=0, clic=0, clicRelache=0, validerLettre=0, gagne=0, perdu=0;

 //CREATION BORDURE POUR LETTRE PROPOSE/DEFINITION COULEUR DE FOND
 bordure = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
 SDL_FillRect(bordure, NULL, SDL_MapRGB(ecran->format, 159, 148, 148));

 //CHARGEMENT POLICE/STYLES ET TEXTURE THEME
 policeTheme = TTF_OpenFont("font/cluisher.otf", 18);
 TTF_SetFontStyle(policeTheme, TTF_STYLE_BOLD);
 sprintf(themeAffiche, "theme : %s",themePendu);
 texteTheme = TTF_RenderText_Blended(policeTheme, themeAffiche, violet);

 //CHARGEMENT POLICE/STYLES ET TEXTURE INSTRUCTION
 policeInstruction = TTF_OpenFont("font/Inkfree.ttf", 20);
 TTF_SetFontStyle(policeInstruction, TTF_STYLE_NORMAL);
 texteInstruction = TTF_RenderText_Blended(policeInstruction, "Entrer une lettre et cliquer sur OK ou appuyer sur la touche ENTREE" , *black);

 //CHARGEMENT POLICE/STYLES ET TEXTURE MOTCACHE
 policeMotCache = TTF_OpenFont("font/CUBE.ttf", 50);
 TTF_SetFontStyle(policeMotCache, TTF_STYLE_NORMAL);
 texteMotCache = TTF_RenderText_Blended(policeMotCache, motUtilisateur, *black);

 //CHARGEMENT POLICE/STYLES PROPOSITION LETTRE
 policeLettre = TTF_OpenFont("font/arial.ttf", 25);
 TTF_SetFontStyle(policeLettre, TTF_STYLE_BOLD);

 //CHARGEMENT SOUS-TITRE DE LA PAGE
 texteSubtitle = TTF_RenderText_Blended(policeSubtitle, "(JEU)", *black);

 //CHARGEMENT VIGNETTE REGLE DU JEU
 vignette = IMG_Load("picture/fondEcran/jeu/regle.png");

 //CHARGEMENT DES BOUTONS PASSIFS
 bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");
 bouton[VALIDER] = IMG_Load("picture/bouton/boutonOk.png");

 //POSITIONNEMENT DES SURFACES
 positionVignette.x = (ecran->w/2) - (vignette->w/2);
 positionVignette.y = positionSubtitle->y;
 positionTentative.x = positionVignette.x;
 positionTentative.y = positionVignette.y;
 positionTheme.x = positionVignette.x;
 positionTheme.y = positionVignette.y + vignette->h + 5;
 positionInstruction.x = positionVignette.x;
 positionInstruction.y = positionTheme.y + texteTheme->h + 5;
 positionMotCache.x = positionVignette.x + ((vignette->w/2) - (texteMotCache->w/2));
 positionMotCache.y = positionInstruction.y + texteInstruction->h + 30;
 positionBordure.x = (ecran->w/2) - (bordure->w/2);
 positionBordure.y = positionMotCache.y + texteMotCache->h + 5;
 positionLettre.x = positionBordure.x + 3;
 positionLettre.y = positionBordure.y + 1;
 positionExergueErreur.x = positionVignette.x + vignette->w/2 + vignette->w/4 - 72;
 positionExergueErreur.y = positionVignette.y + vignette->h/4;
 positionErreur.x = positionExergueErreur.x;
 positionErreur.y = positionExergueErreur.y + 20;
 positionBouton[RETOUR].x = positionSubtitle->x + ((texteSubtitle->w/2)-(tailleBoutonX[RETOUR]/2));
 positionBouton[RETOUR].y = ecran->h - 200;
 positionBouton[VALIDER].x = positionBordure.x + bordure->w + 5;
 positionBouton[VALIDER].y = positionBordure.y;

 while(*continuer && pause && !gameOver)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
    case VALIDER:
	 bouton[VALIDER] = IMG_Load("picture/bouton/boutonOk_Actif.png");
	 break;
   }
   clic=0;
  }

  //CHARGEMENT TEXTURE PROPOSITION LETTRE
  texteLettre = TTF_RenderText_Blended(policeLettre, propositionLettre, *black);

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,239, 216, 7));

  //BLIT LES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(texteSubtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(vignette,NULL,ecran,&positionVignette);
  SDL_BlitSurface(texteTentative,NULL,ecran,&positionTentative);
  SDL_BlitSurface(bouton[RETOUR],NULL,ecran,&positionBouton[RETOUR]);
  SDL_BlitSurface(bouton[VALIDER],NULL,ecran,&positionBouton[VALIDER]);
  SDL_BlitSurface(texteTheme,NULL,ecran,&positionTheme);
  SDL_BlitSurface(texteInstruction,NULL,ecran,&positionInstruction);
  SDL_BlitSurface(texteMotCache,NULL,ecran,&positionMotCache);
  SDL_BlitSurface(bordure,NULL,ecran,&positionBordure);
  SDL_BlitSurface(texteLettre,NULL,ecran,&positionLettre);
  SDL_BlitSurface(texteExergueErreur,NULL,ecran,&positionExergueErreur);
  SDL_BlitSurface(texteErreur,NULL,ecran,&positionErreur);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
	*continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      pause=0;
     	      break;
	 case SDLK_KP_ENTER:
	      validerLettre=1;
	      break;
	 case SDLK_RETURN:
	      validerLettre=1;
	      break;
	 case SDLK_a:
	      *propositionLettre='Q';
	      break;
	 case SDLK_b:
	      *propositionLettre='B';
	      break;
	 case SDLK_c:
	      *propositionLettre='C';
	      break;
	 case SDLK_d:
	      *propositionLettre='D';
	      break;
	 case SDLK_e:
	      *propositionLettre='E';
	      break;
	 case SDLK_f:
	      *propositionLettre='F';
	      break;
	 case SDLK_g:
	      *propositionLettre='G';
	      break;
	 case SDLK_h:
	      *propositionLettre='H';
	      break;
	 case SDLK_i:
	      *propositionLettre='I';
	      break;
	 case SDLK_j:
	      *propositionLettre='J';
	      break;
	 case SDLK_k:
	      *propositionLettre='K';
	      break;
	 case SDLK_l:
	      *propositionLettre='L';
	      break;
	 case SDLK_SEMICOLON:
	      *propositionLettre='M';
	      break;
	 case SDLK_n:
	      *propositionLettre='N';
	      break;
	 case SDLK_o:
	      *propositionLettre='O';
	      break;
	 case SDLK_p:
	      *propositionLettre='P';
	      break;
	 case SDLK_q:
	      *propositionLettre='A';
	      break;
	 case SDLK_r:
	      *propositionLettre='R';
	      break;
	 case SDLK_s:
	      *propositionLettre='S';
	      break;
	 case SDLK_t:
	      *propositionLettre='T';
	      break;
	 case SDLK_u:
	      *propositionLettre='U';
	      break;
	 case SDLK_v:
	      *propositionLettre='V';
	      break;
	 case SDLK_w:
	      *propositionLettre='Z';
	      break;
	 case SDLK_x:
	      *propositionLettre='X';
	      break;
	 case SDLK_y:
	      *propositionLettre='Y';
	      break;
	 case SDLK_z:
	      *propositionLettre='W';
	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_JEU);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, positionBouton, tailleBoutonX, tailleBoutonY, NOMBRE_BOUTON_JEU);
 	 clicRelache=1;
	}
	break;
  }

  //GESTION DES SELECTION / RELACHEMENT CLIC / RECHARGE BOUTON PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 pause=0;
	 break;
    case VALIDER:
	 validerLettre=1;
	 break;
   }

   bouton[RETOUR] = IMG_Load("picture/bouton/boutonRetour.png");
   bouton[VALIDER] = IMG_Load("picture/bouton/boutonOk.png");
   clicRelache=0;
  }

  //SI UTILISATEUR CONFIRME LA LETTRE ON LA TESTE
  if(validerLettre)
  {
   //APPELLE FONCTION QUI TESTE LA LETTRE SAISIE
   if(!testeLettre(motMystere, propositionLettre, motUtilisateur, listeErreur, &selectLettre, &tentativeRestante))
   {
    //CHARGEMENT TEXTE DE LA MISE EN EXERGUE DES LETTRES ERREURS
    texteExergueErreur = TTF_RenderText_Blended(policeInstruction, "LISTE ERREUR", white);

    //ACTUALISATION AFFICHAGE DES LETTRES ERRONEES
    texteErreur = TTF_RenderText_Blended(policeLettre, listeErreur, red);

    //ACTUALISATION AFFICHAGE PENDU
    sprintf(cheminVignette, "picture/fondEcran/jeu/vignettePendu%d.png", tentativeRestante);
    vignette = IMG_Load(cheminVignette);

    //ACTUALISATION AFFICHAGE NOMBRE DE TENTATIVE RESTANT
    sprintf(essaiRestant, "tentative restante: %d", tentativeRestante);
    texteTentative = TTF_RenderText_Blended(policeLettre, essaiRestant, *black);

    selectLettre++;
   }

   //APPELLE FONCTION TESTANT SI LE JOUEUR A PERDU OU GAGNE
   gameOver = testeGameOver(&gagne, &perdu, motMystere, motUtilisateur, tentativeRestante);

   //ACTUALISATION MOT UTILISATEUR A AFFICHER
   texteMotCache = TTF_RenderText_Blended(policeMotCache, motUtilisateur, *black);
   validerLettre = 0;
  }

 }

 //AFFICHE LE RESULTAT DU JEU SI GAMEOVER
 if(gameOver)
 {
  afficherResultat(ecran, title, texteSubtitle, vignette, positionTitle, positionSubtitle, &positionVignette,  &gagne, &perdu, continuer);
 }

 //LIBERATION POLICES
 TTF_CloseFont(policeTheme);
 TTF_CloseFont(policeInstruction);
 TTF_CloseFont(policeMotCache);
 TTF_CloseFont(policeLettre);

 //LIBERATION DES SURFACES
 SDL_FreeSurface(vignette);
 SDL_FreeSurface(texteTentative);
 SDL_FreeSurface(texteTheme);
 SDL_FreeSurface(texteInstruction);
 SDL_FreeSurface(texteMotCache);
 SDL_FreeSurface(texteLettre);
 SDL_FreeSurface(texteExergueErreur);
 SDL_FreeSurface(texteErreur);
 SDL_FreeSurface(texteSubtitle);
 SDL_FreeSurface(bordure);
 SDL_FreeSurface(bouton[RETOUR]);
 SDL_FreeSurface(bouton[VALIDER]);
}

//-------------------------------------------------------------------------------------------------------------------------------

void afficherResultat(SDL_Surface *ecran, SDL_Surface *title, SDL_Surface *subtitle, SDL_Surface *vignette, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, SDL_Rect *positionVignette, _Bool *gagne, _Bool *perdu, _Bool *continuer)
{
 SDL_Surface *boutonRetour = NULL;
 SDL_Surface *texteResultat = NULL;
 SDL_Rect positionBoutonRetour;
 SDL_Rect positionResultat;
 SDL_Color red = {255, 0, 0};
 TTF_Font *policeResultat = NULL;
 SDL_Event event;
 int selectionBouton=40;
 _Bool clic=0, clicRelache=0, pause=1;

 //CHARGEMENT POLICE/STYLES ET TEXTURE RESULTAT
 policeResultat = TTF_OpenFont("font/GAMERIA.ttf", 60);
 TTF_SetFontStyle(policeResultat, TTF_STYLE_NORMAL);
 if(*gagne)
 {
  texteResultat = TTF_RenderText_Blended(policeResultat, "gagne", red);
 }
 else if(*perdu)
 {
  texteResultat = TTF_RenderText_Blended(policeResultat, "perdu", red);
 }

 //CHARGEMENT IMAGE BOUTON PASSIF
 boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");

 //POSITIONNEMENT SURFACES
 positionResultat.x = positionVignette->x + vignette->w/2 - texteResultat->w/2;
 positionResultat.y = positionVignette->y + vignette->h/2 - texteResultat->h/2;
 positionBoutonRetour.x = positionSubtitle->x + ((subtitle->w/2)-(boutonRetour->w/2));
 positionBoutonRetour.y = ecran->h - 200;

 while(*continuer && pause)
 {
  //CHARGEMENT BOUTON ACTIF
  if(clic)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 boutonRetour = IMG_Load("picture/bouton/boutonRetour_Actif.png");
	 break;
   }
   clic=0;
  }

  //CHARGEMENT WALLPAPER
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,239, 216, 7));

  //BLIT LES SURFACES
  SDL_BlitSurface(title,NULL,ecran,positionTitle);
  SDL_BlitSurface(subtitle,NULL,ecran,positionSubtitle);
  SDL_BlitSurface(boutonRetour,NULL,ecran,&positionBoutonRetour);
  SDL_BlitSurface(vignette,NULL,ecran,positionVignette);
  SDL_BlitSurface(texteResultat,NULL,ecran,&positionResultat);

  //RAFRAICHISSEMENT ECRAN
  SDL_Flip(ecran);

  //TEST EVENEMENT UTILISATEUR
  SDL_WaitEvent(&event);
  switch(event.type)
  {
   case SDL_QUIT:
	*continuer=0;
	break;
   case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	 case SDLK_ESCAPE:
	      pause=0;;
     	      break;
	}
	break;
   case SDL_MOUSEBUTTONDOWN:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
         selectionBouton=testClicBouton(event.button.x, event.button.y, &positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clic=1;
	}
	break;
   case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{
	 selectionBouton=testClicBouton(event.button.x, event.button.y, &positionBoutonRetour, &(boutonRetour->w), &(boutonRetour->h), 1);
	 clicRelache=1;
	}
	break;
  }

  //LORS DU RELACHEMENT CLIC GESTION DU BOUTON RETOUR / RECHARGE IMAGE BOUTON EN PASSIF
  if(clicRelache)
  {
   switch(selectionBouton)
   {
    case RETOUR:
	 pause = 0;
	 break;
   }

   boutonRetour = IMG_Load("picture/bouton/boutonRetour.png");
   clicRelache = 0;
  }

 }

 //LIBERATION POLICES
 TTF_CloseFont(policeResultat);

 //LIBERATION DES SURFACES
 SDL_FreeSurface(boutonRetour);
 SDL_FreeSurface(texteResultat);
}

//-------------------------------------------------------------------------------------------------------------------------------

int testClicBouton(int positionSourisX, int positionSourisY, SDL_Rect positionBouton[], int tailleBoutonX[],int tailleBoutonY[], int nbBouton)
{
 int i;

 //TEST SI IL Y A CLIC SUR BOUTON
 for(i=0; i<nbBouton; i++)
 {
  //TEST SI IL Y A CLIC SUR UN BOUTON EN X
  if((positionSourisX>=positionBouton[i].x) && (positionSourisX<=(positionBouton[i].x+tailleBoutonX[i])))
  {
   //TEST SI IL Y A CLIC SUR UN BOUTON EN Y
   if((positionSourisY>=positionBouton[i].y) && (positionSourisY<=(positionBouton[i].y+tailleBoutonY[i])))
   {
    //SI LE CURSEUR EST SUR UN BOUTON RETOURNE LE NUMERO DU BOUTON
    return i;
   }
  }
 }
 //SI AUNCUN CLIC BOUTON REMET A 40
 return 40;
}
