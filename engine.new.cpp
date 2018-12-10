#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "AngularSprite.h"
#include "player.h"

Engine::~Engine() {
  for(auto track: ground)
	delete track;
  std::cout << "Terminating program" << std::endl;
}
Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  viewport( Viewport::getInstance() ),
  ground({new AngularSprite("road"), new Player("Mario")}),
  //pixels(std::vector< unsigned char > ( Viewport::getInstance().getWidth() * Viewport::getInstance().getHeight() * 4, 0 )),
  makeVideo( false)
{
  Viewport::getInstance().setObjectToTrack(ground[0]);
  std::cout << "Loading complete" << std::endl;
  int count = 0;
}

void Engine::draw() const {
  //for(auto track: ground)
  ground[0]->draw(renderer);
  ground[1]->setScale(6);

  ground[1]->draw();

  int fps = 0;
  std::stringstream ss;

  std::string name = "Varsha and Nathan";
  fps = clock.getFps();
  ss << "Current FPS: " << fps;

  //std::cout<<"drawing engine"<<std::endl;
  SDL_Color color = {255,0,0,255};
  IoMod::getInstance().writeText(ss.str(), 10, 50);
  IoMod::getInstance().writeText(name, 10, viewport.getHeight()-30, color); //overloaded function

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  //std::cerr << "called engine update" << std::endl;

  //ground[1]-> update(ticks);
   // viewport.update(); // always update viewport last
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDL_SCANCODE_C]) {
          //printf("count is %d\n", count);
          count = count%7;
          //printf("count is %d\n", count);
          ground[1] = new Player(people[count]);
          count = (count+1)%7;
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
      
      ticks = clock.getElapsedTicks();
      if ( ticks > 0 ) {
        clock.incrFrame();
        int p_x = static_cast<Player*>(ground[1])->getX();
        int p_y = static_cast<Player*>(ground[1])->getY();
        //float velocity = static_cast<AngularSprite*>(ground[0])->GrassVelocity(p_x,p_y);
        
        if (keystate[SDL_SCANCODE_W]) {
          static_cast<AngularSprite*>[ground[0]]->update(ticks, 4, p_x, p_y);
            
        }
        if (keystate[SDL_SCANCODE_S]) {
          static_cast<AngularSprite*>[ground[0]]->update(ticks, 3, p_x, p_y);
            
        }

        ////// "snap back" to forward sprite
      if (!keystate[SDL_SCANCODE_D]) {
        static_cast<Player*>(ground[1])->up();
      }
      if (!keystate[SDL_SCANCODE_A]) {
        static_cast<Player*>(ground[1])->up();
      }
        /////


      if (keystate[SDL_SCANCODE_D]) {
          bool right = static_cast<AngularSprite*>[ground[0]]->update(ticks, 2, p_x, p_y);
          if (right) {
              static_cast<Player*>(ground[1])->right(ticks);
          }
      }
      if (keystate[SDL_SCANCODE_A]) {
          bool left = static_cast<AngularSprite*>[ground[0]]->update(ticks, 1, p_x, p_y);
          if (left) {
              static_cast<Player*>(ground[1])->left(ticks);
          }
      }
      draw();
      update(ticks);
          if ( makeVideo ) {
              frameGen.makeFrame();
              
         }
      }
   }
}
