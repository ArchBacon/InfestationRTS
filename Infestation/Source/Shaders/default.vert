#version 300 es

layout (location = 0) in vec3 aPos;
uniform mat4 UModel;
uniform mat4 UView;
uniform mat4 UProjection;

void main()
{
    gl_Position = UProjection * UView * UModel * vec4(aPos, 1.0f);
}
