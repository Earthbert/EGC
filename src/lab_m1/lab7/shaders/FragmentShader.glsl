#version 410

// Input
// TODO(student): Get color value from vertex shader
layout(location = 0) in vec3 in_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(in_color, 1);

}
