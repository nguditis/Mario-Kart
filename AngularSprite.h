#ifndef ANGULAR_SPRITE__H
#define ANGULAR_SPRITE__H
#include <string>
#include "drawable.h"
#include <SDL.h>
#include "SDL_image.h"
#include "FrustumPoints.h"
#include <map>
#include "tracks.h"
#include <map>
class AngularSprite : public Drawable {
public:
    AngularSprite(const std::string&);
    AngularSprite(const std::string&,  Tracks&);
    AngularSprite(const AngularSprite&);
  virtual void draw() const {};
  virtual void draw(SDL_Renderer *renderer) const;
  virtual void update(Uint32 ticks) ;
  virtual void update(Uint32 ticks, int direction, float factor = 0.2f) ;
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
  virtual bool checkVelocity(Uint32 ticks, int direction, float p_x, float p_y, float factor);
  bool checkLap(float p_x, float p_y, SDL_Surface *s);
  bool CheckNewValue(int x, int y, SDL_Surface *s);

  float GrassVelocity(int x, int y, SDL_Surface *s);
    
  bool mapCheck(int x, int y, SDL_Surface *toTest);

  
protected:
  const Image * image;
    SDL_Surface *sky;
    SDL_Surface *full;
    SDL_Surface *track;
    SDL_Surface *bounds;
    SDL_Surface *water;
    SDL_Surface *grass;
    SDL_Surface *lightWater;
    SDL_Surface *darkWater;
    SDL_Surface *dirt;
    SDL_Surface *jump;
    SDL_Surface *lava;
    SDL_Surface *empty;
    SDL_Surface *start;

  int worldWidth;
  int worldHeight;
  FrustumPoints &cfp;
  AngularSprite& operator=(const AngularSprite&);
};
#endif
