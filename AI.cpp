#include "AI.h"
#include "gameData.h"
#include "imageFactory.h"


AI::AI( const std::string& name) :
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

AI::AI(const AI& s) :
  Drawable(s),
  image(s.image),
  track(s.track),
  sky(s.sky),
  grass(s.grass),
  blocks(s.blocks),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

AI& AI::operator=(const AI& s) {
  Drawable::operator=(s);
  image = (s.image);
  track = s.track;
  sky = s.sky;
  grass = s.grass;
  blocks = s.blocks;
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}
bool AI::checkVelocity(Uint32 ticks, int direction, float p_x, float p_y)
{

    if(direction == 1)
    {
      //fNear -= 0.1f * ticks;
      fWorldA -= 0.1f;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldA += 0.3f;
      }
      return blocked;
    }
    else if (direction == 2)
    {
      fWorldA += 0.1f;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldA -= 0.3f;
      }
      return blocked;
    }
    else if(direction ==3)
    {
      fWorldX += cosf(fWorldA) * 0.1f * ticks;
      fWorldY += sinf(fWorldA) * 0.1f * ticks;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldX -= cosf(fWorldA) * 0.3f * ticks;
        fWorldY -= sinf(fWorldA) * 0.3f * ticks;
      }
      return blocked;

    }
    else if (direction == 4)
    {

      fWorldX -= cosf(fWorldA) * 0.1f * ticks;
      fWorldY -= sinf(fWorldA) * 0.1f * ticks;
      bool blocked = CheckNewValue(p_x, p_y);
      if(!blocked)
      {
        fWorldX += cosf(fWorldA) * 0.3f * ticks;
        fWorldY += sinf(fWorldA) * 0.3f * ticks;
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

void AI::update(Uint32 ticks){}
void AI::update(Uint32 ticks, int direction, float factor)
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
float AI::GrassVelocity(int x, int y)
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
bool AI::CheckNewValue(int x, int y)
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
void AI::draw(SDL_Renderer *renderer) const{

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
}
