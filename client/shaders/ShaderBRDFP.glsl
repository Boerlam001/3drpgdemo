
//
// Global variable definitions
//

uniform sampler2D hmapSampler;
uniform sampler2D nmapSampler;

//
// Function declarations
//

vec4 pixelMain( in vec2 HalfAngleTerms, in vec2 NormalAngleTerms, in vec2 UV, in vec4 diffCol );

//
// Function definitions
//

vec4 pixelMain( in vec2 HalfAngleTerms, in vec2 NormalAngleTerms, in vec2 UV, in vec4 diffCol ) {
    vec4 ht;
    vec4 nt;
    vec4 nspec;

    ht = texture2D( hmapSampler, HalfAngleTerms);
    nt = texture2D( nmapSampler, NormalAngleTerms);
    nspec = ((ht * nt) * vec4( 1.00000, 1.00000, 1.00000, 1.00000));
    return (diffCol + nspec);
}


//
// User varying
//
varying vec4 xlat_varying_TEXCOORD0;
varying vec4 xlat_varying_TEXCOORD1;
varying vec4 xlat_varying_COLOR0;

//
// Translator's entry point
//
void main() {
    vec4 xlat_retVal;

    xlat_retVal = pixelMain( vec2(xlat_varying_TEXCOORD0), vec2(xlat_varying_TEXCOORD1), vec2(xlat_varying_TEXCOORD0), vec4(xlat_varying_COLOR0));

    gl_FragData[0] = vec4( xlat_retVal);
}


 