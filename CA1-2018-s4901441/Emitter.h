#ifndef EMITTER_H
#define EMITTER_H
#include "ParticleFactory.h"
#include "ParticleTypes.h"
#include <ngl/Camera.h>
#include <vector>
#include <memory>

class Emitter
{
public:
  //create particles of random type
  Emitter(ngl::Vec3 _pos, unsigned int _numParticles, ngl::Camera *_cam);
  //create particles of the same type
  Emitter(ngl::Vec3 _pos, unsigned int _numParticles, ngl::Camera *_cam, ParticleType _type );

  ~Emitter();

  void update();
  /// @brief draw all the particles using the particle draw method
  void draw();
  /// @brief add a new particle to the end of the list
  /// @param[in] _type the type of particle to add
  void addParticle( ParticleType _type );
  /// @brief remove the last particle from the list
  void removeParticle();
  /// @brief this will update the emit angle of the SPHERE type particle only
  /// @param[in] _a the new emit angle for sphere, will only update once particle is re-born
  void addPlane();

  inline unsigned int getNumParticles()const {return m_numParticles;}
  /// @brief get the global camera
  inline  ngl::Camera *getCamera() const {return m_cam;}
  /// @brief get the global transform stack
  /// @brief a method to clear all particles
  void clearParticles();
  /// @brief get the position
  inline ngl::Vec3 getPos()const {return m_pos;}
  /// @brief set the position
  inline void setPos(const ngl::Vec3 &_v){m_pos=_v;}
  inline void setGlobalTransform(const ngl::Mat4 &_t){m_globalMouseTX=_t;}
  inline const ngl::Mat4 & getGlobalTransform() const { return m_globalMouseTX;}
  void HandleCollisions();
  ngl::Mat4 inline getMouseGlobalTX() {return m_globalMouseTX;}
  void CollisionResponse(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other, IntersectingData _temp);
  void Friction_Impulse_Calc(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other, IntersectingData _temp);
  void Penetration_Remove(std::unique_ptr<Particles> *_this,std::unique_ptr<Particles> *other, IntersectingData _temp);
  void set_gravity(float _gravity);
  bool Check_Ground_Plane_Exist();
  void set_Friction_Coe(float _coefficient);
  void set_Bouncing_Coe(float _coefficient);


private :
  /// @brief the particle list stores a pointer to each particle, these are created by the
  /// particle factory
  std::vector < std::unique_ptr<Particles>> m_particles;
  /// @brief a pointer to the current camera, this is used for accesing the VP matrix to load to the
  /// shader
  ngl::Camera *m_cam;
  /// @brief the number of particles
  unsigned int m_numParticles;
  /// @brief the position of the emitter this is passed to the particle for creation
  ngl::Vec3 m_pos;
  /// @brief a global mouse transform for drawing
  ngl::Mat4 m_globalMouseTX;
  float m_input_gravity;
  float m_timer_count;
};

#endif // EMITTER_H
