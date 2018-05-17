#include "torus.h"
#include "Emitter.h"
#include "BoudingSphere.h"
#include <cmath>
#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Random.h>
#include <ngl/ShaderLib.h>

torus::torus(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
             Emitter *_parent,ngl::Colour _c):Particles (_P,_v,_f,_mass,_shaderName,_parent)
{
  ngl::Random *rng=ngl::Random::instance();
  m_emitAngle=360.0f;
  // get the angles for emission


  GLfloat theta =ngl::radians(rng->randomNumber(m_emitAngle));
  GLfloat phi = ngl::radians(rng->randomNumber(m_emitAngle));

  v.m_x=sinf(theta)*cosf(phi);
  v.m_y=sinf(theta)*sinf(phi);
  v.m_z=cosf(theta);
  v.normalize();
  //m_radius=rng->randomPositiveNumber(1.2f)+0.1f;
  m_radius = 0.3f;
  P += _P;
  v += _v;
  m_rotX=rng->randomNumber(360);
  m_rotY=rng->randomNumber(360);
  m_rotZ=rng->randomNumber(360);

  m_rotUpdateX=rng->randomNumber(10);
  m_rotUpdateY=rng->randomNumber(10);
  m_rotUpdateZ=rng->randomNumber(10);

}
torus::~torus()
{

}

void torus::draw() const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[m_shaderName]->use();
  shader->setUniform("Colour",Cd);

  ngl::Transformation t;
  t.setPosition(P);
  t.setRotation(m_rotX,m_rotY,m_rotZ);;
  ngl::Mat4 MVP=m_parent->getCamera()->getVPMatrix() *
                m_parent->getGlobalTransform() *
                t.getMatrix();

  shader->setUniform("MVP",MVP);

  // get an instance of the VBO primitives for drawing
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  // draw the sphere
  prim->draw("torus");
}

void torus::update()   //forces and collision detection
{
  //calculate force

  //update vel
  v += f/mass * TimeInc;
  //update position
  P += v*TimeInc;
  //collisiondetection("torus");

}
void torus::setCollider()
{
  m_collider = new BoundingSphere(P,m_radius);

}

