#ifndef BLIB_LOG_HPP
#define BLIB_LOG_HPP

#include <log/spdlog/spdlog.h>

namespace blib {
  namespace utils {
    namespace log {
      class Log {
      public:
        Log( const std::string& aFileName = "Log.log" );
        std::shared_ptr<spdlog::logger> logger( );

      private:
        std::shared_ptr<spdlog::logger> _logger;
      };
    }
  }
}

#define info() logger( )->info()

#endif // BLIB_LOG_HPP
