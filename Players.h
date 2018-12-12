#ifndef PLAYERS__H
#define PLAYERS__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "FrustumPoints.h"

class Players : public Drawable {
public:
  Players(const std::string&);
  Players(const Players&);

  virtual void draw() const;
  virtual void update(Uint32 ticks){};

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

  bool StayInTrack(float x, float y) ;
  int findNextCourse(Uint32 ticks);
  void right(Uint32 ticks);
  void left(Uint32 ticks);
  void up();
  void stop();
  void update(Uint32 ticks, int p_x, int p_y);
  void SetSampleXandSampleY();
  void ResetToNewSetting();


private:
  std::vector<Image *> images_left;
  std::vector<Image *> images_right;
  std::vector<Image *> current_images;    
  SDL_Rect bounds;


  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  SDL_Surface *track;
  FrustumPoints &cfp;
  bool isInFrame;
  float fSampleX_prev;
  float fSampleY_prev;
  std::vector<std::pair<int,int>>Computed_Path;
  int currentPosition;
  //std::vector<Vector2f>path;
  void advanceFrame(Uint32 ticks);
  void reverseAdvanceFrame(Uint32 ticks);
  Players& operator=(const Players&);
};
#endif
