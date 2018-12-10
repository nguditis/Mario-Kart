#include "AngularSprite.h"
#include "gameData.h"
#include "imageFactory.h"


AngularSprite::AngularSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
//Track vector goes here
//

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

AngularSprite::AngularSprite(const AngularSprite& s) :
  Drawable(s),
  image(s.image),
  track(s.track),
  sky(s.sky),
  grass(s.grass),
  blocks(s.blocks),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

AngularSprite& AngularSprite::operator=(const AngularSprite& s) {
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


void AngularSprite::update(Uint32 ticks){}
bool AngularSprite::update(Uint32 ticks, int direction, float p_x, float p_y)
{
    if(direction == 1)
    {
        //fNear -= 0.1f * ticks;
        fWorldA -= 0.1f;
        bool onGrass = checkOffTrack(p_x, p_y, grass)
        bool blocked = checkBounds(p_x, p_y, blocks);
        
        if (onGrass) {
            //change factor/velocity
        }
        
        if(!blocked)
        {
            fWorldA += 0.3f;
        }
        return blocked;
        //fNear -= 0.1f * ticks;
        fWorldA -= factor;
    }
    else if (direction == 2)
    {
        //fNear += 0.1f * ticks;
        fWorldA += 0.1f;
        bool onGrass = checkOffTrack(p_x, p_y, grass)
        bool blocked = checkBounds(p_x, p_y, blocks);
        
        if (onGrass) {
            //change factor/velocity
        }
        
        if(!blocked)
        {
            fWorldA -= 0.3f;
        }
        return blocked;
        //fNear += 0.1f * ticks;
        fWorldA += factor;
    }
    else if(direction ==3)
    {
        fWorldX += cosf(fWorldA) * 0.1f * ticks;
        fWorldY += sinf(fWorldA) * 0.1f * ticks;
        bool onGrass = checkOffTrack(p_x, p_y, grass)
        bool blocked = checkBounds(p_x, p_y, blocks);
        if (onGrass) {
            //change factor/velocity
        }
        if(!blocked)
        {
            fWorldX -= cosf(fWorldA) * 0.3f * ticks;
            fWorldY -= sinf(fWorldA) * 0.3f * ticks;
        }
        return blocked;
        fWorldX += cosf(fWorldA) * factor* ticks;
        fWorldY += sinf(fWorldA) * factor * ticks;
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
        fWorldX -= cosf(fWorldA) * factor * ticks;
        fWorldY -= sinf(fWorldA) * factor * ticks;
    }
    return true;
  }



bool AngularSprite::mapCheck(int x, int y, SDL_Surface *toTest){
    
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
    SDL_LockSurface(toTest);
    Uint32 *pixels = (Uint32*)toTest->pixels;
    Uint32 pixel = pixels[(int(fSampleY) * toTest->pitch / 4) + int(fSampleX)];
    SDL_Color color;
    //SDL_LockSurface(surface2);
    SDL_GetRGBA(pixel, toTest->format, &color.r, &color.g, &color.b, &color.a);
    SDL_UnlockSurface(toTest);
    
    if ( int(color.a) == 255 ) {
        return true;
    }
    else
        return false;
}



bool AngularSprite::checkOffTrack(int x, int y, SDL_Surface* g)
{
    if(mapCheck(x,y,g))
    {
        return true;//0.0f;
    }
    return false;//0.2f;
}

bool AngularSprite::checkBounds(int x, int y, SDL_Surface* b)
{
    //SDL_GetRGBA(pixel2, surface2->format, &color2.r, &color2.g, &color2.b, &color2.a);
    if(mapCheck(x,y,b) || fSampleY < 0 || fSampleX < 0 || fSampleX > 1024 || fSampleY>1024)
    {
      return false;
    }
    return true;
}



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
}
