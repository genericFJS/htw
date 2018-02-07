#version 420 core

in vec3 vs_normal;
in vec3 vs_frag_pos;  
in vec2 vs_text_coord;
  
uniform vec3 light_pos;
uniform vec3 light_pos2; 
uniform vec3 view_pos;
uniform vec3 light_color;
uniform vec3 light_color2;
uniform vec3 object_color;
uniform sampler2D tex;

out vec4 fs_color;

void main() {
    // Ambient:
    float ambient_strength = 0.01f;
    vec3 ambient = ambient_strength * light_color;
    
    // Diffuse (zwei Quellen):
    vec3 norm = normalize(vs_normal);
    vec3 light_dir = normalize(light_pos - vs_frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 norm2 = normalize(vs_normal);
    vec3 light_dir2 = normalize(light_pos2 - vs_frag_pos);
    float diff2 = max(dot(norm, light_dir2), 0.0);
    vec3 diffuse2 = diff2 * light_color2;
    
    // Specular (zwei Quellen):
    float specular_strength = 1.0f;
    vec3 view_dir = normalize(view_pos - vs_frag_pos);
    
    vec3 reflect_dir = reflect(-light_dir, norm);  
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color; 

    vec3 reflect_dir2 = reflect(-light_dir2, norm);  
    float spec2 = pow(max(dot(view_dir, reflect_dir2), 0.0), 32);
    vec3 specular2 = specular_strength * spec2 * light_color2; 
		    
    // Gesamtwert:
    vec3 result = (ambient + diffuse + diffuse2 + specular + specular2) * object_color;
	// Einfacher Farbwert:
    fs_color = vec4(result, 1.0f);
	// Texturierter Farbwert:
    //fs_color = texture(tex, vs_text_coord) * vec4(result, 1.0f);
} 