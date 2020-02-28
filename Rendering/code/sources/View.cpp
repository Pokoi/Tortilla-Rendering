
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
		rasterizer(Color_buffer),
        camera{this}
	{

		std::srand(time(null));      

        camera.get_transform().set_position({ {0.0f, 0.f, 0.f} });        
        camera.get_transform().set_angular_speed(0.0025f);
        camera.get_transform().set_rotation_axis({ {1.f,0.f, 0.f} });
        

		std::shared_ptr<DirectionalLight> directional_light = std::make_shared<DirectionalLight>(Color_Buffer_Rgba8888::Color{ 255,0,0,255 }, toolkit::Vector4f{ {0.f, 10.f, -10.f, 1.f} });		
		directional_lights.push_back(directional_light);        

        std::shared_ptr<DirectionalLight> directional_light2 = std::make_shared<DirectionalLight>(Color_Buffer_Rgba8888::Color{ 252,246,166,255 }, toolkit::Vector4f{ {0.f, 2.f, 1.f, 1.f} });
        directional_lights.push_back(directional_light2);

        std::shared_ptr<PointLight> light = std::make_shared<PointLight>(Color_Buffer_Rgba8888::Color{ 0,0,255,0 }, toolkit::Vector3f{ {-2.f, -2.f, 1.f} }, 1);
        point_lights.push_back(light);      

        std::shared_ptr<PointLight> light2 = std::make_shared<PointLight>(Color_Buffer_Rgba8888::Color{ 252,246,166,0 }, toolkit::Vector3f{ {0.f, -0.f, -4.f} }, 1);
        point_lights.push_back(light2);
				
		std::shared_ptr<Model> ship = std::make_shared<Model>("tie.obj");

		ship->get_transform().set_position({ { 0.01f, -0.25f, -2.f } });
		ship->get_transform().set_scale(0.4f);
		ship->get_transform().set_initial_rotation({ {0.4f, 3.1f, 0.f} });
		ship->get_material(0).set_color({255,255,255});

		models.push_back(ship);
		
        {

		std::shared_ptr<Model> moon = std::make_shared<Model>("sphere.obj");

		moon->get_transform().set_position({ { 0.f, 1.5f, -5.0f } });
		moon->get_transform().set_scale(1.5f);

		moon->get_transform().set_rotation_axis({ {0.5f, 1.f, 0.f} });
		moon->get_transform().set_angular_speed(0.05f);
		

		moon->get_material(0).set_color({ 255,145,0,255 });

		models.push_back(moon);
        
		std::shared_ptr<Model> moon2a = std::make_shared<Model>("sphere.obj");

		moon2a->get_transform().set_position({ { 0.f, 0.f, -1.25f } });
		moon2a->get_transform().set_scale(0.7f);
		moon2a->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		moon2a->get_transform().set_angular_speed(0.0025f);
		moon2a->get_transform().set_parent(&moon->get_transform());

		moon2a->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon2a);

        std::shared_ptr<Model> moon2b = std::make_shared<Model>("sphere.obj");

        moon2b->get_transform().set_position({ { 1.f, 1.f, 0.5f } });
        moon2b->get_transform().set_scale(0.3f);
        moon2b->get_transform().set_rotation_axis({ {1.f, 1.f, 1.f} });
        moon2b->get_transform().set_angular_speed(0.0075f);
        moon2b->get_transform().set_parent(&moon->get_transform());

        moon2b->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });

        models.push_back(moon2b);

		std::shared_ptr<Model> moon3a = std::make_shared<Model>("sphere.obj");

		moon3a->get_transform().set_position({ { 0.f, 0.f, -0.6f } });
		moon3a->get_transform().set_scale(0.2f);
		moon3a->get_transform().set_rotation_axis({ {0.f, 1.f, 1.f} });
		moon3a->get_transform().set_angular_speed(0.005f);
		moon3a->get_transform().set_parent(&moon2a->get_transform());

		moon3a->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon3a);

		std::shared_ptr<Model> moon3b = std::make_shared<Model>("sphere.obj");

		moon3b->get_transform().set_position({ { -0.5f, 0.f, -0.75f } });
		moon3b->get_transform().set_scale(0.3f);
		moon3b->get_transform().set_rotation_axis({ {1.f, 1.f, 0.f} });
		moon3b->get_transform().set_angular_speed(-0.003f);
		moon3b->get_transform().set_parent(&moon2a->get_transform());

		moon3b->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });		

		models.push_back(moon3b);

        std::shared_ptr<Model> moon3c = std::make_shared<Model>("sphere.obj");

        moon3c->get_transform().set_position({ { -0.5f, 0.f, -0.75f } });
        moon3c->get_transform().set_scale(0.5f);
        moon3c->get_transform().set_rotation_axis({ {1.f, 1.f, 0.f} });
        moon3c->get_transform().set_angular_speed(-0.003f);
        moon3c->get_transform().set_parent(&moon2b->get_transform());

        moon3c->get_material(0).set_color({ (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255),0 });

        models.push_back(moon3c);

        }      
		
    }

    void View::update ()
    {
        camera.Update(0.f, *this);

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

}
