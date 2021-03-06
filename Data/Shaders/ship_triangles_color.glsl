###VERTEX

#version 130

// Inputs
in vec2 inShipPointPosition;
in float inShipPointLight;
in float inShipPointWater;
in vec3 inShipPointColor;

// Outputs        
out float vertexLight;
out float vertexWater;
out vec3 vertexCol;

// Params
uniform mat4 paramOrthoMatrix;

void main()
{            
    vertexLight = inShipPointLight;
    vertexWater = inShipPointWater;
    vertexCol = inShipPointColor;

    gl_Position = paramOrthoMatrix * vec4(inShipPointPosition.xy, -1.0, 1.0);
}

###FRAGMENT

#version 130

// Inputs from previous shader        
in float vertexLight;
in float vertexWater;
in vec3 vertexCol;

// Params
uniform float paramAmbientLightIntensity;
uniform float paramWaterLevelThreshold;

void main()
{
    // Apply point water
    float colorWetness = min(vertexWater, paramWaterLevelThreshold) * 0.7 / paramWaterLevelThreshold;
    vec3 fragColour = vertexCol * (1.0 - colorWetness) + vec3(%WET_COLOR_VEC3%) * colorWetness;

     // Apply ambient light
    fragColour *= paramAmbientLightIntensity;

    // Apply point light
    fragColour = fragColour * (1.0 - vertexLight) + vec3(%LAMPLIGHT_COLOR_VEC3%) * vertexLight;
    
    gl_FragColor = vec4(fragColour.xyz, 1.0);
} 

