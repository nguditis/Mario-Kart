#ifndef ANGULAR_SPRITE__H
#define ANGULAR_SPRITE__H
#include <string>
#include "drawable.h"
#include <SDL.h>
#include "SDL_image.h"
#include <map>
class AI : public AngularSprite {
public:
  AI(const std::string&);
  AI(const AI&);

  virtual void draw() const {};
  virtual void draw(SDL_Renderer *renderer) const;
  virtual void update(Uint32 ticks) ;
  virtual void update(Uint32 ticks, int direction, float scale = 0.2f) ;
  //virtual void update(Uint32 ticks, const SDL_Renderer *renderer) ;

  virtual const Image* getImage() const {
    return image;
  }
  int getScaledWidth()  const {
    return getScale()*image->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*image->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return image->getSurface();
  }
  virtual bool checkVelocity(Uint32 ticks, int direction, float p_x, float p_y);
  bool CheckNewValue(int x, int y);

  float GrassVelocity(int x, int y);

protected:
  const Image * image;
  SDL_Surface *track;
  SDL_Surface *sky;
  SDL_Surface *grass;
  SDL_Surface *blocks;
  int worldWidth;
  int worldHeight;
  float fWorldX;// = 132.045f;
  float fWorldY;// = 547.693f;
  float fWorldA;// = 20.5f;
  float fNear;// = 0.95f;
  float fFar;// = -20.987f;
  float fFoVHalf = 3.14159f / 4.0f;
  AI& operator=(const AI&);
};
#endif
