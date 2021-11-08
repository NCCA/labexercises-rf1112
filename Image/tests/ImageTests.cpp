#include "Image.h"
#include <gtest/gtest.h>

TEST(RGBA, ctor)
{
    RGBA a;
    ASSERT_EQ(a.r, 0);
    ASSERT_EQ(a.g, 0);
    ASSERT_EQ(a.b, 0);
    ASSERT_EQ(a.a, 255);
}

TEST(RGBA, userctor)
{
    RGBA a (255,128,64,55);
    ASSERT_EQ(a.r, 255);
    ASSERT_EQ(a.g, 128);
    ASSERT_EQ(a.b, 64);
    ASSERT_EQ(a.a, 55);
}

TEST(IMAGE, ctor)
{
    Image img;
    ASSERT_EQ(img.width(), 0);
    ASSERT_EQ(img.height(), 0);
}

TEST(IMAGE, userctor)
{
    Image img(250,150);
    ASSERT_EQ(img.width(), 250);
    ASSERT_EQ(img.height(), 150);

    for(size_t y=0; y<img.height(); ++y)
    {
        for(size_t x=0; x<img.width(); ++x)
        {
            auto pixel = img.getPixel(x,y);
            ASSERT_EQ(pixel.r,0);
            ASSERT_EQ(pixel.b,0);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.a,255);
        }
    }
}

TEST(IMAGE, userctorColour)
{
    Image img(250, 150, 255, 0, 0, 255);
    ASSERT_EQ(img.width(), 250);
    ASSERT_EQ(img.height(), 150);

    for(size_t y=0; y<img.height(); ++y)
    {
        for(size_t x=0; x<img.width(); ++x)
        {
            auto pixel = img.getPixel(x,y);
            ASSERT_EQ(pixel.r,255);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.b,0);
            ASSERT_EQ(pixel.a,255);
        }
    }
}

TEST(IMAGE, writeToFile)
{
    Image img(1024, 720, 0, 0, 255, 255);
    ASSERT_TRUE(img.write("test.exr"));
}

// TEST(IMAGE, setPixel)
// {
//     Image img(300,100,255,255,255,255);
//     for(int i=0; i<img.width(); ++i)
//     {
//         img.setPixel(i,30,{0,0,255,255});
//         img.setPixel(i,31,{0,255,0,255});
//         img.setPixel(i,32,{255,0,0,255});
//         img.setPixel(i,33,{0,0,0,255});
//     }
//     img.write("test2.exr");
// }

TEST(IMAGE, setPixel)
{
    Image img(100,100,255,255,255,255);
    for(int i=0; i<img.width(); ++i)
    {
        for(int j=30; j<34; ++j)
        {
            img.setPixel(i,j,{100,0,43,54});
        }
    }
    for(int i=0; i<img.width(); ++i)
    {
        for(int j=30; j<34; ++j)
        {
            auto pixel = img.getPixel(i,j);
            ASSERT_EQ(pixel.r,100);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.b,43);
            ASSERT_EQ(pixel.a,54);
        }
    }
}

TEST(IMAGE, setPixelRGBA)
{
    Image img(100,100,255,255,255,255);
    for(int i=0; i<img.width(); ++i)
    {
        for(int j=30; j<34; ++j)
        {
            img.setPixel(i,j,100,0,43,54);
        }
    }
    for(int i=0; i<img.width(); ++i)
    {
        for(int j=30; j<34; ++j)
        {
            auto pixel = img.getPixel(i,j);
            ASSERT_EQ(pixel.r,100);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.b,43);
            ASSERT_EQ(pixel.a,54);
        }
    }
}


TEST(Image, clear)
{
    Image img(1024, 720, 205, 30, 100, 53);
    img.clear();
    for(size_t y=0; y<img.height(); ++y)
    {
        for(size_t x=0; x<img.width(); ++x)
        {
            auto pixel = img.getPixel(x,y);
            ASSERT_EQ(pixel.r,0);
            ASSERT_EQ(pixel.b,0);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.a,255);
        }
    } 
}

TEST(IMAGE,lineHorizontal)
{
    Image a(200,200);

    a.line(0,100,200,101,255,0,0,255);
    RGBA p;
    for(size_t x=0; x<a.width(); ++x)
    {
        p=a.getPixel(x,100);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
    }
    ASSERT_TRUE(a.write("lineh.exr"));
}

TEST(IMAGE,lineVertical)
{
    Image a(200,200);

    a.line(100,0,101,200,255,0,0,255);
    RGBA p;
    for(size_t y=0; y<a.height(); ++y)
    {
        p=a.getPixel(100,y);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
    }
    ASSERT_TRUE(a.write("linev.exr"));
}

TEST(IMAGE,lineHorizontalOutOfRange)
{
    Image a(200,200);

    a.line(0,100,300,101,255,0,0,255);
    RGBA p;
    for(size_t x=0; x<a.width(); ++x)
    {
        p=a.getPixel(x,100);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
        
        p=a.getPixel(x,101);
        ASSERT_EQ(p.r,0);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
    }
    ASSERT_TRUE(a.write("lineho.exr"));
}

TEST(IMAGE,lineVerticalOutOfRange)
{
    Image a(200,200);

    a.line(100,0,101,500,255,0,0,255);
    RGBA p;
    for(size_t y=0; y<a.height(); ++y)
    {
        p=a.getPixel(100,y);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
        
        p=a.getPixel(101,y);
        ASSERT_EQ(p.r,0);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);
    }
    ASSERT_TRUE(a.write("linevo.exr"));
}

TEST(IMAGE,lineOutOfRange)
{
    Image a(200,200);
    a.line(100,200,101,500,255,0,0,255);
    for(size_t y=0; y<a.height(); ++y)
    {
        for(size_t x=0; x<a.width(); ++x)
        {
            auto pixel = a.getPixel(x,y);
            ASSERT_EQ(pixel.r,0);
            ASSERT_EQ(pixel.b,0);
            ASSERT_EQ(pixel.g,0);
            ASSERT_EQ(pixel.a,255);
        }
    }
}