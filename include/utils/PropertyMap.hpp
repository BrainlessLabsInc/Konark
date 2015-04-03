#ifndef BLIB_PROPERTYMAP_HPP
#define BLIB_PROPERTYMAP_HPP

#include <map>
#include <string>
#include <boost/property_map/property_map.hpp>

namespace blib {
  namespace utils {
    typedef boost::associative_property_map< std::map<std::string, std::string> >  PropertyMap;
  }
}

#endif // BLIB_PROPERTYMAP_HPP
