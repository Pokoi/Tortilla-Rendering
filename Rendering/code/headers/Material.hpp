/*
 * File: Material.hpp
 * File Created: 11th February 2020
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

#pragma once
#include <Color_Buffer_Rgba8888.hpp>
#include <Point.hpp>

namespace Rendering3D
{
    /**
    @brief Material
    */
	class Material
	{
        /**
        @brief The diffuse color
        */
		Color_Buffer_Rgba8888::Color original_color{ 255,255,255,255};

        /**
        @brief The transformed colors collection
        */
        std::vector<Color_Buffer_Rgba8888::Color>	transformed_colors;

        /**
        @brief The average color of the triangle
        */
		Color_Buffer_Rgba8888::Color average_color{100,100,100,255};
		

        /**
        @brief The ambient component factor
        */
        float ka;

        /**
        @brief The diffuse component factor
        */
        float kd;

        /**
        @brief The light component factor
        */
        float kl;

    public:

        /**
        @brief Creates an instance with the given size of colors
        @param colors_size The size of vertices of the mesh this material is attached to.
        */
        Material(size_t colors_size)
        {
            transformed_colors.resize(colors_size);
            ka = 0.05f;
            kd = 0.6f;
            kl = 0.4f;
        }

        /**
        @brief Gets a reference to the diffuse color of the material
        @return The reference to the diffuse color
        */
        Color_Buffer_Rgba8888::Color & get_color()
        {
            return original_color;
        }

        /**
        @brief Gets a reference to the average color
        @return The average color
        */
		Color_Buffer_Rgba8888::Color& get_average_color()
		{
			return average_color;
		}

        /**
        @brief Gets a reference to the transformed colors collection
        @return The transformed colors collection
        */
        std::vector<Color_Buffer_Rgba8888::Color>& get_transformed_colors()
        {
            return transformed_colors;
        }

        /**
        @brief Calculate the average color in the given range
        @param first The first in range
        @param last The last in range
        */
		void calculate_average_color(const int * first, const int * last)
		{
			int count = 0;
			int total_r = 0, total_g = 0, total_b = 0;

			for (const int* index = first; index < last; ++index, ++count)
			{
				total_r += transformed_colors[*index].data.component.r;
				total_g += transformed_colors[*index].data.component.g;
				total_b += transformed_colors[*index].data.component.b;				
			}

			average_color.set(total_r / count, total_g / count, total_b / count);
		}

        /**
        @brief Gets the ambient component factor
        @return The ambient component factor
        */
        float get_ka()
        {
            return ka;
        }

        /**
        @brief Gets the diffuse component factor
        @return The diffuse component factor
        */
        float get_kd()
        {
            return kd;
        }

        /**
        @brief Gets the light component factor
        @return The light component factor
        */
        float get_kl()
        {
            return kl;
        }

        /**
        @brief Sets the ambient component factor
        @param ka The ambient component factor
        */
		void set_ka( float ka )
		{
			this->ka = ka;
		}

        /**
        @brief Sets the diffuse component factor
        @param kd The diffuse component factor
        */
		void set_kd( float kd )
		{
			this->kd = kd;
		}

        /**
        @brief Sets the light component factor
        @param kl The light component factor
        */
		void set_kl( float kl )
		{
			this->kl = kl;
		}

        /**
        @brief Sets the diffuse color
        @param color The diffuse color
        */
		void set_color(Color_Buffer_Rgba8888::Color color)
		{
			this->original_color = color;
		}
	};
}