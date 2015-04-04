#ifndef BLIB_BASICGEOMETRIES_HPP
#define BLIB_BASICGEOMETRIES_HPP

#include <cstdint>
#include <vector>
#include <cmath>
#include <boost/geometry/geometries/geometries.hpp>
#include "Ellipse.hpp"

namespace blib {
  namespace geometry {
    typedef bgeom::model::linestring<Point2D> LineString;
    typedef bgeom::model::polygon<Point2D> Polygon;
    typedef bgeom::model::multi_point<Point2D> MultiPoint;
    typedef bgeom::model::multi_linestring<LineString> MultiLineString;
    typedef bgeom::model::multi_polygon<Polygon> MultiPolygon;
    typedef bgeom::model::box<Point2D> Box;
    typedef bgeom::model::ring<Point2D> Ring;
    typedef bgeom::model::segment<Point2D> Segment;
    typedef bgeom::model::referring_segment<Point2D> ReferringSegment;
  }
}

#endif // BLIB_BASICGEOMETRIES_HPP
