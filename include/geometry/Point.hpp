#ifndef BLIB_POINT_HPP
#define BLIB_POINT_HPP

#include <boost/geometry/geometries/geometries.hpp>
#include "math/Matrix.hpp"
#include "CoordinateConfigure.hpp"
#include <cmath>

namespace blib {
  namespace geometry {
    namespace bgeom = ::boost::geometry;
    typedef ::blib::math::RowVector3f Vec3f;;

    // 2D Point Type
    class Point2D {
    public:
      typedef CoordinateType ValueType;

    private:
      ValueType _coordinates[ 2 ];

    public:
      Point2D( const CoordinateType aX = 0, const CoordinateType aY = 0 ) :
        _coordinates{ aX, aY } {}

      void x( const CoordinateType aX ) {
        _coordinates[ 0 ] = aX;
      }

      void y( const CoordinateType aY ) {
        _coordinates[ 1 ] = aY;
      }

      CoordinateType x( ) const {
        return _coordinates[ 0 ];
      }

      CoordinateType y( ) const {
        return _coordinates[ 1 ];
      }

      // Convert to a Vec3f
      operator Vec3f( ) const {
        Vec3f ret( _coordinates[ 0 ], _coordinates[ 1 ], 1 );
        return ret;
      }

      CoordinateType magnitude( ) const {
        const auto ret = std::sqrt( squarMagnitude( ) );
        return ret;
      }

      CoordinateType squarMagnitude( ) const {
        const auto x = _coordinates[ 0 ];
        const auto y = _coordinates[ 1 ];
        const auto ret = x*x + y*y;
        return ret;
      }
    };
  }
}

// Adapting the custom Point2D Class
namespace boost {
  namespace geometry {
    namespace traits {
      // Adapt Point2D to Boost.Geometry
      template<>
      struct tag < ::blib::geometry::Point2D > {
        typedef point_tag type;
      };

      template<>
      struct coordinate_type < ::blib::geometry::Point2D > {
        typedef ::blib::geometry::Point2D::ValueType type;
      };

      template<>
      struct coordinate_system < ::blib::geometry::Point2D > {
        typedef cs::cartesian type;
      };

      template<>
      struct dimension<::blib::geometry::Point2D >
        : boost::mpl::int_ < 2 >
      {};

      template<>
      struct access < ::blib::geometry::Point2D, 0 > {

        static inline ::blib::geometry::CoordinateType get( ::blib::geometry::Point2D const& p ) {
          return p.x( );
        }

        static inline void set( ::blib::geometry::Point2D & p,
                                ::blib::geometry::CoordinateType const& value ) {
          p.x( value );
        }
      };

      template<>
      struct access < ::blib::geometry::Point2D, 1 > {

        static inline ::blib::geometry::CoordinateType get( ::blib::geometry::Point2D const& p ) {
          return p.y( );
        }

        static inline void set( ::blib::geometry::Point2D & p,
                                ::blib::geometry::CoordinateType const& value ) {
          p.y( value );
        }
      };
    }
  }
} // namespace boost::geometry::traits

#endif // BLIB_POINT_HPP
