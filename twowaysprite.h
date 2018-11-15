#ifndef TWOWAYSPRITE_H
#define TWOWAYSPRITE_H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class TwoWaySprites : public Drawable {
public:
  TwoWaySprites(const std::string&);
  TwoWaySprites(const TwoWaySprites&);
  virtual ~TwoWaySprites(){}

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return current_images[currentFrame];
  }
  int getScaledWidth()  const {
    return getScale()*current_images[currentFrame]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*current_images[currentFrame]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return current_images[currentFrame]->getSurface();
  }

protected:
  std::vector<Image *> images_left;
  std::vector<Image *> images_right;
  std::vector<Image *> current_images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
  TwoWaySprites& operator=(const TwoWaySprites&);
};
#endif
