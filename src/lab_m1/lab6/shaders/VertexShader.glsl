#version 330

// Input
// TODO(student): Get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_position;
out vec3 frag_color;
out vec3 frag_normal;
out vec2 frag_texture;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_position = v_position;
    frag_color = v_color;
    frag_normal = v_normal;
    frag_texture = v_texture;

    vec3 position = v_position;

    position.x = v_position.x + cos(Time) * 2.0;
    position.y = v_position.y + cos(Time) * 1.0;
    position.z = v_position.z + cos(Time) * 0.5;

    frag_color.x += cos(Time) * 0.2;
    frag_color.y += cos(Time) * 0.5;
    frag_color.z += cos(Time) * 0.3;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(position, 1.0);
}