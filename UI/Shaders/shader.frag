#version 450

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 fragTexCoord;

layout( set = 1, binding = 1 ) uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, fragTexCoord);
}