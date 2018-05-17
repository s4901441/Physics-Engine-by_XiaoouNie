#ifndef BOUDINGSPHERE_H
#define BOUDINGSPHERE_H
#include "IntersectingData.h"
#include "Collider.h"

#include<cmath>
#include <ngl/Vec3.h>

class BoundingSphere : public Collider
{
public:
  BoundingSphere(ngl::Vec3 _center, float radius);
  ~BoundingSphere();

  IntersectingData IntersectBoundingSphere(BoundingSphere&other);
  virtual void Transform(ngl::Vec3 translation);

  inline ngl::Vec3 getCenter() {return m_center;}
  inline float getRadius() const {return m_radius;}
  //inline BoundingSphere getmyself(){return *this;}
private:
  ngl::Vec3 m_center;
  float m_radius;
};

#endif // BOUDINGSPHERE_H
