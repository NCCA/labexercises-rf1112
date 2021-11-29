#include <iostream>
#include <chrono>
#include "Emitter.h"

int main()
{
  std::cout<<"Particle System\n";
  Emitter e(300);
  for(int i=0; i<50; ++i)
  {
    e.update();
    // std::cout<<"*******************************\n";
    // e.render();
    e.saveFrame(i);
  }
  return EXIT_SUCCESS;
}