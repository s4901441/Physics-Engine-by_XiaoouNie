#include "AABB.h"

AABB::AABB(ngl::Vec3 center, float _scale):Collider::Collider(TYPE_AABB)
{
  //compute min/max extends
  float distance = 0.5f*_scale;
  m_center = center;
  float x_min = center.m_x-distance;
  float y_min = center.m_y-distance;
  float z_min = center.m_z-distance;
  float x_max = center.m_x +distance;
  float y_max = center.m_y +distance;
  float z_max = center.m_z +distance;
  m_minExtends = ngl::Vec3(x_min,y_min,z_min);
  m_maxExtends = ngl::Vec3(x_max,y_max,z_max);
  m_scale = _scale;

}

IntersectingData AABB::IntersectAABB(const AABB& other)
{
  ngl::Vec3 distance1 = other.m_minExtends - m_maxExtends;
  ngl::Vec3 distance2 = m_minExtends - other.m_maxExtends;
  //get the distances between all three axes
  float x1 = distance1.m_x;
  float x2 = distance2.m_x;

  float y1 = distance1.m_y;
  float y2 = distance2.m_y;

  float z1 = distance1.m_z;
  float z2 = distance2.m_z;
  //check if any of those is greater than zero
  if (x1>=0)
  {
    return IntersectingData(false, distance1);

  }
  if (x2>=0)
  {
    return IntersectingData(false, distance1 );

  }
  if (y1>=0)
  {
    return IntersectingData(false, distance1 );

  }
  if (y2>=0)
  {
    return IntersectingData(false, distance1 );

  }
  if (z1>=0)
  {
    return IntersectingData(false, distance1 );

  }
  if (z2>=0)
  {
    return IntersectingData(false,distance1 );

  }
  else
  {
    return IntersectingData(true, distance1);
  }
}

IntersectingData AABB::IntersectBoundingSphere(AABB &other)
{

}

AABB::~AABB()
{

}
