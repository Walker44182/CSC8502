#version 330 core

uniform sampler2D diffuseTex ; // Diffuse texture map
uniform int emissive; 

in Vertex {
vec4 colour ;
vec2 texCoord ;
vec3 normal ;
vec3 worldPos ;
vec4 shadowProj;
} IN ;

out vec4 fragColour; // Our final outputted colours !

void main ( void ) {
fragColour = vec4(1.0);
}
