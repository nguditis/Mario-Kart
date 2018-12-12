#include "AngularSprite.h"
#include "gameData.h"
#include "imageFactory.h"
#define OFCOURSEISTILLLOVEYOU std::cerr << __LINE__ << std::endl;

inline namespace {
  inline void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
  {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
  }
}

AngularSprite::AngularSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  image( ImageFactory::getInstance().getImage(name+"/tracks/Donut_Plains_1/full", name) ),
  track( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/full").c_str())),
  sky( IMG_Load(Gamedata::getInstance().getXmlStr("sky/file").c_str())),
  grass( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/grass").c_str())),
  bounds( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/boundry").c_str())),
  start( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/track_start").c_str())),
  worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("background/height")),
  cfp (FrustumPoints::getInstance())
 {

 }

AngularSprite::AngularSprite( const std::string& name,  Tracks& t) :
Drawable(name,
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                  Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                  Gamedata::getInstance().getXmlInt(name+"/speedY"))
         ),
image( ImageFactory::getInstance().getImage(name+"/tracks/"+t.getName()+"/full", name) ),
track( t.getTrack() ),
sky( IMG_Load(Gamedata::getInstance().getXmlStr("sky/file").c_str())),
grass(  t.getGrass() ),
bounds( t.getBounds() ),
start( t.getStart() ),
worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
worldHeight(Gamedata::getInstance().getXmlInt("background/height")),
cfp (FrustumPoints::getInstance())
{ }

AngularSprite::AngularSprite(const AngularSprite& s) :
  Drawable(s),
  image(s.image),
  track(s.track),
  sky(s.sky),
  grass(s.grass),
  bounds(s.bounds),
  start(s.start),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ), 
  cfp(FrustumPoints::getInstance())
  {
  }

AngularSprite& AngularSprite::operator=(const AngularSprite& s) {
  Drawable::operator=(s);
  image = (s.image);
  track = s.track;
  sky = s.sky;
  grass = s.grass;
  bounds = s.bounds;
  start = s.start;
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  //cfp = (FrustumPoints::getInstance());
  return *this;
}
bool AngularSprite::checkLap(float p_x, float p_y, SDL_Surface *s)
{
    if(mapCheck(p_x,p_y,s))
        {
          return true;
        }  
    return false;
}
bool AngularSprite::checkVelocity(Uint32 ticks, int direction, float p_x, float p_y, float factor)
{
  
    if(direction == 1)
    {
      //cfp.fNear -= 0.1f * ticks;
      float fWorldA = cfp.getfWorldA();
      cfp.setfWorldA(fWorldA-factor);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfWorldA(fWorldA);
      return blocked;
    }
    else if (direction == 2)
    {
      float fWorldA = cfp.getfWorldA();
      cfp.setfWorldA(fWorldA+factor);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfWorldA(fWorldA);
      return blocked;
    }
    else if(direction ==3)
    {
      float fWorldX = cfp.getfWorldX(); 
      float fWorldY = cfp.getfWorldY();
      cfp.setfWorldX(fWorldX+cosf(cfp.getfWorldA()) * factor * ticks);
      cfp.setfWorldY(fWorldY+sinf(cfp.getfWorldA()) * factor * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfWorldX(fWorldX);
      cfp.setfWorldY(fWorldY);
      return blocked;
      
    }
    else if (direction == 4)
    {

      float fWorldX = cfp.getfWorldX(); 
      float fWorldY = cfp.getfWorldY();
      cfp.setfWorldX(fWorldX-cosf(cfp.getfWorldA()) * factor * ticks);
      cfp.setfWorldY(fWorldY-sinf(cfp.getfWorldA()) * factor * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfWorldX(fWorldX);
      cfp.setfWorldY(fWorldY);
      return blocked;
    }
    else if (direction == 5)
    {
      float fNear = cfp.getfNear();
      cfp.setfNear(cfp.getfNear()-0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfNear(fNear);
      return blocked;
    }
    else if (direction == 6)
    {
      float fNear = cfp.getfNear();
      cfp.setfNear(cfp.getfNear()+0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfNear(fNear);
      return blocked;

    }
    else if (direction == 7)
    {
        //cfp.fFoVHalf -= 0.2f * ticks;
      float fFar = cfp.getfFar();
      cfp.setfFar(cfp.getfFar()-0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfFar(fFar);
      return blocked;

    }
    else if (direction == 8)
    {
      float fFar = cfp.getfFar();
      cfp.setfFar(cfp.getfFar()+0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfFar(fFar);
      return blocked;
    }
    else if (direction == 9)
    {
        //cfp.fFoVHalf -= 0.2f * ticks;
      float fFoVHalf = cfp.getfFoVHalf();
      cfp.setfFoVHalf(cfp.getfFoVHalf()-0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfFoVHalf(fFoVHalf);
      return blocked;
    }
    else if (direction == 10)
    {
      float fFoVHalf = cfp.getfFoVHalf();
      cfp.setfFoVHalf(cfp.getfFoVHalf()+0.1f * ticks);
      bool blocked = CheckNewValue(p_x, p_y,bounds);
      cfp.setfFoVHalf(fFoVHalf);
      return blocked;

    }
    return true;
}

void AngularSprite::update(Uint32 ticks){}
void AngularSprite::update(Uint32 ticks, int direction, float factor)
{
    if(direction == 1)
    {
      //cfp.fNear -= 0.1f * ticks;
      cfp.setfWorldA(cfp.getfWorldA()-factor);
    }
    else if (direction == 2)
    {
      cfp.setfWorldA(cfp.getfWorldA()+factor);
    }
    else if(direction ==3)
    {
      float fWorldX = cfp.getfWorldX(); 
      float fWorldY = cfp.getfWorldY();
      cfp.setfWorldX(fWorldX+cosf(cfp.getfWorldA()) * factor * ticks);
      cfp.setfWorldY(fWorldY+sinf(cfp.getfWorldA()) * factor * ticks);
    }
    else if (direction == 4)
    {
      float fWorldX = cfp.getfWorldX(); 
      float fWorldY = cfp.getfWorldY();
      cfp.setfWorldX(fWorldX-cosf(cfp.getfWorldA()) * factor * ticks);
      cfp.setfWorldY(fWorldY-sinf(cfp.getfWorldA()) * factor * ticks);
      //std::cout<<"values in Sprite "<<cfp.getfWorldX()<<" " <<cfp.getfWorldY()<<std::endl;

    }
    else if (direction == 5)
    {
      cfp.setfNear(cfp.getfNear()-0.1f * ticks);
    }
    else if (direction == 6)
    {
      //cfp.fFoVHalf += 0.2f * ticks;
      cfp.setfNear(cfp.getfNear()+0.1f * ticks);

    }
    else if (direction == 7)
    {
        //cfp.fFoVHalf -= 0.2f * ticks;
        cfp.setfFar(cfp.getfFar()-0.1f * ticks);
    }
    else if (direction == 8)
    {
        //cfp.fFoVHalf += 0.2f * ticks;
        cfp.setfFar(cfp.getfFar()+0.1f * ticks);

    }
    else if (direction == 9)
    {
        //cfp.fFoVHalf -= 0.2f * ticks;
        cfp.setfFoVHalf(cfp.getfFoVHalf()-0.1f);
    }
    else if (direction == 10)
    {
        //cfp.fFoVHalf += 0.2f * ticks;
         cfp.setfFoVHalf(cfp.getfFoVHalf()+0.1f);

    } 
  }
bool AngularSprite::mapCheck(int p_x, int p_y, SDL_Surface *toTest){
    
    SDL_LockSurface(toTest);
    Uint32 *pixels = (Uint32*)toTest->pixels;
    SDL_Color color;

    float fFarX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();

    float fFarX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    for(int x = p_x-2;x<= p_x+5; x++)
    {
        for(int y = p_y-2; y<= p_y+5; y++)
        {
            
            float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
            float fSampleWidth = (float)x / (float)worldWidth;
            float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
            float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
            float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
            float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
            float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
            float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
            //SDL_LockSurface(grass);
            //Uint32 *pixels = (Uint32*)grass->pixels;
            Uint32 pixel = pixels[(int(fSampleY) * toTest->pitch / 4) + int(fSampleX)];
            SDL_GetRGBA(pixel, toTest->format, &color.r, &color.g, &color.b, &color.a);
        }
    }
    
    SDL_UnlockSurface(toTest);
    if ( int(color.a) == 255 ) {
        return true;
    }
    else
        return false;
}


float AngularSprite::GrassVelocity(int p_x, int p_y, SDL_Surface *g)
{
   
    if(mapCheck(p_x, p_y, g))
    {
       
      return 0.2f;
    }
    
    return 0.5f;
}
bool AngularSprite::CheckNewValue(int p_x, int p_y, SDL_Surface *b)
{
    if (b == nullptr) {
        return true;
    }
    
    if(mapCheck(p_x, p_y, b))
    {
        return false;
    }
    return true;
}

void AngularSprite::draw(SDL_Renderer *renderer) const{

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif
    static SDL_Surface *surface3 = SDL_CreateRGBSurface(0, 1000, 1000, 32, rmask, gmask, bmask, amask);

  // Create Frustum corner points
    

    float fFarX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX1 = cfp.getfWorldX() + cosf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY1 = cfp.getfWorldY() + sinf(cfp.getfWorldA() - cfp.getfFoVHalf() ) * cfp.getfNear();

    float fFarX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();
    float fFarY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfFar();

    float fNearX2 = cfp.getfWorldX() + cosf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();
    float fNearY2 = cfp.getfWorldY() + sinf(cfp.getfWorldA() + cfp.getfFoVHalf() ) * cfp.getfNear();

    SDL_LockSurface(surface3);

    Uint32 *pixels1 = (Uint32*)sky->pixels;
    Uint32 *pixels2 = (Uint32*)track->pixels;

    auto drawPixel = [&](int _x, int _y, Uint32 _pixel)
    {
      set_pixel(surface3, _x, _y, _pixel);
    };

    auto drawPixelColor = [&](int _x, int _y, Uint8 _r, Uint8 _g, Uint8 _b)
    {
      set_pixel(surface3, _x, _y, SDL_MapRGBA(surface3->format, _r, _g, _b, 255u));
    };
    
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

        // Wrap sample coordinates to give "infinite" periodicity on maps
        //std::cout<<fSampleX<<" "<<fSampleY<<std::endl;
        //fSampleX = fmod(fSampleX, 1024);
        //fSampleY = fmod(fSampleY,1024);
        SDL_Color color = {0,0,0,0};
        
       

        if(fSampleX < 0 || fSampleX > 1024 || fSampleY<0 || fSampleY > 1024)
        {
             drawPixelColor(x, y+ worldHeight/2, color.r, color.g, color.b);
       
        }
        else
        {
           Uint32 pixel2 = pixels2[(int(fSampleY) * track->pitch / 4) + int(fSampleX)];
          SDL_GetRGBA(pixel2, track->format, &color.r, &color.g, &color.b, &color.a);
          drawPixelColor(x, y + worldHeight/2, color.r, color.g, color.b);
        }
        //std::cout<<(int(fSampleY) * sky->pitch / 4) + int(fSampleX)<<std::endl;
        //std::cout<<(int(fSampleY) * track->pitch / 4) + int(fSampleX)<<std::endl;
        
        // Sample symbol and colour from map sprite, and draw the
        // pixel to the screen
        fSampleX = fabs(fmod(fSampleX, 1022)+1);
        fSampleY = fabs(fmod(fSampleY,1022)+1);
        Uint32 pixel1 = pixels1[(int(fSampleY) * sky->pitch / 4) + int(fSampleX)];
        SDL_GetRGBA(pixel1, sky->format, &color.r, &color.g, &color.b, &color.a);

        drawPixelColor(x, y, color.r, color.g, color.b);       

      }
    }

    
    SDL_UnlockSurface(surface3);
    SDL_Texture* frameTexture = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_RenderCopy(renderer, frameTexture, NULL, NULL);

    SDL_DestroyTexture(frameTexture);


}
