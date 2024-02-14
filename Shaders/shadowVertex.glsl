#version 330 core
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec4 nodeColour;

in vec3 position;
in vec4 colour;

out Vertex{
 vec4 colour;
} OUT;

void main(void){
 vec4 worldPos = (modelMatrix * vec4(position,1));
 gl_Position = (projMatrix * viewMatrix) * worldPos;
 OUT.colour = nodeColour;
}
