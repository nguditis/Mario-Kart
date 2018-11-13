#include <sstream>
#include "viewport.h"
#include <math.h>
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  gdata(Gamedata::getInstance()),
  viewPos(0, 0),
  msgPos(
    Vector2f( gdata.getXmlInt("view/loc/x"), gdata.getXmlInt("view/loc/y") )
  ),
  worldWidth(gdata.getXmlInt("background/width")),
  worldHeight(gdata.getXmlInt("background/height")),
  viewWidth(gdata.getXmlInt("view/width")),
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{}

void Viewport::setObjectToTrack(const Drawable *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
  //std::cout<<"drawing viewport"<<std::endl;
  IoMod::getInstance().
    writeText("Tracking: "+objectToTrack->getName(), msgPos[0], msgPos[1]);
}

void Viewport::update() {

}
