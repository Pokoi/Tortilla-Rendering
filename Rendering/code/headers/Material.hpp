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

	class Material
	{
		// Color
		Color_Buffer_Rgba8888::Color original_color{ 255,255,255,255};
        std::vector<Color_Buffer_Rgba8888::Color>	transformed_colors;

		Color_Buffer_Rgba8888::Color average_color{100,100,100,255};
		// Texture

		// ka, kd, ks
        float ka;
        float kd;
        float kl;

    public:

        Material(size_t colors_size)
        {
            transformed_colors.resize(colors_size);
            ka = 0.05f;
            kd = 0.6f;
            kl = 0.4f;
        }

        Color_Buffer_Rgba8888::Color & get_color()
        {
            return original_color;
        }

		Color_Buffer_Rgba8888::Color& get_average_color()
		{
			return average_color;
		}

        std::vector<Color_Buffer_Rgba8888::Color>& get_transformed_colors()
        {
            return transformed_colors;
        }

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

        float get_ka()
        {
            return ka;
        }

        float get_kd()
        {
            return kd;
        }

        float get_kl()
        {
            return kl;
        }

		void set_ka( float ka )
		{
			this->ka = ka;
		}

		void set_kd( float kd )
		{
			this->kd = kd;
		}

		void set_kl( float kl )
		{
			this->kl = kl;
		}

		void set_color(Color_Buffer_Rgba8888::Color color)
		{
			this->original_color = color;
		}
	};
}