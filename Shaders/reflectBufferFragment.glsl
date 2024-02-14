#version 330 core
uniform sampler2D diffuseTex ;
uniform sampler2D bumpTex ;
uniform sampler2D specTex; 
uniform samplerCube cubeTex;
uniform sampler2D shadowTex;
uniform int emissive; 

uniform vec3 cameraPos;

in Vertex {
 vec4 colour;
 vec2 texCoord;
 vec3 normal;
 vec3 tangent;
 vec3 binormal;
 vec3 worldPos;
 vec4 shadowProj;
} IN ;

out vec4 fragColour[5]; // Our final outputted colours !

void main ( void ) {
mat3 TBN = mat3 ( normalize ( IN.tangent ) ,
normalize ( IN.binormal ) ,
normalize ( IN.normal ));

vec3 normal = texture2D ( bumpTex , IN.texCoord ).rgb * 2.0 - 1.0;
normal = normalize ( TBN * normalize ( normal ));

vec3 viewDir = normalize(cameraPos - IN.worldPos);

vec3 reflectDir = reflect(-viewDir, normalize (IN.normal));
vec4 reflectTex = texture(cubeTex, reflectDir);

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

fragColour [0] = reflectTex + (texture2D ( diffuseTex , IN.texCoord ) * IN.colour * 0.25f);
fragColour [1] = vec4 ( normal.xyz * 0.5 + 0.5 ,1.0);
fragColour [2] = vec4(texture(specTex, IN.texCoord).r,1.0,1.0,1.0);
fragColour [3] = vec4(emissive,1.0,1.0,1.0);
fragColour [4] = vec4(shadow,1.0, 1.0, 1.0);
}
