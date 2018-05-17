#ifndef COLLIDEPLANE_H
#define COLLIDEPLANE_H

#include "IntersectingData.h"
#include <ngl/Vec3.h>
#include "BoudingSphere.h"
#include "AABB.h"
class CollidePlane : public Collider
{
public:
  CollidePlane(ngl::Vec3 _normal, float _distance);
  ~CollidePlane();
  CollidePlane Normalized();
  IntersectingData PlaneIntersectBoundingSphere(BoundingSphere&other);
  IntersectingData PlaneIntersectAABB(AABB &other);
  virtual void Transform(ngl::Vec3 translation);
  inline ngl::Vec3 GetNormal() {return m_normal;}
  inline float GetDistance() {return m_distance;}

private:
  ngl::Vec3 m_normal;
  float m_distance;
};

#endif // COLLIDEPLANE_H
