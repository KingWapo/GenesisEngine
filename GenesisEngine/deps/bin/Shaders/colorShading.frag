#version 130

//in vec2 fragmentPosition;
//in vec4 fragmentColor;
//in vec2 fragmentUV;

//out vec4 color;

uniform sampler2D mySampler;

void main() {
	vec3 textureColor = texture(mySampler, gl_TexCoord[0].st).rgb;
	gl_FragColor = vec4(gl_Color.rgb * textureColor, 1.0);

	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
