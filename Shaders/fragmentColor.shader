#version 330 core
out vec4 FragColor;

uniform vec3 ourColor;

void main(){
    vec3 _color = ourColor;
    FragColor = vec4(_color, 1.0f);
}