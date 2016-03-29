varying vec2 tcoord;
uniform mat4 unif_matrix;
uniform sampler2D tex;

const float M_PI = 3.1415926535;
const float aspect = 640.0 / 480.0;
const vec2 center1 = vec2(0.50, 0.53);
const vec2 center2 = vec2(0.49, 0.50);

void main(void) {
        float u = 0.0;
        float v = 0.0;
        vec4 pos = vec4(0.0, 0.0, 0.0, 1.0);
        float phi_orig = M_PI / 2.0 - M_PI * tcoord.y;
        float theta_orig = 2.0 * M_PI * tcoord.x;
        pos.x = cos(phi_orig) * cos(theta_orig);
        pos.y = cos(phi_orig) * sin(theta_orig);
        pos.z = sin(phi_orig);
        pos = unif_matrix * pos;
        float phi = asin(pos.z);
        float theta = atan(pos.x, pos.y);
        if(phi > -0.1 && phi < 0.1) {
        } else if (phi > 0.0) {
                float r = (phi - M_PI / 2.0) / M_PI;
                float theta2 = -theta + M_PI;
                u = r * cos(theta2) + center1.x;
                v = aspect * r * sin(theta2) + center1.y;
                if (u <= 0.0 || u > 1.0 || v <= 0.0 || v > 1.0) {
                        u = 0.0;
                        v = 0.0;
                } else {
                        u = u * 0.5;
                }
        } else {
                float r = (phi + M_PI / 2.0) / M_PI;
                float theta2 = theta + M_PI / 2.0 - M_PI / 90.0;
                u = r * cos(theta2) + center2.x;
                v = aspect * r * sin(theta2) + center2.y;
                if (u <= 0.0 || u > 1.0 || v <= 0.0 || v > 1.0) {
                        u = 0.0;
                        v = 0.0;
                } else {
                        u = u * 0.5 + 0.5;
                }
        }
        if (u == 0.0 && v == 0.0) {
                gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        }
        else {
                gl_FragColor = texture2D(tex, vec2(u, v));
        }
}
