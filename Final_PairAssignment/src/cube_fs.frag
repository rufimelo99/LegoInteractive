#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

uniform vec4 Color;

void main(void)
{
	//vec3 N = normalize(exNormal);
	//vec3 direction = vec3(1.0, 0.5, 0.25);
	//float intensity = max(dot(direction, N), 0.0);
	//FragmentColor = vec4(vec3(intensity), 1.0);

	vec3 normal = abs(exNormal);
	vec3 ex_color = Color.xyz;
	vec3 color3 = ex_color * normal.z + normal.x * ex_color * 0.5 + normal.y * ex_color * 0.7;
	FragmentColor = vec4(vec3(color3), 1.0);
}
