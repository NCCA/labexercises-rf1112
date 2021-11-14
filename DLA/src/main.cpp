#include <iostream>
#include <cstdlib>
#include "Walker.h"
#include <fmt/format.h>
#include <cxxopts.hpp>



int main(int argc, char **argv)
{
    cxxopts::Options options("DLA", "Simple DLA simulation");
    options.add_options()
    ("w,width", "image width", cxxopts::value<int>()->default_value("200")) 
    ("h,height", "image height", cxxopts::value<int>()->default_value("200"))
    ("i,iterations", "number of simulation iterations", cxxopts::value<int>()->default_value("10000"))
    ("f,filename", "Basefilename for saving", cxxopts::value<std::string>()->default_value("image"))
    ("p,path", "path to prepend to file", cxxopts::value<std::string>()->default_value("./"))
    ("e,ext", "image file extension", cxxopts::value<std::string>()->default_value("exr"))
    ("t,imageStep", "how many steps before saving an image", cxxopts::value<int>()->default_value("100"))
    ("s,seeds", "number of seeds", cxxopts::value<int>()->default_value("10"))
    ("l,seedPos", "Seeds position (top, bottom, left, right)", cxxopts::value<std::string>()->default_value(""))
    ("c,colour", "enable colour")
    ("r,reverse", "reverse colour")
    ("u,help", "Print usage");

    auto results = options.parse(argc, argv);
    if (results.count("help"))
    {
        std::cout << options.help() << '\n';
        exit(EXIT_FAILURE);
    }
    auto width=results["width"].as<int>();
    auto height=results["height"].as<int>();
    auto iterations=results["iterations"].as<int>();
    auto filename=results["filename"].as<std::string>();
    auto path=results["path"].as<std::string>();
    auto ext=results["ext"].as<std::string>();
    auto imageStep=results["imageStep"].as<int>();
    auto seeds=results["seeds"].as<int>();
    auto colour=results["colour"].as<bool>();
    auto reverse=results["reverse"].as<bool>();
    auto seedPos=results["seedPos"].as<std::string>();

    std::cout<<"DLA\n";
    Walker w(width,height);
    // w.setImageSeed(0,0);
    if(seedPos.compare("top") == 0)
    {
        for(int i=0; i<width; ++i)
            w.setImageSeed(i, 0);
    }
    else if(seedPos.compare("bottom") == 0)
    {
        for(int i=0; i<width; ++i)
            w.setImageSeed(i, height-1);
    }
    else if(seedPos.compare("left") == 0)
    {
        for(int i=0; i<height; ++i)
            w.setImageSeed(0, i);
    }
    else if(seedPos.compare("right") == 0)
    {
        for(int i=0; i<width; ++i)
            w.setImageSeed(width-1, i);
    }
    else
    {
        for(int i=0; i<seeds; ++i)
            w.randomImageSeed();
    }   
    int simCount = 0;
    int imageIndex = 0;
    for(int i=0; i<iterations; ++i)
    {
        w.resetStart();
        if(w.walk(iterations, colour, reverse) == true)
        {
            if(!(simCount++ %imageStep))
                w.saveImage(fmt::format("{}{}{:04d}.{}", path, filename, imageIndex++, ext));
        }
    }
    w.saveImage(fmt::format("../images/{}.jpg", filename));
    return EXIT_SUCCESS;
}