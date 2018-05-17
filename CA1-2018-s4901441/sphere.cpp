#include "sphere.h"
#include "Emitter.h"

#include <cmath>
#include <ngl/Util.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Random.h>
#include <ngl/ShaderLib.h>

sphere::sphere(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
               Emitter *_parent,ngl::Colour _c) : Particles (_P,_v,_f,_mass,_shaderName,_parent)
{
  m_emitAngle=360.0f;
  // get the angles for emission

  ngl::Random *rng=ngl::Random::instance();
  GLfloat theta =ngl::radians(rng->randomNumber(m_emitAngle));
  GLfloat phi = ngl::radians(rng->randomNumber(m_emitAngle));

  v.m_x=sinf(theta)*cosf(phi);
  v.m_y=sinf(theta)*sinf(phi);
  v.m_z=cosf(theta);
  v.normalize();
  m_radius = 0.300000f;
  P += _P;
  v += _v;
  mass = _mass;
  f= _f;
  m_shaderName = _shaderName;

  ngl::Colour custom_color(1,0,0);
  Cd = custom_color;
  friction_coefficient=0.20000f;
  coefficient_restitution = 0.5f;
  m_collider = NULL;
}


sphere::~sphere()
{
  if(m_collider!= NULL)
  {
     delete m_collider;
  }
}

void sphere::draw() const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["blinn"]->use();
  shader->setUniform("Colour",1.0f,0.0f,0.0f,1.0f);

  ngl::Transformation t;
  t.setPosition(P);
  t.setScale(m_radius,m_radius,m_radius);
  ngl::Mat4 MVP=m_parent->getCamera()->getVPMatrix() *
                m_parent->getGlobalTransform() *
                t.getMatrix();
  shader->setUniform("MVP",MVP);

  // get an instance of the VBO primitives for drawing
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  // draw the sphere
  prim->draw("sphere");

}

void sphere::update()   //forces and collision detection
{

  TimeInc = 0.02f;
  //update momentum to calculate velocity
  if(!bouncing_clamp)
    {
    if (!stop)
      {
      ngl::Vec3 momentum_by_force = f*TimeInc;

      ngl::Vec3 momentum_change = momentum_by_force+linear_momentum + friction_momentum;
      //total plus the change in momentum
      total_momentum += momentum_change;
      //change in velocity calculated by change in momentum devided by mass
      v += momentum_change/mass;
  }

  else
  {
    ngl::Vec3 drag_dir = -1*v/v.length();
    ngl::Vec3 drag = mass*f.m_y*friction_coefficient*drag_dir;
    v+=drag*TimeInc;

  }
  //update position

  P+= penetration_remove_distance;

  P += v*TimeInc;

  }

  linear_momentum = 0;
  friction_momentum = 0;
  penetration_remove_distance = ngl::Vec3::zero();
  stop = false;
  m_collision_flag = false;
  bouncing_clamp = false;

}
void sphere::setCollider()
{
  m_collider = new BoundingSphere(P,m_radius);
}
