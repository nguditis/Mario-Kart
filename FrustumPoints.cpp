#include <SDL.h>
#include "FrustumPoints.h"
#include "gameData.h"

FrustumPoints& FrustumPoints::getInstance()
  {
	static FrustumPoints frstmPnts; 
  	return frstmPnts;
  }
 FrustumPoints::FrustumPoints(): 
  fWorldX(Gamedata::getInstance().getXmlFloat("worldData/fworldx")),
  fWorldY(Gamedata::getInstance().getXmlFloat("worldData/fworldy")),
  fWorldA(Gamedata::getInstance().getXmlFloat("worldData/fworlda")),
  fNear(Gamedata::getInstance().getXmlFloat("worldData/fnear")),
  fFar(Gamedata::getInstance().getXmlFloat("worldData/ffar")),
  fFoVHalf(3.14159f / 4.0f)
  {
   std::fstream outfile;
   outfile.open("computed_path.txt", std::ios::in );
   int x,  y;
   while(outfile >> x)
   {
    if(outfile >> y)
     Calculated_Path[std::make_pair(x,y)] = std::make_pair(0,0);
    //std::cout<<x<<" "<<y<<std::endl;
   } 
   outfile.close();
  }
 
  float FrustumPoints::getfWorldX() const
  {
	return fWorldX;
  }
  float FrustumPoints::getfWorldY() const
  {
  	return fWorldY;
  }

  float FrustumPoints::getfWorldA() const
  {
  	return fWorldA;
  }
  float FrustumPoints::getfNear() const
  {
  	return fNear;
  }
  float FrustumPoints::getfFar() const
  {
  	return fFar;
  }
  float FrustumPoints::getfFoVHalf() const
  {
  	return fFoVHalf;
  }
  void  FrustumPoints::setfWorldX(float value)
  {
  		fWorldX = value;
  }
  void FrustumPoints::setfWorldY(float value) 
  {
  		fWorldY = value;
  }
  void FrustumPoints::setfWorldA(float value) 
  {
  		fWorldA = value;
  }
  void FrustumPoints::setfNear(float value) 
  {
  		fNear = value;
  }
  void FrustumPoints::setfFar(float value) 
  {
  		fFar = value;
  }
  void FrustumPoints::setfFoVHalf(float value) 
  {
  		fFoVHalf = value;
  }