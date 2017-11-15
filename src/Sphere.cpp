#include "Sphere.hpp"

Sphere::Sphere(Eigen::Vector3f center, float radius, int nU, int nV)
:_center(center), _radius(radius), _nU(nU), _nV(nV) {

  int nVertices  = (nU + 1) * (nV + 1);
    int nTriangles =  nU * nV * 2;

    _vertices.resize(nVertices);
    //_indices.resize(3*nTriangles);

    for(int v=0;v<=nV;++v)
    {
        for(int u=0;u<=nU;++u)
        {

            float theta = u / float(nU) * M_PI;
            float phi 	= v / float(nV) * M_PI * 2;

            int index 	= u +(nU+1)*v;

            Eigen::Vector3f normal;

            // normal
            normal[0] = sin(theta) * cos(phi);
            normal[1] = sin(theta) * sin(phi);
            normal[2] = cos(theta);
            normal.normalize();

            // position
            VEF::Vertex vertex = VEF::Vertex(normal * _radius, normal);

            //_vertices[index] = vertex;
            //_normals[index] = normal;
        }
    }

    /*int index = 0;
    for(int v=0;v<nV;++v)
    {
        for(int u=0;u<nU;++u)
        {
            int vindex 	= u + (nU+1)*v;

            _indices[index+0] = vindex;
            _indices[index+1] = vindex+1 ;
            _indices[index+2] = vindex+1 + (nU+1);

            _indices[index+3] = vindex;
            _indices[index+4] = vindex+1 + (nU+1);
            _indices[index+5] = vindex   + (nU+1);

            index += 6;
        }
    }*/

}
