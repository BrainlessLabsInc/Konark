#ifndef BLIB_NANOVG_HPP
#define BLIB_NANOVG_HPP

#include "render/Attributes.hpp"
#include "geometry/BasicGeometries.hpp"
#include "log/Log.hpp"

#include <Windows.h>
#include <glew/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <SDL/SDL.h>
#include <nanovg/nanovg.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>
#include <nanovg/nanovg_gl_utils.h>

namespace blib {
  namespace render {
    namespace nanovg {
      namespace ren = ::blib::render;
      namespace bgeom = ::blib::geometry;

      class NanoVG {
      public:
        typedef ::boost::geometry::traits::coordinate_type< bgeom::Point2D >::type ValueType;
      private:
        NVGcontext *_vg;
        NVGLUframebuffer *_fb;
        ValueType _height, _width;
        ValueType _devicePixelRatio;

      public:
        NanoVG( ) :
          _vg( nullptr ),
          _fb( nullptr ),
          _height( 512 ),
          _width( 1024 ),
          _devicePixelRatio( 1.F ) {

        }

        bool init( const ValueType aHeight,
                   const ValueType aWidth,
                   const ValueType aDevicePixelRatio ) {
          _height = aHeight;
          _width = aWidth;
          _devicePixelRatio = aDevicePixelRatio;

          _vg = nvgCreateGL3( NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG );
          if ( nullptr == _vg ) {
            l( ).error( "Could not init nanovg.\n" );
            return false;
          }
          return true;
        }

        void beginDraw( ) {
          // Calculate pixel ration for hi-dpi devices.
          nvgBeginFrame( _vg, _width, _height, _devicePixelRatio );
        }

        void endDraw( ) {
          nvgEndFrame( _vg );
        }

        void clear( ) {

        }

        void strokeStyle( ren::StrokeStyle const& aStrokeStyle ) {
          NVGcolor color = { 0 };
          const auto& inColor = aStrokeStyle.strokeColor( );
          color.r = inColor._r;
          color.g = inColor._g;
          color.b = inColor._b;
          color.a = inColor._a;
          nvgStrokeColor( _vg, color );
        }

        void fillStyle( ren::FillStyle const& aFillStrokeStyle ) {
          NVGcolor color = { { 0 } };
          const auto& inColor = aFillStrokeStyle.fillColor( );
          color.r = inColor._r;
          color.g = inColor._g;
          color.b = inColor._b;
          color.a = inColor._a;
          nvgFillColor( _vg, color );
        }

        void mitterLimit( ren::MitterLimit const& aMitterLimit ) {
          nvgMiterLimit( _vg, aMitterLimit.mitterLimit( ) );
        }

        void lineJoinStyle( ren::LineJoinStyles const& aJoinStyle ) {
          int val = 0;
          switch ( aJoinStyle.lineJoin( ) ) {
          case ren::LineJoinStyles::LineJoinTypes::kRound:
            val = 1;
            break;
          case ren::LineJoinStyles::LineJoinTypes::kMiter:
            val = 2;
            break;
          }
          nvgLineJoin( _vg, val );
        }

        void lineCapStyle( ren::LineCapStyle const& aCapStyle ) {
          int val = 0;
          switch ( aCapStyle.lineCap( ) ) {
          case ren::LineCapStyle::LineCapTypes::kRound:
            val = 2;
            break;
          case ren::LineCapStyle::LineCapTypes::kSquare:
            val = 1;
            break;
          }
          nvgLineCap( _vg, val );
        }

        void strokeWidth( ren::StrokeWidth const& aWidth ) {
          nvgStrokeWidth( _vg, aWidth.strokeWidth( ) );
        }

        void beginPath( ) {
          nvgBeginPath( _vg );
        }

        // Starts new sub-path with specified point as first point.
        void moveTo( bgeom::Point2D const& aPoint ) {
          nvgMoveTo( _vg, aPoint.x( ), aPoint.y( ) );
        }

        // Adds line segment from the last point in the path to the specified point.
        void lineTo( bgeom::Point2D const& aPoint ) {
          nvgLineTo( _vg, aPoint.x( ), aPoint.y( ) );
        }

        // Creates new rectangle shaped sub-path.
        void rect( bgeom::Box const& aRect ) {
          const auto& min = aRect.min_corner( );
          const auto& max = aRect.max_corner( );
          nvgRect( _vg, min.x( ), min.y( ), max.x( ), max.y( ) );
        }
      };
    }
  }
}
#endif // BLIB_NANOVG_HPP
