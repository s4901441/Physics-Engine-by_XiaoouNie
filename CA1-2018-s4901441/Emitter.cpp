#include "Emitter.h"
#include "IntersectingData.h"
#include "Cloth_object.h"
#include "plane.h"
#include <ngl/Random.h>
#include "CollisionResponse.cpp"

Emitter::Emitter(ngl::Vec3 _pos,unsigned int _numParticles,   ngl::Camera *_cam) //emit random shapes
{
  m_pos = _pos;
  m_numParticles=_numParticles;
  m_cam = _cam;
  m_timer_count = 0;

  std::unique_ptr<ParticleFactory> p(new ParticleFactory);
  ngl::Random *rng=ngl::Random::instance();
  //initial velocity
  ngl::Vec3 dir;
  ngl::Colour c;
  int which;
  // resize the particle container for speed
  m_particles.resize(m_numParticles);
  // loop for each of the particles and create
  for(auto &particle : m_particles)
  {
    // get a random direction and colour
    dir=rng->getRandomVec3();
    c=rng->getRandomColour();
    // choose which input we want
    //GRAVITY
    ngl::Vec3 Gravity = {0.0f,-9.8f,0.0f};
    float Mass = 1.0;
    which=static_cast<int>(rng->randomPositiveNumber(3));
    switch(which)
    {
    // use the factory to create a new particle
    case 0 : particle.reset(p->CreateParticles(ParticleType::SPHERE,m_pos,dir, Gravity,Mass,"blinn",this,c)); break;
    case 1 : particle.reset(p->CreateParticles(ParticleType::TORUS,m_pos,dir, Gravity,Mass,"blinn",this,c)); break;
    case 2 : particle.reset(p->CreateParticles(ParticleType::CUBE,m_pos,dir, Gravity,Mass,"blinn",this,c)); break;
    }
}
}

Emitter::Emitter(ngl::Vec3 _pos, unsigned int _numParticles,  ngl::Camera *_cam, ParticleType _type)
{
  m_cam=_cam;
  m_pos=_pos;
  m_numParticles=_numParticles;
  m_input_gravity = -9.8f;
  // create our render factory
  ParticleFactory *p = new  ParticleFactory;
  ngl::Random *rng=ngl::Random::instance();
  m_particles.resize(m_numParticles);
  ngl::Vec3 dir;
  ngl::Colour c;
  ngl::Vec3 Gravity = {0.0f,-9.80f,0.0f};
  float Mass = 1.0;
  for(auto &particle : m_particles)
  {
    dir=rng->getRandomVec3();
    dir.normalize();
    dir *= 0.1f;
    c=rng->getRandomColour();
   // std::unique_ptr<Particle> part( );
    particle.reset(p->CreateParticles(_type,_pos,dir,Gravity,Mass,"blinn",this,c));
  }
 // we've done with the factory so delete it
  delete p;

}
//this function is called when user sets a new gravity
void Emitter::set_gravity(float _gravity)
{

  for(auto &particle : m_particles)
  {
    particle->set_graviry(_gravity);
    particle->set_active();
  }


}

bool Emitter::Check_Ground_Plane_Exist()
{
  bool groundplane_checker = false;
  if( m_particles[m_numParticles-1]->getType() == ParticleType::PLANE)
 {
   groundplane_checker = true;
 }
  return groundplane_checker;
}

void Emitter::set_Friction_Coe(float _coefficient)
{


  for(auto &particle : m_particles)
  {
  particle->set_Friction_Coe(_coefficient);
  }
}

void Emitter::set_Bouncing_Coe(float _coefficient)
{
  for(auto &particle : m_particles)
  {
  particle->set_Bouncing_Coe(_coefficient);
  }
}


void Emitter::addParticle(ParticleType _type )
{
  // create our render factory
  ParticleFactory *p = new  ParticleFactory;

  ngl::Random *rng=ngl::Random::instance();
  ngl::Vec3 Gravity = {0.0f,-9.8f,0.0f};
  float Mass = 1.0;
  ngl::Vec3 dir = {1.0f,0.0f,0.0f};
  ngl::Colour c;
  c=rng->getRandomColour();
  m_particles.push_back(std::unique_ptr<Particles> (p->CreateParticles(_type,m_pos,dir,Gravity,Mass,"blinn",this,c)));
  // we've done with the factory so delete it
  delete p;
  ++m_numParticles;
}

void Emitter::removeParticle()
{
  // when we remove a particle we need to first check to see if we have any
  if(m_numParticles>0&&Check_Ground_Plane_Exist())
  {
    // now remove from the end of the std::vector
    m_particles.pop_back();
    // decrement the number of particles
    --m_numParticles;
  }
}

void Emitter::draw()
{
  // call the draw method for each of the particles
  for(auto &p : m_particles)
  {
    p->draw();
  }
}

void Emitter::update()
{
  // call the update method for each particle
  for(auto &p : m_particles)
  {
    p->update();
    p->setCollider();
  }

   HandleCollisions();
   m_timer_count += 0.02f;
}

void Emitter::clearParticles()
{
  // must remember to re-size the std::vector back to 0
  m_particles.clear();
  m_numParticles=0;
}
Emitter::~Emitter()
{
  m_particles.clear();
}

void Emitter::HandleCollisions()
{
 //sphere-sphere or cube-cube collision
  for(unsigned int i = 0; i<m_numParticles; i++)
  {

    for(unsigned int j = i+1; j<m_numParticles;j++)
    {

      //Collision Dection
      IntersectingData temp = (m_particles[i]->GetCollider()).Intersect(m_particles[j]->GetCollider());

        if (temp.CheckIntersect()&&(m_particles[i]->Getv()).length()>14)//
        {
          //Collision Response
          std::unique_ptr<Particles> *_this_ = &m_particles[i];
          std::unique_ptr<Particles> *_other_ = &m_particles[j];
          CollisionResponse(_this_,_other_,temp);
          Friction_Impulse_Calc(_this_,_other_,temp);
          Penetration_Remove(_this_,_other_,temp);
        }
      }

  }
    //plane-sphere/plane-cube collision
    for(unsigned int j = 0; j < m_numParticles-1; j++) //check all the particles to see if they are intersecting with the plane
    {
     //collision-detection
      IntersectingData temp = (m_particles[m_numParticles-1]->GetCollider()).Intersect(m_particles[j]->GetCollider());//plane intersects sphere

    //collision response
    if(temp.CheckIntersect())//&&!(m_particles[j]->check_stop())
    {

    std::unique_ptr<Particles> *_this_ = &m_particles[m_numParticles-1];//'this' is plane
    std::unique_ptr<Particles> *_other_ = &m_particles[j];
    //(*_other_)->set_stop();

    CollisionResponse(_this_,_other_,temp);
    Friction_Impulse_Calc(_this_,_other_,temp);
    Penetration_Remove(_this_,_other_,temp);

    }
  }
}


