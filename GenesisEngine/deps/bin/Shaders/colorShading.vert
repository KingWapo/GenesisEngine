#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

//out vec2 fragmentPosition;
//out vec4 fragmentColor;
//out vec2 fragmentUV;

uniform mat4 P;

void main() {
	
	//fragmentPosition = vertexPosition;	
	gl_FrontColor = vertexColor * P;
	gl_TexCoord[0] = vec4(vec2(vertexUV.x, 1.0 - vertexUV.y), 0.0, 1.0);

	vec2 transformed = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
}