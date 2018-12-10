#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "BackGround.h"
#include "viewport.h"
#include "tracks.h"


class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

private:
  const RenderContext& rc;
  const IoMod& io;
  Clock& clock;
  SDL_Renderer * const renderer;
  Viewport& viewport;
    std::vector<Tracks> roads;
  std::vector<Drawable*> ground;
  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void printScales() const;
  void checkForCollisions();
  std::vector<std::string> people {"Mario", "Luigi","Peach","Bowser", "Koopa","Toad","DK","Yoshi"};
  std::vector<Tracks> Cup(int cup);

  int count = 0;

};
