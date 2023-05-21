#define PI (3.1415926536)
#define TWO_PI (6.2831853072)

#ifdef GL_ES
precision mediump float;
#endif

uniform float elapsedTime;
varying vec3 position, normal;
varying float randomOffset;

float time = elapsedTime;
uniform vec4 baseColor;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float stage;
uniform float scale;
uniform float t;

const vec4 on = vec4(1.);
const vec4 g  = vec4(0,1,0,1);
const vec4 off = vec4(vec3(0.), 1.);

// creates a cosine wave in the plane at a given angle
float wave(float angle, vec2 point) {
    float cth = cos(angle);
    float sth = sin(angle);
    return (cos (cth*point.x + sth*point.y) + 1.) / 2.;
}

void main() {
    
    if(stage < 1.) {
          float speed = 3.;
        float cutoff = 0.8;
        vec3 cur = mod(position  , scale) / scale;
        cur *= 1. - normal;
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : vec4(1.0);
        
    } else if(stage < 2.) {
        float speed = 3.;
        float cutoff = 0.5;
        vec3 cur = mod(position  , scale) / scale;
        cur *= 1. - normal;
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : baseColor;
    } else if(stage < 3.) {
        gl_FragColor = vec4(sin(mod(position.x + elapsedTime*2., PI)),
                            sin(mod(-randomOffset + elapsedTime*2., TWO_PI)),
                            0,
                            1);
    } else if(stage < 4.) {
        // crazy triangles, grid lines
        float speed = 0.01;
        float cutoff = 0.9;
        vec3 cur = mod(position, scale*10.0) / (scale*10.0);
        //cur *= 1.0 - abs(normal);
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : vec4(sin(mod(position.x + elapsedTime*2., PI)),
                                                                             sin(mod(-randomOffset + elapsedTime*2., TWO_PI)),
                                                                             sin(mod(elapsedTime,PI)),
                                                                             1)*vec4(normal*.5+0.5, 1.0);
    } else if(stage < 5.) {
        
        float speed = 0.01;
        float cutoff = 0.9;
        vec3 cur = mod(position, scale) / scale;
        //cur *= 1.0 - abs(normal);
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : vec4(sin(mod(position.x + elapsedTime*2., PI)),
                                                                             sin(mod(-randomOffset + elapsedTime*2., TWO_PI)),
                                                                             sin(mod(elapsedTime,PI)),
                                                                             1)*vec4(normal*.5+0.5, 1.0);
    } else if (stage < 6.) {
        vec4 c = baseColor*dot((normal), baseColor.xyz)+baseColor;
        c.a = 1.0;
        gl_FragColor = c;
    } else if (stage < 7.) {
        float d = mod(position.z * scale, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.50) gl_FragColor = baseColor;
        else gl_FragColor = off;
    } else if (stage < 8.) {
        float d = mod(position.y * scale, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.90) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 9.) {
        float d = mod(position.x * scale, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.90) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 10.) {
        float d = mod(length(position) * scale, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        if (a > 0.9) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 11.) {
          float d = mod(position.x * scale, t) / t;
          float d2 = mod(position.y * scale, t) / t;
          float a = sin(d * TWO_PI) * 0.5 + 0.5;
          float b = sin(d2 * TWO_PI) * 0.5 + 0.5;
          if (a > 0.50 && b > 0.50) gl_FragColor = baseColor;
          else gl_FragColor = off;
      }
    
}
