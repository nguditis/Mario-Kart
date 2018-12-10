#ifndef TRACKS__H
#define TRACKS__H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>



class Tracks {
public:
    Tracks(std::string name);
    std::vector<Tracks> Cup(int cup);
    std::string getName();
    SDL_Surface* getFull();
    SDL_Surface* getTrack();
    SDL_Surface* getBounds();
    SDL_Surface* getWater();
    SDL_Surface* getGrass();
    SDL_Surface* getLightWater();
    SDL_Surface* getDarkWater();
    SDL_Surface* getDirt();
    SDL_Surface* getJump();
    SDL_Surface* getLava();
    SDL_Surface* getEmpty();

private:
    std::string name;
    SDL_Surface *full;
    SDL_Surface *track;
    SDL_Surface *bounds;
    SDL_Surface *water;
    SDL_Surface *grass;
    SDL_Surface *lightWater;
    SDL_Surface *darkWater;
    SDL_Surface *dirt;
    SDL_Surface *jump;
    SDL_Surface *lava;
    SDL_Surface *empty;

};
#endif
