varying vec2 tcoord;
uniform sampler2D tex;

const float M_PI = 3.1415926535;
const float aspect = 640.0 / 480.0;
const vec2 center1 = vec2(0.50, 0.53);
const vec2 center2 = vec2(0.49, 0.50);

void main(void) {
	float x = 0.0;
	float y = 0.0;
	if(tcoord.y > 0.49 && tcoord.y < 0.51) {
	} else if (tcoord.y < 0.5) {
		float r = tcoord.y;
		float theta = 2.0 * M_PI * -tcoord.x + M_PI;
		x = r * cos(theta) + center1.x;
		y = aspect * r * sin(theta) + center1.y;
		if (x <= 0.0 || x > 1.0 || y <= 0.0 || y > 1.0) {
			x = 0.0;
			y = 0.0;
		} else {
			x = x * 0.5;
		}
	} else {
		float r = 1.0 - tcoord.y;
		float theta = 2.0 * M_PI * tcoord.x - M_PI / 2.0 - M_PI / 90.0;
		x = r * cos(theta) + center2.x;
		y = aspect * r * sin(theta) + center2.y;
		if (x <= 0.0 || x > 1.0 || y <= 0.0 || y > 1.0) {
			x = 0.0;
			y = 0.0;
		} else {
			x = x * 0.5 + 0.5;
		}
	}
	if (x == 0.0 && y == 0.0) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else {
		gl_FragColor = texture2D(tex, vec2(x, y));
	}
}

