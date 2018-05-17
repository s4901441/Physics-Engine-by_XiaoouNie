#include "Particles.h"

Particles::Particles( ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass,const std::string &_shaderName,
                      Emitter *_parent)

{
  P = _P;
  v = _v;
  f = _f;
  mass = _mass;
  m_shaderName=_shaderName;
  m_oldP = P;
  m_parent=_parent;
  linear_momentum= 0;
  friction_momentum = 0;
  coefficient_restitution = 0.5f;
  total_momentum = mass*v;//initialize the total momentum
  stop = false;
  bouncing_clamp = false;
  m_collision_flag = false;
  m_bouncing_count = 0;
}

Particles::~Particles()
{

}


Collider& Particles::createCollider()
{
  ngl::Vec3 my_translation = P - m_oldP;
  m_oldP = P;
  m_collider->Transform(my_translation);
  return *m_collider;
}
