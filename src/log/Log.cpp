#include <iostream>
#include "log/Log.hpp"

namespace blib {
  namespace utils {
    namespace log {
      namespace spd = spdlog;
      Log::Log( const std::string& aFileName ) {
        try {
          //
          // Asynchronous logging is very fast..
          // Just call spdlog::set_async_mode(q_size) and all created loggers from now on will be asynchronous..
          //
          const size_t q_size = 1048576; //queue size must be power of 2
          spd::set_async_mode( q_size );
          spd::set_level( spd::level::info ); //Set global log level to info
          spd::set_pattern( "*** [%H:%M:%S %z] [thread %t] %v ***" );
          _logger = spd::rotating_logger_mt( "rotating_file_logger_mt", aFileName, 1048576 * 5, 3 );
        }
        catch ( const spd::spdlog_ex& ex ) {
          std::cout << "Log failed: " << ex.what( ) << std::endl;
        }
      }

      std::shared_ptr<spdlog::logger> Log::logger( ) {
        return _logger;
      }
    }
  }
}
