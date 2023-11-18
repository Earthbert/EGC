#version 410

// Input
// TODO(student): Get values from vertex shader
layout(location = 0) in vec3 frag_position;
layout(location = 1) in vec3 frag_color;
layout(location = 2) in vec3 frag_normal;
layout(location = 3) in vec2 frag_texture;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4((frag_color + 1) / 2, 1);
}
