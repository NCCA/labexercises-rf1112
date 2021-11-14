#include "Walker.h"
#include <iostream>

std::random_device g_rd;
std::seed_seq g_seed{g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd(), g_rd()};
std::mt19937 g_rng(g_seed);
std::uniform_int_distribution<>g_walkDir(-1,1);

Walker::Walker(size_t _w, size_t _h)
{
    m_map = std::make_unique<Image> (_w, _h, 255, 255, 255, 0);
    initRNG();
}

void Walker::setImageSeed(size_t _x, size_t _y)
{
    m_map->setPixel(_x, _y, 255, 0, 0, 255);
}

void Walker::saveImage(const std::string &_fname) const
{
    m_map->write(_fname);
}

void Walker::initRNG()
{
    m_xRand = std::uniform_int_distribution<>(1, m_map->width()-1);
    m_yRand = std::uniform_int_distribution<>(1, m_map->height()-1);
}

void Walker::randomImageSeed()
{
    m_map->setPixel(m_xRand(g_rng), m_yRand(g_rng), 255, 0, 0, 255);
}

bool Walker::walk()
{
    while (m_xpos>0 && m_xpos<m_map->width() && m_ypos>0 && m_ypos<m_map->height())
    {
        // std::cout<<"Walk "<<m_xpos<<' '<<m_ypos<<'\n';
        for(int i=-1; i<=1; ++i)
        {
            for(int j=-1; j<=1; ++j)
            {
                if(m_map->getPixel(m_xpos+i, m_ypos+j).a == 255)
                {
                    std::cout<<"Set Pixel "<<m_xpos<<' '<<m_ypos<<'\n';
                    m_map->setPixel(m_xpos, m_ypos, 0, 0, 0, 255);
                    return true;
                }
            }
        }
        m_xpos += g_walkDir(g_rng);
        m_ypos += g_walkDir(g_rng);
    }
    std::cout<<"Out of Range "<<m_xpos<<' '<<m_xpos<<'\n';
    return false;
}

void Walker::resetStart()
{
    m_xpos = m_xRand(g_rng);
    m_ypos = m_yRand(g_rng);
    std::cout<<"New Start "<<m_xpos<<' '<<m_ypos<<'\n';
}
