#ifndef BLIB_CIRCLE_HPP
#define BLIB_CIRCLE_HPP

#include <boost/geometry/geometries/geometries.hpp>
#include "Point.hpp"

namespace blib {
  namespace geometry {

    class Circle : public bgeom::model::ring < Point2D > {
    public:
      typedef ::boost::geometry::traits::coordinate_type< ::blib::geometry::Point2D >::type ValueType;
      Circle( ) :
        _radius( 0 ),
        _center( ) {}

      void radius( const ValueType  aHeight ) {
        _radius = aHeight;
      }

      ValueType radius( ) const {
        return _radius;
      }


      Point2D& center( ) {
        return _center;
      }

      Point2D const& center( ) const {
        return _center;
      }

    private:
      ValueType _radius;
      Point2D _center;
    };
  }
}

#endif // BLIB_CIRCLE_HPP
