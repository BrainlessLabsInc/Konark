#ifndef BLIB_SINGLETON_HPP
#define BLIB_SINGLETON_HPP

#include <boost/noncopyable.hpp>
#include <memory>
//#include <mutex>

// TO-DO
// Use following
// http://enki-tech.blogspot.in/2012/08/c11-generic-singleton.html
// http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
// https://www10.informatik.uni-erlangen.de/Teaching/Courses/SS2010/CPP/sembritzki.pdf

namespace blib {
  namespace utils {
    template <class ThisClassType>
    class Singleton : private boost::noncopyable {
    public:
      typedef ThisClassType ThisClass;
      typedef Singleton<ThisClass> SelfType;
     
    public:
      static ThisClass& i( ) {
        if ( !_i ) {
 //         std::unique_lock<std::mutex> lock( m );
          if ( !_i ) {
            _i = std::make_unique<ThisClass>( );
          }
        }

        return *_i;
      }
      static std::unique_ptr<ThisClass> _i;
    };

    template <class ThisClass> std::unique_ptr<ThisClass> Singleton<ThisClass>::_i = nullptr;
  }
}

#endif // BLIB_SINGLETON_HPP
