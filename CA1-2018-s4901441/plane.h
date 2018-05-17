#ifndef PLANE_H
#define PLANE_H
#include "Particles.h"
#include <vector>
#include <ngl/AbstractVAO.h>
#include <memory>
class plane : public Particles
{
public:
  plane(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
        Emitter *_parent,ngl::Colour _c);
  virtual ~plane();
  void draw() const;
  void update();
  virtual inline ParticleType getType()const {return m_type;}
  virtual void setCollider();


private:
  const static ParticleType m_type = ParticleType::PLANE;
  ngl::Vec3 m_normal;
  float m_distance;
  std::vector<ngl::Vec3> verts;
  std::unique_ptr<ngl::AbstractVAO> m_vao;

};

#endif // PLANE_H
