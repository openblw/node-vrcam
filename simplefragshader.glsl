varying vec2 tcoord;
uniform sampler2D tex;
uniform vec4 threshLow, threshHigh;

const float M_2PI = 2.0*3.1415926535;

void main(void) 
{
	if(tcoord.y < 0.5)
	{
	    float r = tcoord.y;
        float theta = M_2PI * tcoord.x;
        float x = r * cos(theta) + 0.5;
        float y = r * sin(theta) + 0.5;

        gl_FragColor = texture2D(tex,vec2(x*0.5,y));
	}
	else{
	    float r = 1.0 - tcoord.y;
        float theta = M_2PI * tcoord.x;
        float x = r * cos(theta) + 0.5;
        float y = r * sin(theta) + 0.5;

        gl_FragColor = texture2D(tex,vec2(x*0.5+0.5,y));
	}
}
