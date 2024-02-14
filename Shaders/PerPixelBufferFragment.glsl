#version 330 core

uniform sampler2D diffuseTex ; // Diffuse texture map
uniform sampler2D shadowTex;
uniform int emissive; 

in Vertex {
vec4 colour ;
vec2 texCoord ;
vec3 normal ;
vec3 worldPos ;
vec4 shadowProj;
} IN ;

out vec4 fragColour[5]; // Our final outputted colours !

void main ( void ) {
float shadow = 1.0;
 
 vec3 shadowNDC = IN.shadowProj.xyz / IN.shadowProj.w;
 if(abs(shadowNDC.x) < 1.0f &&
    abs(shadowNDC.y) < 1.0f &&
    abs(shadowNDC.z) < 1.0f) {
     vec3 biasCoord = shadowNDC * 0.5f + 0.5f;
     float shadowZ = texture(shadowTex, biasCoord.xy).x;
     if(shadowZ < biasCoord.z){
      shadow = 0.0f;
     }
 }

fragColour [0] = texture2D ( diffuseTex , IN.texCoord ) * IN.colour ;
fragColour [1] = vec4 ( IN.normal.xyz * 0.5 + 0.5 ,1.0);
fragColour [2] = vec4(0.2,0.2,0.2,1.0);
fragColour [3] = vec4(emissive,1.0,1.0,1.0);
fragColour [4] = vec4(shadow, 1.0, 1.0, 1.0); 
}
