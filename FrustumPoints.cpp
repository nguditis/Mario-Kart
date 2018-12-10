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
  {}
 
