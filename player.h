#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class Player : public Drawable {
public:
  Player(const std::string&);
  Player(const Player&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return current_images[currentFrame];
  }

  int getCurrentFrameNum() {
      return currentFrame;
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

  void right(Uint32 ticks);
  void left(Uint32 ticks);
  void up();
  void down();
  void stop();

private:
  std::vector<Image *> images_left;
  std::vector<Image *> images_right;
  std::vector<Image *> current_images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  Vector2f initialVelocity;

  void advanceFrame(Uint32 ticks);
  void reverseAdvanceFrame(Uint32 ticks);
  Player& operator=(const Player&);
};
#endif
