#ifndef POLYHEDRON_BUILDER_HPP
#define POLYHEDRON_BUILDER_HPP

#include "VEF.hpp"
#include <vector>
#include <sstream>
#include <QtOpenGL>
#include <surface_mesh/surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>

template <class HDS>
class PolyhedronBuilder : public CGAL::Modifier_base<HDS> {

public:
  PolyhedronBuilder(class VEF* vef);

  void operator()(HDS& hds);

private:
  VEF* _vef;
};

#endif // POLYHEDRON_BUILDER_HPP
