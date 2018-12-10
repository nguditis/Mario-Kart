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



int currentCourse;


Engine::~Engine() {
  for(auto track: ground)
	delete track;
  std::cout << "Terminating program" << std::endl;
}
Engine::Engine() :
  currentCourse(0),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  viewport( Viewport::getInstance() ),
  roads({Tracks("Mario_Circut_1")}),
  ground({new AngularSprite("road", roads[0] ), new Player("Mario")}),
  makeVideo( false)
{
  
  Viewport::getInstance().setObjectToTrack(ground[0]);
  std::cout << "Loading complete" << std::endl;
  int count = 0;

}

Engine::Engine(std::vector<Tracks> t, int c) :
currentCourse(c),
rc( RenderContext::getInstance() ),
io( IoMod::getInstance() ),
clock( Clock::getInstance() ),
renderer( rc.getRenderer() ),
viewport( Viewport::getInstance() ),
roads(t),
ground({new AngularSprite("road", roads[c] ), new Player("Mario")}),
makeVideo( false)
{
    Viewport::getInstance().setObjectToTrack(ground[0]);
    //std::cout << "Loading complete" << std::endl;
    int count = 0;
    int currentCourse = c;
    //std::cout << "currentCourse is " << currentCourse << std::endl;
    //std::cout << "The current course is " << roads[currentCourse].getName() << std::endl;

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
        float velocity;
        //std::cout << "The current course is " << roads[currentCourse].getName() << std::endl;
        if (roads[currentCourse].getGrass() != nullptr && roads[currentCourse].getDirt() == nullptr) {

            velocity = static_cast<AngularSprite*>(ground[0])->GrassVelocity(p_x,p_y,roads[currentCourse].getGrass());
        }
        else if (roads[currentCourse].getDirt() != nullptr && roads[currentCourse].getGrass() != nullptr) {
            velocity = static_cast<AngularSprite*>(ground[0])->GrassVelocity(p_x,p_y,roads[currentCourse].getDirt());
        }
        else if (roads[currentCourse].getDarkWater() != nullptr) {
            velocity = static_cast<AngularSprite*>(ground[0])->GrassVelocity(p_x,p_y,roads[currentCourse].getDarkWater());
        }
        else if (roads[currentCourse].getEmpty() != nullptr) {
            velocity = static_cast<AngularSprite*>(ground[0])->GrassVelocity(p_x,p_y,roads[currentCourse].getEmpty());
        }
        else {
            velocity = 0.5f;
        }
      //std::cout<<velocity<<std::endl;
      if (keystate[SDL_SCANCODE_W]) {
        if(static_cast<AngularSprite*>(ground[0])->checkVelocity(ticks, 4, p_x, p_y,velocity))
        {
          static_cast<AngularSprite*>(ground[0])->update(10,4,velocity);
        }
      }
      if (keystate[SDL_SCANCODE_S]) {
        if(static_cast<AngularSprite*>(ground[0])->checkVelocity(ticks, 3, p_x, p_y,velocity))
        {
          static_cast<AngularSprite*>(ground[0])->update(10,3,velocity);
        }
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
        if(static_cast<AngularSprite*>(ground[0])->checkVelocity(ticks, 2, p_x, p_y,velocity))
        {
            static_cast<Player*>(ground[1])->right(ticks);
            static_cast<AngularSprite*>(ground[0])->update(10,2,velocity);
        }
      }
      if (keystate[SDL_SCANCODE_A]) {
        if(static_cast<AngularSprite*>(ground[0])->checkVelocity(ticks, 1, p_x, p_y,velocity))
        {
          static_cast<Player*>(ground[1])->left(ticks);
        //static_cast<Player*>(player)->down();
         static_cast<AngularSprite*>(ground[0])->update(10,1,velocity);
        }

      }
      if (keystate[SDL_SCANCODE_Y]) {
        //static_cast<Player*>(player)->down();
        static_cast<AngularSprite*>(ground[0])->update(10,5);

      }
      if (keystate[SDL_SCANCODE_H]) {
        //static_cast<Player*>(player)->down();
        static_cast<AngularSprite*>(ground[0])->update(10,6);

      }
        if (keystate[SDL_SCANCODE_U]) {
            //static_cast<Player*>(player)->down();
            static_cast<AngularSprite*>(ground[0])->update(10,7);

        }
        if (keystate[SDL_SCANCODE_J]) {
            //static_cast<Player*>(player)->down();
            static_cast<AngularSprite*>(ground[0])->update(10,8);

        }
        if (keystate[SDL_SCANCODE_I]) {
            //static_cast<Player*>(player)->down();
            static_cast<AngularSprite*>(ground[0])->update(10,9);

        }
        if (keystate[SDL_SCANCODE_K]) {
            //static_cast<Player*>(player)->down();
            static_cast<AngularSprite*>(ground[0])->update(10,10);

        }
       draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
