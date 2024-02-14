#version 330 core

out vec4 fragColour;

in Vertex{
 vec4 colour;
} IN;

void main(void){
 fragColour = vec4(1.0);
}
