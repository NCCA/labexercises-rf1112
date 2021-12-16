#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
//#include "Particle.h"
#include <ngl/Vec3.h>
#include <ngl/SimpleVAO.h>
#include <memory>

class Emitter
{
    public:
        Emitter()=default;
        // Emitter(const Emitter &)=default;
        Emitter(size_t _numParticles, const ngl::Vec3 &_emitDir);
        void update();
        void render() const;
        size_t numParticles() const;
        void saveFrame(int _frameNo) const;

    private:
        //std::vector<Particle> m_particles;
        std::vector<ngl::Vec4> m_posSize;
        std::vector<ngl::Vec3> m_dir;
        std::vector<ngl::Vec3> m_colour;
        // float size = 1.0f;
        std::vector<int> m_life;
        std::vector<int> m_maxLife;

        ngl::Vec3 m_emitDir = {0.0f, 1.0f, 0.0f};
        float m_spread = 2.0f;
        size_t m_numParticles;
        void resetParticle(size_t _index);
        std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif