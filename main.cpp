// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"
#include "tracks.h"

int main(int, char*[]) {
    
    std::vector<Tracks> Mushroom {
        Tracks("Mario_Circut_1"),
        Tracks("Donut_Plains_1"),
        Tracks("Ghost_Valley_1"),
        Tracks("Bowser_Castle_1"),
        Tracks("Mario_Circut_2")};
    
    std::vector<Tracks> Flower {
        Tracks("Choco_Island_1"),
        Tracks("Ghost_Valley_2"),
        Tracks("Donut_Plains_2"),
        Tracks("Bowser_Castle_2"),
        Tracks("Mario_Circut_3")};
    
    std::vector<Tracks> Star {
        Tracks("Koopa_Beach_1"),
        Tracks("Choco_Island_2"),
        Tracks("Vanilla_Lake_1"),
        Tracks("Bowser_Castle_3"),
        Tracks("Mario_Circut_4")};
    
    std::vector<Tracks> Special {
        Tracks("Donut_Plains_3"),
        Tracks("Koopa_Beach_2"),
        Tracks("Ghost_Valley_3"),
        Tracks("Vanilla_Lake_2"),
        Tracks("Rainbow_Road")};
    
    std::vector<std::vector<Tracks>> Cups {Mushroom, Flower, Star, Special};
    
    
   try {
      Engine *engine = new Engine(Cups[0], 2);

      engine->play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}

