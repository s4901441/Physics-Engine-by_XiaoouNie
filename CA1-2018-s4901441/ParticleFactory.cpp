#include "ParticleFactory.h"
#include "sphere.h"

#include "cube.h"
#include "plane.h"
Particles *ParticleFactory::CreateParticles(ParticleType _type,ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass,const std::string &_shaderName,Emitter *_parent,ngl::Colour _c)
{
  if(_type==ParticleType::SPHERE)
  {
    return new sphere(_P,_v,_f,_mass,_shaderName,_parent,_c);
  }

  if(_type==ParticleType::CUBE)
  {
    return new cube(_P,_v,_f,_mass,_shaderName,_parent,_c);
  }
  if(_type==ParticleType::PLANE)
  {
    return new plane(_P,_v,_f,_mass,_shaderName,_parent,_c);
  }
  else return nullptr;
}
