#version 410 core

layout (location = 0) in vec4 inPos;
// layout (location = 1) in vec3 inColour;
// layout (location = 2) in float inSize;
out vec3 colour;
uniform mat4 MVP; //Modelling Viewing Projection

void main()
{
    colour = vec3(1); //inColour;
    gl_PointSize = inPos.w;
    gl_Position = MVP*vec4(inPos.xyz, 1);
}