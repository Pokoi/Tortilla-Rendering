
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <vector>
    #include <Point.hpp>
    #include "Rasterizer.hpp"
    #include "Color_Buffer_Rgb565.hpp"
    #include "Color_Buffer_Rgba8888.hpp"
	
	#include <map>				// For model collection
	#include <Model.hpp>		// For model collection
    #include <string>

    #include <Camera.hpp>       // For camera reference
	#include <Light.hpp>		// for light referece

    namespace Rendering3D
    {

        using std::vector;
        using toolkit::Point4i;
        using toolkit::Point4f;

        class View
        {
        private:

            typedef Color_Buffer_Rgba8888 Color_Buffer;
            typedef Color_Buffer::Color   Color;
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector< int    >      Index_Buffer;
            typedef vector< Color  >      Vertex_Colors;

        private:

            size_t width;
            size_t height;

            Color_Buffer               Color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            Camera	camera;
            Light	light;

            Color_Buffer_Rgba8888::Color ambient_color{  117, 28, 83, 255  };

			float ambient_intensity = 0.f;

            std::map<std::string, std::shared_ptr<Model>> models;
            

        public:

            View(size_t width, size_t height);

            void update ();
            void paint  ();

            size_t get_width() 
            {
                return width;
            }

            size_t get_height() 
            {
                return height;
            }

			Rasterizer<Color_Buffer_Rgba8888>& get_rasterizer()
			{
				return rasterizer;
			}

            Camera& get_camera()
            {
                return camera;
            }

			Light& get_light()
			{
				return light;
			}

			float get_ambient_intensity()
			{
				return ambient_intensity;
			}

            Color_Buffer_Rgba8888::Color get_ambient_color()
            {
                return ambient_color;
            }

            void clear();
            void swap();

        };

    }

#endif
