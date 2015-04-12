#ifndef BLIB_SDL_HPP
#define BLIB_SDL_HPP

#include <glew/glew.h>
#include <SDL/SDL.h>
#include "log/Log.hpp"
#include <memory>

namespace blib {
  namespace render {
    namespace sdl {
      class Event {
      public:
        typedef SDL_Event EventType;
        typedef std::shared_ptr<EventType> EventTypePtr;

      private:
        EventTypePtr _event;

      public:
        Event( ) {
          _event = std::make_shared<SDL_Event>( );
        }

        Event( Event const& aOther ) {
          _event = aOther._event;
        }

        Event& operator=( Event const& aOther ) {
          _event = aOther._event;
          return *this;
        }

        ~Event( ) {

        }

        bool operator==( Event const& aOther ) {
          return aOther._event == _event;
        }

        EventType& event( ) {
          return *_event;
        }

        EventTypePtr& eventPtr( ) {
          return _event;
        }
      };

      class SDL {
      public:
        typedef float ValueType;

      private:
        ValueType _height, _width;
        ValueType _devicePixelRatio;
        SDL_GLContext _maincontext;
        SDL_Surface* _surfDisplay;
        SDL_Window* _window;

      public:
        SDL( ) :
          _surfDisplay( nullptr ),
          _window( nullptr ),
          _height( 512 ),
          _width( 1024 ),
          _maincontext( nullptr ),
          _devicePixelRatio( 1.F ) {}

        bool init( const ValueType aHeight,
                   const ValueType aWidth,
                   const ValueType aDevicePixelRatio ) {
          _height = aHeight;
          _width = aWidth;
          _devicePixelRatio = aDevicePixelRatio;

          if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
            l( ).error( "Could not init SDL" );
            return false;
          }
          // Declare display mode structure to be filled in.
          SDL_DisplayMode current = { { 0 } };

          if ( 0 == SDL_GetCurrentDisplayMode( 0, &current ) ) {
            _width = static_cast< ValueType >( current.w );
            _height = static_cast< ValueType >( current.h );
          }

          SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
          SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
          //SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG ); // May be a performance booster in *nix?
          SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
          SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
          /* Turn on double buffering with a 24bit Z buffer.
          * You may need to change this to 16 or 32 for your system */
          SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
          SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
          // Create our window centered at 512x512 resolution
          _window = SDL_CreateWindow( "Konark",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      static_cast< int >( _width ),
                                      static_cast< int >( _height ),
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
          if ( !_window ) {
            l( ).error( "Could not create window" );
            cleanup( );
            return false;
          }
          // Create our opengl context and attach it to our window
          _maincontext = SDL_GL_CreateContext( _window );
          if ( !_maincontext ) {
            cleanup( );
            l( ).error( "Could not create context" );
            return false;
          }
          glewExperimental = GL_TRUE;
          if ( glewInit( ) != GLEW_OK ) {
            l( ).error( "Could not init glew." );
            return false;
          }
          // GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
          glGetError( );
          /* This makes our buffer swap syncronized with the monitor's vertical refresh */
          SDL_GL_SetSwapInterval( 1 );

          return true;
        }

        void cleanup( ) {
          /* Delete our opengl context, destroy our window, and shutdown SDL */
          if ( _maincontext ) {
            SDL_GL_DeleteContext( _maincontext );
          }

          if ( _window ) {
            SDL_DestroyWindow( _window );
          }

          SDL_Quit( );
        }

        void clear( ) {
          // Update and render
          glClearColor( 1.F, 1.F, 1.F, 1.F );
          glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
        }

        void beginDraw( ) {
          clear( );
        }

        bool loop( ) {
          //SDL_Event Event = { 0 };

          //while ( _running ) {
          //  while ( SDL_PollEvent( &Event ) ) {
          //    OnEvent( &Event );
          //  }

          //  OnLoop( );
          //  OnRender( );
          //}

          //return 0;
        }

        void endDraw( ) {
          /* Swap our back buffer to the front */
          SDL_GL_SwapWindow( _window );
        }

        Event pollEvent( ) {
          Event ret;
          auto& event = ret.eventPtr( );
          SDL_PollEvent( event.get( ) );
          return ret;
        }
      };
    }
  }
}


#endif // BLIB_SDL_HPP
