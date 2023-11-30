#version 410

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

layout(location = 0) out vec3 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform int health;

uniform vec3 object_color;

void main()
{
    color = object_color;
    if (health == -1)
        gl_Position = projection_matrix * view_matrix * model_matrix * vec4(v_position, 1.0);
    else {
        gl_Position = projection_matrix * view_matrix * model_matrix * vec4(v_position, 1.0);
    }
}
