#include "Emitter.h"
#include "IntersectingData.h"
#include <cmath>
void Emitter::CollisionResponse(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other,IntersectingData _temp)
{
  ngl::Vec3 contactNormal = _temp.GetDirection();//this is contact normal
  ngl::Vec3 invert_dir = -1*contactNormal;
  contactNormal.normalize();
  invert_dir.normalize();

  //Calculate linear collision momentum for both particles
  float d1 = ((*_this)->GetCurrentMomentum()).dot(invert_dir);
  float j1 =-(1+(*_this)->GetCoefficient())*d1;
  float d2 = ((*other)->Get_total_Momentum()).dot(contactNormal);
  float j2 = (-(1+(*other)->GetCoefficient())*d2);

  if ((*_this)->getType()==ParticleType::SPHERE && (*other)->getType()==ParticleType::SPHERE)//sphere-sphere collision
    {
    (*_this)->set_LinearMomentum(j1*invert_dir);
    (*other)->set_LinearMomentum(j2*contactNormal);
    (*_this)->set_active();
    (*other)->set_active();
   }
  if((*_this)->getType()==ParticleType::PLANE &&(*other)->getType()==ParticleType::SPHERE) //sphere-plane
  {

    if((*other)->get_bouncing_count()>7)
    {

      (*other)->set_bouncingClamp(true);

    }

    //force particles to stop by reducing linear collision momentum
    if((*other)->get_bouncing_count()>=4&&(*other)->get_bouncing_count()<=7)
    {

      j2*=0.25*(7-(*other)->get_bouncing_count());

    }

    //force particles to slide along the plane if the linear momentum is too small
    if ((*other)->Get_total_Momentum().length() < 0.01f)
    {
      (*other)->set_stop();
      ngl::Vec3 velocity_sliding = ((*other)->Getv())-((*other)->Getv().dot(contactNormal)*contactNormal);
      velocity_sliding.m_y = 0;
      (*other)->setv(velocity_sliding);
    }

    else
    {
      (*other)->set_LinearMomentum(j2*contactNormal);
      (*other)->set_Collision_Flag(true);
      (*other)->increase_bouncing_count();
    }

  }
  //plane-cube
    if((*_this)->getType()==ParticleType::PLANE &&(*other)->getType()==ParticleType::CUBE)
    {
      if((*other)->get_bouncing_count()>8)
    {

      (*other)->set_bouncingClamp(true);

    }
   //force to stop by reducing linear collision momentum
    if((*other)->get_bouncing_count()>=4&&(*other)->get_bouncing_count()<=8)
    {

      j2*=0.2*(8-(*other)->get_bouncing_count());

    }
    if ((*other)->Get_total_Momentum().length() < 0.01f)
    {
      (*other)->set_stop();
      ngl::Vec3 velocity_sliding = ((*other)->Getv())-((*other)->Getv().dot(contactNormal)*contactNormal);
      velocity_sliding.m_y = 0;
      (*other)->setv(velocity_sliding);
    }

    else
    {
      (*other)->set_LinearMomentum(j2*contactNormal);
      (*other)->set_Collision_Flag(true);
      (*other)->increase_bouncing_count();
    }

  }
  //cube-cube
  if((*_this)->getType()==ParticleType::CUBE &&(*other)->getType()==ParticleType::CUBE)
  {

    (*_this)->set_LinearMomentum(j1*invert_dir);
    (*other)->set_LinearMomentum(j2*contactNormal);
    (*_this)->set_active();
    (*other)->set_active();
  }
}
