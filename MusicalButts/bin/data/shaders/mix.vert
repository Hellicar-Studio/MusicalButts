#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
