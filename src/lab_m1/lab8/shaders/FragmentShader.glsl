#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction[2];
uniform vec3 light_position[2];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int is_spot_light[2];

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;

    float light = ambient_light;

    for (int i = 0; i < 2; i++) {
    float diffuse_light = 0;
    float specular_light = 0;

 
    vec3 L = normalize(light_position[i] - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);

    vec3 R = reflect(-L, world_normal);

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    diffuse_light = material_kd * max(dot(world_normal, L), 0);

     if (diffuse_light > 0)
    {    
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    float attenuation_factor = 1.0 / pow(distance(light_position[i], world_position), 2);

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    if (is_spot_light[i] == 1) {
        diffuse_light = 0;
        specular_light = 0;

        float cut_off = radians(30);
        float spot_light = dot(-L, light_direction[i]);
        float spot_light_limit = cos(cut_off);

        float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        float light_att_factor = pow(linear_att, 2);

        if (spot_light > cos(cut_off)) {
	        diffuse_light = material_kd * max(dot(world_normal, L), 0);

            if (diffuse_light > 0) {    
                specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
            }
        }
        attenuation_factor = light_att_factor;
    }

    light += attenuation_factor * (diffuse_light + specular_light);
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
    out_color = vec4(object_color * light, 1);
    
}
