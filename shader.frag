// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

out vec4 FragColor;

uniform sampler2D onetex;
uniform float time;
uniform float hurt;
uniform float startTime;

void main()
{
	vec4 color = texture2D(onetex, uv_interp);
	FragColor = vec4(color.r,color.g,color.b,color.a);
    if((color.r + color.g + color.b) / 3.0 > 0.99 || color.a  == 0)
	{
 		discard;
	}

	if(hurt > 0)
	{
		float myTime = time - startTime;
		vec4 red = vec4(1.0f, abs(cos(myTime * 8)), abs(cos(myTime * 8)), 1.0f);
		FragColor  *= red;
	}

//	 FragColor = color_interp;
}