#ifndef BLIB_BASICSCENEMANAGER_HPP
#define BLIB_BASICSCENEMANAGER_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_char_.hpp>
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
            for ( auto shape : doc.children( "g" ) ) {
              const auto node = createShapeNode( shape );
              if ( node ) {
                const blib::render::Group group( "test" );
                ret.data( group );
                ret.addChild( node );
              }

              //_private::SceneGraphNodeDataTypesPtr g( new SceneGraphNodeDataTypes );
              //::std::shared_ptr<ModelGroupId> grpId( new ModelGroupId );
              //*g = grpId;
              //ret.insert( g );
              //ret.push_back( node );
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
        // Create a shape node
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
          if ( !attribNode ) {
            attribNode.data( geomNode );
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
              strokeAttrib.strokeColor( blib::render::stringToColor( color ) );
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
          ret.addChild( renderAttributes );

          return ret;
        }

        // This will parse points like 200,10 250,190 160,210
        ::std::vector<bgeom::Point2D> parsePoints( std::string const& aPointString ) {
          using namespace boost::spirit;
          using namespace boost::spirit::qi;
          using qi::phrase_parse;

          ::std::vector<bgeom::Point2D> retVal;
          bgeom::Point2D point;
          auto it = aPointString.begin( );
          typedef ::boost::geometry::traits::coordinate_type< ::blib::geometry::Point2D >::type PointValueType;
          const bool r = qi::phrase_parse( it,
                                           aPointString.end( ),
                                           // Begin Grammar
                                           (
                                           *( // Repeat this grammar
                                           float_[ ( [ &point ]( const PointValueType aVal ) {point.x( aVal ); } ) ]
                                           >> char_( ',' )
                                           >> float_[ ( [ &point, &retVal ]( const PointValueType aVal ) {point.y( aVal ); retVal.push_back( point ); } ) ]
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
    } // _private

    // Basic scene manager. Just a flat tree
    class BasicSceneManager {
    private:
      typedef _private::Node Node;
      typedef _private::Tree Tree;

    private:
      Tree _t;
      _private::SVGReader svgReader;
    private:

    public:
      BasicSceneManager( ) {
        const Group g( "BasicSceneManager" );
        _t.root( g );
      }

      void addModel( std::string const& aFileName ) {
        const auto node = svgReader.createGroupNode( aFileName );
        _t.root( ).addChild( node );
      }
    };
  }
}

#endif // BLIB_BASICSCENEMANAGER_HPP
