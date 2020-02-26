
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * File: View.hpp
 * File Modified: 2020
 * ––––––––––––––––––––––––
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ––––––––––––––––––––––––
 * MIT License
 *
 * Copyright (c) 2020 Pokoidev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <vector>
    #include <Point.hpp>
    #include "Rasterizer.hpp"
    #include "Color_Buffer_Rgb565.hpp"
    #include "Color_Buffer_Rgba8888.hpp"	
	
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
            
			//////////////////////////////////////////////////////////
			// Lights
            std::vector<std::shared_ptr<DirectionalLight>> directional_lights;
			std::vector<std::shared_ptr<PointLight>> point_lights;

			//////////////////////////////////////////////////////////
			// Models
            std::vector<std::shared_ptr<Model>> models;
            
            Color_Buffer_Rgba8888::Color ambient_color{ 247, 223, 186, 255  };			

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

			std::vector<std::shared_ptr<DirectionalLight>> & get_directional_lights()
			{
				return directional_lights;
			}			

			std::vector<std::shared_ptr<PointLight>>& get_point_lights()
			{
				return point_lights;
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
