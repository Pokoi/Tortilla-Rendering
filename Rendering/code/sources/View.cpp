
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
 * File: View.cpp
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


#include <cmath>
#include <cassert>
#include <View.hpp>
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>

#include <Color_Buffer_Rgba8888.hpp>
#include <Vector.hpp>

using namespace toolkit;

namespace Rendering3D
{

	View::View(size_t width, size_t height)
		:
		width(width),
		height(height),
		Color_buffer(width, height),
		rasterizer(Color_buffer)
	{
		directional_lights.push_back(std::make_shared<DirectionalLight>(Color_Buffer_Rgba8888::Color{ 255,255,255,255 }, toolkit::Vector4f{ {0.5f, 0.5f, 0.5f, 1.f} }));

		/*std::shared_ptr<PointLight> light = std::make_shared<PointLight>(Color_Buffer_Rgba8888::Color{ 255,255,255,255 }, toolkit::Vector3f{ {0, -0.5f, 0} });
		point_lights.push_back(light);*/

		
		/*
		std::shared_ptr<Model> deer = std::make_shared<Model>("deer.obj");
		deer->get_transform().set_position({ { 0.f, -0.28f, -2.f } });
		deer->get_transform().set_scale(0.0025f);
		deer->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		deer->get_transform().set_angular_speed(0.0025f);

		models.push_back(deer);
		std::shared_ptr<Model> nature = std::make_shared<Model>("nature.obj");

		nature->get_transform().set_position({ { 0.f, -0.3f, -2.5f } });
		nature->get_transform().set_scale(0.5f);
		nature->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		nature->get_transform().set_angular_speed(0.0025f);

		models.push_back(nature);
		std::shared_ptr<Model> pointer = std::make_shared<Model>("pointer.obj");

		pointer->get_transform().set_position({ { 0.f, 0.f, -2.f } });
		pointer->get_transform().set_scale(0.01f);
		pointer->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		pointer->get_transform().set_angular_speed(0.0025f);

		models.push_back(pointer);
		*/
		

		
		std::shared_ptr<Model> death_star = std::make_shared<Model>("tie.obj");

		death_star->get_transform().set_position({ { 0.f, 0.f, -3.f } });
		death_star->get_transform().set_scale(0.5f);
		//death_star->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		//death_star->get_transform().set_angular_speed(0.0025f);

		models.push_back(death_star);
		
		std::shared_ptr<Model> moon = std::make_shared<Model>("sphere.obj");

		moon->get_transform().set_position({ { -2.f, 0.f, -3.f } });
		moon->get_transform().set_scale(1.f);		
		moon->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		moon->get_transform().set_angular_speed(0.0025f);

		models.push_back(moon);
        
		std::shared_ptr<Model> moon2 = std::make_shared<Model>("sphere.obj");

		moon2->get_transform().set_position({ { 0.f, 0.f, -2.f } });
		moon2->get_transform().set_scale(1.f);
		//moon2->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		//moon2->get_transform().set_angular_speed(0.0025f);
		moon2->get_transform().set_parent(&moon->get_transform());

		models.push_back(moon2);

    }

    void View::update ()
    {
		for (std::shared_ptr<Model>& model : models)
		{
			model->Update(0.f, *this);
		}
    }

    void View::paint ()
    {      
        rasterizer.clear();

		for (std::shared_ptr<Model> & model : models)
		{
			model->Render(*this);
		}

        rasterizer.get_color_buffer ().gl_draw_pixels (0, 0);
    }

    void View::clear()
    {
        rasterizer.clear();
    }

    void View::swap()
    {
        rasterizer.get_color_buffer().gl_draw_pixels(0, 0);
    }

}
