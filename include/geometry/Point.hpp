#ifndef BLIB_POINT_HPP
#define BLIB_POINT_HPP

#include <boost/geometry/geometries/geometries.hpp>
#include "TransformMatrix.hpp"
#include "CoordinateConfigure.hpp"
#include <cmath>
#include <array>
#include <boost/operators.hpp>

namespace blib {
  namespace geometry {
    namespace bgeom = ::boost::geometry;
    typedef ::blib::math::RowVector3f Vec3f;;

    // 2D Point Type
    class Point2D : public boost::field_operators < Point2D > {
    public:
      typedef CoordinateType ValueType;
      typedef Point2D SelfType;
      typedef boost::mpl::int_ < 2 > Dimensions;

    private:
      std::array<ValueType, Dimensions::value> _coordinates;

    public:
      Point2D( const ValueType aX = 0, const ValueType aY = 0 ) :
        _coordinates( { { aX, aY } } ) {}

      void x( const ValueType aX ) {
        _coordinates[ 0 ] = aX;
      }

      void y( const ValueType aY ) {
        _coordinates[ 1 ] = aY;
      }

      ValueType x( ) const {
        return _coordinates[ 0 ];
      }

      ValueType y( ) const {
        return _coordinates[ 1 ];
      }

      ValueType& x( ) {
        return _coordinates[ 0 ];
      }

      ValueType& y( ) {
        return _coordinates[ 1 ];
      }

      Vec3f vec3f( ) const {
        const Vec3f ret( _coordinates[ 0 ], _coordinates[ 1 ], 1 );
        return ret;
      }
      // Convert to a Vec3f
      operator Vec3f( ) const {
        return vec3f( );
      }

      SelfType& operator=( Vec3f& aOther ) {
        _coordinates[ 0 ] = aOther( 0 );
        _coordinates[ 1 ] = aOther( 1 );
        return *this;
      }

      SelfType& apply( TransformMatrix& aMat ) {
        const Vec3f v( _coordinates[ 0 ], _coordinates[ 1 ], 1 );
        const auto& p = aMat.mat( ) * v;
        _coordinates[ 0 ] = p( 0 );
        _coordinates[ 1 ] = p( 1 );
      }

      ValueType magnitude( ) const {
        const auto ret = std::sqrt( squarMagnitude( ) );
        return ret;
      }

      ValueType squarMagnitude( ) const {
        const auto x = _coordinates[ 0 ];
        const auto y = _coordinates[ 1 ];
        const auto ret = x*x + y*y;
        return ret;
      }

      SelfType& operator+=( SelfType const& aOther ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x + aOther._coordinates[ 0 ];
        y = y + aOther._coordinates[ 1 ];
        return *this;
      }

      SelfType& operator-=( SelfType const& aOther ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x - aOther._coordinates[ 0 ];
        y = y - aOther._coordinates[ 1 ];
        return *this;
      }

      SelfType& operator+=( const ValueType aFactor ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x + aFactor;
        y = y + aFactor;
        return *this;
      }

      SelfType& operator-=( const ValueType aFactor ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x - aFactor;
        y = y - aFactor;
        return *this;
      }

      SelfType& operator*=( const ValueType aFactor ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x * aFactor;
        y = y * aFactor;
        return *this;
      }

      // Factor should be greater than 0
      SelfType& operator/=( const ValueType aFactor ) {
        auto& x = _coordinates[ 0 ];
        auto& y = _coordinates[ 1 ];
        x = x / aFactor;
        y = y / aFactor;
        return *this;
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
        : ::blib::geometry::Point2D::Dimensions
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

// Overloading the operators
blib::geometry::Point2D operator*( blib::geometry::TransformMatrix & aTransformMatrix, blib::geometry::Point2D& aPoint ) {
  const auto p = aTransformMatrix.mat( ) * aPoint.vec3f( );
  blib::geometry::Point2D point( p( 0 ), p( 1 ) );
}

#endif // BLIB_POINT_HPP
