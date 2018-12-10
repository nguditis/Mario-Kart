#include <SDL.h>
#include <string>

class FrustumPoints {
public:
  static FrustumPoints& getInstance();
  float fWorldX;// = 132.045f;
  float fWorldY ;//= 547.693f;
  float fWorldA ;//= 20.5f;
  float fNear ;//= 0.95f;
  float fFar;// = -20.987;
  float fFoVHalf;//= 3.14159f / 4.0f;
private:
  FrustumPoints();
};
