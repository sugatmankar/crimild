#ifndef CRIMILD_COLLADA_UTILS_
#define CRIMILD_COLLADA_UTILS_

#define COLLADA_ACCESSOR "accessor"
#define COLLADA_ANIMATION "animation"
#define COLLADA_BIND_MATERIAL "bind_material"
#define COLLADA_CHANNEL "channel"
#define COLLADA_COLOR "color"
#define COLLADA_COUNT "count"
#define COLLADA_CONTROLLER "controller"
#define COLLADA_DIFFUSE "diffuse"
#define COLLADA_FLOAT_ARRAY "float_array"
#define COLLADA_GEOMETRY "geometry"
#define COLLADA_ID "id"
#define COLLADA_INPUT "input"
#define COLLADA_INSTANCE_EFFECT "instance_effect"
#define COLLADA_INSTANCE_CONTROLLER "instance_controller"
#define COLLADA_INSTANCE_GEOMETRY "instance_geometry"
#define COLLADA_INSTANCE_MATERIAL "instance_material"
#define COLLADA_LIBRARY_ANIMATIONS "library_animations"
#define COLLADA_LIBRARY_CAMERAS "library_cameras"
#define COLLADA_LIBRARY_CONTROLLERS "library_controllers"
#define COLLADA_LIBRARY_EFFECTS "library_effects"
#define COLLADA_LIBRARY_GEOMETRIES "library_geometries"
#define COLLADA_LIBRARY_MATERIALS "library_materials"
#define COLLADA_LIBRARY_VISUAL_SCENES "library_visual_scenes"
#define COLLADA_JOINTS "joints"
#define COLLADA_MATRIX "matrix"
#define COLLADA_MESH "mesh"
#define COLLADA_NAME "name"
#define COLLADA_NAME_ARRAY "Name_array"
#define COLLADA_NODE "node"
#define COLLADA_OFFSET "offset"
#define COLLADA_P "p"
#define COLLADA_PHONG "phong"
#define COLLADA_PROFILE_COMMON "profile_COMMON"
#define COLLADA_ROTATE "rotate"
#define COLLADA_SCALE "scale"
#define COLLADA_SEMANTIC "semantic"
#define COLLADA_SEMANTIC_INPUT "INPUT"
#define COLLADA_SEMANTIC_INTERPOLATION "INTERPOLATION"
#define COLLADA_SEMANTIC_JOINT "JOINT"
#define COLLADA_SEMANTIC_NORMAL "NORMAL"
#define COLLADA_SEMANTIC_OUTPUT "OUTPUT"
#define COLLADA_SEMANTIC_POSITION "POSITION"
#define COLLADA_SEMANTIC_TEXCOORD "TEXCOORD"
#define COLLADA_SEMANTIC_VERTEX "VERTEX"
#define COLLADA_SID "sid"
#define COLLADA_SKIN "skin"
#define COLLADA_SAMPLER "sampler"
#define COLLADA_SOURCE "source"
#define COLLADA_STRIDE "stride"
#define COLLADA_TARGET "target"
#define COLLADA_TECHNIQUE "technique"
#define COLLADA_TECHNIQUE_COMMON "technique_common"
#define COLLADA_TRANSLATE "translate"
#define COLLADA_TRIANGLES "triangles"
#define COLLADA_TYPE "type"
#define COLLADA_TYPE_JOINT "JOINT"
#define COLLADA_URL "url"
#define COLLADA_V "v"
#define COLLADA_V_COUNT "vcount"
#define COLLADA_VERTICES "vertices"
#define COLLADA_VERTEX_WEIGHTS "vertex_weights"
#define COLLADA_VISUAL_SCENE "visual_scene"

#include <Crimild.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sstream>
#include <string>

namespace crimild {

	namespace collada {

		template< typename T >
		T xmlStringToValue( const xmlChar *input )
		{
			std::stringstream str;
			str << ( const char * ) input;
			T result;
			str >> result;
			return result;
		}

		class XMLUtils {
		public:
			static xmlNode *getChildXMLNodeWithName( xmlNode *parent, const char *name )
			{
				for ( xmlNode *node = parent->children; node != NULL; node = node->next ) {
					if ( compareXMLNodeName( node, name ) ) {
						return node;
					}
				}

				return NULL;
			}

			static bool compareXMLNodeName( const xmlNode *node, const char *str )
			{
				return std::string( ( const char * ) node->name ) == str;
			}

			static bool compareXMLString( const xmlChar *str1, const char *str2 )
			{
				return std::string( ( const char * ) str1 ) == str2;
			}

		};

	}

}

#endif
