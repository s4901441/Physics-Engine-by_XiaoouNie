#ifndef AABB_H
#define AABB_H
#include <ngl/Vec3.h>
#include <cmath>
#include "IntersectingData.h"
#include "Collider.h"

class AABB : public Collider
{
public:
  AABB( ngl::Vec3 center,float _scale);
  ~AABB();
  IntersectingData IntersectAABB(const AABB& other);
  IntersectingData IntersectBoundingSphere(AABB &other);

  inline const ngl::Vec3 GetMinExtends() {return m_minExtends;}
  inline const ngl::Vec3 GetMaxExtends() {return m_maxExtends;}
  inline ngl::Vec3 getCenter() {return m_center;}
  inline float getScale() {return m_scale;}
private:
  ngl::Vec3 m_minExtends;
  ngl::Vec3 m_maxExtends;
  ngl::Vec3 m_center;
  float m_scale;
};

#endif // AABB_H
