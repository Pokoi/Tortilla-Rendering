/*
 * File: Mesh.cpp
 * File Created: 11th February 2020
 * ������������������������
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ������������������������
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
	
	
	void Mesh::Render()
	{
		
	}
}


//anotaciones para el recorte de tri�ngulos
/*
Se recomienda hacerlo en una clase aparte
int polygon_clipper (
						toolkit::Point4i * vertices,
						const int * first,
						const int * last,
						const int	viewport_width,
						const int	viewport_height,
						toolkit::Point4i * clipped_vertices
					)
{
	

}

*/