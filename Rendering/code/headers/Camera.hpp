/*
 * File: Camera.hpp
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

#include <Transform.hpp>
#include <Projection.hpp>

namespace Rendering3D
{
    /**
    @brief: Class that manages camera behaviour    
    */
    class Camera
    {
        /**
        @brief Transform of the camera
        */
        Transform transform;

        /**
        @brief Projection's matrix
        */
		toolkit::Projection3f projection;

        /**
        @brief Initial field of view 
        */
        float initial_fov = 80.f;

        /**
        @brief Current field of view
        */
        float current_fov = 80.f;

    public:

        /**
        @brief Creates a camera instance. Default projection values are:
        ** near field: 1
        ** far field: 50
        ** field of view: initial_fov value
        ** aspect ratio: 1
        */
        Camera() : projection{ 1, 50, initial_fov, 1 } {}

        /**
        @brief Creates a camera instance.
        @param view A pointer to the container view
        */
        Camera(class View * view);

        /**
        @brief Gets the projection matrix
        @return The matrix projection
        */
        toolkit::Projection3f get_projection()
        {
            return projection;
        }

        /**
        @brief Gets a reference to the transform 
        @return The reference to the transform
        */
        Transform& get_transform()
        {
            return transform;
        }     

        /**
        @brief Update the camera
        @param delta The delta time
        @param view The view reference
        */
        void Update(float delta, class View& view);

        /**
        @brief Change the field of view
        @param view The view reference
        @param modificator The modification to apply
        */
        void change_fov(View& view, float modificator);
    };
}

