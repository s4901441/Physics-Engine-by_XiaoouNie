#include "CollidePlane.h"
#include <cmath>
#include <iostream>
CollidePlane::CollidePlane(ngl::Vec3 _normal, float _distance):Collider(Collider::TYPE_PLANE)
{
  m_normal = _normal;
  m_distance = _distance;
}
CollidePlane CollidePlane::Normalized()
{
  float magnitude = m_normal.length();

  return CollidePlane(m_normal/magnitude, m_distance/magnitude);
}

CollidePlane::~CollidePlane()
{

}

IntersectingData CollidePlane::PlaneIntersectBoundingSphere(BoundingSphere&other)
{
  //calculate distance from sphere center along plane normal
  //and add the plane distance(e.g, the plane is one unit above the (0,0,0),)
  float distance_fromSphereCenter =fabs((other.getCenter()).dot(m_normal)+m_distance);
  float distanceFromSphere = distance_fromSphereCenter - other.getRadius();
  m_normal.normalize();
  return IntersectingData(distanceFromSphere<0, m_normal*fabs(distanceFromSphere));
}

IntersectingData CollidePlane::PlaneIntersectAABB(AABB &other)
{
  float distance_from_AABB_center = fabs((other.getCenter()).dot(m_normal)+m_distance);
  float distance_from_AABB = distance_from_AABB_center - other.getScale()/2.0f; ;
  m_normal.normalize();

  return IntersectingData(distance_from_AABB<0, m_normal*fabs(distance_from_AABB));

}
void CollidePlane::Transform(ngl::Vec3 translation)
{
  m_normal += translation;
}
