#ifndef CLOTH_PARTICLE_H
#define CLOTH_PARTICLE_H

#include<ngl/Vec3.h>
#include<ngl/Mat4.h>

class Cloth_Particle
{
  private:
    float mass;
    ngl::Vec3 m_pos;
    ngl::Vec3 force_total;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_normal;
    float stretching_coefficient;
    float damp_coefficient;
    float TimeInc;
    bool is_movable;

  public:
    Cloth_Particle();
    Cloth_Particle(const ngl::Vec3 &_pos, const ngl::Vec3 &_v, const ngl::Vec3 &_f, float _mass, float _sk, float _dk);
    Cloth_Particle& operator=(Cloth_Particle& particle);

    const float &Getmass() const        {return mass;}
    const float &Get_sk() const         {return stretching_coefficient;}
    const float &Get_dk() const         {return damp_coefficient;}
    const ngl::Vec3 &GetPos() const     {return m_pos;}
    const ngl::Vec3 &GetVel() const     {return m_velocity;}
    const ngl::Vec3 &Getforce() const   {return force_total;}
    const ngl::Vec3 &getNormal() const  {return m_normal;}

    void setNormal(const ngl::Vec3 &_normal) {m_normal = _normal;}
    void setConstraint(){is_movable = false;}

    void update();
    void accumulate_force(const ngl::Vec3 &_force) {force_total+=_force;}
    void multiply_force(float _scalar){force_total *= _scalar;}
    void addNormal(const ngl::Vec3 &_normal) {m_normal += _normal;}

    void draw(const std::string &_shaderName, const ngl::Mat4 &_Mouse_Global, const ngl::Mat4 &_VP) ;

    ~Cloth_Particle() noexcept = default;
};

#endif // CLOTH_PARTICLE_H
