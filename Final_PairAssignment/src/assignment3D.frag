#version 330 core

in vec4 ex_Color;
in vec3 ex_Normal;
out vec4 out_Color;

void main(void)
{
	vec3 normal = abs(exNormal);
	vec3 color3 = ex_color * normal.z + normal.x * ex_color * 0.5 + normal.y * ex_color * 0.7;
	
	out_Color = vec4(color3, 1.0);
	//out_Color = ex_Color;
}