#ifndef BLIB_VIEW_HPP
#define BLIB_VIEW_HPP

namespace blib {
  namespace render {
    namespace traits {
      template<typename ViewTag>
      struct render_type;

      template<typename ViewTag>
      struct scene_manager;

      template<typename ViewTag>
      struct display_type;

      template<typename ViewTag>
      struct display_value_type;

      template<typename ViewTag>
      struct render_element_type;

      template<typename ViewTag>
      struct event_type;
    } // namespace traits

    // Trying to model as per Notus
    // http://notus.sourceforge.net/notusguide.pdf
    template<typename _ViewTag>
    class View {
    public:
      typedef _ViewTag ViewTag;
      // display surface
      typedef typename traits::display_type<ViewTag>::type Display;
      // The drawing APIs
      typedef typename traits::render_type<ViewTag>::type Renderer;
      // Scene manager
      typedef typename traits::scene_manager<ViewTag>::type SceneManager;
      //typedef std::vector<SceneManager> SceneManager;
      typedef typename traits::render_element_type<ViewTag>::type RenderElementType;
      typedef typename traits::event_type<ViewTag>::type EventType;
      // Value type for display
      typedef typename traits::display_value_type<ViewTag>::type ValueType;

    private:
      ValueType _height, _width;
      ValueType _devicePixelRatio;
      Display _d;
      Renderer _r;
      SceneManager _s;
      bool _running;

    public:
      View( ) :
        _height( 512 ),
        _width( 1024 ),
        _devicePixelRatio( 1 ),
        _running( false ) {
        init( );
      }

      ~View( ) {
        cleanup( );
      }

      bool init( ) {
        if ( _d.init( _height, _width, _devicePixelRatio ) ) {
          return _r.init( _height, _width, _devicePixelRatio );
        }
        return false;
      }

      void cleanup( ) {
        _r.cleanup( );
        _d.cleanup( );
      }

      void clear( ) {
        _d.clear( );
      }

      void beginDraw( ) {
        _d.beginDraw( );
        _r.beginDraw( );
      }

      void endDraw( ) {
        _d.endDraw( );
        _r.endDraw( );
      }

      void loop( ) {
        EventType e = _d.pollEvent( );
        while ( s.next( e ) ) {
          clear( );
          beginDraw( );
          for ( const RenderElementType re : _s.renderElements( ) ) {
            _r.apply( re );
          }
          endDraw( );
          e = _d.pollEvent( );
        }
      }
    };
  }
}

#endif // BLIB_VIEW_HPP
