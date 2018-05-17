#include "plane.h"
#include "Emitter.h"
#include "CollidePlane.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/SimpleIndexVAO.h>
#include <ngl/VAOPrimitives.h>

plane::plane(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
          Emitter *_parent,ngl::Colour _c) : Particles (_P,_v,_f,_mass,_shaderName,_parent)
{
    m_distance = 0.0f;
    P = ngl::Vec3(0.0f,m_distance,0.0f);
      v += _v;
      mass = _mass;
      f= _f;
      m_shaderName = _shaderName;
      Cd = _c;
      m_distance = 0;
      linear_momentum = 0;
      friction_coefficient=0.1f;
      m_collider = NULL;
      //set up vertex array for this plane

      verts =
      {
        ngl::Vec3(-100,P.m_y,-100),
        ngl::Vec3(100,P.m_y,-100),
        ngl::Vec3(-100,P.m_y,100),
        ngl::Vec3(100,P.m_y,100)
       };


      const static GLbyte indices[] = {

        0,1,2,2,1,3

      };
      GLfloat colours[]={
        1,1,1,
        1,1,1,
                           1,1,1,
                           1,1,1
                         };
      m_vao.reset(ngl::VAOFactory::createVAO("simpleIndexVAO",GL_TRIANGLES) );
      m_vao->bind();
      // in this case we are going to set our data as the vertices above
      m_vao->setData(ngl::SimpleIndexVAO::VertexData( 4*sizeof (ngl::Vec3), verts[0].m_x, sizeof(indices),&indices[0], GL_UNSIGNED_BYTE,GL_STATIC_DRAW));
      m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
      m_vao->setData(ngl::SimpleIndexVAO::VertexData( 4*sizeof (ngl::Vec3), colours[0], sizeof(colours),&indices[0], GL_UNSIGNED_BYTE,GL_STATIC_DRAW));
      m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);
//      m_vao->setNumIndices(verts.size());
      m_vao->setNumIndices(sizeof (indices));
      m_vao->unbind();

}


void plane::draw()const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["diffuse"]->use();
  shader->setUniform("Colour",0.3f,0.3f,0.3f,1.0f);
  ngl::Transformation t;
  //t.setPosition(P);
  t.setPosition(0,0,0);
  //t.addPosition(0,-10,0);
  ngl::Mat3 normalMatrix;

  ngl::Mat4 MVP=m_parent->getCamera()->getVPMatrix() *
                m_parent->getGlobalTransform() *
                t.getMatrix();
  shader->setUniform("MVP",MVP);
  normalMatrix =m_parent->getCamera()->getViewMatrix()*m_parent->getGlobalTransform() *
      t.getMatrix();

  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();

}
plane::~plane()
{

  if(m_collider!= NULL)
  {
   delete m_collider;
  }
}

void plane::update()
{
  //do nothing because plane doesn't move
  P=P;
}

void plane::setCollider()
{
  //set plane notmal
  ngl::Vec3 test_N(0,1,0);
  m_collider = new CollidePlane(test_N,m_distance);
}
