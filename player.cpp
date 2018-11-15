#include "player.h"
#include "gameData.h"
#include "imageFactory.h"

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void Player::reverseAdvanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame-1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}


Player::Player( const std::string& name) :
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
  worldHeight(Gamedata::getInstance().getXmlInt("background/height")),
  initialVelocity(getVelocity())
{printf("current frame num is %d\n", getCurrentFrameNum() ); }

Player::Player(const Player& s) :
  Drawable(s),
  images_left(s.images_left),
  images_right(s.images_right),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  initialVelocity( s.initialVelocity )
  { }

Player& Player::operator=(const Player& s) {
  Drawable::operator=(s);
  images_left = (s.images_left),
  images_right = (s.images_right),
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  initialVelocity = ( s.initialVelocity );
  return *this;
}

void Player::draw() const {
  current_images[currentFrame]->draw(getX(), getY(), getScale());
}

void Player::stop() {
  //setVelocity( Vector2f(0, 0) );
  setVelocityX( 0.93*getVelocityX() );
  setVelocityY(0);
}

void Player::right(Uint32 ticks) {
	//bool x = (current_images == images_left);
	//printf("images_left == %s", x ? "true" : "false");
    if (current_images == images_left){
        while (getCurrentFrameNum() < numberOfFrames-1) {
					//printf("current left to right frame num is %d\n", getCurrentFrameNum() );
            advanceFrame(ticks);
        }
        current_images = images_right;
    }
    while (getCurrentFrameNum() < numberOfFrames-1) {
			//printf("current right to right frame num is %d\n", getCurrentFrameNum() );
        advanceFrame(ticks);
    }


  //if ( getX() < worldWidth-getScaledWidth()) {
  //  setVelocityX(initialVelocity[0]);
  //}
}
void Player::left(Uint32 ticks)  {
	//bool x = (current_images == images_right);
	//printf(" images_right == %s", x ? "true" : "false");
    if (current_images == images_right){
        while (getCurrentFrameNum() > 0) {
					//printf("current right to left frame num is %d\n", getCurrentFrameNum() );
            reverseAdvanceFrame(ticks);
        }
        current_images = images_left;
    }
    while (getCurrentFrameNum() > 0) {
			//printf("current left to _Left frame num is %d\n", getCurrentFrameNum() );
        reverseAdvanceFrame(ticks);
    }
  /*if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }*/
}
void Player::up()    {
	if (currentFrame != 0) {
		currentFrame = 0;
	}
	current_images = images_right;

	//if ( getY() > 0) {
  //  setVelocityY( -initialVelocity[1] );
  //}
}
void Player::down()  {
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }

  stop();
}
