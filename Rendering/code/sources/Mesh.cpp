/*
 * File: Mesh.cpp
 * File Created: 11th February 2020
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

#include <Mesh.hpp>

#include <Model.hpp>		// For constructor assignation

#include <Scaling.hpp>		// For Update transformations
#include <Rotation.hpp>		// For Update transformations
#include <Projection.hpp>	// For Update transformations
#include <Translation.hpp>	// For Update transformations

#include <View.hpp>         // For render
#include <Clipping.hpp>     // For polygon clipping

#include <Color_Buffer_Rgba8888.hpp> // For illumination


namespace Rendering3D
{
	
	Mesh::Mesh(
				std::vector<int>	vertices_indices,
				std::vector<int>	normals_indices,
				std::vector<int>	textures_coord_indices,
				Model * owner
			): material{vertices_indices.size()}
	{
		original_vertices_indices			 = vertices_indices;
		original_normals_indices			 = normals_indices;
		original_texture_coordinates_indices = textures_coord_indices;
		model								 = owner;	
	}
	
	
	void Mesh::Render(View& view)
	{

        // Ilumination
        illuminate(view);        
        
        // World Coordinates to Screen Coordinates
        display_coordinates_transformation(view.get_width(), view.get_height());    
        
        // Clipping and Rendering
        for (int* indices = original_vertices_indices.data(), *end = indices + original_vertices_indices.size(); indices < end; indices += 3)
        {           

            if (is_frontface(model->get_transformed_vertices().data(), indices))
            {
				
                // Clip polygons                
                std::vector<toolkit::Point4i> clipped_vertices;
                static const int clipped_indices[] = { 0,1,2,3,4,5,6,7,8,9 };
				
				material.calculate_average_color(indices, indices + 3);
                
                int vertex_count = Clipping::get().polygon_clipper
                (
                    model->get_display_vertices().data(),
                    indices,
                    indices + 3,
                    view.get_width(),
                    view.get_height(),
                    clipped_vertices
                );
				
                // Render
                if (vertex_count >= 3)
                {
                    view.get_rasterizer().set_color(material.get_average_color());
                    
                    // With clipping
                    view.get_rasterizer().fill_convex_polygon_z_buffer(clipped_vertices.data(), clipped_indices, clipped_indices + vertex_count);
					
                    // Whitout clipping:
                    // view.get_rasterizer().fill_convex_polygon_z_buffer(model->get_display_vertices().data(), indices, indices + 3);
                }
            }
        }
	}

    bool Mesh::is_frontface(const toolkit::Point4f* const projected_vertices, const int* const indices)
    {
        const toolkit::Point4f & v0 = projected_vertices[indices[0]];
        const toolkit::Point4f & v1 = projected_vertices[indices[1]];
        const toolkit::Point4f & v2 = projected_vertices[indices[2]];

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
    }

    void Mesh::illuminate(View& view)
    {
        auto normals = model->get_original_normals();
        auto & transformed_normals = model->get_transformed_normals();        

        for (int i = 0; i < original_normals_indices.size(); ++i)
        {
			Color_Buffer_Rgba8888::Color	diffuse			= material.get_color();
			float							ambient			= view.get_ambient_intensity();
			Color_Buffer_Rgba8888::Color	light_color		= view.get_light().get_light_color();
			toolkit::Vector4f				direction		= view.get_light().get_direction();
			
			float multiplier = model->get_transformed_normals()[original_normals_indices[i]].dot_product(direction);			
			if (multiplier > 1) multiplier = 1;
			else if (multiplier < 0) multiplier = 0;

			int transformed_blue	= (diffuse.data.component.g * ambient) + (diffuse.data.component.g * light_color.data.component.g * multiplier);
			int transformed_green	= (diffuse.data.component.b * ambient) + (diffuse.data.component.b * light_color.data.component.b * multiplier);
			int transformed_red		= (diffuse.data.component.r * ambient) + (diffuse.data.component.r * light_color.data.component.r * multiplier);

			if (transformed_blue > 255) transformed_blue = 255;
			else if (transformed_blue < 0) transformed_blue = 0;

			if (transformed_green > 255) transformed_green = 255;
			else if (transformed_green < 0) transformed_green = 0;

			if (transformed_red > 255) transformed_red = 255;
			else if (transformed_red < 0) transformed_red = 0;

			material.get_transformed_colors()[original_normals_indices[i]].set(transformed_red, transformed_blue, transformed_green);            
        }

       
    }   

    void Mesh::NDC_transformation()
    {   
        auto & transformed_vertices = model->get_transformed_vertices();

        for (int i = 0; i < original_vertices_indices.size(); ++i)
        {
            toolkit::Point4f& vertex = transformed_vertices[original_vertices_indices[i]];
            
            float inv_w = 1.f / vertex[3];
            vertex[0] *= inv_w;
            vertex[1] *= inv_w;
            vertex[2] *= inv_w;        
        }
    }


    void Mesh::display_coordinates_transformation(size_t width, size_t height)
    {
        toolkit::Scaling3f        scaling = toolkit::Scaling3f(float(width / 2), float(height / 2), 100000000.f);
        toolkit::Translation3f    translation = toolkit::Translation3f(float(width / 2), float(height / 2), 0.f);

        toolkit::Transformation3f transformation = translation * scaling;

        for (int i = 0; i < original_vertices_indices.size(); ++i)
        {
            model->get_display_vertices()[original_vertices_indices[i]] = Point4i(toolkit::Matrix44f(transformation) * toolkit::Matrix41f(model->get_transformed_vertices()[original_vertices_indices[i]]));
        }
    }
}
