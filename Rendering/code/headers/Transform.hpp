/*
 * File: Transform.hpp
 * File Created: 14th February 2020
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

#include <Scaling.hpp>		// For Update transformations
#include <Rotation.hpp>		// For Update transformations
#include <Projection.hpp>	// For Update transformations
#include <Translation.hpp>	// For Update transformations

#include <Vector.hpp>		// For transformations values

namespace Rendering3D
{
    struct Transform
    {
        toolkit::Scaling3f			scaling;
        toolkit::Rotation3f			rotation_x;
        toolkit::Rotation3f			rotation_y;
        toolkit::Rotation3f			rotation_z;
        toolkit::Translation3f		translation; 
        toolkit::Transformation3f	transformation;
        toolkit::Matrix44f          inverse_transformation;

		Transform					* parent = nullptr;

		float scale				= 1.f;
		float angular_speed		= 0.f;
		float translation_speed	= 0.f;

        float rot_speed     = 0;
        float tran_speed    = 0;

		toolkit::Vector3f initial_position{ {0.f, 0.f, 0.f} };
		toolkit::Vector3f initial_rotation{ {0.f, 0.f, 0.f} };
		toolkit::Vector3f rotation_axis{ {0.f, 0.f, 0.f} };
		toolkit::Vector3f translation_axis{ {0.f, 0.f, 0.f} };
		      

        toolkit::Transformation3f get_transformation()
        {
            return transformation;
        }

		void set_scale(float scale)
		{
			this->scale = scale;
		}

		void set_position(toolkit::Vector3f position)
		{
			this->initial_position = position;
			translation.set(position);
		}

		void set_initial_rotation(toolkit::Vector3f rotation)
		{
			this->initial_rotation = rotation;
		}

		void set_rotation_axis(toolkit::Vector3f axis)
		{
			this->rotation_axis = axis;
		}

		void set_translation_axis(toolkit::Vector3f axis)
		{
			this->translation_axis = axis;
		}

		void set_parent(Transform* parent)
		{
			this->parent = parent;
		}

		void set_angular_speed(float speed)
		{
			this->angular_speed = speed;
		}

		void set_translation_speed(float speed)
		{
			this->translation_speed = speed;
		}

        void update_transform();

        void calculate_inverse_transformation();

        toolkit::Matrix44f get_inverse_transformation()
        {
            return inverse_transformation;
        }

    };
}