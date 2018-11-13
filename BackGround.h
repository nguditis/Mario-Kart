#include <string>
#include "image.h"
#include "viewport.h"

class BackGround {
public:
  BackGround(const std::string& name, int fact);
  // ~World() { } // The image will be deleted by the FrameFactory
  void update();
  void draw() const;
private:
  Image* const image;
  int factor;
  unsigned backgroundWidth;
  unsigned imageWidth;
  unsigned imageHeight;
  float viewX;
  float viewY;
  const Viewport & view;
  //BackGround(const BackGround&);
  BackGround& operator=(const BackGround&);
};
