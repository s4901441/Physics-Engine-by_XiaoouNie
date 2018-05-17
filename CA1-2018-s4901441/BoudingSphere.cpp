#include "BoudingSphere.h"
#include <ngl/Vec3.h>
BoundingSphere::BoundingSphere(ngl::Vec3 _center, float radius): Collider(Collider::TYPE_SPHERE)
{
  m_radius = radius;
  m_center = _center;

}

IntersectingData BoundingSphere::IntersectBoundingSphere( BoundingSphere&other)
{
  float radius_sum = m_radius + other.getRadius();
  //contact normal
  ngl::Vec3 direction =(other.getCenter()-m_center);
  float centerDistance = direction.length();
  direction/=centerDistance;
  float distance = centerDistance - radius_sum;
  //second parameter is the contact normal
  return IntersectingData(distance<0,direction*distance);
}


BoundingSphere::~BoundingSphere()
{

}

void BoundingSphere::Transform(ngl::Vec3 translation)
{
  m_center += translation;
}

