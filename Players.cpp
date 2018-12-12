#include "Players.h"
#include "gameData.h"
#include "imageFactory.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

float distance(float x1, float y1, float x2, float y2)
{
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void Players::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

void Players::reverseAdvanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame-1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}


Players::Players( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images_left( ImageFactory::getInstance().getImages(name+"_Left") ),
  images_right( ImageFactory::getInstance().getImages(name+"_Right") ),
  current_images(images_right),
  bounds({(int)getX()-2,(int)getY()-2, 5, 5}),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  track( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/track").c_str())),
  worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("background/height")),
  cfp (FrustumPoints::getInstance()),
  isInFrame(true),
  currentPosition(1)
 { 
   std::fstream outfile;
   outfile.open("computed_path.txt", std::ios::in );
   int x,  y;
   while(outfile >> x)
   {
    if(outfile >> y)
     Computed_Path.push_back(std::make_pair(x,y));
    //std::cout<<x<<" "<<y<<std::endl;
   } 
   outfile.close();
   setX(Computed_Path[0].first);
   setY(Computed_Path[0].second);
   //SetSampleXandSampleY();

}

Players::Players(const Players& s) :
  Drawable(s),
  images_left(s.images_left),
  images_right(s.images_right),
  bounds(s.bounds),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  track(s.track),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  cfp(FrustumPoints::getInstance()),
  Computed_Path(s.Computed_Path)
  { }

Players& Players::operator=(const Players& s) {
  Drawable::operator=(s);
  images_left = (s.images_left);
  images_right = (s.images_right);
  bounds = (s.bounds);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  track = (s.track);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  Computed_Path = s.Computed_Path;
  return *this;
}

void Players::draw() const {
  //if(!isInFrame || getVelocityY()>0 || getVelocityX() > 0)
    //return;
 // if(isInFrame)
    current_images[currentFrame]->draw(getX(), getY(), getScale());
}

void Players::stop() {
  //setVelocity( Vector2f(0, 0) );
  setVelocityX( 0.93*getVelocityX() );
  setVelocityY(0);
}

void Players::right(Uint32 ticks) {
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
void Players::left(Uint32 ticks)  {
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
void Players::up()    {
  if (currentFrame != 0) {
    currentFrame = 0;
  }
  current_images = images_right;

  //if ( getY() > 0) {
  //  setVelocityY( -initialVelocity[1] );
  //}
}
bool Players::StayInTrack(float x, float y)
{

    SDL_LockSurface(track);
    Uint32 *pixels = (Uint32*)track->pixels;
    //int X1 = cfp.Path[currentPosition%28].first;
    //int Y1 = cfp.Path[currentPosition%28].second;
    float fFarX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();

    float fFarX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    //std::cout<<fFarX1<<" "<<fFarY1<<" "<<fFarX2<<" "<<fFarY2<<" "<<fNearX1<<" "<<fNearY1<<fNearX2<<" "<<fNearY2<<std::endl;
    //std::cout<<x<<" "<<y<<std::endl;

        float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
        float fSampleWidth = (float)x / (float)worldWidth;
        float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
        float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
        float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
        float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
        float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
        float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
        //fSampleX = fabs(fmod(fSampleX, 1022)+1);
        //fSampleY = fabs(fmod(fSampleY,1022)+1);
        Uint32 pixel = pixels[(int(fSampleY) * track->pitch / 4) + int(fSampleX)];
        SDL_Color color;
      //SDL_LockSurface(surface2);
        SDL_GetRGBA(pixel, track->format, &color.r, &color.g, &color.b, &color.a);
        
        //SDL_GetRGBA(pixel2, surface2->format, &color2.r, &color2.g, &color2.b, &color2.a);
        if(int(color.a) == 255 && fSampleX > 0 && fSampleX < 1022 && fSampleY > 0 && fSampleY < 1022)
        {
          //std::cout<<x<<" "<<y<<" "<<fSampleX<<" "<<fSampleY<<std::endl;
          SDL_UnlockSurface(track);
          return true;
        } 

    SDL_UnlockSurface(track);
    return false;
}
void Players::SetSampleXandSampleY()
{
    
    currentPosition++;
    float fFarX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();

    float fFarX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    //std::cout<<getY()<<" "<<worldHeight/2<<std::endl;
    
    //isInside(polygon1, n, p)?
    //Point p = {fSampleX, fSampleY}; 
   // float fSampleX = Computed_Path[currentPosition%Computed_Path.size()].first;
    //float fSampleY = Computed_Path[currentPosition%Computed_Path.size()].second;

    //x = fSampleX-fNearX1
        //if(!isInside(polygon1, n, p))
          //continue;
    for (int y = 0; y < worldHeight/2; y++)
    {
      
      // Take a sample point for depth linearly related to rows down screen
      //std::cout<<fSampleDepth<<std::endl;
     float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
      //std::cout<<fSampleDepth<<std::endl;
      if(fSampleDepth == 0)
         fSampleDepth = 1;
      // Use sample point in non-linear (1/x) way to enable perspective
      // and grab start and end points for lines across the screen
      float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
      float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
      float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
      float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;

      // Linearly interpolate lines across the screen
      for (int x = 0; x < worldWidth; x++)
      {
        //std::cout<<"drawing x "<<x<<std::endl;
        float fSampleWidth = (float)x / (float)worldWidth;
        float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
        float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
        //fSampleX = fabs(fmod(fSampleX, 1022)+1);
        //fSampleY = fabs(fmod(fSampleY,1022)+1);
        //std::cout<<fSampleX<<" "<<fSampleY<<std::endl;
        if(fSampleX < 0 || fSampleX > 1024 || fSampleY<0 || fSampleY > 1024)
          continue;
        //if(!isInside(polygon1, n, p))
          //continue;
        if((int)fSampleX==Computed_Path[currentPosition%Computed_Path.size()].first && (int)fSampleY==Computed_Path[currentPosition%Computed_Path.size()].second) 
        {
          //std::cout<<x<<" "<<y+worldHeight/2<<std::endl;
          //currentPosition++;
          //std::cout<<currentPosition<<std::endl;
          setX(x);
          if(y<350)
            setY(y+worldHeight/2);
          else
            setY(y);
          currentPosition++;
          return;
        }
      }
    }

}
    
void Players::ResetToNewSetting()
{
    SDL_LockSurface(track);
    Uint32 *pixels = (Uint32*)track->pixels;
    //int X1 = cfp.Path[currentPosition%28].first;
    //int Y1 = cfp.Path[currentPosition%28].second;
    float fFarX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();

    float fFarX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    //std::cout<<fFarX1<<" "<<fFarY1<<" "<<fFarX2<<" "<<fFarY2<<" "<<fNearX1<<" "<<fNearY1<<fNearX2<<" "<<fNearY2<<std::endl;
    //std::cout<<x<<" "<<y<<std::endl;
    for(int x=10;x<worldWidth;x++)
    {
      for(int y=worldHeight/2-10;y<worldHeight;y++)
      {
        float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
        float fSampleWidth = (float)x / (float)worldWidth;
        float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
        float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
        float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
        float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
        float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
        float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
        //fSampleX = fabs(fmod(fSampleX, 1022)+1);
        //fSampleY = fabs(fmod(fSampleY,1022)+1);
        //std::cout<<fSampleX_prev<<" "<<fSampleY_prev<<" "<<fSampleX<<" "<<fSampleY<<std::endl;
        if(fabs(fSampleX -fSampleX_prev) < 1 && fabs(fSampleY-fSampleY_prev)< 1 )
        {
          //std::cout<<x<<" "<<y<<" "<<fSampleX<<" "<<fSampleY<<std::endl;
          setX(x);
          setY(y);
          SDL_UnlockSurface(track);
          return;
        } 
      }
    }
    SDL_UnlockSurface(track);
    //return false;
}
int Players::findNextCourse(Uint32 ticks)
{
  int nbLeft=0;
  int nbRight=0;
  int nbUp=0;
  int direction = 0;
  /*left = 0
  right = 1;
  up=2*/
  for(float x = getX();x<3+getX() && x<1000;x+=3)
  {
    //std::cout<<x<<" "<<getY()<<std::endl;
    if(StayInTrack(x,getY()))
      nbRight++;
    else
      break;
  }
  for(float x = getX();x>getX()-3 && x>0;x-=3)
  {
    // std::cout<<x<<" "<<getY()<<std::endl;
    if(StayInTrack(x,getY()))
      nbLeft++;
    else
      break;
  }
  for(float y=getY();y>getY()-4&& y>330;y-=4)
  {
    //std::cout<<getX()<<" "<<y<<std::endl;
    if(StayInTrack(getX(),y))
    {
      return 2;
    }
    else
      break;
  }
  
  if(nbRight>=nbLeft)
    direction = 1;
  //std::cout<<nbLeft<<" "<<nbRight<<" "<<nbUp<<std::endl;
  if(direction == 0 && nbLeft <= nbUp)
    direction = 2;
  else if(direction == 1 && nbRight <= nbUp)
    direction = 2;
  return direction;

}

void Players::update(Uint32 ticks, int p_x, int p_y) {  

  //setScale(abs(int((700-getY()/10))));
  // std::cout<<"update start"<<std::endl;
  isInFrame = true;
  int d = distance(p_x,p_y,getX(),getY());
  int direction = findNextCourse(ticks);
  
  //std::cout<<direction<<std::endl;
  if(direction == 0)
  {
    //vx = -30;
    setX(getX()-3);
    left(ticks);
  }
  else if(direction == 1)
  {
    //vx= 30;
    setX(getX()+3);
    right(ticks);
  }
  else
   {
    //vy = -30;
    up();
    for(int i =0 ;i<4;i++)
    {
      if(getY() > 330)
      setY(getY()- i);
    }
   } 

  float scale = 5;
  if(d<50)
    scale = 6;
  else
    scale = 900/d;

  //std::cout<<scale<<std::endl;
  setScale(scale);
  
  //Increment x
  /*bool isInTrack = StayInTrack(getX(),getY());
  if(!isInTrack)
  {
    for(int i = 1; i< 5 && getX()>0;i+=0.5)
    {
      setX(getX()-i);
      left(ticks);
      isInTrack = StayInTrack();
      if(isInTrack)
        break;

    }
    if(!isInTrack)
    {
      for(int i = 1; i< 10 && getX()<worldWidth;i+=0.5)
      {
        setX(getX()+i);
        right(ticks);
        isInTrack = StayInTrack();
        if(isInTrack)
          break;

      }
   }
  }
  
  if ( getY() < 350) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if(getX()<0)
    setVelocityX(fabs(getVelocityX()));
  if(getX() > 1000)
    setVelocityX(-fabs(getVelocityX()));
  if ( getY() > 1000) {
    setVelocityY( -fabs( getVelocityY() ) );
  }*/

}
