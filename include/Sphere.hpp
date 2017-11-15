#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "VEF.hpp"
#include "ext/eigen3/Eigen/Eigen"


class Sphere : public VEF {

private:
  float _radius;
  int _nU;
  int _nV;
  Eigen::Vector3f _center;

public:
  Sphere(Eigen::Vector3f center, float radius=1.f, int nU=40, int nV=40);
  //virtual QMatrix4x4 worldMatrix() override;
};

#endif // SPHERE_HPP
