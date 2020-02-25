/*
 * File: Light.hpp
 * File Created: 20th February 2020
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

#include <Transform.hpp>
#include <Color_Buffer_Rgba8888.hpp>
#include <cmath>
#include <Point.hpp>

namespace Rendering3D
{

	class Light
	{
    protected:
        Transform transform;		
		Color_Buffer_Rgba8888::Color light_color;	
	
	public:

		Light(Color_Buffer_Rgba8888::Color color) : light_color{ color } {}

        virtual toolkit::Vector4f get_direction(toolkit::Point4f point) = 0;
		
		Color_Buffer_Rgba8888::Color get_light_color(toolkit::Point4f point)
		{	
            /*
            float distance = std::sqrt  (
                                            std::pow ( point.coordinates().get_values()[0] - toolkit::Matrix44f(transform.transformation)[3][0], 2) +
                                            std::pow ( point.coordinates().get_values()[1] - toolkit::Matrix44f(transform.transformation)[3][1], 2) +
                                            std::pow ( point.coordinates().get_values()[2] - toolkit::Matrix44f(transform.transformation)[3][2], 2)
                                        
                                        );

            Color_Buffer_Rgba8888::Color color = light_color;

            color * (intensity * distance) ;
           */
            return light_color;            
		}

        void set_position(toolkit::Vector3f & position)
        {
            transform.translation.set(position);
        }

	};

    class PointLight : public Light
    {
    public:       

        PointLight(Color_Buffer_Rgba8888::Color color, toolkit::Vector3f position) : Light{ color }
        {
            set_position(position);
        }

        virtual toolkit::Vector4f get_direction(toolkit::Point4f point)
        {

            toolkit::Vector4f direction{
                                            {
                                                toolkit::Matrix44f(transform.transformation)[3][0] - point.coordinates().get_values()[0],
                                                toolkit::Matrix44f(transform.transformation)[3][1] - point.coordinates().get_values()[1],
                                                toolkit::Matrix44f(transform.transformation)[3][2] - point.coordinates().get_values()[2],
                                                0
                                            }
            };

            float v = std::sqrt(std::pow(direction[0], 2) + std::pow(direction[1], 2) + std::pow(direction[2], 2));
            v = 1 / v;
            direction[0] *= v;
            direction[1] *= v;
            direction[2] *= v;
            direction[3] = 0.f;

            return	direction;
        }

    };

    class DirectionalLight : public Light
    {

    public:

        toolkit::Vector4f direction;

        DirectionalLight(Color_Buffer_Rgba8888::Color color, toolkit::Vector4f direction) : Light{ color }, direction{ direction } {}

        virtual toolkit::Vector4f get_direction(toolkit::Point4f point) override
        {
            float v = std::sqrt(std::pow(direction[0], 2) + std::pow(direction[1], 2) + std::pow(direction[2], 2));
            v = 1 / v;
            direction[0] *= v;
            direction[1] *= v;
            direction[2] *= v;
            direction[3] = 0.f;

            return	direction;
        }

    };
}
