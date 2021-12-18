#include "Emitter.h"
#include <iostream>
#include "Random.h"
#include <fstream>
#include <sstream>
#include <fmt/format.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/Util.h>

Emitter::Emitter(size_t _numParticles, const ngl::Vec3 &_emitDir, const ngl::Vec3 &_pos)
{
    m_emitDir = _emitDir;
    m_numParticles = _numParticles;
    m_pos = _pos;
    m_posSize.resize(m_numParticles);
    m_dir.resize(m_numParticles);
    m_colour.resize(m_numParticles);
    m_life.resize(m_numParticles);
    m_maxLife.resize(m_numParticles);
    for (size_t p=0; p<m_numParticles; ++p)
    {
        resetParticle(p);
    }
    m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO, GL_POINTS));
    m_vao->bind();
        m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); //points 0
        m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); //colours 1
    m_vao->unbind();
}

void Emitter::update()
{
    float dt = 0.1f;
    const ngl::Vec3 gravity(0.0f, -9.81f, 0.0f);
    for(size_t i=0; i<m_numParticles; ++i)
    {
        m_dir[i] += gravity * dt * 0.5f;
        m_posSize[i] += m_dir[i] * dt;
        m_posSize[i].m_w += Random::randomPositiveFloat(0.5f);
        if(++m_life[i] >= m_maxLife[i] || m_posSize[i].m_y <= 0.0f)
        {
            resetParticle(i);
        }
    }

}

void Emitter::render() const
{
    m_vao->bind();
        m_vao->setData(0,ngl::MultiBufferVAO::VertexData(m_numParticles*sizeof(ngl::Vec4),m_posSize[0].m_x));
        
        m_vao->setVertexAttributePointer(0,4,GL_FLOAT, 0,0);
        // m_vao->setVertexAttributePointer(1,3,GL_FLOAT, sizeof(Particle),6);
        // m_vao->setVertexAttributePointer(2,1,GL_FLOAT, sizeof(Particle),9);
        m_vao->setData(1,ngl::MultiBufferVAO::VertexData(m_numParticles*sizeof(ngl::Vec3),m_colour[0].m_x));
        m_vao->setVertexAttributePointer(1,3,GL_FLOAT, 0,0);
        
        m_vao->setNumIndices(m_numParticles);
        glEnable(GL_PROGRAM_POINT_SIZE);
        m_vao->draw();
        glDisable(GL_PROGRAM_POINT_SIZE);
   m_vao->unbind();
}

void Emitter::updatePos(float _dx, float _dy, float _dz)
{
    m_pos.m_x += _dx;
    m_pos.m_y += _dy;
    m_pos.m_z += _dz;
}

void Emitter::resetParticle(size_t _index)
{
    if(Random::randomPositiveFloat(500)> 450)
    {
        m_posSize[_index].set(m_pos.m_x,m_pos.m_y,m_pos.m_z, 0.01f);
        m_dir[_index] = m_emitDir * Random::randomPositiveFloat() + Random::randomVectorOnSphere() * m_spread;
        m_dir[_index].m_y = std::abs(m_dir[_index].m_y);
        m_colour[_index] = Random::randomPositiveVec3();
        m_maxLife[_index] = static_cast<int>(Random::randomPositiveFloat(5000)+100);
        m_life[_index] = 0;
    }
    else
    {
        m_dir[_index].set(0.0f, 0.0f, 0.0f);
        m_posSize[_index].set(-1000, -10000, -10000, 0.0f);
        m_maxLife[_index] = 100;
        m_life[_index] = 0;
    }
}