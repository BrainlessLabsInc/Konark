#ifndef BLIB_MATHUTILS_HPP
#define BLIB_MATHUTILS_HPP

#include <boost/math/constants/constants.hpp>

namespace blib {
  namespace utils {
    namespace math {
      inline float toRadian( const float aDegree ) {
        return aDegree * ::boost::math::float_constants::degree;
      }

      inline float toDegree( const float aRadian ) {
        return aRadian * ::boost::math::float_constants::radian;
      }
    }
  }
}


#endif //BLIB_MATHUTILS_HPP
