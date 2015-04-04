#ifndef BLIB_TRANSFORMMATRIX_HPP
#define BLIB_TRANSFORMMATRIX_HPP

#include "utils/MathUtils.hpp"
#include "math/Matrix.hpp"
#include "geometry/Point.hpp"

namespace blib {
  namespace geometry {
    class TransformMatrix : public ::blib::math::Matrix < ::blib::geometry::CoordinateType, 3, 3 > {
    public:
      typedef ::blib::math::Matrix < ::blib::geometry::CoordinateType, 3, 3 > BaseType;
      typedef ::blib::geometry::CoordinateType CoordinateType;

    public:
      TransformMatrix( ) : BaseType( ) {
        this->BaseType::operator( )( 2, 2 ) = 1;
      }

      void translateX( const CoordinateType aX ) {
        this->BaseType::operator( )( 0, 0 ) = 1;
        this->BaseType::operator( )( 1, 1 ) = 1;
        this->BaseType::operator( )( 0, 2 ) = aX;
      }

      CoordinateType translateX( )const {
        return this->BaseType::operator( )( 0, 2 );
      }

      void translateY( const CoordinateType aY ) {
        this->BaseType::operator( )( 0, 0 ) = 1;
        this->BaseType::operator( )( 1, 1 ) = 1;
        this->BaseType::operator( )( 1, 2 ) = aY;
      }

      CoordinateType translateY( )const {
        return this->BaseType::operator( )( 1, 2 );
      }

      void scaleX( const CoordinateType aX ) {
        this->BaseType::operator( )( 0, 0 ) = aX;
      }

      CoordinateType scaleX( )const {
        return this->BaseType::operator( )( 0, 0 );
      }

      void scaleY( const CoordinateType aY ) {
        this->BaseType::operator( )( 1, 1 ) = aY;
      }

      CoordinateType scaleY( )const {
        return this->BaseType::operator( )( 1, 1 );
      }

      void rotateThetaDegree( const CoordinateType aThetaDegree ) {
        const CoordinateType aThetaRadian = blib::utils::math::toRadian( aThetaDegree );
        const CoordinateType sine = std::sin( aThetaRadian );
        const CoordinateType cos = std::cos( aThetaRadian );
        this->BaseType::operator( )( 0, 0 ) = cos;
        this->BaseType::operator( )( 1, 1 ) = cos;
        this->BaseType::operator( )( 0, 1 ) = -sine;
        this->BaseType::operator( )( 1, 0 ) = sine;
      }

      CoordinateType thetaDegree( )const {
        const auto thetaRadian = std::acos( this->BaseType::operator( )( 0, 0 ) );
        const auto thetaDegree = blib::utils::math::toDegree( thetaRadian );
        return thetaDegree;
      }

      void searX( const CoordinateType aX ) {
        this->BaseType::operator( )( 0, 0 ) = 1;
        this->BaseType::operator( )( 1, 1 ) = 1;
        this->BaseType::operator( )( 0, 1 ) = aX;
      }

      CoordinateType searX( )const {
        return this->BaseType::operator( )( 0, 1 );
      }

      void searY( const CoordinateType aY ) {
        this->BaseType::operator( )( 0, 0 ) = 1;
        this->BaseType::operator( )( 1, 1 ) = 1;
        this->BaseType::operator( )( 1, 0 ) = aY;
      }

      CoordinateType searY( )const {
        return this->BaseType::operator( )( 1, 0 );
      }
    };
  }
}

#endif // BLIB_TRANSFORMMATRIX_HPP
