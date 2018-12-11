#include "tracks.h"
#include "gameData.h"
#include "SDL_image.h"
#include "image.h"
#include <SDL.h>
#include <vector>

std::string path = "road/tracks/";

Tracks::Tracks(std::string name){
    if (name.find("Bowser") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Bowser_Castle_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/lava").c_str());
            this->empty = nullptr;

        }
        if (name.find("2") != std::string::npos) {
            this->name = "Bowser_Castle_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/lava").c_str());
            this->empty = nullptr;

        }
        if (name.find("3") != std::string::npos) {
            this->name = "Bowser_Castle_3";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/lava").c_str());
            this->empty = nullptr;
        }
    }
    if (name.find("Choco") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Choco_Island_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Choco_Island_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
    }
    if (name.find("Donut") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Donut_Plains_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/water").c_str());
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Donut_Plains_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/water").c_str());
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        if (name.find("3") != std::string::npos) {
            this->name = "Donut_Plains_3";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/water").c_str());
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
    }
    if (name.find("Ghost") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Ghost_Valley_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = nullptr;
            this->empty = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/empty").c_str());
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Ghost_Valley_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            std::cout << "Loading " << this->name << std::endl;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = nullptr;
            this->empty = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/empty").c_str());
        }
        if (name.find("3") != std::string::npos) {
            this->name = "Ghost_Valley_3";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/jump").c_str());
            this->lava = nullptr;
            this->empty = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/empty").c_str());
        }
    }
    if (name.find("Koopa") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Koopa_Beach_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = nullptr;
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/lightWater").c_str());
            this->darkWater = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/darkWater").c_str());
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Koopa_Beach_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = nullptr;
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/lightWater").c_str());
            this->darkWater = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/darkWater").c_str());
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
    }
    if (name.find("Mario") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Mario_Circut_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Mario_Circut_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        if (name.find("3") != std::string::npos) {
            this->name = "Mario_Circut_3";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("4") != std::string::npos) {
            this->name = "Mario_Circut_4";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = nullptr;
            this->grass = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/grass").c_str());
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/dirt").c_str());
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
    }
    if (name.find("Rainbow") != std::string::npos) {
            this->name = "Rainbow_Road";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = nullptr;
            this->water = nullptr;
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/empty").c_str());
    }
    if (name.find("Vanilla") != std::string::npos) {
        if (name.find("1") != std::string::npos) {
            this->name = "Vanilla_Lake_1";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/water").c_str());
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
        
        if (name.find("2") != std::string::npos) {
            this->name = "Vanilla_Lake_2";
            std::cout << "Loading " << this->name << std::endl;
            this->full = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/full").c_str());
            this->track = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/track").c_str());
            this->bounds = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/boundry").c_str());
            this->water = IMG_Load(Gamedata::getInstance().getXmlStr(path+name+"/water").c_str());
            this->grass = nullptr;
            this->lightWater = nullptr;
            this->darkWater = nullptr;
            this->dirt = nullptr;
            this->jump = nullptr;
            this->lava = nullptr;
            this->empty = nullptr;
        }
    }
}

std::vector<Tracks> Tracks::Cup(int cup){
    std::vector <Tracks> Mushroom, Flower, Star, Special;
    switch (cup) {
        case 1:
            std::cout << "Loading Mushroom Cup" << std::endl;
            Mushroom.reserve(5);
            Mushroom.push_back(Tracks("Mario_Circut_1"));
            Mushroom.push_back(Tracks("Donut_Plains_1"));
            Mushroom.push_back(Tracks("Ghost_Valley_1"));
            Mushroom.push_back(Tracks("Bowser_Castle_1"));
            Mushroom.push_back(Tracks("Mario_Circut_2"));
            
            for (Tracks t : Mushroom) {
                std::cout << "Loaded " << t.getName() << "succsesfull" << std::endl;
            }
            return Mushroom;
            break;
            
        case 2:
            std::cout << "Loading Flower Cup" << std::endl;
            Flower.reserve(5);
            Flower.push_back(Tracks("Choco_Island_1"));
            Flower.push_back(Tracks("Ghost_Valley_2"));
            Flower.push_back(Tracks("Donut_Plains_2"));
            Flower.push_back(Tracks("Bowser_Castle_1"));
            Flower.push_back(Tracks("Mario_Circut_3"));
            
            for (Tracks t : Flower) {
                std::cout << "Loaded " << t.getName() << "succsesfull" << std::endl;
            }
            return Flower;
            break;
            
        case 3:
            std::cout << "Loading Star Cup" << std::endl;
            Star.reserve(5);
            Star.push_back(Tracks("Koopa_Beach_1"));
            Star.push_back(Tracks("Choco_Island_2"));
            Star.push_back(Tracks("Vanilla_Lake_1"));
            Star.push_back(Tracks("Bowser_Castle_3"));
            Star.push_back(Tracks("Mario_Circut_4"));
            
            for (Tracks t : Flower) {
                std::cout << "Loaded " << t.getName() << "succsesfull" << std::endl;
            }
            return Star;
            break;
            
        case 4:
            std::cout << "Loading Special Cup" << std::endl;
            Special.reserve(5);
            Special.push_back(Tracks("Donut_Plains_3"));
            Special.push_back(Tracks("Koopa_Beach_2"));
            Special.push_back(Tracks("Ghost_Valley_3"));
            Special.push_back(Tracks("Vanilla_Lake_1"));
            Special.push_back(Tracks("Rainbow_Road"));
            
            for (Tracks t : Flower) {
                std::cout << "Loaded " << t.getName() << "succsesfull" << std::endl;
            }
            return Special;
            break;
            
        default:
            exit(2);
            break;
    }
}


std::string Tracks::getName(){
    return this->name;
}

SDL_Surface* Tracks::getFull(){
    return this->full;
}
SDL_Surface* Tracks::getTrack(){
    return this->track;
}

SDL_Surface* Tracks::getBounds(){
    return this->bounds;
}

SDL_Surface* Tracks::getWater(){
    return this->water;
}

SDL_Surface* Tracks::getGrass(){
    return this->grass;
}

SDL_Surface* Tracks::getLightWater(){
    return this->lightWater;
}

SDL_Surface* Tracks::getDarkWater(){
    return this->darkWater;
}

SDL_Surface* Tracks::getDirt(){
    return this->dirt;
}

SDL_Surface* Tracks::getJump(){
    return this->jump;
}

SDL_Surface* Tracks::getLava(){
    return this->lava;
}

SDL_Surface* Tracks::getEmpty(){
    return this->empty;
}

