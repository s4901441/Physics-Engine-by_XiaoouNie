#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H
#include "Particles.h"

class Emitter;
class ParticleFactory
{
public:
  Particles *CreateParticles(ParticleType _type,ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass,const std::string &_shaderName,Emitter *_parent,ngl::Colour _c);
private:
};

#endif // PARTICLEFACTORY_H
