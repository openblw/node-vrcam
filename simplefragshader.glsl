varying vec2 tcoord;
uniform sampler2D tex;
uniform vec4 threshLow, threshHigh;

const float M_PI = 3.1415926535;
const float aspect = 640.0 / 480.0;

void main(void) {
	float x = 0.0;
	float y = 0.0;
	if(tcoord.y > 0.49 && tcoord.y < 0.51) {
	} else if (tcoord.y < 0.5) {
		float r = tcoord.y;
		float theta = 2.0 * M_PI * -tcoord.x + M_PI;
		x = r * cos(theta) + 0.5;
		y = aspect * r * sin(theta) + 0.5;
		x = x * 0.5;
	} else {
		float r = 1.0 - tcoord.y;
		float theta = 2.0 * M_PI * tcoord.x - M_PI / 2.0;
		x = r * cos(theta) + 0.5;
		y = aspect * r * sin(theta) + 0.5;

		x = x * 0.5 + 0.5;
	}
	if (x <= 0.0 || x > 1.0 || y <= 0.0 || y > 1.0) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else {
		gl_FragColor = texture2D(tex, vec2(x, y));
	}
}

