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
  fragColour= vec4(0);
  // normalize the vertex normal
  vec3 N = normalize(fragmentNormal);
  // The Light source vector
  // get the Light vector
  vec3 L = normalize(light.position.xyz);
  // calculate diffuse based on Lambert's law (L.N)
  fragColour += Colour*light.diffuse *dot(L, N);

}
