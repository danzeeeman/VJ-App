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
    float stages = 7.;
    
    if(stage < 1.) {
        vec2 normPosition = (position.xz + position.yz)/(1.0+abs(sin(elapsedTime)*10.0));
        vec2 normPosition2 = (position.xz + position.xy)/(1.0+abs(cos(elapsedTime)*13.0));
        normPosition = mix(normPosition, normPosition2, vec2(sin(1.+elapsedTime), cos(1.+elapsedTime)));
        float b = wave(elapsedTime, (normPosition));
        gl_FragColor = vec4(vec3(b)-sin(elapsedTime), 1.0);
        
    } else if(stage < 2.) {
        float speed = 3.;
        float scale = 30.0;
        float cutoff = .9;
        vec3 cur = mod(position  , scale) / scale;
        cur *= 1. - abs(normal);
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : vec4(1.0);
    } else if(stage < 3.) {
        gl_FragColor = vec4(sin(mod(position.x + elapsedTime*2., PI)),
                            sin(mod(-randomOffset + elapsedTime*2., TWO_PI)),
                            0,
                            1);
    } else if(stage < 4.) {
        // crazy triangles, grid lines
        float speed = 0.1;
        float scale = 10.01;
        float cutoff = 0.9;
        vec3 cur = mod(position + speed * elapsedTime, scale) / scale;
        cur *= 1. - abs(normal);
        gl_FragColor = (max(max(cur.x, cur.y), cur.z) < cutoff) ? off : vec4(sin(mod(position.x + elapsedTime*2., PI)),
                                                                             sin(mod(-randomOffset + elapsedTime*2., TWO_PI)),
                                                                             sin(mod(elapsedTime,PI)),
                                                                             1)*vec4(normal*.5+0.5, 1.0);
    } else if(stage < 5.) {
        
        float sum = 0.0;
        float size = resolution.x / 1000.0;
        for (int i = 0; i < 20; ++i) {
            vec2 position = resolution / 2.0;
            float t = (float(i) + elapsedTime) / 5.0;
            float c = float(i) * 4.0;
            position.x += tan(8.0 * t + c) * resolution.x * 0.2;
            position.y += sin(t) * resolution.y * 0.8;
            
            sum += size / length(gl_FragCoord.xy - position);
        }
        gl_FragColor = vec4(sum * 0.5, sum, sum * 3.1, 1);
    } else if (stage < 6.) {
        gl_FragColor = vec4(normal * 0.5 + 0.5, 1);
    } else if (stage < 7.) {
        float t = mod(elapsedTime , 120.) +15.0;
        float d = mod(position.z * 1.0, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.50) gl_FragColor = baseColor;
        else gl_FragColor = off;
    } else if (stage < 8.) {
        float t = mod(elapsedTime , 120.) +15.0;
        float d = mod(position.y * 1.0, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.50) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 9.) {
        float t = mod(elapsedTime , 120.) +15.0;
        float d = mod(position.x * 1.0, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.50) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 10.) {
        float t = mod(elapsedTime , 120.) +15.0;
        float d = mod(length(position) * 1.0, t) / t;
        float a = sin(d * TWO_PI) * 0.5 + 0.5;
        
        if (a > 0.50) gl_FragColor = baseColor;
        else gl_FragColor = off;
    }
    else if (stage < 11.) {
          float t = mod(elapsedTime , 15.0) +15.0;
          float d = mod(position.x * 2.0, t) / t;
          float d2 = mod(position.y * 2.0, t) / t;
          float a = sin(d * TWO_PI) * 0.5 + 0.5;
          float b = sin(d2 * TWO_PI) * 0.5 + 0.5;
          if (a > 0.50 && b > 0.50) gl_FragColor = baseColor;
          else gl_FragColor = off;
      }
    
}
