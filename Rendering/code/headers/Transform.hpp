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
    /**
    @brief Transform data
    */
    struct Transform
    {
        /**
        @brief Scale matrix
        */
        toolkit::Scaling3f			scaling;
        /**
        @brief Rotation matrix to x axis
        */
        toolkit::Rotation3f			rotation_x;
        /**
        @brief Rotation matrix to y axis
        */
        toolkit::Rotation3f			rotation_y;
        /**
        @brief Rotation matrix to z axis
        */
        toolkit::Rotation3f			rotation_z;
        /**
        @brief Translation matrix
        */
        toolkit::Translation3f		translation; 
        /**
        @brief Transformation matrix
        */
        toolkit::Transformation3f	transformation;
        /**
        @brief Inverse transformation matrix
        */
        toolkit::Matrix44f          inverse_transformation;

        /**
        @brief A pointer to parent's transform
        */
		Transform					* parent = nullptr;

        /**
        @brief The scale factor
        */
		float scale				= 1.f;
        /**
        @brief The rotation speed
        */
        float angular_speed		= 0.f;
        /**
        @brief The movement speed
        */
        float translation_speed	= 0.f;

        /**
        @brief The current rotation speed progress
        */
        float rot_speed     = 0;

        /**
        @brief The current movement speed progress
        */
        float tran_speed    = 0;

        /**
        @brief The initial position
        */
		toolkit::Vector3f initial_position{ {0.f, 0.f, 0.f} };
        /**
        @brief The initial rotation
        */
        toolkit::Vector3f initial_rotation{ {0.f, 0.f, 0.f} };
        /**
        @brief The rotation index per axis to apply rotation speed
        */
        toolkit::Vector3f rotation_axis{ {0.f, 0.f, 0.f} };
        /**
        @brief The movement index per axis to apply movement speed
        */
		toolkit::Vector3f translation_axis{ {0.f, 0.f, 0.f} };
		      
        /**
        @brief Gets the transformation as copy
        @return The copy to the transformation matrix
        */
        toolkit::Transformation3f get_transformation()
        {
            return transformation;
        }

        /**
        @brief Sets the scale of the transform
        @param scale The scale to apply
        */
		void set_scale(float scale)
		{
			this->scale = scale;
		}

        /**
        @brief Sets the initial position of the transform
        @param position The position to apply
        */
		void set_position(toolkit::Vector3f position)
		{
			this->initial_position = position;
			translation.set(position);
		}

        /**
        @brief Sets the initial rotation of the transform
        @param rotation The rotation to apply
        */
		void set_initial_rotation(toolkit::Vector3f rotation)
		{
			this->initial_rotation = rotation;
		}

        /**
        @brief Sets the rotation index per axis of the transform
        @param axis The rotation index per axis to apply
        */
		void set_rotation_axis(toolkit::Vector3f axis)
		{
			this->rotation_axis = axis;
		}

        /**
        @brief Sets the translation index per axis of the transform
        @param scale The translation index per axis to apply
        */
		void set_translation_axis(toolkit::Vector3f axis)
		{
			this->translation_axis = axis;
		}

        /**
        @brief Sets the parent of the transform
        @param parent A pointer to the parent
        */
		void set_parent(Transform* parent)
		{
			this->parent = parent;
		}

        /**
        @brief Sets the rotation speed of the transform
        @param speed The speed to apply
        */
		void set_angular_speed(float speed)
		{
			this->angular_speed = speed;
		}

        /**
        @brief Sets the translation speed of the transform
        @param speed The speed to apply
        */
		void set_translation_speed(float speed)
		{
			this->translation_speed = speed;
		}

        /**
        @brief Updates the transform        
        */
        void update_transform();

        /**
        @brief Calculates the inverse transformation        
        */
        void calculate_inverse_transformation();

        /**
        @brief Gets the inverse transformation as copy
        @return The copy of the inverse transformation
        */
        toolkit::Matrix44f get_inverse_transformation()
        {
            return inverse_transformation;
        }

    };
}