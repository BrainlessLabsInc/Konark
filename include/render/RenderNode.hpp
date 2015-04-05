#ifndef BLIB_RENDERNODE_HPP
#define BLIB_RENDERNODE_HPP

#include "geometry/BasicGeometries.hpp"
#include "geometry/TransformMatrix.hpp"
#include "render/Attributes.hpp"
#include <boost/variant.hpp>
#include <vector>

namespace blib {
  namespace render {
    namespace bgeom = blib::geometry;

    typedef ::boost::variant <
      bgeom::Point2D,
      bgeom::MultiPoint,
      bgeom::LineString,
      bgeom::MultiLineString,
      bgeom::Polygon,
      bgeom::MultiPolygon,
      bgeom::Box,
      bgeom::Ring,
      bgeom::Segment,
      bgeom::ReferringSegment,
      bgeom::Ellipse> MultiGeometry;

    typedef ::boost::variant <
      StrokeWidth,
      LineCapStyle,
      LineJoinStyles,
      MitterLimit,
      StrokeStyle,
      FillStyle,
      bgeom::TransformMatrix,
      RoundedEdgeAttrib
    > Attribute;
    typedef ::std::vector<Attribute> Attributes;

    typedef ::boost::variant <
      MultiGeometry,
      Attributes,
      Group> RenderNode;
  }
}

#endif // BLIB_RENDERNODE_HPP
