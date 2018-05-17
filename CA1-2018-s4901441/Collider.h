#ifndef COLLIDER_H
#define COLLIDER_H

#include "IntersectingData.h"
#include "ngl/Vec3.h"

class Collider
{
public:
  Collider(int _type);

  inline int getType() const {return m_type;}
  virtual ~Collider();
  enum
  {
    TYPE_SPHERE,
    TYPE_AABB,
    TYPE_PLANE
  };
  IntersectingData Intersect( Collider&other);
  virtual void Transform(ngl::Vec3 translation);


private:
  int m_type;
};

#endif // COLLIDER_H
