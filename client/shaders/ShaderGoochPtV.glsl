//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Position;
    vec4 Color;
};


//
// Global variable definitions
//

uniform vec4 LightPos;
uniform mat4 World;
uniform mat4 mWorldViewProj;

//
// Function declarations
//

VS_OUTPUT vertexMain( in vec4 Position, in vec3 Normal );

//
// Function definitions
//

VS_OUTPUT vertexMain( in vec4 Position, in vec3 Normal ) {
    vec3 Nn;
    vec4 Po;
    vec3 Pw;
    vec3 Ln;
    float mixer;
    vec3 surfColor;
    vec3 toneColor;
    vec3 mixColor;
    VS_OUTPUT OUT;

    Nn = -Normal;
    Po = vec4( Position.xyz , 1.00000);
    Pw = ( World * Po  ).xyz ;
    Ln = normalize( (Pw - vec3( LightPos)) ).xyz ;
    mixer = (0.500000 * (dot( Nn, Ln) + 1.00000));
    surfColor = mix( vec3( 0.000000, 0.000000, 0.000000), vec3( 0.800000, 0.500000, 0.100000), vec3( mixer));
    toneColor = mix( vec3( 0.0500000, 0.0500000, 0.600000), vec3( 0.500000, 0.400000, 0.0500000), vec3( mixer));
    mixColor = (surfColor + toneColor);
    OUT.Color = vec4( mixColor.xyz , 1.00000);
    OUT.Position = ( mWorldViewProj * Po  );
    return OUT;
}


//
// User varying
//
varying vec4 xlat_varying_COLOR0;

//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;

    xlat_retVal = vertexMain( vec4(gl_Vertex), vec3(gl_Normal));

    gl_Position = vec4( xlat_retVal.Position);
    xlat_varying_COLOR0 = vec4( xlat_retVal.Color);
}


 