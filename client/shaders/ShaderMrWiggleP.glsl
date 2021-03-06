
//
// Global variable definitions
//

uniform sampler2D tex0;

//
// Function declarations
//

vec4 pixelMain( in vec2 UV, in vec4 Color, in vec4 specCol );

//
// Function definitions
//

vec4 pixelMain( in vec2 UV, in vec4 Color, in vec4 specCol ) {
    vec4 final;

    final = ((Color * texture2D( tex0, UV)) + specCol);
    return final;
}


//
// User varying
//
varying vec4 xlat_varying_TEXCOORD0;
varying vec4 xlat_varying_COLOR0;
varying vec4 xlat_varying_COLOR1;

//
// Translator's entry point
//
void main() {
    vec4 xlat_retVal;

    xlat_retVal = pixelMain( vec2(xlat_varying_TEXCOORD0), vec4(xlat_varying_COLOR0), vec4(xlat_varying_COLOR1));

    gl_FragData[0] = vec4( xlat_retVal);
}


 