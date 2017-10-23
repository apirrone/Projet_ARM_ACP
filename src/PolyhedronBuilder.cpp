#include "PolyhedronBuilder.hpp"

template <class HDS>
PolyhedronBuilder<HDS>::PolyhedronBuilder() {
  _vef = vef;
}

template <class HDS>
void PolyhedronBuilder<HDS>::operator()(HDS& hds) {

  typedef typename HDS::Vertex   Vertex;
  typedef typename Vertex::Point Point;

  CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
  // surface with the number of vert, facets and HS
/*  B.begin_surface( _vertices.size(), _faces.size(), 1);

  for (size_t i = 0; i < _faces.size(); i+=3) {
    VEF::Vertex& v1 = _vertices[_faces[i]];
    VEF::Vertex& v2 = _vertices[_faces[i+1]];
    VEF::Vertex& v3 = _vertices[_faces[i+2]];

    B.add_vertex( Point( v1.position[0], v1.position[1], v1.position[2]));
    B.add_vertex( Point(v2.position[0], v2.position[1], v2.position[2]));
    B.add_vertex( Point(v3.position[0], v3.position[1], v3.position[2]));
    B.begin_facet();
    B.add_vertex_to_facet(i);
    B.add_vertex_to_facet(i+1);
    B.add_vertex_to_facet(i+2);
    B.end_facet();
  }
  B.end_surface();*/
}
