#ifndef BLIB_LOG_HPP
#define BLIB_LOG_HPP

#include <log/spdlog/spdlog.h>
#include "utils/PropertyMap.hpp"
#include "utils/Singleton.hpp"

namespace blib {
  namespace utils {
    namespace log {
      class Log : public blib::utils::Singleton < Log > {
        friend class Singleton < Log >;

      private:
        typedef std::shared_ptr<spdlog::logger> LoggerPtr;
        LoggerPtr _logger;

      public:
        void setLogPreference( const blib::utils::PropertyMap& aPreference ) {
          namespace spd = spdlog;
          const size_t q_size = 1048576; //queue size must be power of 2
          spd::set_async_mode( q_size );
          spd::set_level( spd::level::info ); //Set global log level to info
          spd::set_pattern( "*** [%H:%M:%S %z] [thread %t] %v ***" );
          // Create a file rotating logger with 5mb size max and 3 rotated files
          _logger = spd::rotating_logger_mt( "KonarkLogger", "Konark.log", 1048576 * 5, 3 );
        }

        LoggerPtr::element_type& logger( ) const {
          return *_logger;
        }

      };
    }
  }
}

#define l() blib::utils::log::Log::i().logger()

#endif // BLIB_LOG_HPP
