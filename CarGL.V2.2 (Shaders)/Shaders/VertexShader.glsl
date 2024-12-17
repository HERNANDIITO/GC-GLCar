attribute vec4 a_Position;              // in: Posición de cada vértice
attribute vec3 a_Normal;                // in: Normal de cada vértice

uniform mat4 u_ProjectionMatrix;        // in: Matriz Projection
uniform mat4 u_MVMatrix;                // in: Matriz ModelView
uniform mat4 u_VMatrix;                 // in: Matriz View (cámara)
uniform vec4 u_Color;                   // in: Color del objeto

// Uniformes para luz 0
uniform int uLuz0Location;
uniform vec4 uLuz0Ambient;
uniform vec4 uLuz0Diffuse;
uniform vec4 uLuz0Specular;
uniform vec4 uLuz0Position;
uniform float uLuz0Intensity;

// Uniformes para luz 1
uniform int uLuz1Location;
uniform vec4 uLuz1Ambient;
uniform vec4 uLuz1Diffuse;
uniform vec4 uLuz1Specular;
uniform vec4 uLuz1Position;
uniform float uLuz1Intensity;

// Uniformes para luz 2
uniform int uLuz2Location;
uniform vec4 uLuz2Ambient;
uniform vec4 uLuz2Diffuse;
uniform vec4 uLuz2Specular;
uniform vec4 uLuz2Position;
uniform float uLuz2Intensity;

varying vec4 v_Color;                   // out: Color al fragment shader

void main() {
    vec3 P = vec3(u_MVMatrix * a_Position);             // Posición del vértice en espacio de vista
    vec3 N = normalize(vec3(u_MVMatrix * vec4(a_Normal, 0.0))); // Normal del vértice en espacio de vista

    vec4 ambientLight = vec4(0.0);
    vec4 diffuseLight = vec4(0.0);
    vec4 specularLight = vec4(0.0);

    vec3 V = normalize(-P); // Vector hacia la cámara (vista)

    // Procesar luz 0 si está activa
    if (uLuz0Location > 0) {
        vec3 L0 = normalize(vec3(u_VMatrix * uLuz0Position) - P);
        float diff0 = max(dot(N, L0), 0.0) * uLuz0Intensity;
        diffuseLight += uLuz0Diffuse * diff0;
        ambientLight += uLuz0Ambient;

        // Cálculo especular para luz 0
        vec3 R0 = reflect(-L0, N); // Vector reflejado
        float spec0 = pow(max(dot(R0, V), 0.0), 32.0) * uLuz0Intensity; // Exponente especular
        specularLight += uLuz0Specular * spec0;
    }

    // Procesar luz 1 si está activa
    if (uLuz1Location > 0) {
        vec3 L1 = normalize(vec3(u_VMatrix * uLuz1Position) - P);
        float diff1 = max(dot(N, L1), 0.0) * uLuz1Intensity;
        diffuseLight += uLuz1Diffuse * diff1;
        ambientLight += uLuz1Ambient;

        // Cálculo especular para luz 1
        vec3 R1 = reflect(-L1, N);
        float spec1 = pow(max(dot(R1, V), 0.0), 32.0) * uLuz1Intensity;
        specularLight += uLuz1Specular * spec1;
    }

    // Procesar luz 2 si está activa
    if (uLuz2Location > 0) {
        vec3 L2 = normalize(vec3(u_VMatrix * uLuz2Position) - P);
        float diff2 = max(dot(N, L2), 0.0) * uLuz2Intensity;
        diffuseLight += uLuz2Diffuse * diff2;
        ambientLight += uLuz2Ambient;

        // Cálculo especular para luz 2
        vec3 R2 = reflect(-L2, N);
        float spec2 = pow(max(dot(R2, V), 0.0), 32.0) * uLuz2Intensity;
        specularLight += uLuz2Specular * spec2;
    }

    // Combinar luces con el color del objeto
    v_Color = u_Color * (ambientLight + diffuseLight) + specularLight;

    // Transformar la posición del vértice
    gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}