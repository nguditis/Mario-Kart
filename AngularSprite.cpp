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
  image( ImageFactory::getInstance().getImage(name+"/tracks/Donut_Plains_1/full", name) ),
  surface1( IMG_Load(Gamedata::getInstance().getXmlStr("sky/file").c_str())),
  surface2( IMG_Load(Gamedata::getInstance().getXmlStr("road/tracks/Donut_Plains_1/full").c_str())),
 // pixels ((Uint32*)surface->pixels),
  worldWidth(Gamedata::getInstance().getXmlInt("background/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("background/height"))
{ }

AngularSprite::AngularSprite(const AngularSprite& s) :
  Drawable(s),
  image(s.image),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

AngularSprite& AngularSprite::operator=(const AngularSprite& s) {
  Drawable::operator=(s);
  image = (s.image);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void AngularSprite::update(Uint32 ticks){}
void AngularSprite::update(Uint32 ticks, int direction)
{
    if(direction == 1)
    {
      //fNear -= 0.1f * ticks;
      fWorldA -= 0.2f;
    }
    else if (direction == 2)
    {
      fWorldA += 0.2f;
      //fNear += 0.1f * ticks;
    }
    else if(direction ==3)
    {
      fWorldX += cosf(fWorldA) * 0.2f * ticks;
      fWorldY += sinf(fWorldA) * 0.2f * ticks;
    }
    else if (direction == 4)
    {
      fWorldX -= cosf(fWorldA) * 0.2f * ticks;
      fWorldY -= sinf(fWorldA) * 0.2f * ticks;
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
void AngularSprite::draw(SDL_Renderer *renderer) const{

    SDL_Surface *surface3 = new SDL_Surface;

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

    SDL_LockSurface(surface1);
    SDL_LockSurface(surface2);
    SDL_LockSurface(surface3);

    Uint32 *pixels1 = (Uint32*)surface1->pixels;
    Uint32 *pixels2 = (Uint32*)surface2->pixels;

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
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        //std::cout<<"draw color set "<<std::endl;


        if (fSampleX > 1024) {
          fSampleX = 1024;
          SDL_RenderDrawPoint(renderer, fSampleX, fSampleY);
        }
        if (fSampleY > 1024) {
          fSampleY = 1024;
          SDL_RenderDrawPoint(renderer, fSampleX, fSampleY);
        }
          if (fSampleX < 0) {
              fSampleX = 0;
              SDL_RenderDrawPoint(renderer, fSampleX, fSampleY);
          }
          if (fSampleY < 0) {
              fSampleY = 0;
              SDL_RenderDrawPoint(renderer, fSampleX, fSampleY);
          }
        //std::cout<<fSampleX<<" "<<fSampleY<<std::endl;
        Uint32 pixel1 = pixels1[(int(fSampleY) * surface1->pitch / 4) + int(fSampleX)];
        Uint32 pixel2 = pixels2[(int(fSampleY) * surface2->pitch / 4) + int(fSampleX)];
        // Sample symbol and colour from map sprite, and draw the
        // pixel to the screen
        //SDL_Color color = getPixelColor(fSampleX,fSampleY);

        SDL_GetRGBA(pixel1, surface1->format, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        //std::cout<<"draw color set "<<std::endl;
        SDL_RenderDrawPoint(renderer, x, y);

        SDL_GetRGBA(pixel2, surface2->format, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        //std::cout<<"draw color set "<<std::endl;
        SDL_RenderDrawPoint(renderer, x, y+worldHeight/2);

      }
    }
    SDL_UnlockSurface(surface2);
    SDL_UnlockSurface(surface1);
    SDL_UnlockSurface(surface3);

    //SDL_Texture* texture = image->getTexture();//SDL_CreateTextureFromSurface( renderer,getSurface());

}
