#version 330


layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;

//uniform mat4 modelMatrix;
//uniform mat4 modelViewMatrix;
uniform mat4 mvpMatrix;
//uniform mat4 normalMatrix;
//uniform vec4 lightPosition;

//out vec4 fragColor;

out vec3 tescNormal;

void main() {
    gl_Position = vec4(vertPosition, 1.0);
    tescNormal = vertNormal;
}

    /*vec4 white = vec4(1.0); // light color (diffuse & specular)
    vec4 grey = vec4(0.15, 0.15, 0.17, 1.0);  // ambient light color

    vec4 material = vec4(0.6, 0.6, 0.65, 1.0);
    vec4 ambient = grey * material;

    vec4 eyePosition = modelViewMatrix * vec4(vertPosition, 1.0);
    vec4 eyeNormal = normalMatrix * vec4(vertNormal, 0.0);
    vec4 lightDirection;
    // if the light is directional (non-point lighting)
    if (lightPosition.w == 0) {
        lightDirection = vec4(normalize(lightPosition.xyz), 1.0);
    } else {
        lightDirection = normalize(lightPosition - eyePosition);
    }
    vec4 view = normalize(vec4(-eyePosition.xyz, 0.0));
    vec4 halfVector = normalize(lightDirection + view);

    float diffuseTerm = max(dot(lightDirection, eyeNormal), 0.0);
    vec4 diffuse = material * diffuseTerm;

    float shininess = 100.0;
    float specularTerm = max(dot(halfVector, eyeNormal), 0.0);
    vec4 specular = white * pow(specularTerm, shininess);


    fragColor = ambient + diffuse;*/


/*vec3 applyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePosition, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    // check if the light position is a directional light (e.g. the sun)
    if (lightPosition.w == 0.0) {
        // is direction light..
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; // no attenuation for directional lights
    } else {
        // ..non-direction light / point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + lgiht.attenuation * pow(distanceToLight, 2));

        // cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degress(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if (lightToSurfaceAngle > light.coneAngle)
            attenuation = 0.0;

    }

    // ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    // diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

    // specular
    float specularCoefficient = 0.0;
    if (diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))));
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

    // linear color
    return ambient + attenuation * (diffuse + specular);
}*/
