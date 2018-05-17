#ifndef CLOTH_OBJECT_H
#define CLOTH_OBJECT_H

#include "Cloth_Particle.h"
#include "Emitter.h"
#include <vector>
#include <memory>
#include <algorithm>

class Cloth_object
{
private:
  float m_width; //cloth width
  float m_height; //cloth height
  std::size_t width_num; //Number of particles contained in the width
  std::size_t height_num; //Number of particles contained in the height
  float distance_x;  //distance between the particles in x(width)
  float distance_y; //distance between the particles in x(height)
  float stretching_coefficient;
  float damp_coefficient;
  std::vector<Cloth_Particle> m_particles;
  std::vector<ngl::Vec3> verts;

  std::string m_shaderName;
  std::unique_ptr<ngl::AbstractVAO> m_vao;
 // std::unique_ptr <Emitter> m_parent;
  ngl::Mat4 MouseGlobalTX;
  ngl::Mat4 VPMatrix;
  ngl::Mat4 ViewMatrix;
  std::size_t m_numParticles;

public:
  Cloth_object(const std::string &_shaderName);
  ~Cloth_object();
  void draw();
  void update();
  void Calculate_Cloth_Normal();
  Cloth_Particle* getParticle(unsigned int _x, unsigned int _y);
  ngl::Vec3 Calc_Triangle_Normal(ngl::Vec3 p1, ngl::Vec3 p2,ngl::Vec3 p3);
  inline void setMouseGlobalTX(ngl::Mat4 _MG) {MouseGlobalTX = _MG;}
  inline void setVPMatrix(ngl::Mat4 _VP) {VPMatrix = _VP;}
  inline void setViewMatrix(ngl::Mat4 _V){ViewMatrix = _V;}
  void Calculate_forces(const ngl::Vec3 &_gravity, const ngl::Vec3 &_wind);
};

#endif // CLOTH_OBJECT_H
