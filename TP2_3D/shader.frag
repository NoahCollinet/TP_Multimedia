// --------------------------------------------------------------------------
// gMini,
// a minimal Glut/OpenGL app to extend                              
//
// Copyright(C) 2007-2009                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
//                                                                          
// --------------------------------------------------------------------------

uniform float ambientRef;
uniform float diffuseRef;
uniform float specRef;
uniform float shininess;

varying vec4 p;
varying vec3 n;

void main (void) {
     vec3 P = vec3 (gl_ModelViewMatrix * p); //Position du point à éclairer
     vec3 N = normalize (gl_NormalMatrix * n); //Normal en ce point
     vec3 V = normalize (-P); //Vecteur de vue
     vec3 L0 = normalize (gl_LightSource[0].position.xyz-P);
     vec3 L1 = normalize (gl_LightSource[1].position.xyz-P);
     vec3 L2 = normalize (gl_LightSource[2].position.xyz-P);
     vec3 R0 = reflect(L0,N);
     vec3 R1 = reflect(L1,N);
     vec3 R2 = reflect(L2,N);
    
    vec4 lightContribution = ambientRef * gl_LightModel.ambient*gl_FrontMaterial.ambient; 

    vec4 lightD = diffuseRef*gl_LightSource[0].diffuse*gl_FrontMaterial.diffuse*dot(L0,N); 

    vec4 lightS = specRef * gl_LightSource[0].specular*gl_FrontMaterial.specular *pow(dot(R0,V),shininess);


    vec4 lightContribution1 = ambientRef * gl_LightModel.ambient*gl_FrontMaterial.ambient; 

    vec4 lightD1 = diffuseRef*gl_LightSource[1].diffuse*gl_FrontMaterial.diffuse*dot(L1,N); 

    vec4 lightS1 = specRef * gl_LightSource[1].specular*gl_FrontMaterial.specular *pow(dot(R1,V),shininess);



    vec4 lightContribution2 = ambientRef * gl_LightModel.ambient*gl_FrontMaterial.ambient; 

    vec4 lightD2 = diffuseRef*gl_LightSource[2].diffuse*gl_FrontMaterial.diffuse*dot(L2,N); 

    vec4 lightS2 = specRef * gl_LightSource[2].specular*gl_FrontMaterial.specular *pow(dot(R2,V),shininess);
    

    ////////////////////////////////////////////////
    //Eclairage de Phong à calculer en utilisant
    ///////////////////////////////////////////////
    
    // gl_LightSource[i].position.xyz Position de la lumière i
    // gl_LightSource[i].diffuse Couleur diffuse de la lumière i
    // gl_LightSource[i].specular Couleur speculaire de la lumière i
    // gl_FrontMaterial.diffuse Matériaux diffus de l'objet
    // gl_FrontMaterial.specular Matériaux speculaire de l'objet

    gl_FragColor = vec4 (lightContribution.xyz, 1) + vec4 (lightD.xyz,1) + vec4 (lightS.xyz,1) +vec4 (lightContribution1.xyz, 1) + vec4 (lightD1.xyz,1) + vec4 (lightS1.xyz,1) +vec4 (lightContribution2.xyz, 1) + vec4 (lightD2.xyz,1) + vec4 (lightS2.xyz,1);
}
 
