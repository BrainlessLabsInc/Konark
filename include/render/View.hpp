#ifndef BLIB_VIEW_HPP
#define BLIB_VIEW_HPP

namespace blib {
  namespace render {

    // Trying to model as per Notus
    // http://notus.sourceforge.net/notusguide.pdf
    template<
      // display
      typename DisplayType,
      // The drawing APIs
      typename RendererType,
      // Scene manager
      typename template<typename Renderer> class SceneManagerType
    >
    class View {
    public:
      typedef DisplayType Display;
      typedef RendererType Renderer;
      typedef SceneManagerType<Renderer> SceneManager;
      typedef typename DisplayType::ValueType ValueType;

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
        init( )
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
    };
  }
}

#endif // BLIB_VIEW_HPP
