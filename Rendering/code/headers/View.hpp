
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

    #include <Camera.hpp>       // For camera reference	

    namespace Rendering3D
    {

        using std::vector;
        using toolkit::Point4i;
        using toolkit::Point4f;

        /**
        @brief View management
        */
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

            /**
            @brief The width of the view. This width is equals to the width of the window
            */
            size_t width;
            /**
            @brief The height of the view. This height is equals to the height of the window
            */
            size_t height;

            /**
            @brief The color buffer of the view
            */
            Color_Buffer               Color_buffer;
            /**
            @brief The rasterizer of the view
            */
            Rasterizer< Color_Buffer > rasterizer;

            /**
            @brief The camera
            */
            Camera	camera;            		

            /**
            @brief The collection of directional lights
            */
            std::vector<std::shared_ptr<class DirectionalLight  >> directional_lights;
            /**
            @brief The collection of point lights
            */
			std::vector<std::shared_ptr<class PointLight        >> point_lights;
            			
            /**
            @brief The collection of models
            */
            std::vector<std::shared_ptr<Model>> models;
            
            /**
            @brief The ambient color of the view
            */
            Color_Buffer_Rgba8888::Color ambient_color{ 150, 0, 50, 255  };			

        public:

            /**
            @brief Creates an instance 
            @param width The width of the view
            @param height The height of the view
            */
            View(size_t width, size_t height);

            /**
            @brief Updates the view
            */
            void update ();
            /**
            @brief Renders the view
            */
            void paint  ();

            /**
            @brief Gets the width of the view as copy
            @return The copy of the width
            */
            size_t get_width() 
            {
                return width;
            }

            /**
            @brief Gets the height of the view as copy
            @return The copy of the height
            */
            size_t get_height() 
            {
                return height;
            }

            /**
            @brief Gets a reference of the rasterizer
            @return The reference of the rasterizer
            */
			Rasterizer<Color_Buffer_Rgba8888>& get_rasterizer()
			{
				return rasterizer;
			}

            /**
            @brief Gets a reference of the camera
            @return The reference of the camera
            */
            Camera& get_camera()
            {
                return camera;
            }

            /**
            @brief Gets the directional light collection as reference
            @return The reference of the direction light collection
            */
			std::vector<std::shared_ptr<class DirectionalLight>> & get_directional_lights()
			{
				return directional_lights;
			}			

            /**
            @brief Gets the point light collection as reference
            @return The reference of the point light collection
            */
			std::vector<std::shared_ptr<class PointLight>>& get_point_lights()
			{
				return point_lights;
			}

            /**
            @brief Gets a copy of the ambient color
            @return The ambient color as copy
            */
            Color_Buffer_Rgba8888::Color get_ambient_color()
            {
                return ambient_color;
            }

        };

    }

#endif
