#include "Mesh.h"
#include <iostream>
#include <fstream>

Vec3 Mesh::scalarToRGB( float scalar_value ) const //Scalar_value ∈ [0, 1]
{
    Vec3 rgb;
    float H = scalar_value*360., S = 1., V = 0.85,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        rgb = Vec3( V,  T,  P);
    else if (1. <= H && H < 2.)
        rgb = Vec3( Q,  V,  P);
    else if (2. <= H && H < 3.)
        rgb = Vec3( P,  V,  T);
    else if (3. <= H && H < 4.)
        rgb = Vec3( P,  Q,  V);
    else if (4. <= H && H < 5.)
        rgb = Vec3( T,  P,  V);
    else if (5. <= H && H < 6.)
        rgb = Vec3( V,  P,  Q);
    else
        rgb = Vec3( 0.,  0.,  0.);

    return rgb;
}

void Mesh::computeSkinningWeights( Skeleton & skeleton ) {
    // code to change :

    // Indications:
    // you should compute weights for each vertex w.r.t. the skeleton bones
    // so each vertex will have B weights (B = number of bones)
    // Don't forget to normalize weights
    // these weights shoud be stored in vertex.weights:
    // os.joints[0] l'indice de la première extrémité de l'os
    // os.joints[1] l'indice de la deuxième extrémité de l'os
    // skeleton.articulations[id_articul].p pour récupérer les articulations

    for (int i =0; i < skeleton.bones.size(); i++){ //on affiche les positions des extrémités des os
        Bone bone = skeleton.bones[i];
        int id0 = bone.joints[0];
        int id1 = bone.joints[1];
        Vec3 p0 = skeleton.articulations[id0].position;
        std::cout<<"Mon os "<<i<<" va de l'articulation "<<id0<<" qui a pour position "<<p0<<" à l'articulation "<<id1<<std::endl;

    }

    for( unsigned int i = 0 ; i < vertices.size() ; ++i ) {
        MeshVertex & vertex = vertices[i];
        Vec3 C = vertex.position;

        vertex.weights.resize(skeleton.bones.size());
        float poids_total = 0.0;

        for( int iBone=0; iBone < skeleton.bones.size(); iBone++){
            Bone bone = skeleton.bones[iBone];
            int art0 = bone.joints[0];
            int art1 = bone.joints[1];

            Vec3 A = skeleton.articulations[art0].position;
            Vec3 B = skeleton.articulations[art1].position;

            Vec3 AB = B-A;
            Vec3 AC = C-A;

            float normeAB = sqrt(pow(AB[0],2) + pow(AB[1],2) + pow(AB[2],2));
            Vec3 u = AB/normeAB;

            float normeAprojC = (Vec3::dot(AB,AC))/normeAB;

            if (normeAprojC < 0)
            { 
                normeAprojC = 0;
                }
            else if (normeAprojC > normeAB) 
            { 
                normeAprojC = normeAB;
                }
            Vec3 projC = Vec3(A[0] + u[0]*normeAprojC, A[1]+u[1]*normeAprojC , A[2]+u[2]*normeAprojC);

            float distCprojC = (C-projC).length();

            float w_ij = std::pow(1.0/distCprojC, 5); //on a choisi 5 pour avoir un beau mouvement

            poids_total += w_ij;
            vertex.weights[iBone] = w_ij;

        }

        for (int iBone=0; iBone < skeleton.bones.size(); iBone++)
        {
            vertex.weights[iBone] /= poids_total;
        }
        
    }

}


void Mesh::draw( int displayed_bone ) const {

    glEnable(GL_LIGHTING);
    glBegin (GL_TRIANGLES);

    for (unsigned int i = 0; i < triangles.size (); i++)
        for (unsigned int j = 0; j < 3; j++) {
        const MeshVertex & v = vertices[triangles[i].v[j]];
            if( displayed_bone >= 0 && v.weights.size() > 0 ){
            // code to change :

            // Indications:
            //Call the function scalarToRGB so that you get the same coloring as slide 51
            //Update the color from the Vec3 resulting color

            Vec3 couleur = scalarToRGB(v.weights[displayed_bone]);
            glColor3f(couleur[2], couleur[1], couleur[0]);

        }
        glNormal3f (v.normal[0], v.normal[1], v.normal[2]);
        glVertex3f (v.position[0], v.position[1], v.position[2]);
        }
    glEnd ();
}

void Mesh::drawTransformedMesh( SkeletonTransformation & transfo ) const {
    std::vector< Vec3 > new_positions( vertices.size() );

    //---------------------------------------------------//
    //---------------------------------------------------//
    // code to change :
    for( unsigned int i = 0 ; i < vertices.size() ; ++i ) {
        Vec3 p = vertices[i].position;

        // Indications:
        // you should use the skinning weights to blend the transformations of the vertex position by the bones.
        // to update the position use the weight and the bone transformation
        // for each bone p'=R*p+t
        new_positions[ i ] = Vec3(0, 0, 0);

        for (int j=0; j< transfo.bone_transformations.size(); j++){
            float w_ij = vertices[i].weights[j];
            Mat3 rotation = transfo.bone_transformations[j].world_space_rotation;
            Vec3 translation = transfo.bone_transformations[j].world_space_translation;
            new_positions[i] += w_ij * (rotation * p + translation);
        }

    }

    glEnable(GL_LIGHTING);
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size (); i++)
        for (unsigned int j = 0; j < 3; j++) {
            const MeshVertex & v = vertices[triangles[i].v[j]];
            Vec3 p = new_positions[ triangles[i].v[j] ];
            glNormal3f (v.normal[0], v.normal[1], v.normal[2]);
            glVertex3f (p[0], p[1], p[2]);
        }
    glEnd ();
}

void Mesh::loadOFF (const std::string & filename) {
    std::ifstream in (filename.c_str ());
    if (!in)
        exit (EXIT_FAILURE);
    std::string offString;
    unsigned int sizeV, sizeT, tmp;
    in >> offString >> sizeV >> sizeT >> tmp;
    vertices.resize (sizeV);
    triangles.resize (sizeT);
    for (unsigned int i = 0; i < sizeV; i++)
        in >> vertices[i].position;
    int s;
    for (unsigned int i = 0; i < sizeT; i++) {
        in >> s;
        for (unsigned int j = 0; j < 3; j++)
            in >> triangles[i].v[j];
    }
    in.close ();
    recomputeNormals ();
}

void Mesh::recomputeNormals () {
    for (unsigned int i = 0; i < vertices.size (); i++)
        vertices[i].normal = Vec3 (0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < triangles.size (); i++) {
        Vec3 e01 = vertices[triangles[i].v[1]].position -  vertices[triangles[i].v[0]].position;
        Vec3 e02 = vertices[triangles[i].v[2]].position -  vertices[triangles[i].v[0]].position;
        Vec3 n = Vec3::cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 3; j++)
            vertices[triangles[i].v[j]].normal += n;
    }
    for (unsigned int i = 0; i < vertices.size (); i++)
        vertices[i].normal.normalize ();
}
