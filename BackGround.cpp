#include <iostream>
#include "BackGround.h"
#include "imageFactory.h"
#include <math.h>

BackGround::BackGround(const std::string& name, int fact) :
  image( (ImageFactory::getInstance()).getImage(name) ),
  factor(fact),
    backgroundWidth( Gamedata::getInstance().getXmlInt("background/height") ),
    imageWidth( image->getWidth() ),
    imageHeight( image->getHeight() ),
    viewX(500.0), viewY(500.0),
    view(Viewport::getInstance())
{ }

void BackGround::update() {
  viewY = static_cast<int>(view.getY() / factor) % imageHeight;
  viewX =  static_cast<int>(view.getX() / factor) % imageWidth;
}

void BackGround::draw() const {
  image->draw(0,0,-viewX,-viewY);
  //image->draw(0,0,(imageWidth-viewX),-viewY);
}
