#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> 
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "head.h"
#include <stdbool.h>



void init_background(SDL_Surface* screen, const char* filename)
{
    
    SDL_Surface* background = IMG_Load(filename);
    if (background == NULL) {
        fprintf(stderr, "Error loading background image: %s\n", IMG_GetError());
        exit(1);
    }
    
  
    
    if (SDL_BlitSurface(background, NULL, screen, NULL) != 0) {
        fprintf(stderr, "Error blitting background image: %s\n", SDL_GetError());
        exit(1);
    }
    
    
    SDL_FreeSurface(background);
    
}


void init_map(minimap* m, SDL_Rect player)
{
    
    m->img = IMG_Load("minimap3.jpg");
    if (!m->img) {
        printf("Error: Failed to load minimap image: %s\n", SDL_GetError());
        exit(1);
    }
    
    
    m->plyr = IMG_Load("player.png");
    m->pos_plyr.x = 0;
    m->pos_plyr.y = 0;
    
    
    m->enm = IMG_Load("enemy.png");
    
    
    m->enig = IMG_Load("enig2.png");
    
    
    m->pos_img.w = 89; 
    m->pos_img.h = 233;
    m->pos_img.x = 0;
    m->pos_img.y = 0;
    m->lastUpdate=0;
    m->frame=0;
    // Set the player and enemy positions 
    //m->pos_plyr.x = (357 - m->pos_img.w) + 20;
    //m->pos_plyr.y = m->pos_img.h - 70;
    //m->pos_enm.x = 600;
    //m->pos_enm.y = 300;
    //m->pos_enig.x = 500;
    //m->pos_enig.y = 300;
}

void afficheminimap(minimap m, SDL_Surface* screen, SDL_Rect player_pos, SDL_Rect enm_pos, SDL_Rect enig_pos)
{
   
    m.pos_plyr.x = (player_pos.x / 10) + 8;
    m.pos_plyr.y = (player_pos.y / 10);
    m.pos_enm.x = (enm_pos.x / 10) + 8;
    m.pos_enm.y = (enm_pos.y / 10);
    m.pos_enig.x = (enig_pos.x / 10) + 8;
    m.pos_enig.y = (enig_pos.y / 10);

    
    SDL_BlitSurface(m.img, NULL, screen, &m.pos_img);
    SDL_BlitSurface(m.plyr, NULL, screen, &m.pos_plyr);
    SDL_BlitSurface(m.enm, NULL, screen, &m.pos_enm);
    SDL_BlitSurface(m.enig, NULL, screen, &m.pos_enig);
}




void affichertemps(int* temps, SDL_Surface* screen, TTF_Font* font)
{
    
    char time_str[32];
    sprintf(time_str, "Remaining Time: %d", *temps);

    SDL_Color text_color = {255, 255, 255}; // white text
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, time_str, text_color);

 
    SDL_Rect text_position = {0, 0, 0, 0}; 
    SDL_BlitSurface(text_surface, NULL, screen, &text_position);

    SDL_FreeSurface(text_surface);
}


void animerMinimap(minimap *m)
{
	 
         SDL_Surface* frames[2];
    frames[0] = IMG_Load("enig1.png");
    frames[1] = IMG_Load("enig2.png");

    Uint32 current_time = SDL_GetTicks();
    int span =current_time-m->lastUpdate;
    int seconds =1; 
  
    if (span>1000*seconds)
     {
     	printf("\ncurrent frame at (%d): %d",current_time,m->frame);
       if(m->frame==0)
       {
       	m->frame=1;
       	printf("smol");
       }
        else if(m->frame==1)
       {
       	m->frame=0;
       
       }
       m->lastUpdate =  current_time;
    }
    printf("\nframe (%d)",current_time);
    m->enig = frames[m->frame];
}

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
SDL_Color color;
Uint32 col=0;

char* pPosition=(char*)pSurface->pixels;
pPosition+=(pSurface->pitch * y);
pPosition+=(pSurface->format->BytesPerPixel * x);
memcpy(&col,pPosition,pSurface->format->BytesPerPixel);
SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
return(color);
}


int collisionPP(Personne p,SDL_Surface *collision_surface) 
{
    SDL_Color color;
    Uint32 col;

    
    for (int y = p.y; y < p.y + p.h; y++) {
        for (int x = p.x; x < p.x + p.w; x++) {
            
            color = GetPixel(collision_surface, x, y);

            
            if (color.r == 0 && color.g == 0 && color.b == 0) {
                return 1;
            }
        }
    }

    return 0;
}






