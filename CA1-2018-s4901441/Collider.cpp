#include "Collider.h"
#include "BoudingSphere.h"
#include"AABB.h"
#include "CollidePlane.h"
#include <iostream>
Collider::Collider(int _type)
{
  m_type = _type;
}
Collider::~Collider()
{

}
IntersectingData Collider::Intersect(Collider&other)
{
  if(m_type == TYPE_SPHERE && other.getType() == TYPE_SPHERE)
  {
  BoundingSphere *self = dynamic_cast<BoundingSphere*>(this);

  return self->IntersectBoundingSphere((BoundingSphere&)other);


  }
   if(m_type == TYPE_PLANE && other.getType() == TYPE_SPHERE)
   {

     CollidePlane*self = dynamic_cast<CollidePlane*>(this);

     return self->PlaneIntersectBoundingSphere((BoundingSphere&)other);
    }
   if(m_type == TYPE_PLANE && other.getType() == TYPE_AABB)
   {
     CollidePlane*self = dynamic_cast<CollidePlane*>(this);
     return self->PlaneIntersectAABB((AABB&)other);
   }
   if(m_type == TYPE_AABB && other.getType() == TYPE_AABB)
   {
     AABB *self = dynamic_cast<AABB*>(this);

     return self->IntersectAABB((AABB&)other);

   }
   else
  {
     return  IntersectingData(false,ngl::Vec3(0,0,0));
  }

}
void Collider::Transform(ngl::Vec3 translation)
{
  translation = {0.0f,0.0f,0.0f};
}
