#ifndef FRUSTUM_POINTS_H
#define FRUSTUM_POINTS_H
#include <SDL.h>
#include <string>
#include "vector"
#include <map>

class FrustumPoints {
public:
  static FrustumPoints& getInstance();
  float getfWorldX() const;
  float getfWorldY() const;
  float getfWorldA() const;
  float getfNear() const;
  float getfFar() const;
  float getfFoVHalf() const;
  void  setfWorldX(float value);
  void setfWorldY(float value) ;
  void setfWorldA(float value) ;
  void setfNear(float value) ;
  void setfFar(float value) ;
  void setfFoVHalf(float value) ;
  std::map<std::pair<int,int>,std::pair<int,int>>Calculated_Path; 
private:
  FrustumPoints();  
  float fWorldX;// = 132.045f;
  float fWorldY ;//= 547.693f;
  float fWorldA ;//= 20.5f;
  float fNear ;//= 0.95f;
  float fFar;// = -20.987;
  float fFoVHalf;//= 3.14159f / 4.0f;
  FrustumPoints& operator = (const FrustumPoints&) = delete;
  FrustumPoints(const FrustumPoints&)  = delete;
};
#endif