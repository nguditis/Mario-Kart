#ifndef ANGULAR_SPRITE__H
#define ANGULAR_SPRITE__H
#include <string>
#include "drawable.h"
#include <SDL.h>
#include "SDL_image.h"
#include <map>
class AngularSprite : public Drawable {
public:
  AngularSprite(const std::string&);
  AngularSprite(const AngularSprite&);

  virtual void draw() const {};
  virtual void draw(SDL_Renderer *renderer) const;
  virtual void update(Uint32 ticks) ;
  virtual void update(Uint32 ticks, int direction) ;
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
  
protected:
  const Image * image;
  SDL_Surface *surface1;
  SDL_Surface *surface2;
  int worldWidth;
  int worldHeight;
  float fWorldX = 132.045f;
  float fWorldY = 547.693f;
  float fWorldA = 20.5f;
  float fNear = 0.95f;
  float fFar = -20.987f;
  float fFoVHalf = 3.14159f / 4.0f;
  AngularSprite& operator=(const AngularSprite&);
};
#endif
