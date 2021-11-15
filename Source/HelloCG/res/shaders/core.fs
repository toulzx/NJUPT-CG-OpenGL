#version 330 core


out vec4 color;


in vec3 ourColor;
in vec3 ourNormalVector;
in vec3 FragPos;


uniform vec3 LightPos;
uniform vec3 ViewPos;


struct Material
{
    float diffuse;
    float specular;
};

uniform Material material;


void main()
{

	vec3 lightDirection = normalize(LightPos - FragPos);
    vec3 viewDirection = normalize(ViewPos - FragPos);
    vec3 norm = normalize(ourNormalVector);

    // ambient 环境光
    vec3 ambient = 0.2f * ourColor;

    // diffuse 漫反射
    float diff = material.diffuse * max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = diff * ourColor;

    // specular 镜面反射
    vec3 halfAngle = normalize(viewDirection + lightDirection);
    float spec = material.specular * pow(max(dot(norm, halfAngle), 0.0f), 64.0f);
    vec3 specular = spec * ourColor;

    color = vec4(ambient + diffuse + specular, 1.0f);

}