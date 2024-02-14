#version 330 core

uniform sampler2D depthTex ;
uniform sampler2D normTex ;
uniform sampler2D specTex;

uniform vec2 pixelSize ; // reciprocal of resolution
uniform vec3 cameraPos ;

uniform float lightRadius ;
uniform vec3 lightPos ;
uniform vec4 lightColour ;
uniform mat4 inverseProjView ;

out vec4 diffuseOutput ;
out vec4 specularOutput ;
void main ( void ) {
float outerCone = 0.90f;
float innerCone = 0.95f;
 
vec2 texCoord = vec2 ( gl_FragCoord.xy * pixelSize );
float depth = texture ( depthTex , texCoord.xy ).r ;
vec3 ndcPos = vec3 ( texCoord , depth ) * 2.0 - 1.0;
vec4 invClipPos = inverseProjView * vec4 ( ndcPos , 1.0);
vec3 worldPos = invClipPos.xyz / invClipPos.w ;

float dist = length ( lightPos - worldPos );
float atten = 1.0 - clamp ( dist / lightRadius , 0.0 , 1.0);

if( atten == 0.0) {
discard ;
}

vec3 normal = normalize ( texture ( normTex , texCoord.xy ).xyz *2.0 -1.0);
vec3 incident = normalize ( lightPos - worldPos );
vec3 viewDir = normalize ( cameraPos - worldPos );
vec3 halfDir = normalize ( incident + viewDir );

float lambert = clamp ( dot ( incident , normal ) ,0.0 ,1.0);
float rFactor = clamp ( dot ( halfDir , normal ) ,0.0 ,1.0);
float specFactor = clamp ( dot ( halfDir , normal ) ,0.0 ,1.0);
if(texture(specTex, texCoord.xy).xyz == vec3(0.2,0.2,0.2)){
specFactor = pow ( specFactor , 60);
}
else{
specFactor = pow ( specFactor , texture(specTex, texCoord.xy).r);
}

float angle = dot(vec3(0.0f, -1.0f, 0.0f), -incident);
float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f); 

vec3 attenuated = lightColour.xyz * atten ;
diffuseOutput = vec4 ( attenuated * lambert * inten, 1.0);
specularOutput = vec4 ( attenuated * specFactor * inten * 0.33 , 1.0);
}