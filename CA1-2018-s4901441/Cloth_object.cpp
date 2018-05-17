#include "Cloth_object.h"
#include"Cloth_Particle.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/SimpleIndexVAO.h>
#include <ngl/NGLStream.h>
#include <ngl/VAOPrimitives.h>
#include<ngl/Random.h>

Cloth_object::Cloth_object(const std::string &_shaderName)
{
  //width and height of particles
  m_width = 10;
  m_height = 10;
  float m_offest = 4;
  //how many particles in width and height
  width_num =40;
  height_num =20;
  //space between particles in x and y direction
  distance_x = m_width*(1.0f/(float)width_num);
  distance_y = m_height*(1.0f/(float)height_num);
  stretching_coefficient = 20.0f;
  damp_coefficient = 2.0f ;

  m_numParticles = width_num*height_num;

  verts.resize(m_numParticles);
  m_shaderName = _shaderName;


  ngl::Vec3 initial_force(0,0,0);
  //insert particles to cloth
  for (std::size_t y = 0; y<height_num; y++)
  {
    for (std::size_t x = 0; x<width_num; x++)
    {
      ngl::Vec3 position(m_width*(static_cast<float>(x)/width_num),m_offest+m_height*(static_cast<float>(y)/height_num),0.0f);
      m_particles.emplace_back(position, ngl::Vec3::zero(),initial_force, 0.5f, 0.5f,0.2f);
     }
  }

  //constrain the top two rows of particles
  std::for_each(m_particles.rbegin(),m_particles.rbegin()+80,[](Cloth_Particle &p)
                                                             {
                                                                p.setConstraint();
                                                             });
//-------------------------------------------------------------------------------

//work out the indices for drawing, the following code didn't work unfortunately

  /*
  GLushort indices[(width_num-1)*(height_num - 1)*6]; //(width_num-1)*(height_num - 1)*6](width_num*height_num-2)*3there are (n-2)*3 indices , where n is the vertex number
  for ( unsigned int y = 0; y<height_num-1;y++)
  {
    for (unsigned int x = 0; x<width_num-1;x++)//loop through all polygons in the cloth
    {
      unsigned int offset = (6*(width_num*y+x));
      //std::cout<<offset;
      indices[offset] = (x+y*width_num);        //x,y
      indices[offset+1] = (x+1+y*width_num);      //x+1,y
      indices[offset+2] = (x+(y+1)*width_num);    //x,y+1
      indices[offset+3] = (x+(y+1)*width_num);    //x,y+1
      indices[offset+4] =  (x+1+y*width_num);        //x+1,y
      indices[offset+5] = (x+1+(y+1)*width_num);  //x+1,y+1

    std::cout<<indices[offset];
    std::cout<<indices[offset+1];
    std::cout<<indices[offset+2];
    std::cout<<indices[offset+3];
    std::cout<<indices[offset+4];
    std::cout<<indices[offset+5];
      //std::cout<<(width_num-1)*(height_num - 1)*6;
    }
  }
  unsigned int total_num = (width_num-1)*(height_num - 1)*6;
  m_vao.reset(ngl::VAOFactory::createVAO("simpleIndexVAO",GL_TRIANGLES) );
  m_vao->bind();
  m_vao->setData(ngl::SimpleIndexVAO::VertexData(width_num*height_num*sizeof(ngl::Vec3), verts[0].m_x, total_num*sizeof(GLushort),&indices[0], GL_UNSIGNED_SHORT,GL_STATIC_DRAW));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,false);
  m_vao->setNumIndices(total_num);
  m_vao->unbind();
  */

}

Cloth_object::~Cloth_object()
{

}

void Cloth_object::Calculate_Cloth_Normal()
{
  for (unsigned int y = 0; y<height_num-1;y++)
  {
    for (unsigned int x = 0; x<width_num-1;x++)
    {
    ngl::Vec3 normal_1 =Calc_Triangle_Normal( getParticle(x+1, y)->GetPos(), getParticle(x,y)->GetPos(), getParticle(x, y+1)->GetPos());
    getParticle(x+1,y)->addNormal(normal_1);
    getParticle(x,y)->addNormal(normal_1);
    getParticle(x,y+1)->addNormal(normal_1);
    ngl::Vec3 normal =Calc_Triangle_Normal( getParticle(x+1, y+1)->GetPos(), getParticle(x+1,y)->GetPos(), getParticle(x, y+1)->GetPos());
    getParticle(x+1,y+1)->addNormal(normal);
    getParticle(x+1,y)->addNormal(normal);
    getParticle(x,y+1)->addNormal(normal);
    }
  }
}


void Cloth_object::draw()
{

  //following code is an attempt to visualize the cloth as triangles,
  //but it didn't work

  /* unsigned int indices[(width_num*height_num-2)*3]; //there are (n-2)*3 indices , where n is the vertex number
  for ( unsigned int y = 0; y<height_num-1;y++)
  {
    for (unsigned int x = 0; x<width_num-1;x++)
    {
      unsigned int offset = (6*(width_num*y+x));
      //std::cout<<offset;
      indices[offset] =( x+1+y*width_num);        //x+1,y
      indices[offset+1] = x+y*width_num;        //x,y
      indices[offset+2] = x+(y+1)*width_num;    //x,y+1
      indices[offset+3] = x+1+(y+1)*width_num;  //x+1,y+1
      indices[offset+4] = x+1+y*width_num;      //x+1,y
      indices[offset+5] = x+(y+1)*width_num;    //x,y+1

    }

  }
  m_vao.reset(ngl::VAOFactory::createVAO("simpleIndexVAO",GL_TRIANGLES) );
  m_vao->bind();
  m_vao->setData(ngl::SimpleIndexVAO::VertexData( width_num*height_num*sizeof (ngl::Vec3), verts[0].m_x, sizeof(indices),&indices[0], GL_UNSIGNED_BYTE,GL_STATIC_DRAW));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
  m_vao->setNumIndices(sizeof (indices));
  m_vao->unbind();*/

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[m_shaderName]->use();
  // shader->setUniform("Colour",Cd);
  ngl::Transformation t;
  //t.setPosition(P);
  t.setPosition(0,0,0);

  for (std::size_t y = 0; y<height_num;y++)
  {
    for (std::size_t x = 0; x<width_num;x++)
    {
      m_particles[(width_num*y)+x].draw("blinn",MouseGlobalTX, VPMatrix);

    }
  }

}

void Cloth_object::update()
{

  //generate wind with turbulence
  ngl::Random *rng=ngl::Random::instance();
  //calculate net force on particles
  Calculate_forces(ngl::Vec3(0,-9.8f,0),rng->getRandomVec3());

  for (std::size_t y = 0; y<height_num;y++)
  {
    for (std::size_t x = 0; x<width_num;x++)
    {
      m_particles[(width_num*y)+x].update();
    }
  }

}


Cloth_Particle* Cloth_object::getParticle(unsigned int _x, unsigned int _y)
{
  Cloth_Particle* particle = &m_particles[(_y*width_num)+_x];
  return particle;
}

ngl::Vec3 Cloth_object::Calc_Triangle_Normal(ngl::Vec3 p1, ngl::Vec3 p2, ngl::Vec3 p3)
{
  ngl::Vec3 normal = (p2 - p1).cross(p3- p1);
  normal.normalize();
  return normal;

}

void Cloth_object::Calculate_forces(const ngl::Vec3 &_gravity, const ngl::Vec3 &_wind)
{
  Calculate_Cloth_Normal();

  for (std::size_t y = 0; y<height_num;y++)
  {
    for (std::size_t x = 0; x<width_num;x++)
    {
     Cloth_Particle &p = m_particles[width_num*y+x];
     p.accumulate_force(p.Getmass()*ngl::Vec3(0,-9.8f,0));

     // Apply the wind using the last calculated normals
     ngl::Vec3 force =p.getNormal() * (p.getNormal().dot(_wind*0.6f));
     p.accumulate_force(force);

     // Reset the normal, will recalculate after position is adjusted
     p.setNormal(ngl::Vec3::zero());

   }
  }

   for (int y = 0; y<height_num;y++) {
     for (int x = 0; x<width_num;x++)
     {
       Cloth_Particle* p = getParticle(x,y);				// Current particle
       float squares = 0;							              // A count of the adjacent particles
       ngl::Vec3 springForce =  ngl::Vec3(0,0,0);		// Will contain the forces of all adjacent particles are applying
       float largestStretch = 0;					          // Used to cap the length the cloth can stretch

       // Evaluate the Closest 24 positions
       for (int a = -2; a <= 2; ++a) {
         for (int b = -2; b <=2 ; ++b)
         {
           // Ensure a particle exist and it isn't the current one
           if ((a != 0 || b != 0) && (x+a >= 0) && (x+a < width_num) && (y+b >= 0) && (y+b <height_num))
           {
             // Get the direction this spring is pulling
             ngl::Vec3 springVector = (getParticle(x+a, y+b))->GetPos() - p->GetPos();
             //normalize this direction
             ngl::Vec3 force_direction = springVector/(springVector.length());
             //calculate the velocity difference for damping calculation
             ngl::Vec3 vel_diff = (getParticle(x+a, y+b))->GetVel() - p->GetVel();
             // calculate current spring length
             float current_length = springVector.length();
             //calculate the natural length of the spring
             float normalLength = sqrtf((a * distance_x) * (a * distance_x) + (b *distance_y) * (b * distance_y)) ;
             //calculate the final force
             ngl::Vec3 final_force = force_direction*(stretching_coefficient*(current_length - normalLength)+damp_coefficient*(vel_diff.dot(force_direction)));
             //calculate a force scalar for capping
             float forceScalar =final_force.length();
             //accumulate the force
             springForce += final_force;
             squares++;

             // Keep track of which spring is exerting the most force
             if (forceScalar > largestStretch) {
               largestStretch = forceScalar;
             }
           }
         }
       }

       // If a spring is stretched beyond 20% we will begin to minimize the effects of other forces to maintain the cloth shape
       if (largestStretch >= 0.20f){
         p->multiply_force((largestStretch >=0.75f)? 0: (0.75-largestStretch));
      }

      // Apply the force of the cloth on this particle
       p->accumulate_force(springForce);
    }
   }

}

