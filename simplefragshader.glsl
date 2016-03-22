varying vec2 tcoord;
uniform sampler2D tex;
uniform vec4 threshLow, threshHigh;

const float M_PI = 3.1415926535;

void main(void) 
{
	if(tcoord.y < 0.5)
	{
	    float r = tcoord.y;
        float theta = 2.0 * M_PI * -tcoord.x + M_PI;
        float x = r * cos(theta) + 0.5;
        float y = r * sin(theta) + 0.5;

        gl_FragColor = texture2D(tex,vec2(x*0.5,y));
	}
	else{
	    float r = 1.0 - tcoord.y;
        float theta = 2.0 * M_PI * tcoord.x + M_PI / 2.0;
        float x = r * cos(theta) + 0.5;
        float y = r * sin(theta) + 0.5;

        gl_FragColor = texture2D(tex,vec2(x*0.5+0.5,y));
	}
}
