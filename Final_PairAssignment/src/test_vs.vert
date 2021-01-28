#version 330 core
in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 FragPos;
out vec3 Normal;


uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;



void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;

	vec4 MCPosition = vec4(inPosition, 1.0f);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
	FragPos = vec3(ModelMatrix * vec4(inPosition, 1.0f));
    Normal = mat3(transpose(inverse(ModelMatrix))) * inNormal;
}