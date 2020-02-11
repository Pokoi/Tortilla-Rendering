/*
 * File: Mesh.hpp
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

#include <vector>					// For collections
#include <memory>					// For shared_ptr
#include <Material.hpp>				// For Material reference

namespace Rendering3D
{
	class Mesh
	{
		std::vector<int> original_vertices_indices;
		std::vector<int> original_normals_indices;
		std::vector<int> original_texture_coordinates_indices;
		
		std::shared_ptr<Material> material;
			

	public:

		Mesh(
				std::vector<int> vertices_indices,
				std::vector<int> normals_indices,
				std::vector<int> textures_coord_indices				
			) 
			: 
			original_vertices_indices			{ vertices_indices		} ,
			original_normals_indices			{ normals_indices		} ,
			original_texture_coordinates_indices{ textures_coord_indices} 			
		{

		}

		void Render();
	};
}