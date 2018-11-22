#include "AngularSprite.h"
#include "gameData.h"
#include "imageFactory.h"

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
  surface2( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/full").c_str())), // S2, track
  surface1( IMG_Load(Gamedata::getInstance().getXmlStr("sky/file").c_str())), //S1, sky
  grass( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/grass").c_str())),
  blocks( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/boundry").c_str())),
  worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("background/height")),
  fWorldX(Gamedata::getInstance().getXmlFloat("worldData/fworldx")),
  fWorldY(Gamedata::getInstance().getXmlFloat("worldData/fworldy")),
  fWorldA(Gamedata::getInstance().getXmlFloat("worldData/fworlda")),
  fNear(Gamedata::getInstance().getXmlFloat("worldData/fnear")),
  fFar(Gamedata::getInstance().getXmlFloat("worldData/ffar"))
{

 }

AngularSprite::AngularSprite(const AngularSprite& s) :
  Drawable(s),
  image(s.image),
  surface2(s.surface2),//track(s.track),
  surface1(s.surface1),//sky(s.sky),
  grass(s.grass),
  blocks(s.blocks),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

AngularSprite& AngularSprite::operator=(const AngularSprite& s) {
  Drawable::operator=(s);
  image = (s.image);
  surface2 = s.surface2;//track = s.track;
  surface1 = s.surface1;//sky = s.sky;
  grass = s.grass;
  blocks = s.blocks;
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}
bool AngularSprite::checkVelocity(Uint32 ticks, int direction, float p_x, float p_y)
{

    if(direction == 1)
    {
      //fNear -= 0.1f * ticks;
      fWorldA -= 0.2f;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldA += 0.2f;
      }
      return blocked;
    }
    else if (direction == 2)
    {
      fWorldA += 0.2f;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldA -= 0.2f;
      }
      return blocked;
    }
    else if(direction ==3)
    {
      fWorldX += cosf(fWorldA) * 0.2f * ticks;
      fWorldY += sinf(fWorldA) * 0.2f * ticks;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldX -= cosf(fWorldA) * 0.2f * ticks;
        fWorldY -= sinf(fWorldA) * 0.2f * ticks;
      }
      return blocked;
      
    }
    else if (direction == 4)
    {

      fWorldX -= cosf(fWorldA) * 0.2f * ticks;
      fWorldY -= sinf(fWorldA) * 0.2f * ticks;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldX += cosf(fWorldA) * 0.2f * ticks;
        fWorldY += sinf(fWorldA) * 0.2f * ticks;
      }
      return blocked;
    }
    else if (direction == 5)
    {
      //fFoVHalf -= 0.2f * ticks;
      fNear -= 0.1f * ticks;
    }
    else if (direction == 6)
    {
      //fFoVHalf += 0.2f * ticks;
      fNear += 0.1f * ticks;

    }
    else if (direction == 7)
    {
        //fFoVHalf -= 0.2f * ticks;
        fFar -= 0.1f * ticks;
    }
    else if (direction == 8)
    {
        //fFoVHalf += 0.2f * ticks;
        fFar += 0.1f * ticks;

    }
    else if (direction == 9)
    {
        //fFoVHalf -= 0.2f * ticks;
        fFoVHalf -= 0.1f;
    }
    else if (direction == 10)
    {
        //fFoVHalf += 0.2f * ticks;
        fFoVHalf += 0.1f;

    }
    return true;
}

void AngularSprite::update(Uint32 ticks){}
void AngularSprite::update(Uint32 ticks, int direction, float factor)
{
    if(direction == 1)
    {
      //fNear -= 0.1f * ticks;
      fWorldA -= factor;
    }
    else if (direction == 2)
    {
      fWorldA += factor;
      //fNear += 0.1f * ticks;
    }
    else if(direction ==3)
    {
      fWorldX += cosf(fWorldA) * factor* ticks;
      fWorldY += sinf(fWorldA) * factor * ticks;
    }
    else if (direction == 4)
    {
      fWorldX -= cosf(fWorldA) * factor * ticks;
      fWorldY -= sinf(fWorldA) * factor * ticks;
    }
    else if (direction == 5)
    {
      //fFoVHalf -= 0.2f * ticks;
      fNear -= 0.1f * ticks;
    }
    else if (direction == 6)
    {
      //fFoVHalf += 0.2f * ticks;
      fNear += 0.1f * ticks;

    }
    else if (direction == 7)
    {
        //fFoVHalf -= 0.2f * ticks;
        fFar -= 0.1f * ticks;
    }
    else if (direction == 8)
    {
        //fFoVHalf += 0.2f * ticks;
        fFar += 0.1f * ticks;

    }
    else if (direction == 9)
    {
        //fFoVHalf -= 0.2f * ticks;
        fFoVHalf -= 0.1f;
    }
    else if (direction == 10)
    {
        //fFoVHalf += 0.2f * ticks;
        fFoVHalf += 0.1f;

    }

  }
float AngularSprite::GrassVelocity(int x, int y)
{
    float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;

    float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
    float fSampleWidth = (float)x / (float)worldWidth;
    float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
    float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
    float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
    float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
    float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
    float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
    SDL_LockSurface(grass);
    Uint32 *pixels = (Uint32*)grass->pixels;
    Uint32 pixel = pixels[(int(fSampleY) * grass->pitch / 4) + int(fSampleX)];
    SDL_Color color;
  //SDL_LockSurface(surface2);
    SDL_GetRGBA(pixel, grass->format, &color.r, &color.g, &color.b, &color.a);
    SDL_UnlockSurface(grass);
    //SDL_GetRGBA(pixel2, surface2->format, &color2.r, &color2.g, &color2.b, &color2.a);
    if(int(color.a) == 255)
    {
      return 0.0f;
    }   
    return 0.2f;
}
bool AngularSprite::CheckNewValue(int x, int y)
{
    float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;

    float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
    float fSampleWidth = (float)x / (float)worldWidth;
    float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
    float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
    float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
    float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
    float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
    float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
    SDL_LockSurface(blocks);
    Uint32 *pixels = (Uint32*)blocks->pixels;
    Uint32 pixel = pixels[(int(fSampleY) * blocks->pitch / 4) + int(fSampleX)];
    SDL_Color color;
  //SDL_LockSurface(surface2);
    SDL_GetRGBA(pixel, blocks->format, &color.r, &color.g, &color.b, &color.a);
    SDL_UnlockSurface(blocks);
    //SDL_GetRGBA(pixel2, surface2->format, &color2.r, &color2.g, &color2.b, &color2.a);
    if(int(color.a) == 255 || fSampleY < 0 || fSampleX < 0 || fSampleX > 1024 || fSampleY>1024)
    {
      return false;
    }
    
    
    
    return true;
}
/*
void AngularSprite::draw(SDL_Renderer *renderer) const{

  // Create Frustum corner points
    float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;
    // Starting with furthest away line and work towards the camera point
    
    SDL_LockSurface(sky);
    SDL_LockSurface(track);

    Uint32 *pixels1 = (Uint32*)sky->pixels;
    Uint32 *pixels2 = (Uint32*)track->pixels;

    // [250*500];
    //memcpy( cur_pixels, pixels, surface->pitch * surface->h );
    for (int y = 0; y < worldHeight/2; y++)
    {
      //std::cout<<"drawing y "<<y<<std::endl;
      // Take a sample point for depth linearly related to rows down screen
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
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        //std::cout<<"draw color set "<<std::endl;

        if(fSampleX < 0 || fSampleX > 1024 || fSampleY<0 || fSampleY > 1024)
        {
              SDL_Color w_color = {0,0,0,255};
              SDL_SetRenderDrawColor(renderer, w_color.r, w_color.g, w_color.b, w_color.a);
              SDL_RenderDrawPoint(renderer, x, y+worldHeight/2);
       
        }
        else
        {

              Uint32 pixel2 = pixels2[(int(fSampleY) * track->pitch / 4) + int(fSampleX)];
              SDL_GetRGBA(pixel2, track->format, &color.r, &color.g, &color.b, &color.a);
              SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
              SDL_RenderDrawPoint(renderer, x, y+worldHeight/2);

        }
        fSampleX = fabs(fmod(fSampleX, 1022)+1);
        fSampleY = fabs(fmod(fSampleY,1022)+1);

        Uint32 pixel1 = pixels1[(int(fSampleY) * sky->pitch / 4) + int(fSampleX)];
        
        // Sample symbol and colour from map sprite, and draw the
        // pixel to the screen
        //SDL_Color color = getPixelColor(fSampleX,fSampleY);

        SDL_GetRGBA(pixel1, sky->format, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        //std::cout<<"draw color set "<<std::endl;
        SDL_RenderDrawPoint(renderer, x, y);



      }
    }
    SDL_UnlockSurface(track);
    SDL_UnlockSurface(sky);
}*/
 
 
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
 static SDL_Surface *surface3 = SDL_CreateRGBSurface(0, 1024, 1024, 32, rmask, gmask, bmask, amask);
 
 // Create Frustum corner points
 float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
 float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;
 
 float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
 float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;
 
 float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
 float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;
 
 float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
 float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;
 // Starting with furthest away line and work towards the camera point
 //std::cout<<"drawing "<<fFarX1<<" "<<fFarY1<<" "<<fNearX1<<" "<<fNearY1<<" "<<fFarX2<<" " << fFarY2<<std::endl;
 
 SDL_LockSurface(surface3);
 
 Uint32 *pixels1 = (Uint32*)surface1->pixels;
 Uint32 *pixels2 = (Uint32*)surface2->pixels;
 
 auto drawPixel = [&](int _x, int _y, Uint32 _pixel)
 {
 set_pixel(surface3, _x, _y, _pixel);
 };
 
 auto drawPixelColor = [&](int _x, int _y, Uint8 _r, Uint8 _g, Uint8 _b)
 {
 set_pixel(surface3, _x, _y, SDL_MapRGBA(surface3->format, _r, _g, _b, 255u));
 };
 
 // [250*500];
 //memcpy( cur_pixels, pixels, surface->pitch * surface->h );
 for (int y = 1; y < worldHeight/2; y++)
 {
 //std::cout<<"drawing y "<<y<<std::endl;
 // Take a sample point for depth linearly related to rows down screen
 float fSampleDepth = (float)y / ((float)worldHeight / 2.0f);
 //std::cout<<fSampleDepth<<std::endl;
 
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
 
 if (fSampleX > 1024) {
 fSampleX = 1024;
 drawPixel(fSampleX, fSampleY, 0u);
 }
 else if (fSampleY > 1024) {
 fSampleY = 1024;
 drawPixel(fSampleX, fSampleY, 0u);
 }
 else if (fSampleX < 0) {
 fSampleX = 0;
 drawPixel(fSampleX, fSampleY, 0u);
 }
 else if (fSampleY < 0) {
 fSampleY = 0;
 drawPixel(fSampleX, fSampleY, 0u);
 }
 
 Uint32 pixel1 = pixels1[(int(fSampleY) * surface1->pitch / 4) + int(fSampleX)];
 Uint32 pixel2 = pixels2[(int(fSampleY) * surface2->pitch / 4) + int(fSampleX)];
 // Sample symbol and colour from map sprite, and draw the
 // pixel to the screen
 
 SDL_GetRGBA(pixel1, surface1->format, &color.r, &color.g, &color.b, &color.a);
 
 drawPixelColor(x, y, color.r, color.g, color.b);
 
 SDL_GetRGBA(pixel2, surface2->format, &color.r, &color.g, &color.b, &color.a);
 
 drawPixelColor(x, y + worldHeight/2, color.r, color.g, color.b);
 
 }
 }
 
 SDL_UnlockSurface(surface3);
 
 SDL_Texture* frameTexture = SDL_CreateTextureFromSurface(renderer, surface3);
 
 SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
 
 SDL_DestroyTexture(frameTexture);
 
 
 }
