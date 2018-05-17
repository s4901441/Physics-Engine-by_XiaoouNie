#ifndef SPHERE_H
#define SPHERE_H

#include "Particles.h"

#include "BoudingSphere.h"
class sphere : public Particles  //create a chiled class of "Particles" class
{
public:
  sphere(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
         Emitter *_parent,ngl::Colour _c);
  virtual ~sphere();
  inline void setEmitAngle(GLfloat _a){m_emitAngle=_a;}
   void draw() const;
   void update();

  virtual inline ParticleType getType()const {return m_type;}
  virtual void setCollider();
private :
  /// @brief the max emission angle for the sphere particle
  GLfloat m_emitAngle;
  /// @brief the current radius for the sphere
  GLfloat m_radius;
  /// @brief what type of particle this is
  const static ParticleType m_type=ParticleType::SPHERE;


};

#endif // SPHERE_H
