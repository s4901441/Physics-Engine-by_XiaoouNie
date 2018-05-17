#include "Emitter.h"
#include "IntersectingData.h"
#include <cmath>

void Emitter::Friction_Impulse_Calc(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other, IntersectingData _temp)
{
  //calculate contact normal
  ngl::Vec3 contactNormal = _temp.GetDirection();
  ngl::Vec3 invert_dir = -1*contactNormal;
  contactNormal.normalize();
  invert_dir.normalize();

  //calculate the inverse direction of friction
  ngl::Vec3 tangent_dir =(*_this)->Getv() - (((*_this)->Getv()).dot(contactNormal))*contactNormal;
  tangent_dir.normalize();
  float j1 = ((*_this)->Get_LinearMomentum().length())*((*_this)->get_frictionCoefficient());

  ngl::Vec3 tangent_dir_other =(*other)->Getv() - (((*other)->Getv()).dot(invert_dir))*invert_dir;
  tangent_dir_other.normalize();
  float j2 = ((*other)->Get_LinearMomentum().length())*((*other)->get_frictionCoefficient());


  (*_this)->set_FrictionMomentum(j1*(-1)*tangent_dir);
  (*other)->set_FrictionMomentum(j2*(-1)*tangent_dir_other);


}
