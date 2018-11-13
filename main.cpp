// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"

int main(int, char*[]) {
   try {
      Engine engine;
      engine.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
