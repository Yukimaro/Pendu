#ifndef GESTION_H
#define GESTION_H

#define TENTATIVE_MAX 10

typedef enum Difficulte Difficulte;

enum Difficulte
{
 FACILE, NORMAL, DIFFICILE
};

typedef enum Theme Theme;
enum Theme
{
 BASE, MANGA, INFORMATIQUE, JEU, GRAVELEUX, DISNEY
};

typedef struct Parametre Parametre;
struct Parametre
{
 Difficulte difficulteActuel;
 Theme themeActuel;
};


 void testOption(int *difficulteSelectionnee, int *themeSelectionnee);
 void selectionTheme(const short selecTheme, char nameTheme[]);
 void initMotUtilisateur(char chaineAInit[], int longeurChaine);
 _Bool testeLettre(char motMystere[], char *lettreSaisie, char motUser[], char lettreErronee[], int *j, int *tentativeRestante);
 int testeGameOver(_Bool *gagne, _Bool *perdu, char motMystere[], char motUser[], int nombreEssai);

#endif
