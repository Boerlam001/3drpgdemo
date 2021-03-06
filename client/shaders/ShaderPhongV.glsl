//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Pos;
    vec3 Light;
    vec3 Norm;
    vec3 View;
    vec2 TexCo;
};


//
// Global variable definitions
//

uniform vec4 CamPos;
uniform vec4 LightPos;
uniform mat4 World;
uniform mat4 mWorldViewProj;

//
// Function declarations
//

VS_OUTPUT vertexMain( in vec4 Pos, in vec3 Normal, in vec2 TexC );

//
// Function definitions
//

VS_OUTPUT vertexMain( in vec4 Pos, in vec3 Normal, in vec2 TexC ) {
    VS_OUTPUT Out;
    vec3 PosWorld;

    Out = VS_OUTPUT( vec4( 0.000000, 0.000000, 0.000000, 0.000000), vec3( 0.000000, 0.000000, 0.000000), vec3( 0.000000, 0.000000, 0.000000), vec3( 0.000000, 0.000000, 0.000000), vec2( 0.000000, 0.000000));
    Out.Pos = ( mWorldViewProj * Pos  );
    Out.Light = normalize( (vec3( LightPos) - Pos.xyz ) );
    PosWorld = vec3( normalize( ( World * Pos  ) ));
    Out.View = normalize( (vec3( CamPos) - PosWorld) );
    Out.Norm = normalize( ( Normal ) );
    Out.TexCo = TexC;
    return Out;
}


//
// User varying
//
varying vec4 xlat_varying_TEXCOORD0;
varying vec4 xlat_varying_TEXCOORD1;
varying vec4 xlat_varying_TEXCOORD2;
varying vec4 xlat_varying_TEXCOORD3;

//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;

    xlat_retVal = vertexMain( vec4(gl_Vertex), vec3(gl_Normal), vec2(gl_MultiTexCoord0));

    gl_Position = vec4( xlat_retVal.Pos);
    xlat_varying_TEXCOORD0 = vec4( xlat_retVal.Light, 0.0);
    xlat_varying_TEXCOORD1 = vec4( xlat_retVal.Norm, 0.0);
    xlat_varying_TEXCOORD2 = vec4( xlat_retVal.View, 0.0);
    xlat_varying_TEXCOORD3 = vec4( xlat_retVal.TexCo, 0.0, 0.0);
}


 