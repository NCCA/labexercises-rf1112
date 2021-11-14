#include <iostream>
#include <cstdlib>
#include "Walker.h"
#include <fmt/format.h>

int main()
{
    std::cout<<"DLA\n";
    Walker w(200,200);
    w.setImageSeed(0,0);
    for(int i=0; i<20; ++i)
        w.randomImageSeed();
    
    int iterations = 3000;
    int simCount = 0;
    int imageIndex = 0;
    for(int i=0; i<iterations; ++i)
    {
        w.resetStart();
        if(w.walk() == true)
        {
            if(!(simCount++ %100))
                w.saveImage(fmt::format("sim{:04d}.exr", imageIndex++));
        }
    }

    w.saveImage("test.exr");
    return EXIT_SUCCESS;
}