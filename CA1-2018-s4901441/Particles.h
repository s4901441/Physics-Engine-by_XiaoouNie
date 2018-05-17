#ifndef PARTICLES_H
#define PARTICLES_H
#include "ParticleTypes.h"
#include "BoudingSphere.h"
#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/Transformation.h>


class Emitter;
class Particles
{
public:
  Particles(ngl::Vec3 _P, ngl::Vec3 _v, ngl::Vec3 _f, float _mass, const std::string &_shaderName,
            Emitter *_parent);
  virtual ~Particles();
  virtual void draw() const =0;
  /// @brief methods to update the particle
  virtual void update()=0;
  /// @brief method to get particle type
  virtual ParticleType getType() const =0;
  inline ngl::Vec3 GetP() {return P;}
  inline ngl::Vec3 Getv() {return v;}
  inline ngl::Vec3 Getf() {return f;}
  inline ngl::Vec3 Geta() {return a;}
  inline float Getmass() {return  mass;}
  inline float GetCoefficient() {return coefficient_restitution;}
  inline ngl::Vec3 Get_LinearMomentum(){return linear_momentum;}
  inline ngl::Vec3 Get_total_Momentum(){return total_momentum;}
  inline void setv(ngl::Vec3 _v) {v = _v;}
  inline void setP(ngl::Vec3 _P) {penetration_remove_distance = _P;}
  inline void set_LinearMomentum(ngl::Vec3 _linearMomentum){linear_momentum = _linearMomentum;}
  inline Collider* GetExistCollider(){return m_collider;}
  inline Collider& GetCollider(){return *m_collider;}
  inline ngl::Vec3 GetCurrentMomentum() {return v*mass;}
  inline void set_FrictionMomentum(ngl::Vec3 _frictionMomentum){friction_momentum += _frictionMomentum;}
  Collider& createCollider();
  virtual void setCollider()=0;
  inline bool check_stop() {return stop;}
  inline void set_stop() {stop = true;}
  inline void set_active() {stop = false;}
  inline float get_frictionCoefficient() {return friction_coefficient;}
  inline void setPenetration_distance(ngl::Vec3 _distance) {penetration_remove_distance+=_distance;}
  inline bool check_bouncingClamp() {return bouncing_clamp;}
  inline void set_bouncingClamp(bool _clamp){bouncing_clamp = _clamp;}
  float TimeInc;
  inline void set_graviry(float _gravity) {f = ngl::Vec3(0.0f,_gravity,0.0f);}
  inline void set_Collision_Flag(bool _flag) {m_collision_flag = _flag;}
  inline void increase_bouncing_count() {m_bouncing_count +=1;}
  inline int get_bouncing_count() {return m_bouncing_count;}
  inline void set_Friction_Coe(float _coe){friction_coefficient = _coe;}
  inline void set_Bouncing_Coe(float _coe){coefficient_restitution = _coe;}
protected:
  ngl::Vec3 P;  //I am a Houdini user so I just set the same parameter name of the software:)
  ngl::Vec3 v;

  ngl::Vec3 f;
  ngl::Vec3 a;
  float mass;
  ngl::Colour Cd;
  std::string m_shaderName;
  Emitter *m_parent; //pointer to the parent emitter that emitted this current particle
  Collider *m_collider;
  ngl::Vec3 m_oldP;
  float coefficient_restitution;
  ngl::Vec3 linear_momentum; //assigned to a value if collision, otherwise it is 0
  ngl::Vec3 total_momentum; //total moment at each time
  ngl::Vec3 friction_momentum;//momentum by friction
  bool stop;
  bool bouncing_clamp;
  float friction_coefficient;
  ngl::Vec3 penetration_remove_distance;
  bool m_collision_flag;
  int m_bouncing_count;
};

#endif // PARTICLES_H
