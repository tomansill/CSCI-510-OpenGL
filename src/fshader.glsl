#version 120

// Phong shading fragment shader
//Color data
uniform vec4 diffuse;
uniform float diffuseref;
uniform vec4 ambient;
uniform float ambientref;
uniform vec4 specular;
uniform float specularE;
uniform float specularCoef;
uniform sampler2D tex;
//Varying data
varying vec4 normal;
varying vec4 vertexInEye;
varying vec4 lightInEye;
varying vec2 Texcoord;
void main()
{
	//calculations
	//Vector towards camera
	vec4 V = normalize(-vertexInEye);
	//Vector towards light 
	vec4 S = normalize(lightInEye - vertexInEye);
	//Reflection vector of S
	vec4 R = normalize(reflect(-S, normal));

	//Specular is always pink??? why?? lets hardcode it anyways
	vec4 specularW = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	//calculations
    gl_FragColor  = ((ambient * ambientref) 
				  + ((diffuse*diffuseref)*dot(normalize(S), normalize(normal)))
				  + specularCoef*specularW*pow(max(0.0, dot(R, V)), specularE))
				  * texture2D(tex, Texcoord);
}
