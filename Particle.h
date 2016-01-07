
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "stdafx.h"
#include "Vector.h"
#include "OpenGLObject.h"

/*
    Particle structure. This structure
  stores information of a single
  particle.
 */

struct Particle
{
	Vector3 position;		     // Position of the particle
	Vector3 velocity;            // Velocity of the particle
	Vector3 acceleration;        // Acceleration of the particle
	float lifetime;              // Life time of the particle
	float dec;		             // Vanishing speed of the particle
	float size;		             // Size of the particle
	float color[3];              // Color of the particle
};

/*
    Particle explosion class. This
  class represents one explosion of a 
  bunch of particles. An explosion is
  created when two balls hit, and when
  its life time is over, it will be
  removed.
 */

class ParticleExplosion : public OpenGLObject
{
public:
	ParticleExplosion();          // Constructor
	~ParticleExplosion();         // Destructor

    /// Public interfaces 
	void Init(int num);           // Initialization
    virtual void Draw();          // Render the particles
    virtual void Update();        // Update the particles

private:
	int m_Num;                    // Total number of particles
	unsigned int m_Life;          // Life time of hte explosion
	Particle* m_List;             // A list of particles
};

/*
    Particle system class
 */
class ParticleSystem : public OpenGLObject
{

};

#endif // __PARTICLE_H__