#version 130

uniform sampler2D tex;

void main() {
    vec2 position = gl_TexCoord[0].xy;
    vec4 color = texture(tex, position);
    gl_FragColor = color;
}
