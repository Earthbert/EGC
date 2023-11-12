#version 430

// Input
layout(location = 0) in vec3 world_position;
layout(location = 1) in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform samplerCube texture_cubemap;
uniform samplerCube texture_cubemap_dynamic;
uniform int type;

uniform vec3 camera_position;

// Output
layout(location = 0) out vec4 out_color;


vec3 myReflect()
{
    // TODO(student): Compute the reflection color value
    return vec3(0.5);

}


vec3 myRefract(float refractive_index)
{
    // TODO(student): Compute the refraction color value
    return vec3(0.5);

}


void main()
{

    if (type == 0)
    {
        out_color = vec4(myReflect(), 0);
    }
    else
    {
        out_color = vec4(myRefract(1.33), 0);
    }
}
