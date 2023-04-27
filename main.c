#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> 
#include "head.h"

int main()
{
    int h, w;
    SDL_Surface *screen;
    SDL_Event event;
    int running = 1;
   
    int x,y;
    x=100;
    y=700;
    SDL_Rect player,enemy,enigme;
    player.x = 50;
    player.y = 650;
    enemy.x=300;
    enemy.y=650;
    enigme.x=800;
    enigme.y=650;
    w =1500;
    h = 1080;
    Personne p;
    p.x=player.x;
    p.y=player.y;
    p.w=80;
    p.h=130;
    int game_duration = 60;
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1) {
        printf("could not initialize SDL : %s.\n ", SDL_GetError());
        return -1;
    }
    
    TTF_Font* font = TTF_OpenFont("Economica-Bold.ttf", 24);
    screen = SDL_SetVideoMode(w,h, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    if (!screen) 
    {
        printf("could not set video mode: %s\n", SDL_GetError());
        return -1;
    }
    
    Uint32 start_time = SDL_GetTicks();
    init_background(screen, "MM_BackgroundBulled.jpg");
    SDL_Surface* mask = IMG_Load("MM_BackgroundBulled1.jpg");
    
    p.screen = IMG_Load("play.png");
    SDL_Surface* enem = IMG_Load("enem.png");
    SDL_Surface* enig = IMG_Load("enig.png");
    minimap m;
    
    init_map(&m, player);
    
    while (running) {
  
        afficheminimap(m, screen,player,enemy,enigme);
        
       
        
        animerMinimap(&m);
        SDL_BlitSurface(p.screen, NULL, screen, &player);
        SDL_BlitSurface(enem, NULL, screen, &enemy);
        SDL_BlitSurface(enig, NULL, screen, &enigme);
      
        
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        player.y = player.y+50;
                        y= y+(100);
                        printf("DOWN - x:%d y:%d\n", x, y);
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        player.y = player.y-50;
                        y =(y-100);
                        printf("UP - x:%d y:%d\n",x, y);
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        player.x =player.x+ 50;
                        x =(x+ 100);
                        printf("RIGHT - x:%d y:%d\n", x,y);
                    }
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        player.x = player.x-50;
                        x =x- (100);
                        printf("LEFT - x:%d y:%d\n",x, y);
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                    }
                    break;
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
        p.x=player.x;
        p.y=player.y;
         int collided = collisionPP(p,mask);
          printf("collision:%d",collided);
        
          
  Uint32 elapsed_time = SDL_GetTicks() - start_time;
  int remaining_time = game_duration - (elapsed_time / 1000);

  
  if (remaining_time <= 0) break;

  
  affichertemps(&remaining_time, screen, font);


  SDL_BlitSurface(p.screen, NULL, screen, &player);
  SDL_BlitSurface(enem, NULL, screen, &enemy);

  

  
  SDL_Flip(screen);

  
  SDL_Delay(1000/60);
  
}

  SDL_Quit();

  return 0;
}

