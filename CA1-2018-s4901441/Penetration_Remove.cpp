#include "Emitter.h"
#include "IntersectingData.h"
#include <cmath>

//Removes penetration (especially with plane)
void Emitter::Penetration_Remove(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other, IntersectingData _temp)
{
  //this is contact normal
  ngl::Vec3 contactNormal = _temp.GetDirection();
  ngl::Vec3 invert_dir = -1*contactNormal;
  invert_dir.normalize();
  contactNormal.normalize();

  float penetration_distance = _temp.GetDistance();
//sphere_plane,only move the sphere
  if((*_this)->getType()==ParticleType::PLANE &&(*other)->getType()==ParticleType::SPHERE)
  {
    (*other)->setPenetration_distance(penetration_distance*contactNormal);
  }
  //cube_plane,only move the cube
  if((*_this)->getType()==ParticleType::PLANE &&(*other)->getType()==ParticleType::CUBE)
  {
   (*other)->setP(penetration_distance*contactNormal);
  }
}
