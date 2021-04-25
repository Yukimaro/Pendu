
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "gestion.h"

#define NOMBRE_BOUTON_MENU 3
#define NOMBRE_BOUTON_OPTION 6
#define NOMBRE_BOUTON_JEU 2
#define QUITTER 0
#define JOUER 1
#define OPTION 2
#define RETOUR 0
#define VALIDER 1
#define SELECTION_DIFFICULTE_L 2
#define SELECTION_DIFFICULTE_R 3
#define SELECTION_THEME_L 4
#define SELECTION_THEME_R 5


void introduction(SDL_Surface *ecran);
int menu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, _Bool *continuer);
_Bool option(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, Parametre *parametre, _Bool *continuer);
void jeu(SDL_Surface *ecran, SDL_Surface *title, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, TTF_Font *policeSubtitle, SDL_Color *black, char themePendu[], char motMystere[], char motUtilisateur[], _Bool *continuer);
void afficherResultat(SDL_Surface *ecran, SDL_Surface *title, SDL_Surface *subtitle, SDL_Surface *vignette, SDL_Rect *positionTitle, SDL_Rect *positionSubtitle, SDL_Rect *positionVignette, _Bool *gagne, _Bool *perdu, _Bool *continuer);
int testClicBouton(int positionSourisX, int positionSourisY, SDL_Rect positionBouton[], int tailleBoutonX[],int tailleBoutonY[], int nbBouton);
#endif
