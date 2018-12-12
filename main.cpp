// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"
#include "tracks.h"
#include <iostream>
#include <SDL.h>
#include "ioMod.h"

// To run this demo you will need to install SDL2_mixer
// Notice the flag in the Makefile, which you also must add

const int WIDTH = 800;
const int HEIGHT = 800;
const int DELAY = 1000;

SDL_Window* initWindow( ) {
	SDL_Window* window = 
    SDL_CreateWindow( "Mario Kart Menu ", SDL_WINDOWPOS_CENTERED, 
       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    throw (std::string("Couldn't make a window: ")+SDL_GetError());
  }
  return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) {
  SDL_Renderer* renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if ( renderer == NULL ) throw std::string("No Renderer");
  return renderer;
}

void draw() {
SDL_RenderClear(RenderContext::getInstance().getRenderer());
  IoMod::getInstance().writeText("Mario Kart Track Select", 200, 50);
  IoMod::getInstance().writeText("A. Mushroom", 50, 160);
  IoMod::getInstance().writeText("B. Flower", 50, 185);
  IoMod::getInstance().writeText("C. Star", 50, 210);
  IoMod::getInstance().writeText("D. Special", 50, 235);
}

void drawSubMenu(int selection)
{
  SDL_RenderClear(RenderContext::getInstance().getRenderer());
  if(selection == 1)
  {
  	IoMod::getInstance().writeText("1. Mario Circut 1", 50, 160);
  	IoMod::getInstance().writeText("2. Donut Plains 1", 50, 185);
  	IoMod::getInstance().writeText("3. Ghost Valley 1", 50, 210);
  	IoMod::getInstance().writeText("4. Bowser Castle 1", 50, 235);
  	IoMod::getInstance().writeText("5. Mario Circut 2", 50, 260);
  	
  }
  else if (selection == 2)
  {
  	IoMod::getInstance().writeText("1. Choco Island 1", 50, 160);
  	IoMod::getInstance().writeText("2. Ghost Valley 2", 50, 185);
  	IoMod::getInstance().writeText("3. Donut Plains 2", 50, 210);
  	IoMod::getInstance().writeText("4. Bowser Castle 2", 50, 235);
  	IoMod::getInstance().writeText("5. Mario Circut 3", 50, 260);
  }
  if(selection == 3)
  {
  	IoMod::getInstance().writeText("1. Koopa Beach 1", 50, 160);
  	IoMod::getInstance().writeText("2. Choco Island 2", 50, 185);
  	IoMod::getInstance().writeText("3. Vanilla Lake 1", 50, 210);
  	IoMod::getInstance().writeText("4. Bowser Castle 3", 50, 235);
  	IoMod::getInstance().writeText("5. Mario Circut 4", 50, 260);
  }
  else if (selection == 4)
  {
  	IoMod::getInstance().writeText("1. Donut Plains 3", 50, 160);
  	IoMod::getInstance().writeText("2. Koopa Beach 2", 50, 185);
  	IoMod::getInstance().writeText("3. Ghost Valley 3", 50, 210);
  	IoMod::getInstance().writeText("4. Vanilla Lake 2", 50, 235);
  	IoMod::getInstance().writeText("5. Rainbow Road", 50, 260);
  }
}

int main( ) {
	int selection = 1;
    int sub_selection = 1;
  try {
	  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		  throw (std::string("Could not init SDL: ") + SDL_GetError());
	  }
	const RenderContext& rc = RenderContext::getInstance();
    SDL_Renderer* renderer = rc.getRenderer();

    // Paint the screen teal:
    //SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    //if ( SDL_RenderClear(renderer) ) {
    //  throw std::string("oops,coudln't clear screen to Teal!");
    //}
    
    bool menu = false;
    SDL_Event event;
    const Uint8* keystate;
    bool done = false;
    while ( !done ) {
      while ( SDL_PollEvent(&event) ) {
        keystate = SDL_GetKeyboardState(NULL);
        if (event.type ==  SDL_QUIT) { done = true; break; }
        if(event.type == SDL_KEYDOWN) {
          if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
            done = true;
            break;
          }
          if ( !menu && keystate[SDL_SCANCODE_A] ) {
          	menu = true;
            selection = 1;
            break;       

          }
          if ( !menu && keystate[SDL_SCANCODE_B] ) {
            menu = true;
            selection = 2;
            break;
          }
          if ( !menu && keystate[SDL_SCANCODE_C] ) {
            menu = true;
            selection = 3;
            break;
          }
          if (!menu &&  keystate[SDL_SCANCODE_D] ) {
            menu = true;
            selection = 4;
            break;
          }

          if ( menu && keystate[SDL_SCANCODE_1] ) {
            sub_selection = 1;
            done = true;
            break;
          }
          if ( menu && keystate[SDL_SCANCODE_2] ) {
            sub_selection = 2;
            done = true;
            break;
          }
          if (menu &&  keystate[SDL_SCANCODE_3] ) {
            sub_selection = 3;
            done = true;
            break;
          }
          if (menu &&  keystate[SDL_SCANCODE_4] ) {
           sub_selection = 4;
           done = true;
           break;
          }
          if (menu &&  keystate[SDL_SCANCODE_5] ) {
            sub_selection = 5;
            done = true;
            break;
          }
        }
      }
      if(!menu)
      	draw();
      if(menu)
      	drawSubMenu(selection);
      SDL_RenderPresent(renderer);
}

    std::vector<Tracks> Mushroom {
        Tracks("Mario_Circut_1"),
        Tracks("Donut_Plains_1"),
        Tracks("Ghost_Valley_1"),
        Tracks("Bowser_Castle_1"),
        Tracks("Mario_Circut_2")};
    
    std::vector<Tracks> Flower {
        Tracks("Choco_Island_1"),
        Tracks("Ghost_Valley_2"),
        Tracks("Donut_Plains_2"),
        Tracks("Bowser_Castle_2"),
        Tracks("Mario_Circut_3")};
    
    std::vector<Tracks> Star {
        Tracks("Koopa_Beach_1"),
        Tracks("Choco_Island_2"),
        Tracks("Vanilla_Lake_1"),
        Tracks("Bowser_Castle_3"),
        Tracks("Mario_Circut_4")};
    
    std::vector<Tracks> Special {
        Tracks("Donut_Plains_3"),
        Tracks("Koopa_Beach_2"),
        Tracks("Ghost_Valley_3"),
        Tracks("Vanilla_Lake_2"),
        Tracks("Rainbow_Road")};
    
    std::vector<std::vector<Tracks>> Cups {Mushroom, Flower, Star, Special};
    
    
      Engine *engine = new Engine(Cups[selection-1], sub_selection-1);

      engine->play();
}
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }

   return 0;
}
