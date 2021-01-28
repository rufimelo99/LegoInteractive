#version 330 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec4 Color;
uniform vec4 Brightness;

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_Color = Color * Brightness;
}