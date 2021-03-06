###VERTEX

#version 130

// Inputs
in vec2 inShipPointPosition;

// Outputs        
out vec2 vertexTextureCoords;

// Params
uniform mat4 paramOrthoMatrix;

void main()
{
    vertexTextureCoords = inShipPointPosition; 
    gl_Position = paramOrthoMatrix * vec4(inShipPointPosition.xy, -1.0, 1.0);
}

###FRAGMENT

#version 130

// Inputs
in vec2 vertexTextureCoords;

// Input texture
uniform sampler2D inputTexture;

void main()
{
    gl_FragColor = texture2D(inputTexture, vertexTextureCoords);
} 
