#version 410

uniform vec3 color;
out vec4 fragColor;

void
main()
{
    fragColor = vec4(color,1);
    //fragColor = vec4(1,0.5,0,1);
}
