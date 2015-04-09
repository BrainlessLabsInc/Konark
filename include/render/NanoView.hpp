#ifndef BLIB_NANOVIEW_HPP
#define BLIB_NANOVIEW_HPP

#include "View.hpp"
#include "sdl.hpp"
#include "Nanovg.hpp"
#include "RenderNode.hpp"
#include <boost/variant.hpp>
#include <memory>

namespace blib {
  namespace render {
    namespace nanovg {
      class NanoRender {
      private:
        NanoVG _vg;

      public:
        NanoRender( ) {
          _vg.init( );
        }

        ~NanoRender( ) {}
      };

      typedef std::shared_ptr<NanoVG> VgPtrType;
      typedef std::shared_ptr<bgeom::TransformMatrix> TransformMatrixPtr;

      class MultiGeometryVisitor : public boost::static_visitor < > {
      private:
        TransformMatrixPtr _curTransMatPtr;
        VgPtrType _vg;

      private:
        void drawPoint( bgeom::Point2D& aPoint ) {
          bgeom::Circle circle;
          auto& center = circle.center( );
          center.x( aPoint.x( ) );
          center.y( aPoint.y( ) );
          circle.radius( 0.1 );
          transformPoint( center );
          _vg->circle( circle );
        }

        void drawLineString( bgeom::LineString& aLineString ) {
          bool first = true;
          for ( auto p : aLineString ) {
            transformPoint( p );
            _vg->moveTo( p );
            if ( first ) {
              first = false;
            }
            else {
              _vg->lineTo( p );
            }
          }
        }

        void drawRing( bgeom::Ring& aRing ) {
          bool first = false;
          bgeom::Point2D firstPoint;
          for ( auto& p : aRing ) {
            transformPoint( p );
            _vg->moveTo( p );
            if ( first ) {
              first = false;
              firstPoint = p;
            }
            else {
              _vg->lineTo( p );
            }
          }
          _vg->moveTo( firstPoint );
          _vg->lineTo( firstPoint );
        }

        void drawPolygon( bgeom::Polygon& aPolygon ) {
          drawRing( aPolygon.outer( ) );
          for ( auto& innerRing : aPolygon.inners( ) ) {
            drawRing( innerRing );
          }
        }

        bgeom::Point2D& transformPoint( bgeom::Point2D& aPoint ) {
          if ( _curTransMatPtr ) {
            aPoint.apply( *_curTransMatPtr );
          }
          return aPoint;
        }

      public:
        void init( VgPtrType& aPtr ) {
          vg( aPtr );
        }

        VgPtrType vg( ) const {
          return _vg;
        }

        void vg( VgPtrType& aPtr ) {
          _vg = aPtr;
        }

        void curTransMat( TransformMatrixPtr& aMat ) {
          _curTransMatPtr = aMat;
        }

        TransformMatrixPtr curTransMat( ) const {
          return _curTransMatPtr;
        }

        void operator()( bgeom::Point2D& aPoint ) {
          drawPoint( aPoint );
        }

        void operator()( bgeom::MultiPoint& aMultiPoint ) {
          for ( auto& p : aMultiPoint ) {
            drawPoint( p );
          }
        }

        void operator()( bgeom::LineString& aLineString ) {
          drawLineString( aLineString );
        }

        void operator()( bgeom::MultiLineString& aMultiLineString ) {
          for ( auto lineString : aMultiLineString ) {
            drawLineString( lineString );
          }
        }

        void operator()( bgeom::Polygon& aPolygon ) {
          drawPolygon( aPolygon );
        }

        void operator()( bgeom::MultiPolygon& aMultiPolygon ) {
          for ( auto& polygon : aMultiPolygon ) {
            drawPolygon( polygon );
          }
        }

        void operator()( bgeom::Box& aBox ) {
          _vg->rect( aBox );
        }

        void operator()( bgeom::Ring& aRing ) {
          drawRing( aRing );
        }

        void operator()( bgeom::Segment& aSegment ) {
          // TODO
        }

        void operator()( bgeom::ReferringSegment& aReferringSegment ) {
          // TODO
        }

        void operator()( bgeom::Ellipse& aEllipse ) {
          auto& center = aEllipse.center( );
          transformPoint( center );
          _vg->ellipse( aEllipse );
        }

        void operator()( bgeom::Circle& aCircle ) {
          auto& center = aCircle.center( );
          transformPoint( center );
          _vg->circle( aCircle );
        }
      };

      class RenderAttributeVisitor : public boost::static_visitor < > {
      private:
        VgPtrType _vg;

      public:
        ~RenderAttributeVisitor( ) {}

        void init( VgPtrType& aPtr ) {
          vg( aPtr );
        }

        VgPtrType vg( ) const {
          return _vg;
        }

        void vg( VgPtrType& aPtr ) {
          _vg = aPtr;
        }

        void operator()( StrokeWidth& aAttr ) {
          _vg->strokeWidth( aAttr );
        }

        void operator()( LineCapStyle& aAttr ) {
          _vg->lineCapStyle( aAttr );
        }

        void operator()( LineJoinStyles& aAttr ) {
          _vg->lineJoinStyle( aAttr );
        }

        void operator()( MitterLimit& aAttr ) {
          _vg->mitterLimit( aAttr );
        }

        void operator()( StrokeStyle& aAttr ) {
          _vg->strokeStyle( aAttr );
        }

        void operator()( FillStyle& aAttr ) {
          _vg->fillStyle( aAttr );
        }

        void operator()( RoundedEdgeAttrib& aAttr ) {
          // TODO
          l( ).info( "RoundedEdgeAttrib Not implemented" );
        }
      };

      class RenderNodeDataVisitor : public boost::static_visitor < > {
      private:
        VgPtrType _vg;
        RenderAttributeVisitor _renderNodeDataVisitor;
        MultiGeometryVisitor _multiGeomVisitor;
        TransformMatrixPtr _curTransMatPtr;

      public:
        void init( VgPtrType& aPtr ) {
          vg( aPtr );
          _renderNodeDataVisitor.init( vg( ) );
          _multiGeomVisitor.init( vg( ) );
          _curTransMatPtr = std::make_shared<bgeom::TransformMatrix>( );
        }

        VgPtrType vg( ) const {
          return _vg;
        }

        void vg( VgPtrType& aPtr ) {
          _vg = aPtr;
        }

        ~RenderNodeDataVisitor( ) {}

        void operator()( MultiGeometry& aGeom ) {}

        void operator()( RenderAttributes& aRenderAttribute ) {
          for ( auto re : aRenderAttribute ) {
            boost::apply_visitor( _renderNodeDataVisitor, re );
          }
        }

        void operator()( bgeom::TransformMatrix& aTransMat ) {
          *_curTransMatPtr = aTransMat;
          _multiGeomVisitor.curTransMat( _curTransMatPtr );
        }

        void operator()( Group& aGroup ) {
          // TODO
          // Dont know what to do yet
          l( ).info( "Not implemented {}", aGroup.id( ) );
        }
      };

      // View tag, this will be used to specialize the traits.
      // This is inorder used in the view class
      struct NanoViewTag {};
    }

    namespace traits {
      template<>
      struct render_type < blib::render::nanovg::NanoViewTag > {
        typedef ::blib::render::nanovg::NanoVG type;
      };

      template<>
      struct scene_manager < blib::render::nanovg::NanoViewTag > {

      };

      template<>
      struct display_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct display_value_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct render_element_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct event_type < blib::render::nanovg::NanoViewTag > {};
    } // namespace traits
  }
}

#endif // BLIB_NANOVIEW_HPP
