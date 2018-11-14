#include "ioMod.h"
#include "vector2f.h"
#include "renderContext.h"

ImageFactory& ImageFactory::getInstance() {    
  static ImageFactory instance;
  return instance;
}

ImageFactory::~ImageFactory() {
  std::cout << "Deleting images in Factory" << std::endl;
  // Free single image containers
  std::map<std::string, SDL_Surface*> ::const_iterator ptr1 = surfaces.begin();
  std::map<std::string, SDL_Texture*> ::const_iterator ptr2 = textures.begin();
  std::map<std::string, Image*> ::const_iterator ptr3 = images.begin();
  while(ptr1!= surfaces.end()) {SDL_FreeSurface(ptr1->second); ptr1++;}
  while(ptr2!= textures.end()) {SDL_DestroyTexture(ptr2->second); ptr2++;}
  while(ptr3!= images.end()) {
    std::cout << "deleting " << ptr3->first << std::endl;
    delete ptr3->second;
    ptr3++;
  }

  // Free multi-image containers
  std::map<std::string, std::vector<SDL_Surface*>>::iterator ptr4 = multiSurfaces.begin();
  while(ptr4 != multiSurfaces.end()){
    for (unsigned int i = 0; i < (*ptr4).second.size(); ++i) {  //get the size of each vector using surfaces.second.size() 
      SDL_FreeSurface( (*ptr4).second[i]);    //iterating through the vector using []. can use better methods here              
    }
    ++ptr4;
  } 
  
  for ( auto textures : multiTextures ) {  
    for (unsigned int i = 0; i < textures.second.size(); ++i) {
      SDL_DestroyTexture( textures.second[i] );
    }
  }

  for ( auto images : multiImages ) {
    std::cout << "deleting " << images.first << std::endl;
    for (unsigned int i = 0; i < images.second.size(); ++i) {
      delete images.second[i];
    }
  }
}


Image* ImageFactory::getImage(const std::string& name) {
    std::map<std::string, Image*>::const_iterator it = images.find(name); 
  if ( it == images.end() ) {
    SDL_Surface * const surface =
      IoMod::getInstance().readSurface( gdata.getXmlStr(name+"/file"));
    bool transparency = gdata.getXmlBool(name+"/transparency");
    if ( transparency ) {
      int keyColor = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
      SDL_SetColorKey(surface, SDL_TRUE, keyColor);
    }
    surfaces[name] = surface;
    Image * const image =new Image(surface);
    images[name] = image;
    return image;
  }
  else {
    return it->second;
  }
}

Image* ImageFactory::getImage(const std::string& name, const std::string& root) {
    std::map<std::string, Image*>::const_iterator it = images.find(name);
    if ( it == images.end() ) {
        SDL_Surface * const surface =
        IoMod::getInstance().readSurface( gdata.getXmlStr(name));
        bool transparency = gdata.getXmlBool(root+"/transparency");
        if ( transparency ) {
            int keyColor = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
            SDL_SetColorKey(surface, SDL_TRUE, keyColor);
        }
        surfaces[name] = surface;
        Image * const image =new Image(surface);
        images[name] = image;
        return image;
    }
    else {
        return it->second;
    }
}

std::vector<Image*> ImageFactory::getImages(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Image*> >::const_iterator 
    pos = multiImages.find(name); 
  if ( pos != multiImages.end() ) {
    return pos->second;
  }

  IoMod& iomod = IoMod::getInstance();
  RenderContext &renderContext  = RenderContext::getInstance();
  std::string sheetPath = gdata.getXmlStr(name+"/file");
  SDL_Surface* spriteSurface = iomod.readSurface(sheetPath);
  bool transparency = gdata.getXmlBool(name+"/transparency");

  // It wasn't in the map, so we have to make the vector of Images:
  unsigned numberOfFrames = gdata.getXmlInt(name+"/frames");
  std::vector<Image*> images;
  std::vector<SDL_Surface*> surfaces;
  std::vector<SDL_Texture*> textures;
  images.reserve(numberOfFrames);
  surfaces.reserve(numberOfFrames);
  textures.reserve(numberOfFrames);

  int width = spriteSurface->w/numberOfFrames;
  int height = spriteSurface->h;

  if(  gdata.checkTag(name+"/imageWidth") 
    && gdata.checkTag(name+"/imageHeight") ){
    width  = gdata.getXmlInt(name+"/imageWidth");
    height = gdata.getXmlInt(name+"/imageHeight");
  }

  SpriteSheet sheet(spriteSurface,width,height);

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    SDL_Surface* surface = sheet[i];
    if ( transparency ) {
      int keyColor = SDL_MapRGBA(spriteSurface->format, 255, 255, 255, 255);
      SDL_SetColorKey(surface, SDL_TRUE, keyColor);
    }
    SDL_Texture* texture = 
      SDL_CreateTextureFromSurface(renderContext.getRenderer(),surface);
    surfaces.push_back( surface );
    textures.push_back( texture );
    images.push_back( new Image(surface) );
  }
  multiSurfaces[name] = surfaces;
  multiTextures[name] = textures;
  multiImages[name] = images;
  return images;
}

