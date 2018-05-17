#ifndef INTERSECTINGDATA_H
#define INTERSECTINGDATA_H
#include <ngl/Vec3.h>
class IntersectingData
{
public:
  IntersectingData(bool _doesIntersect,ngl::Vec3 _direction);
  ~IntersectingData();
  inline bool CheckIntersect() const {return m_doesIntersect;}
  inline float GetDistance() const {return m_direction.length();}
  inline ngl::Vec3 GetDirection() const{return m_direction;}
private:
  bool m_doesIntersect;
  ngl::Vec3 m_direction;
};



#endif // INTERSECTINGDATA_H
