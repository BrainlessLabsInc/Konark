#ifndef BLIB_ATTRIBUTES_HPP
#define BLIB_ATTRIBUTES_HPP

#include "geometry/CoordinateConfigure.hpp"
#include <cstdint>
#include <string>

namespace blib {
  namespace render {
    struct Color {
    public:
      typedef ::blib::geometry::CoordinateType ValueType;

      union {
        ValueType _rgba[ 4 ];
        struct {
          ValueType _r, _g, _b, _a;
        };
      };

      Color( ) :_r( 0 ), _g( 0 ), _b( 0 ), _a( 225 ) {}

      Color( ValueType aR, ValueType aG, ValueType aB, ValueType aA = 225 ) :
        _r( aR ), _g( aG ), _b( aB ), _a( aA ) {}

      Color( Color const& aOther ) {
        _r = aOther._r;
        _g = aOther._g;
        _b = aOther._b;
        _a = aOther._a;
      }

      Color& operator=( Color const& aOther ) {
        _r = aOther._r;
        _g = aOther._g;
        _b = aOther._b;
        _a = aOther._a;
        return *this;
      }

      bool operator==( Color const& aOther ) const {
        bool ret = false;
        if ( aOther._r == _r &&
             aOther._g == _g &&
             aOther._b == _b &&
             aOther._a == _a ) {
          ret = true;
        }
        return ret;
      }
    };

    struct StrokeWidth {
      typedef ::blib::geometry::CoordinateType StrokeWidthType;

    private:
      StrokeWidthType _strokeWidth;

    public:
      StrokeWidth( const StrokeWidthType aStrokeWidth = 1. ) :
        _strokeWidth( aStrokeWidth ) {}

      StrokeWidth( StrokeWidth const& aOther ) :
        _strokeWidth( aOther._strokeWidth ) {}

      void strokeWidth( const StrokeWidthType aStrokeWidth ) {
        _strokeWidth = aStrokeWidth;
      }

      StrokeWidthType strokeWidth( ) const {
        return _strokeWidth;
      }

      StrokeWidth& operator=( StrokeWidth const& aOther ) {
        _strokeWidth = aOther._strokeWidth;
        return *this;
      }

      bool operator==( StrokeWidth const& aOther ) const {
        return aOther._strokeWidth == _strokeWidth;
      }
    };

    class LineCapStyle {
    public:
      enum class LineCapTypes : ::std::uint8_t {
        kButt = 0,
        kSquare,
        kRound
      };

    private:
      LineCapTypes _lineCap;

    public:
      LineCapStyle( const LineCapTypes aLineCap = LineCapTypes::kButt ) :
        _lineCap( aLineCap ) {}

      LineCapStyle( LineCapStyle const& aOther ) :
        _lineCap( aOther._lineCap ) {}

      void lineCap( const LineCapTypes aLineCap ) {
        _lineCap = aLineCap;
      }

      LineCapTypes lineCap( ) const {
        return _lineCap;
      }

      LineCapStyle& operator=( LineCapStyle const& aOther ) {
        _lineCap = aOther._lineCap;
        return *this;
      }

      bool operator==( LineCapStyle const& aOther ) const {
        return aOther._lineCap == _lineCap;
      }
    };

    class LineJoinStyles {
    public:
      enum class LineJoinTypes : ::std::uint8_t {
        kBevel = 0,
        kRound,
        kMiter
      };

    private:
      LineJoinTypes _lineJoin;

    public:
      LineJoinStyles( const LineJoinTypes aLineJoin = LineJoinTypes::kBevel ) :
        _lineJoin( aLineJoin ) {}

      LineJoinStyles( LineJoinStyles const& aOther ) :
        _lineJoin( aOther._lineJoin ) {}

      void lineJoin( const LineJoinTypes aLineJoin ) {
        _lineJoin = aLineJoin;
      }

      LineJoinTypes lineJoin( ) const {
        return _lineJoin;
      }

      LineJoinStyles& operator=( LineJoinStyles const& aOther ) {
        _lineJoin = aOther._lineJoin;
        return *this;
      }

      bool operator==( LineJoinStyles const& aOther ) const {
        return aOther._lineJoin == _lineJoin;
      }
    };

    class MitterLimit {
    public:
      typedef ::blib::geometry::CoordinateType MitterLimitType;

    private:
      MitterLimitType _mitterLimit;

    public:
      MitterLimit( const MitterLimitType aMitterLimit = 10. ) :
        _mitterLimit( aMitterLimit ) {}

      MitterLimit( MitterLimit const& aOther ) :
        _mitterLimit( aOther._mitterLimit ) {}

      MitterLimit& operator=( MitterLimit const& aOther ) {
        _mitterLimit = aOther._mitterLimit;
        return *this;
      }

      bool operator==( MitterLimit const& aOther ) const {
        return aOther._mitterLimit == _mitterLimit;
      }

      MitterLimitType mitterLimit( ) const {
        return _mitterLimit;
      }

      void mitterLimit( const MitterLimitType aMitterLimit ) {
        _mitterLimit = aMitterLimit;
      }
    };

    class StrokeStyle {
    private:
      Color _strokeColor;

    public:
      StrokeStyle( Color const& aColor = Color( ) ) :
        _strokeColor( aColor ) {}

      void strokeColor( Color const & aColor ) {
        _strokeColor = aColor;
      }

      StrokeStyle( StrokeStyle const& aOther ) :
        _strokeColor( aOther._strokeColor ) {}

      StrokeStyle& operator=( StrokeStyle const& aOther ) {
        _strokeColor = aOther._strokeColor;
        return *this;
      }

      bool operator==( StrokeStyle const& aOther ) const {
        return aOther._strokeColor == _strokeColor;
      }

      Color& strokeColor( ) {
        return _strokeColor;
      }

      Color const& strokeColor( ) const {
        return _strokeColor;
      }
    };

    class FillStyle {
    private:
      Color _fillColor;

    public:
      FillStyle( Color const& aColor = Color( ) ) :
        _fillColor( aColor ) {}

      FillStyle( FillStyle const& aOther ) :
        _fillColor( aOther._fillColor ) {}

      FillStyle& operator=( FillStyle const& aOther ) {
        _fillColor = aOther._fillColor;
        return *this;
      }

      bool operator==( FillStyle const& aOther ) const {
        return aOther._fillColor == _fillColor;
      }

      void fillColor( Color const & aColor ) {
        _fillColor = aColor;
      }

      Color const& fillColor( ) const {
        return _fillColor;
      }

      Color& fillColor( ) {
        return _fillColor;
      }
    };

    class RoundedEdgeAttrib {
    public:
      typedef ::blib::geometry::CoordinateType CoordinateType;

    private:
      CoordinateType _rx;
      CoordinateType _ry;

    public:
      RoundedEdgeAttrib( ) :
        _rx( 0 ),
        _ry( 0 ) {}

      RoundedEdgeAttrib( RoundedEdgeAttrib const& aOther ) :
        _rx( aOther._rx ),
        _ry( aOther._ry ) {

      }

      RoundedEdgeAttrib& operator=( RoundedEdgeAttrib const& aOther ) {
        _rx = aOther._rx;
        _ry = aOther._ry;
      }

      bool operator==( RoundedEdgeAttrib const& aOther ) const {
        bool ret = false;
        if ( aOther._rx == _rx &&
             aOther._ry == _ry ) {
          ret = true;
        }
        return ret;
      }

      void rx( const CoordinateType aRx ) {
        _rx = aRx;
      }

      CoordinateType rx( ) const {
        return _rx;
      }

      CoordinateType& rx( ) {
        return _rx;
      }

      void ry( const CoordinateType aRy ) {
        _ry = aRy;
      }

      CoordinateType ry( ) const {
        return _ry;
      }

      CoordinateType& ry( ) {
        return _ry;
      }
    };

    class Group {
    public:
      typedef std::string IdType;

    private:
      IdType _id;

    public:
      Group( IdType const & aId ) : _id( aId ) {}

      Group( Group const& aOther ) {
        _id = aOther._id;
      }

      ~Group( ) {}

      void id( IdType const& aId ) {
        _id = aId;
      }

      IdType& id( ) {
        return _id;
      }

      IdType const& id( ) const {
        return _id;
      }

      bool operator==( Group const& aOther ) const {
        return aOther._id == _id;
      }

      Group& operator=( Group const& aOther ) {
        _id = aOther._id;
        return *this;
      }
    };

    class Id {
    public:
      typedef std::string IdType;

    private:
      IdType _id;

    public:
      Id( IdType const & aId ) : _id( aId ) {}

      Id( Id const& aOther ) {
        _id = aOther._id;
      }

      ~Id( ) {}

      void id( IdType const& aId ) {
        _id = aId;
      }

      IdType& id( ) {
        return _id;
      }

      IdType const& id( ) const {
        return _id;
      }

      bool operator==( Id const& aOther ) const {
        return aOther._id == _id;
      }

      Id& operator=( Id const& aOther ) {
        _id = aOther._id;
        return *this;
      }
    };
  }
}

#endif // BLIB_ATTRIBUTES_HPP
