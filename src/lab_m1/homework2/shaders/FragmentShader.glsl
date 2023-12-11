#version 410

layout(location = 0) in vec3 in_color;

layout(location = 0) out vec4 out_color;

uniform int health;

void main()
{
    if (health == -1)
        out_color = vec4(in_color, 1);
    else {
        float alpha = 1;
        if (health < 3)
            alpha = (float(health + 1) / 4);
		out_color = vec4(in_color * alpha, 1);
    }
}
