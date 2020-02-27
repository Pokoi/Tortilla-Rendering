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

#include <View.hpp>		// For update

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
		
		virtual Color_Buffer_Rgba8888::Color get_light_color(toolkit::Point4f point)
		{          
            return light_color;            
		}      

		Transform & get_transform()
		{
			return transform;
		}

		void Update(float delta, View & view)
		{
			transform.update_transform();

			transform.transformation = view.get_camera().get_projection() * transform.get_transformation();
		}

	};

    class PointLight : public Light
    {
		float attenuation = 0;

    public:       

		PointLight(Color_Buffer_Rgba8888::Color color, toolkit::Vector3f position, float attenuation) : Light{ color }, attenuation{ attenuation }
        {
			transform.set_position(position);
        }

        virtual toolkit::Vector4f get_direction(toolkit::Point4f point)
        {

            toolkit::Vector4f direction{
                                            {
                                                toolkit::Matrix44f(transform.transformation)[0][3] - point.coordinates().get_values()[0],
                                                toolkit::Matrix44f(transform.transformation)[1][3] - point.coordinates().get_values()[1],
                                                toolkit::Matrix44f(transform.transformation)[2][3] - point.coordinates().get_values()[2],
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

		virtual Color_Buffer_Rgba8888::Color get_light_color(toolkit::Point4f point) override
		{
			
			float self_x = toolkit::Matrix44f(transform.transformation)[0][3];
			float self_y = toolkit::Matrix44f(transform.transformation)[1][3];
			float self_z = toolkit::Matrix44f(transform.transformation)[2][3];


			float distance = std::sqrt  (
											std::pow ( point.coordinates().get_values()[0] - toolkit::Matrix44f(transform.transformation)[0][3], 2) +
											std::pow ( point.coordinates().get_values()[1] - toolkit::Matrix44f(transform.transformation)[1][3], 2) +
											std::pow ( point.coordinates().get_values()[2] - toolkit::Matrix44f(transform.transformation)[2][3], 2)

										);
			

			Color_Buffer_Rgba8888::Color color = light_color;

			color * (1/distance * attenuation) ;
		   

			return color;
		}

    };

    class DirectionalLight : public Light
    {

    public:

        toolkit::Vector4f direction;

        DirectionalLight(Color_Buffer_Rgba8888::Color color, toolkit::Vector4f direction) : Light{ color }, direction{ direction } 
		{
			float v = std::sqrt(std::pow(direction[0], 2) + std::pow(direction[1], 2) + std::pow(direction[2], 2));
			v = 1 / v;
			direction[0] *= v;
			direction[1] *= v;
			direction[2] *= v;
			direction[3] = 0.f;
		}

        virtual toolkit::Vector4f get_direction(toolkit::Point4f point) override
        {   
            toolkit::Vector4f new_direction{ {point.coordinates().get_values()[0] + direction[0], point.coordinates().get_values()[1] + direction[1], point.coordinates().get_values()[2] + direction[2] } };

            float v = std::sqrt(std::pow(new_direction[0], 2) + std::pow(new_direction[1], 2) + std::pow(new_direction[2], 2));
            v = 1 / v;
            new_direction[0] *= v;
            new_direction[1] *= v;
            new_direction[2] *= v;
            new_direction[3] = 0.f;

            return	new_direction;
        }

    };
}
