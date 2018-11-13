#include "twowaysprite.h"
#include "gameData.h"
#include "imageFactory.h"

void TwoWaySprites::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWaySprites::TwoWaySprites( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images_left( ImageFactory::getInstance().getImages(name+"_Left") ),
  images_right( ImageFactory::getInstance().getImages(name+"_Right") ),
  current_images(images_right),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("background/height"))
{ }

TwoWaySprites::TwoWaySprites(const TwoWaySprites& s) :
  Drawable(s), 
  images_left(s.images_left),
  images_right(s.images_right),
  current_images(s.current_images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

TwoWaySprites& TwoWaySprites::operator=(const TwoWaySprites& s) {
  Drawable::operator=(s);
  images_left=(s.images_left),
  images_right=(s.images_right),
  current_images=(s.current_images),
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void TwoWaySprites::draw() const { 
  current_images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWaySprites::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    current_images = images_right;
    currentFrame = 0;
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    current_images = images_left;
    currentFrame = 0;
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}
