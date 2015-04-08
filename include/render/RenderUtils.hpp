#ifndef BLIB_RENDERUTILS_HPP
#define BLIB_RENDERUTILS_HPP

#include <cstdint>
#include <string>
#include <boost/algorithm/hex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace blib {
  namespace render {
    enum class GeometryTypesEnum : ::std::uint8_t {
      kMultiPoint = 0,
      kLineString,
      kMultiLineString,
      kPolygon,
      kMultiPolygon,
      kBox,
      kRing,
      kSegment,
      kReferringSegment,
      kCircle,
      kEllipse,
      kUndefined
    };

    inline GeometryTypesEnum stringToGeometryTypesEnum( ::std::string const & aName ) {
      GeometryTypesEnum ret = GeometryTypesEnum::kUndefined;

      if ( aName == "rect" ) {
        ret = GeometryTypesEnum::kBox;
      }
      else if ( aName == "circle" ) {
        ret = GeometryTypesEnum::kCircle;
      }
      else if ( aName == "line" ) {
        ret = GeometryTypesEnum::kLineString;
      }
      else if ( aName == "polyline" ) {
        ret = GeometryTypesEnum::kLineString;
      }
      else if ( aName == "polygon" ) {
        ret = GeometryTypesEnum::kPolygon;
      }
      else if ( aName == "ellipse" ) {
        ret = GeometryTypesEnum::kEllipse;
      }

      return ret;
    }

    inline ::std::string colorNameToHex( ::std::string& aColor ) {
      ::std::string ret;
      boost::trim( aColor );
      boost::to_lower( aColor );

      // names got from http://www.w3schools.com/cssref/css_colornames.asp

      return ret;
    }

    inline Color stringToColor( ::std::string& aColor ) {
      std::string hexVal = aColor;
      auto itr = aColor.begin( );

      if ( *itr != '#' ) {
        hexVal = colorNameToHex( aColor );
        itr = hexVal.begin( );
      }

      Color rgba;

      ::std::string rs;
      ::boost::algorithm::unhex( ++itr, ++itr, ::std::back_inserter( rs ) );
      rgba._r = ::boost::lexical_cast< decltype( Color::_r ) >( rs );

      ::std::string gs;
      ::boost::algorithm::unhex( ++itr, ++itr, ::std::back_inserter( gs ) );
      rgba._g = ::boost::lexical_cast< decltype( Color::_g ) >( gs );

      ::std::string bs;
      ::boost::algorithm::unhex( ++itr, ++itr, ::std::back_inserter( bs ) );
      rgba._b = ::boost::lexical_cast< decltype( Color::_b ) >( bs );

      if ( aColor.size( ) == 9 ) {
        ::std::string as;
        ::boost::algorithm::unhex( ++itr, ++itr, ::std::back_inserter( as ) );
        rgba._a = ::boost::lexical_cast< decltype( Color::_a ) >( as );
      }

      return rgba;
    }
  }
}

#endif // BLIB_RENDERUTILS_HPP
