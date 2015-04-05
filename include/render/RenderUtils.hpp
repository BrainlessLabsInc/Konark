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
  }
}

#endif // BLIB_RENDERUTILS_HPP
