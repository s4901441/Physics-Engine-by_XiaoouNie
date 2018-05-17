#ifndef CUBE_H
#define CUBE_H

#include "Particles.h"
class cube : public Particles
{
public:
  cube(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
       Emitter *_parent,ngl::Colour _c);
  virtual ~cube();
  inline void setEmitAngle(GLfloat _a){m_emitAngle=_a;}
  void draw() const;
  void update();
  virtual inline ParticleType getType()const {return m_type;}
  virtual void setCollider();
private :
  /// @brief the max emission angle for the sphere particle
  GLfloat m_emitAngle;
  /// @brief the current radius for the sphere
  GLfloat m_size;
  /// @brief what type of particle this is
  const static ParticleType m_type=ParticleType::CUBE;
};

#endif // CUBE_H
