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
        //illuminate(view);        
        
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
                    view.get_rasterizer().set_color(material.get_color());
                    
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

        toolkit::Vector4f light({ 0.5, -0.2, -0.8, 1 });

        for (int i = 0; i < original_normals_indices.size(); ++i)
        {
            transformed_normals[original_normals_indices[i]] = toolkit::Matrix44f(model->get_transformation()) * toolkit::Matrix41f(normals[original_normals_indices[i]]);
            
            float normal_divisor = 1.f / transformed_normals[original_normals_indices[i]][3];

            transformed_normals[original_normals_indices[i]][0] *= normal_divisor;
            transformed_normals[original_normals_indices[i]][1] *= normal_divisor;
            transformed_normals[original_normals_indices[i]][2] *= normal_divisor;
            transformed_normals[original_normals_indices[i]][3] = 1.f;  
            
            /*
            float intensity = light.dot_product(transformed_normals[original_normals_indices[i]]);

            if (intensity < 0.f)
            {
                intensity = 0.f;
            }
            else if (intensity > 1.f)
            {
                intensity = 1.f;
            }

            material.get_transformed_colors()[original_normals_indices[i]] = { 
                                                                                material.get_color().data.component.r * intensity,
                                                                                material.get_color().data.component.g * intensity,
                                                                                material.get_color().data.component.b * intensity,
                                                                                material.get_color().data.component.a,
                                                                             };
            */
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
