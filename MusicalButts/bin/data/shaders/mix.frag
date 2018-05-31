#version 120

uniform sampler2DRect top;
uniform sampler2DRect bot;

float length(vec3 v) {
    return (v.x + v.y + v.z) / 3.0;
}

void main() {
    
    
    vec2 uv = gl_FragCoord.xy;
    
    vec3 topCol = texture2DRect(top, uv).rgb;
    vec3 botCol = texture2DRect(bot, uv).rgb;

    vec3 col;

    if(length(topCol) == 0.0)
    	col = botCol;
    else if(length(botCol) == 0.0)
    	col = topCol;
    else
    	col = topCol + botCol;
    
    gl_FragColor = vec4(col, 1.0);
}
