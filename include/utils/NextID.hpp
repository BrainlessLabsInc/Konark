#ifndef BLIB_NEXTID_HPP
#define BLIB_NEXTID_HPP

#include <cstdint>
#include <atomic>

namespace blib {
  namespace utils {

    template<typename ThisClass>
    class NextID {
    public:
      typedef std::uint_fast64_t IdType;
      typedef std::atomic_uint_fast64_t IdTypeAtomic;
      typedef NextID<ThisClass> SelfType;

      NextID( ) {
        _id.store( 0 );
      }

      IdType next( ) {
        return ++_id;
      }

    private:
      IdTypeAtomic _id;
    };
  }
}

#endif //BLIB_NEXTID_HPP
