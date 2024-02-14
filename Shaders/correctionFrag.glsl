#version 330 core

uniform sampler2D correctionTex;
uniform float exposure; 

in Vertex{
	vec2 texCoord;
}IN;

out vec4 fragColour;

void main(void)
{          
    const float gamma = 2.2;
    vec3 hdrColor = texture(correctionTex, IN.texCoord).rgb;

    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    mapped = pow(mapped, vec3(1.0 / gamma));

    fragColour = vec4(mapped, 1.0);
}
