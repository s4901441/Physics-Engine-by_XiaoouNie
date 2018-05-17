#include <QMouseEvent>
#include "GLWidget.h"
#include "plane.h"
#include "Cloth_object.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Vec3.h>
#include <ngl/Light.h>
#include <ngl/Mat4.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Material.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Colour.h>

//Constructor
GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent)
{
  setFocus();
  this->resize(parent->size());
  m_emitterPos.set(-2,8,0);
  m_startSimulate = false;
  m_particleType_index = 0; //set default type to sphere
  m_change_back_to_sphere = 0;
  m_custom_gravity = -9.8f;
  m_gravity_change_flag = false;
  Cloth_Activated = true;
  Rigid_Actived = true;
}

//Destructor
GLWidget::~GLWidget()
{
  
}

void GLWidget::reset()
{
  if(m_emitter!=NULL)
  {
     m_emitter.reset( new Emitter(m_emitterPos,100, m_cam, ParticleType::SPHERE));
     m_emitter->addParticle(ParticleType::PLANE);
     m_emitter->set_gravity(-9.8f);

  }
  m_startSimulate = false;
  if(m_object!= NULL)
  {
    m_object = new Cloth_object("blinn");
    Cloth_Activated = true;
  }
}

bool GLWidget::Has_GroundPlane()
{
  return m_emitter->Check_Ground_Plane_Exist();
}

void GLWidget::Add_ground_plane()
{
  m_emitter->addParticle(ParticleType::PLANE);
}

void GLWidget::Delete_ground_plane()
{
  m_emitter->removeParticle();
}

void GLWidget::set_particle_count(int _count)
{
  m_emitter.reset( new Emitter(m_emitterPos,(unsigned)_count, m_cam, ParticleType::SPHERE));
  if(m_emitter->Check_Ground_Plane_Exist())
  {
    m_emitter->addParticle(ParticleType::PLANE);
  }
}

void GLWidget::Set_Friction_Coe(float _coefficient)
{
  m_emitter->set_Friction_Coe(_coefficient);
}

void GLWidget::Set_Bouncing_Coe(float _coefficient)
{
  m_emitter->set_Bouncing_Coe(_coefficient);
}

//Initialize

void GLWidget::initializeGL()
{
  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
//-----------------------------------------------------------
    //CAMERA
  ngl::Vec3 eye(18,19,35);
  ngl::Vec3 look(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_cam = new ngl::Camera();
  m_cam->set(eye,look,up);
  m_cam->setShape( 45.0f, 720.0f / 576.0f, 0.05f, 350.0f );

//-----------------------------------------------------
  //SHADERS
  //Shader for ground plane
  ngl::ShaderLib *shader_1 = ngl::ShaderLib::instance();
  //shader program
  shader_1->createShaderProgram("diffuse");
  //attatch shader
  shader_1->attachShader("vertex",ngl::ShaderType::VERTEX);
  shader_1->attachShader("fragment",ngl::ShaderType::FRAGMENT);
  //Load sources (.glsl files)
  shader_1->loadShaderSource("vertex","shaders/diffuseVertex.glsl");
  shader_1->loadShaderSource("fragment","shaders/diffuseFrag.glsl");
  //compile shaders
  shader_1->compileShader("vertex");
  shader_1->compileShader("fragment");
  //attatch shader to program
  shader_1->attachShaderToProgram("diffuse","vertex");
  shader_1->attachShaderToProgram("diffuse","fragment");
  // now bind the shader attributes for most NGL primitives we use the following
  // layout attribute 0 is the vertex data (x,y,z)
  shader_1->bindAttribute("diffuse",0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader_1->bindAttribute("diffuse",1,"inUV");
  // attribute 2 are the normals x,y,z
  shader_1->bindAttribute("diffuse",2,"inNormal");
  //link shader program
  shader_1->linkProgramObject("diffuse");
  //active
  shader_1->use("diffuse");

  //shader for everything else
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  //shader program
  shader->createShaderProgram("blinn");
  //attatch shader
  shader->attachShader("vertex",ngl::ShaderType::VERTEX);
  shader->attachShader("fragment",ngl::ShaderType::FRAGMENT);
  //Load sources (.glsl files)
  shader->loadShaderSource("vertex","shaders/PhongVertex.glsl");
  shader->loadShaderSource("fragment","shaders/PhongFragment.glsl");
  //compile shaders
  shader->compileShader("vertex");
  shader->compileShader("fragment");
  //attatch shader to program
  shader->attachShaderToProgram("blinn","vertex");
  shader->attachShaderToProgram("blinn","fragment");
  // now bind the shader attributes for most NGL primitives we use the following
  // layout attribute 0 is the vertex data (x,y,z)
  shader->bindAttribute("blinn",0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader->bindAttribute("blinn",1,"inUV");
  // attribute 2 are the normals x,y,z
  shader->bindAttribute("blinn",2,"inNormal");
  //link shader program
  shader->linkProgramObject("blinn");
  //active
  shader->use("blinn");


//-----------------------------------------------------------
  //LIGHTING

   ngl::Mat4 ViewMatrix = m_cam->getViewMatrix();
   ViewMatrix.transpose();
   ngl::Light light(ngl::Vec3(50, 20,25), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::SPOTLIGHT);
   light.setTransform(ViewMatrix);

   light.loadToShader("light");


   ngl::VAOPrimitives *prim1 = ngl::VAOPrimitives::instance();
   prim1->createSphere("sphere",1.0,20);

   //prim1->createTorus("torus",0.3f,0.8f,20,20);


   // create the default particle inital position

   m_object = new Cloth_object("blinn");

   m_emitter.reset( new Emitter(m_emitterPos,100, m_cam, ParticleType::SPHERE));

   m_emitter->addParticle(ParticleType::PLANE);

   startTimer(20);

}

void GLWidget::loadMatricesToShader()
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M            = m_mouseGlobalTX;
  MV           = m_cam->getViewMatrix() * M;
  MVP          = m_cam->getVPMatrix() * M;

//  normalMatrix = MV;
  //normalMatrix.inverse().transpose();
  //shader->setUniform( "MV", MV );
  shader->setUniform( "MVP", MVP );
  //shader->setUniform( "normalMatrix", normalMatrix );
  //shader->setUniform( "M", M );
}

void GLWidget::paintGL()
{
  glViewport( 0, 0, width, height );
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  ( *shader )["blinn"]->use();

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX( spinXFace );
  rotY.rotateY( spinYFace );
  // multiply the rotations
  m_mouseGlobalTX = rotX * rotY;
  // add the translations
  m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;
  if(m_emitter!=NULL)
  {
  m_emitter->setGlobalTransform(m_mouseGlobalTX);
  }


  //plane my_plane(test,test,test,1.0f,"blinn",m_emitter);
  if(m_emitter!=NULL&&Rigid_Actived == true)
  {
     m_emitter->draw();
  }

  //set up the cloth
  m_object->setMouseGlobalTX(m_mouseGlobalTX);
  m_object->setVPMatrix(m_cam->getVPMatrix());
  m_object ->setViewMatrix(m_cam->getViewMatrix());

  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  //draw the cloth
  if(Cloth_Activated == true)
  {
  m_object->draw();
  }
}

void GLWidget::resizeGL(int w, int h)
{

  m_cam->setShape( 45.0f, static_cast<float>( w ) / h, 0.05f, 350.0f );
  width  = static_cast<int>( w * devicePixelRatio() );
  height = static_cast<int>( h * devicePixelRatio() );

}
void GLWidget::addParticles( int _type)
{
switch(_type)
{
  case 0 : m_emitter->addParticle(ParticleType::SPHERE); break;
  case 1 : m_emitter->addParticle(ParticleType::TORUS); break;

}

}
void GLWidget::timerEvent( QTimerEvent *_event)
{
  NGL_UNUSED(_event);

  if(m_particleType_index==1)
  {

    m_emitter.reset(new Emitter(m_emitterPos,100, m_cam, ParticleType::CUBE));
    m_emitter->addParticle(ParticleType::PLANE);
    m_particleType_index = 0;//to stop continuously resetting the emitter

  }
  if(m_change_back_to_sphere == 1)
  {
    m_emitter.reset(new Emitter(m_emitterPos,100, m_cam, ParticleType::SPHERE));
    m_emitter->addParticle(ParticleType::PLANE);
    m_change_back_to_sphere = 0;//to stop continuously resetting the emitter

  }

  if(m_gravity_change_flag)
  {
    m_emitter->set_gravity(m_custom_gravity);
  }
  if(m_startSimulate && m_emitter!= NULL)
  {
    m_gravity_change_flag = false;
    if(Rigid_Actived == true)
    {
    m_emitter->update();
    }
    if(Cloth_Activated == true)
    {
    m_object->update();
    }
  }

  update();
}
//----------------------------------------------------------------------------------------------------------
void GLWidget::mouseMoveEvent( QMouseEvent* _event )
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if ( rotate && _event->buttons() == Qt::LeftButton )
  {
    int diffx = _event->x() - origX;
    int diffy = _event->y() - origY;
    spinXFace += static_cast<int>( 0.5f * diffy );
    spinYFace += static_cast<int>( 0.5f * diffx );
    origX = _event->x();
    origY = _event->y();
    update();
  }
  // right mouse translate code
  else if ( translate && _event->buttons() == Qt::RightButton )
  {
    int diffX      = static_cast<int>( _event->x() - origXPos );
    int diffY      = static_cast<int>( _event->y() - origYPos );
    origXPos = _event->x();
    origYPos = _event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }
}


//----------------------------------------------------------------------------------------------------------------------
void GLWidget::mousePressEvent( QMouseEvent* _event )
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if ( _event->button() == Qt::LeftButton )
  {
    origX  = _event->x();
    origY  = _event->y();
    rotate = true;
  }
  // right mouse translate mode
  else if ( _event->button() == Qt::RightButton )
  {
    origXPos  = _event->x();
    origYPos  = _event->y();
    translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void GLWidget::mouseReleaseEvent( QMouseEvent* _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if ( _event->button() == Qt::LeftButton )
  {
    rotate = false;
  }
  // right mouse translate mode
  if ( _event->button() == Qt::RightButton )
  {
    translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void GLWidget::wheelEvent( QWheelEvent* _event )
{

  // check the diff of the wheel position (0 means no change)
  if ( _event->delta() > 0 )
  {
    m_modelPos.m_z += 5*ZOOM;
  }
  else if ( _event->delta() < 0 )
  {
    m_modelPos.m_z -= 5*ZOOM;
  }
  update();
}
