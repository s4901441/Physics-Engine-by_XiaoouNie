#version 330 core

/// @brief[in] the vertex normal
in vec3 fragmentNormal;
/// @brief our output fragment colour
out vec4 fragColour;
// @brief light structure
struct Lights
{
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};


uniform vec4 Colour;

uniform Lights light;

void main ()
{
  // set the output colour to black
  fragColour= vec4(0.);
  // normalize the vertex normal
  vec3 N = normalize(fragmentNormal);
  // The Light source vector
  // get the Light vector
  vec3 L = normalize(light.position.xyz);
  // calculate diffuse based on Lambert's law (L.N)
  fragColour += Colour;  //*light.diffuse *dot(L, N);

}

/*
#version 410 core
/// @brief our output fragment colour
layout (location =0) out vec4 fragColour;
/// @brief[in] the vertex normal
in  vec3 fragmentNormal;
/// @brief material structure

uniform vec4 Colour;
struct Materials
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

// @brief light structure
struct Lights
{
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};
// @param material passed from our program
uniform Materials material;

uniform Lights light;
in vec3 lightDir;
// out the blinn half vector
in vec3 halfVector;
in vec3 eyeDirection;
in vec3 vPosition;

/// @brief a function to compute point light values
/// @param[in] _light the number of the current light

vec4 pointLight()
{
  vec3 N = normalize(fragmentNormal);
  vec3 halfV;
  float ndothv;
  float attenuation;
  vec3 E = normalize(eyeDirection);
  vec3 L = normalize(lightDir);
  float lambertTerm = dot(N,L);
  vec4 diffuse=vec4(0);
  vec4 ambient=vec4(0);
  vec4 specular=vec4(0);
  if (lambertTerm > 0.0)
  {
  float d;            // distance from surface to light position
  vec3 VP;            // direction from surface to light position

  // Compute vector from surface to light position
  VP = vec3 (light.position) - vPosition;

  // Compute distance between surface and light position
    d = length (VP);


    diffuse+=material.diffuse*light.diffuse*lambertTerm;
    ambient+=material.ambient*light.ambient;
    halfV = normalize(halfVector);
    ndothv = max(dot(N, halfV), 0.0);
    specular+=material.specular*light.specular*pow(ndothv, material.shininess);
  }
return ambient + diffuse + specular;
}


void main ()
{

fragColour=pointLight();
}



//#version 330 core
//in vec3 vertColour;
//layout (location=0)out vec4 outColour;
//void main ()
//{
// // set the fragment colour
// outColour = vec4(vertColour,1);
//}*/
