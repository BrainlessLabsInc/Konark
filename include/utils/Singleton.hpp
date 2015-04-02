#ifndef BLIB_SINGLETON_HPP
#define BLIB_SINGLETON_HPP

#include <boost/noncopyable.hpp>
#include <memory>
#include <mutex>

namespace blib {
  namespace utils {
    template <class ThisClassType>
    class Singleton : private boost::noncopyable {
    public:
      typedef ThisClassType ThisClass;
      typedef Singleton<ThisClass> SelfType;
     
    public:
      static ThisClass* i( ) {
        if ( !_i ) {
          std::unique_lock<std::mutex> lock( m );
          if ( !_i ) {
            _i = std::make_unique<ThisClass>( );
          }
        }

        return _i;
      }
      static std::unique_ptr<ThisClass> _i;
    };

    template <class ThisClass> std::unique_ptr<ThisClass> Singleton<ThisClass>::_i = nullptr;
  }
}

#endif // BLIB_SINGLETON_HPP
