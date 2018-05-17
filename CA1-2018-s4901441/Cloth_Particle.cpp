#include "Cloth_Particle.h"
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>


Cloth_Particle::Cloth_Particle()
{

}

Cloth_Particle::Cloth_Particle(const ngl::Vec3 &_pos, const ngl::Vec3 &_v, const ngl::Vec3 &_f, float _mass, float _sk, float _dk)
{
  m_pos = _pos;
  m_velocity = _v;
  force_total = _f;
  mass = _mass;
  stretching_coefficient = _sk;
  damp_coefficient = _dk;
  TimeInc = 0.02f;
  is_movable = true;
}

Cloth_Particle& Cloth_Particle::operator=( Cloth_Particle& particle)
{
  m_pos = particle.GetPos();
  m_velocity = particle.GetVel();
  force_total = particle.Getforce();
  mass = particle.Getmass();
  stretching_coefficient = particle.Get_sk();
  damp_coefficient = particle.Get_dk();
  TimeInc = 0.02f;
  return *this;
}

void Cloth_Particle::update()
{
  if (is_movable)
  {
  TimeInc = 0.02f;
  m_pos += m_velocity*TimeInc;
  //f = ma
  ngl::Vec3 acceleration = force_total/mass;
  force_total = ngl::Vec3::zero();
  m_velocity += acceleration*TimeInc;
  }
}

void Cloth_Particle::draw(const std::string &_shaderName, const ngl::Mat4 &_Mouse_Global, const ngl::Mat4 &_VP)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[_shaderName]->use();
  shader->setUniform("Colour",0.0f,0.0f,1.0f,1.0f);
  ngl::Transformation t;
  t.setPosition(m_pos);
  t.setScale(0.1f,0.1f,0.1f);
  ngl::Mat4 M = _Mouse_Global* t.getMatrix();
  ngl::Mat4 MVP= _VP *  M;
  shader->setUniform("MVP",MVP);
  // get an instance of the VBO primitives for drawing
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  // draw the sphere
  prim->draw("sphere");
}





