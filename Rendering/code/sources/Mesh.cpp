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
				class Model& owner
			)		
	{
		original_vertices_indices			 = vertices_indices;
		original_normals_indices			 = normals_indices;
		original_texture_coordinates_indices = textures_coord_indices;
		model								 = std::make_shared<Model>(owner);
	}
	
	
	void Mesh::Render(View& view)
	{

        // Insert here ilumination
        // <-->

        // World Coordinates to Screen Coordinates
        size_t width    = view.get_width();
        size_t height   = view.get_height();  

        toolkit::Scaling3f        scaling       = toolkit::Scaling3f    (float(width / 2), float(height / 2), 100000000.f);
        toolkit::Translation3f    translation   = toolkit::Translation3f(float(width / 2), float(height / 2), 0.f);
        
        toolkit::Transformation3f transformation = translation * scaling;

        for (int index : original_vertices_indices)
        {
            view.get_display_vertices()[index] = Point4i(toolkit::Matrix44f(transformation) * toolkit::Matrix41f(model->get_transformed_vertices()[index]));
        }

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
                    view.get_display_vertices().data(),
                    indices,
                    indices + 3,
                    width,
                    height,
                    clipped_vertices
                );

                // Render
                if (vertex_count >= 3)
                {

                    view.get_rasterizer().set_color(material->get_color());
                    view.get_rasterizer().fill_convex_polygon_z_buffer(clipped_vertices.data(), clipped_indices, clipped_indices + vertex_count);
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
}


//anotaciones para el recorte de triángulos
/*
Se recomienda hacerlo en una clase aparte

{
	

}

*/