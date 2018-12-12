#ifndef MENU_ENGINE_H
#define MENU_ENGINE_H
#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play();
  int getOptionChoice() const { return optionChoice; }
  int getTrackNumber() const {return track;}
  void setTrack(int track) {track = track;};
private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;
  int optionChoice;
  int track;

  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
#endif