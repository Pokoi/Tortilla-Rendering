
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
#include <Light.hpp>		// for light referece

#include <ctime>			// For random color 

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

		std::srand(time(null));

		std::shared_ptr<DirectionalLight> directional_light = std::make_shared<DirectionalLight>(Color_Buffer_Rgba8888::Color{ 255,0,0,0 }, toolkit::Vector4f{ {1.f, 0.5f, 0.5f, 1.f} });
		
		directional_lights.push_back(directional_light);

		std::shared_ptr<PointLight> light = std::make_shared<PointLight>(Color_Buffer_Rgba8888::Color{ 255,0,0,0 }, toolkit::Vector3f{ {0.f, -1.5f, 0.f} }, 1);		
		//point_lights.push_back(light);      
		
				
		std::shared_ptr<Model> ship = std::make_shared<Model>("tie.obj");

		ship->get_transform().set_position({ { 0.f, -1.f, -2.5f } });
		ship->get_transform().set_scale(0.5f);
		ship->get_transform().set_initial_rotation({ {0.4f, 3.1f, 0.f} });
		//ship->get_material(0).set_color({51,11,17});

		models.push_back(ship);
		
		std::shared_ptr<Model> moon = std::make_shared<Model>("sphere.obj");

		moon->get_transform().set_position({ { -4.f, 1.5f, -2.5f } });
		moon->get_transform().set_scale(1.f);

		moon->get_transform().set_rotation_axis({ {0.5f, 1.f, 0.f} });
		moon->get_transform().set_angular_speed(0.05f);

		//moon->get_transform().set_translation_speed(0.01f);
		//moon->get_transform().set_translation_axis({ {0, 0, -1.f} });

		moon->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t) (rand() % 255), (uint8_t) (rand() % 255),0 });		

		models.push_back(moon);
        
		std::shared_ptr<Model> moon2 = std::make_shared<Model>("sphere.obj");

		moon2->get_transform().set_position({ { 0.f, 0.f, -1.f } });
		moon2->get_transform().set_scale(0.7f);
		moon2->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		moon2->get_transform().set_angular_speed(0.0025f);
		moon2->get_transform().set_parent(&moon->get_transform());

		moon2->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon2);

		std::shared_ptr<Model> moon3a = std::make_shared<Model>("sphere.obj");

		moon3a->get_transform().set_position({ { 0.f, 0.f, -0.75f } });
		moon3a->get_transform().set_scale(0.2f);
		moon3a->get_transform().set_rotation_axis({ {0.f, 1.f, 1.f} });
		moon3a->get_transform().set_angular_speed(0.005f);
		moon3a->get_transform().set_parent(&moon2->get_transform());

		moon3a->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon3a);

		std::shared_ptr<Model> moon3b = std::make_shared<Model>("sphere.obj");

		moon3b->get_transform().set_position({ { -0.5f, 0.f, -1.f } });
		moon3b->get_transform().set_scale(0.3f);
		moon3b->get_transform().set_rotation_axis({ {1.f, 1.f, 0.f} });
		moon3b->get_transform().set_angular_speed(-0.003f);
		moon3b->get_transform().set_parent(&moon2->get_transform());

		moon3b->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon3b);

		/*
		std::shared_ptr<Model> asteroid = std::make_shared<Model>("asteroid.obj");

		asteroid->get_transform().set_position({ {-3.f, 0.f, -3.f } });
		asteroid->get_transform().set_scale(0.05f);
		asteroid->get_transform().set_rotation_axis({ {1.f, 1.f, 0.f} });
		asteroid->get_transform().set_angular_speed(-0.003f);

		models.push_back(asteroid);
		*/
		
    }

    void View::update ()
    {
		for (std::shared_ptr<DirectionalLight>& light : directional_lights)
		{
			light->Update(0.f, *this);
		}

		for (std::shared_ptr<PointLight>& light : point_lights)
		{
			light->Update(0.f, *this);
		}

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
