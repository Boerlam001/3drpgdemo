//
// Structure definitions
//

struct VS_OUTPUT {
    vec4 Position;
    vec2 UV;
};


//
// Global variable definitions
//

uniform vec4 LightPos;
uniform mat4 ViewI;
uniform mat4 World;
uniform mat4 mWorldViewProj;

//
// Function declarations
//

VS_OUTPUT vertexMain( in vec3 Position, in vec4 Normal );

//
// Function definitions
//

VS_OUTPUT vertexMain( in vec3 Position, in vec4 Normal ) {
    vec3 Nn;
    vec4 Po;
    vec3 Pw;
    vec3 Vn;
    vec3 Ln;
    vec3 Hn;
    VS_OUTPUT OUT;

    Nn = ( Normal.xyz  );
    Po = vec4( Position.xyz , 1.00000);
    Pw = ( World * Po  ).xyz ;
    Vn = normalize( (ViewI[ 3 ].xyz  - Pw) );
    Ln = normalize( (vec3( LightPos) - Pw) );
    Hn = normalize( (Vn + Ln) );
    OUT.UV = vec2( dot( Ln, Nn), dot( Hn, Nn));
    OUT.Position = ( mWorldViewProj * Po );
    return OUT;
}


//
// User varying
//
varying vec4 xlat_varying_TEXCOORD0;

//
// Translator's entry point
//
void main() {
    VS_OUTPUT xlat_retVal;

    xlat_retVal = vertexMain( vec3(gl_Vertex), vec4(gl_Normal, 0.0));

    gl_Position = vec4( xlat_retVal.Position);
    xlat_varying_TEXCOORD0 = vec4( xlat_retVal.UV, 0.0, 0.0);
}


 