#include "Emitter.h"
#include <iostream>
#include "Random.h"
#include <fstream>
#include <sstream>
#include <fmt/format.h>

Emitter::Emitter(size_t _numParticles)
{
    Particle p;
    for(size_t i=0; i<_numParticles; ++i)
    {
        p.dir = m_emitDir * Random::randomPositiveFloat() + Random::randomVectorOnSphere() * m_spread;
        p.dir.y = std::abs(p.dir.y);
        m_particles.push_back(p);
    }
}

size_t Emitter::numParticles() const
{
    return m_particles.size();
}

void Emitter::update()
{
    float dt = 0.1f;
    const Vec3 gravity(0.0f, -9.8f, 0.0f);
    for(auto &p : m_particles)
    {
        p.dir += gravity * dt * 0.5f;
        p.pos += p.dir * dt;
        p.size += Random::randomPositiveFloat(0.05f);
        if(++p.life >= p.maxLife)
        {
            p.pos = Vec3(0,0,0);
        }
    }

}

void Emitter::render() const
{
    for(auto p : m_particles)
    {
        std::cout<<p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z<<' ';
        std::cout<<p.dir.x<<' '<<p.dir.y<<' '<<p.dir.z<<'\n';
    }
}

void Emitter::saveFrame(int _frameNo) const
{
    // of = outfile
    std::ofstream file;
    file.open(fmt::format("particle{:04d}.geo", _frameNo+1));
    std::stringstream ss;
    ss << "PGEOMETRY V5\n";
    ss << "NPoints " << m_particles.size() << " NPrims 1\n";
    ss << "NPointGroups 0 NPrimGroups 0\n";
    ss << "NPointAttrib 2  NVertexAttrib 0 NPrimAttrib 1 NAttrib 0\n";
    ss << "PointAttrib\n";
    ss << "Cd 3 float 1 1 1\n";
    ss << "pscale 1 float 1\n";
    for(auto p : m_particles)
    {
        ss << p.pos.x << ' '<< p.pos.y << ' '<< p.pos.z << " 1 (";
        ss << p.colour.x << ' '<< p.colour.y << ' '<< p.colour.z << ' ';
        ss << p.size << ")\n";
    }
    ss << "PrimitiveAttrib\n";
    ss << "generator 1 index 1 papi\n";
    ss << "Part " << m_particles.size() << ' ';
    for(size_t i=0; i<m_particles.size(); ++i)
    {
        ss << i << ' ';
    }
    ss << "[0]\n";
    ss << "beginExtra\n";
    ss << "endExtra\n";
    file<<ss.rdbuf();
    file.close();
}