#ifndef BLIB_ELLIPSE_HPP
#define BLIB_ELLIPSE_HPP

#include <boost/geometry/geometries/geometries.hpp>
#include "Point.hpp"

namespace blib {
  namespace geometry {

    // Ellipse implementation
    class Ellipse : public bgeom::model::ring < Point2D > {
    public:
      typedef ::boost::geometry::traits::coordinate_type< ::blib::geometry::Point2D >::type ValueType;
      Ellipse( ) :
        _heigth( 0 ),
        _width( 0 ),
        _center( ) {}

      void height( const ValueType  aHeight ) {
        _heigth = aHeight;
      }

      void width( const ValueType  aWidth ) {
        _width = aWidth;
      }

      ValueType height( ) const {
        return _heigth;
      }

      ValueType width( ) const {
        return _width;
      }

      Point2D& center( ) {
        return _center;
      }

    private:
      ValueType _heigth, _width;
      Point2D _center;
    };
  }
}

#endif // BLIB_ELLIPSE_HPP
