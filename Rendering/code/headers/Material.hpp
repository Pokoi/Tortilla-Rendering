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
		Color_Buffer_Rgba8888::Color original_color{ 100,100,100,255};
        std::vector<Color_Buffer_Rgba8888::Color>	transformed_colors;
		// Texture

		// ka, kd, ks

    public:

        Material(size_t colors_size)
        {
            transformed_colors.resize(colors_size);
        }

        Color_Buffer_Rgba8888::Color get_color()
        {
            return original_color;
        }

        std::vector<Color_Buffer_Rgba8888::Color>& get_transformed_colors()
        {
            return transformed_colors;
        }

	};
}