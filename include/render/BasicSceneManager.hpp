#ifndef BLIB_BASICSCENEMANAGER_HPP
#define BLIB_BASICSCENEMANAGER_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_char_.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include "containers/tree/NTree.hpp"
#include "RenderNode.hpp"
#include "RenderUtils.hpp"
#include "xml/pugixml.hpp"
#include "log/Log.hpp"

namespace blib {
  namespace render {
    namespace _private {
      typedef ::blib::container::tree::Node<blib::render::RenderNodeData> Node;
      typedef ::blib::container::tree::NTree<Node> Tree;

      // Class reads svg files and builds the tree nodes
      class SVGReader {
      public:
        SVGReader( ) {}
        ~SVGReader( ) {}
        Node createGroupNode( const std::string& aFileName ) {
          ::pugi::xml_document doc;
          ::pugi::xml_parse_result result = doc.load_file( aFileName.c_str( ) );

          Node ret;
          if ( result ) {
            const blib::render::Group group( aFileName );
            ret.data( group );

            for ( auto g : doc.children( "g" ) ) {
              for ( auto shape : g.children( ) ) {
                const auto shapeNode = createShapeNode( shape );
                if ( shapeNode ) {
                  ret.addChild( shapeNode );
                }
              }
            }
          }
          else {
            //std::cout << "SVG [" << aFileName << "] parsed with errors" << "\n";
            //std::cout << "Error description: " << result.description( ) << "\n";
            //std::cout << "Error offset: " << result.offset << std::endl;
            l( ).error( "SVG Parser Error" );
          }

          return ret;
        }
      private:
        // Create a complete shape node
        Node createShapeNode( ::pugi::xml_node const& aShapeSVGNode ) {

          const auto geomType = stringToGeometryTypesEnum( aShapeSVGNode.name( ) );
          Node geomNode;
          switch ( geomType ) {
          case GeometryTypesEnum::kBox:
            geomNode = createBoxNode( aShapeSVGNode );
            break;
          case GeometryTypesEnum::kCircle:
            geomNode = createCircleNode( aShapeSVGNode );
            break;
          case GeometryTypesEnum::kLineString:
            break;
          case GeometryTypesEnum::kPolygon:
            geomNode = createPolygonNode( aShapeSVGNode );
            break;
          case GeometryTypesEnum::kEllipse:
            geomNode = createEllipseNode( aShapeSVGNode );
            break;
          }

          auto attribNode = createAttributeNode( aShapeSVGNode );

          Node ret;
          if ( attribNode ) {
            attribNode.addChild( geomNode );
            ret = attribNode;
          }
          else {
            ret = geomNode;
          }

          return ret;
        }

        // Create a Box node
        Node createBoxNode( ::pugi::xml_node const& aShapeSVGNode ) {
          bgeom::Point2D maxCorner, minCorner;
          for ( auto const& attr : aShapeSVGNode.attributes( ) ) {
            const std::string attrName = attr.name( );
            if ( attrName == "x" ) {
              minCorner.x( attr.as_float( ) );
            }
            else if ( attrName == "y" ) {
              minCorner.y( attr.as_float( ) );
            }
            else if ( attrName == "height" ) {
              maxCorner.y( attr.as_float( ) );
            }
            else if ( attrName == "width" ) {
              maxCorner.x( attr.as_float( ) );
            }
          }

          maxCorner.x( maxCorner.x( ) + minCorner.x( ) );
          maxCorner.y( maxCorner.y( ) + minCorner.y( ) );

          bgeom::Box box;
          box.min_corner( ) = minCorner;
          box.max_corner( ) = maxCorner;

          const MultiGeometry geom = box;

          Node ret;
          ret.data( geom );

          return ret;
        }

        // Create a circle node
        Node createCircleNode( ::pugi::xml_node const& aShapeSVGNode ) {
          bgeom::Circle circle;

          for ( auto const& attr : aShapeSVGNode.attributes( ) ) {
            const std::string attrName = attr.name( );
            if ( "cx" == attrName ) {
              circle.center( ).x( attr.as_float( ) );
            }
            else if ( "cy" == attrName ) {
              circle.center( ).y( attr.as_float( ) );
            }
            else if ( "r" == attrName ) {
              circle.radius( attr.as_float( ) );
            }
          }

          const MultiGeometry geom = circle;

          Node ret;
          ret.data( geom );

          return ret;
        }

        // Create polygon node
        Node createPolygonNode( ::pugi::xml_node const& aShapeSVGNode ) {
          bgeom::Polygon polygon;

          for ( auto const& attr : aShapeSVGNode.attributes( ) ) {
            const std::string attrName = attr.name( );
            if ( "points" == attrName ) {
              const std::string pointString = attr.value( );
              const auto points = parsePoints( pointString );
              for ( auto const& point : points ) {
                polygon.outer( ).push_back( point );
              }
            }
          }

          const MultiGeometry geom = polygon;
          Node ret;
          ret.data( geom );

          return ret;
        }

        // Create Ellipse node
        Node createEllipseNode( ::pugi::xml_node const& aShapeSVGNode ) {
          bgeom::Ellipse ellipse;

          for ( auto const& attr : aShapeSVGNode.attributes( ) ) {
            const std::string attrName = attr.name( );
            if ( "cx" == attrName ) {
              ellipse.center( ).x( attr.as_float( ) );
            }
            else if ( "cy" == attrName ) {
              ellipse.center( ).y( attr.as_float( ) );
            }
            else if ( "rx" == attrName ) {
              ellipse.width( attr.as_float( ) );
            }
            else if ( "ry" == attrName ) {
              ellipse.height( attr.as_float( ) );
            }
          }

          const MultiGeometry geom = ellipse;

          Node ret;
          ret.data( geom );

          return ret;
        }

        // Create Attribute Node
        Node createAttributeNode( ::pugi::xml_node const& aShapeSVGNode ) {
          RenderAttributes renderAttributes;
          RoundedEdgeAttrib roundEdgeAttrib;

          bool hasrxry = false;

          for ( auto const& attr : aShapeSVGNode.attributes( ) ) {
            const std::string attrName = attr.name( );
            if ( attrName == "stroke-width" ) {
              StrokeWidth strokeWidth;
              strokeWidth.strokeWidth( attr.as_float( ) );
              renderAttributes.push_back( strokeWidth );
            }
            else if ( attrName == "rx" ) {
              roundEdgeAttrib.rx( attr.as_float( ) );
              hasrxry = true;
            }
            else if ( attrName == "ry" ) {
              roundEdgeAttrib.ry( attr.as_float( ) );
              hasrxry = true;
            }
            else if ( attrName == "stroke" ) {
              std::string color = attr.value( );
              StrokeStyle strokeAttrib;
              const auto stroke = blib::render::stringToColor( color );
              strokeAttrib.strokeColor( stroke );
              renderAttributes.push_back( strokeAttrib );
            }
            else if ( attrName == "fill" ) {
              std::string color = attr.value( );
              FillStyle fillStyleAttrib;
              fillStyleAttrib.fillColor( blib::render::stringToColor( color ) );
              renderAttributes.push_back( fillStyleAttrib );
            }
          }

          if ( hasrxry ) {
            renderAttributes.push_back( roundEdgeAttrib );
          }

          Node ret;
          ret.data( renderAttributes );

          return ret;
        }

        // This will parse points like 200,10 250,190 160,210
        std::vector<bgeom::Point2D> parsePoints( std::string const& aPointString ) {
          using namespace boost::spirit;
          using namespace boost::spirit::qi;
          using qi::phrase_parse;

          ::std::vector<bgeom::Point2D> retVal;
          bgeom::Point2D point;
          auto it = aPointString.begin( );
          typedef ::boost::geometry::traits::coordinate_type< ::blib::geometry::Point2D >::type PointValueType;
          // To capture a single point like 23
          const auto for1 = [ &point ]
            ( const PointValueType aVal ) {
            point.x( aVal );
          };
          // Capture something like 23,24,..
          const auto forMore = [ &point, &retVal ]
            ( const PointValueType aVal ) {
            point.y( aVal );
            retVal.push_back( point );
          };

          const bool r = qi::phrase_parse( it,
                                           aPointString.end( ),
                                           // Begin Grammar
                                           (
                                           *( // Repeat this grammar
                                           float_[ for1 ]
                                           >> char_( ',' )
                                           >> float_[ forMore ]
                                           )
                                           ),
                                           // End Grammar
                                           space );
          if ( !r ) {
            // Do something. We did not get a full match
            l( ).alert( "We did not get a full match" );
          }

          return retVal;
        }
      };

      // Iterator for the scene manager
      template<typename _BasicSceneManager>
      class basic_scene_iterator :
        public boost::iterator_facade < basic_scene_iterator<_BasicSceneManager>, typename _BasicSceneManager::RenderData, boost::forward_traversal_tag > {
      private:
        typedef _BasicSceneManager BasicSceneManager;
        typedef typename BasicSceneManager::RenderData RenderData;
        typedef typename BasicSceneManager::Tree Tree;
        typedef typename Tree::pre_order_iterator pre_order_iterator;
        friend class boost::iterator_core_access;

      public:
        typedef basic_scene_iterator<BasicSceneManager> SelfType;

      private:
        Tree _t;
        pre_order_iterator _it;

      public:
        basic_scene_iterator( ) {}

        basic_scene_iterator( basic_scene_iterator const& aOther ) :
          _t( aOther._t ),
          _it( aOther._it ) {

        }

        basic_scene_iterator( Tree& aTree ) :
          _t( aTree ) {
          _it = aTree.pre_order_begin( );
        }

        SelfType& operator = ( SelfType const& aOther ) {
          _t = aOther._t;
          _it = aOther._it;
        }

      private:
        void increment( ) {
          ++_it;
        }

        bool equal( SelfType const& aOther ) const {
          return _it == aOther._it;
        }

        RenderData& dereference( ) const {
          return _it->data( );
        }
      };
    } // _private

    // Basic scene manager. Just a flat tree
    class BasicSceneManager {
    public:
      typedef _private::Node Node;
      typedef _private::Tree Tree;
      typedef _private::SVGReader SVGReader;
      typedef _private::basic_scene_iterator<BasicSceneManager> basic_scene_iterator;
      typedef RenderNodeData RenderData;

    private:
      Tree _t;
      SVGReader svgReader;

    public:
      BasicSceneManager( ) {
        const Group g( "BasicSceneManager" );
        _t.root( g );
      }

      void addModel( std::string const& aFileName ) {
       const auto node = svgReader.createGroupNode( aFileName );
        _t.root( ).addChild( node );
      }

      basic_scene_iterator begin( ) {
        return basic_scene_begin( );
      }

      basic_scene_iterator end( ) {
        return basic_scene_end( );
      }

      basic_scene_iterator basic_scene_begin( ) {
        const basic_scene_iterator ret( _t );
        return ret;
      }

      basic_scene_iterator basic_scene_end( ) {
        const basic_scene_iterator ret;
        return ret;
      }
    };
  }
}

#endif // BLIB_BASICSCENEMANAGER_HPP
