
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
        width       (width ),
        height      (height),
        Color_buffer(width, height),
        rasterizer  (Color_buffer )
    {
		directional_lights.push_back(std::make_shared<DirectionalLight>( Color_Buffer_Rgba8888::Color{255,255,255,255}, toolkit::Vector4f{ {1.f, 0.5f, 0.5f, 0.f} } ));

		std::shared_ptr<PointLight> light = std::make_shared<PointLight>(Color_Buffer_Rgba8888::Color{ 255,255,255,255 }, toolkit::Vector3f{ {0, -0.5f, 0} });
		point_lights.push_back(light);
		
		std::shared_ptr<Model> deer = std::make_shared<Model>("deer.obj");

		deer->get_transform().set_position({ { 0.f, -0.4f, -2.f } });
		deer->get_transform().set_scale(0.00005f);
		deer->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		deer->get_transform().set_angular_speed(0.025f);

		models.push_back(deer);

		std::shared_ptr<Model> nature = std::make_shared<Model>("nature.obj");

		nature->get_transform().set_position({ { 0.f, -0.3f, -2.f } });
		nature->get_transform().set_scale(0.05f);
		nature->get_transform().set_rotation_axis({ {0.f, 1.f, 0.f} });
		nature->get_transform().set_angular_speed(0.025f);

		models.push_back(nature);



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
