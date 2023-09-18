#version 330
in vec3 position;
in vec3 normal;
out vec3 vNormal;

#pragma include "global_uniforms_incl.glsl"

void main(void) {
    gl_Position = g_projection * g_view * g_model * vec4(position,1.0);
    vNormal = normal;
}