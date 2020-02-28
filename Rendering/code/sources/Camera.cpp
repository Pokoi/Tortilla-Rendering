/*
 * File: Camera.cpp
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

#include <Camera.hpp>
#include <View.hpp>

#include <math.h>

namespace Rendering3D
{
    Camera::Camera(View* view) : projection{ 1, 50, initial_fov, view->get_width() / view->get_height()}
    {       
        
    }
    void Camera::Update(float delta, View & view)
    {
        static float fov_modificator    = 0;
        static float dissplacement      = 0;

        fov_modificator += 0.0015f;
        dissplacement   += std::abs(transform.angular_speed);       
    

        if (dissplacement > 0.5f)
        {
            transform.angular_speed *= -1.f;
            fov_modificator *= -1.f;
            dissplacement = 0;
        }
        
        change_fov(view, fov_modificator);             

        transform.update_transform();
        transform.calculate_inverse_transformation();
    }

    void Camera::change_fov(View& view, float modificator)
    {
        current_fov += modificator;
        projection.set(1, 50, current_fov, view.get_width() / view.get_height());
    }
}