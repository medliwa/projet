#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct 
{
    SDL_Surface* img;
    SDL_Surface* plyr;
    SDL_Surface* enm;
    SDL_Surface* enig;
    SDL_Rect pos_img;
    
    SDL_Rect pos_plyr;
    SDL_Rect pos_enm;
    SDL_Rect pos_enig;
    Uint32 lastUpdate;
    
    int frame;
} minimap;
typedef struct{
    SDL_Surface* screen;
    int x, y;       
    int w, h;  
    
} Personne;
typedef struct
{
SDL_Surface* mask;
SDL_Rect pos;
}masque;



void init_map(minimap* m, SDL_Rect player);
void afficheminimap(minimap m, SDL_Surface* screen, SDL_Rect player_pos,SDL_Rect enm_pos,SDL_Rect enig_pos);
void animerMinimap(minimap *m);
void init_background(SDL_Surface* screen, const char* filename);
void affichertemps(int* temps, SDL_Surface* screen, TTF_Font* font);
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int collisionPP(Personne p, SDL_Surface* mask);




#endif
