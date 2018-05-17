#include "IntersectingData.h"

IntersectingData::IntersectingData(bool _doesIntersect,ngl::Vec3 _direction)
{
  m_doesIntersect = _doesIntersect;
  m_direction= _direction;

}
IntersectingData::~IntersectingData()
{

}
