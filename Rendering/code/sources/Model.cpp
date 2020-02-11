/*
 * File: Model.cpp
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

#define TINYOBJLOADER_IMPLEMENTATION

#include <Model.hpp>
#include <tiny_obj_loader.h> // For load the obj file

#include <Scaling.hpp>		// For Update transformations
#include <Rotation.hpp>		// For Update transformations
#include <Projection.hpp>	// For Update transformations
#include <Translation.hpp>	// For Update transformations

namespace Rendering3D
{
	Model::Model(std::string mesh_path)
	{
		/////////////////////////////////////////////////////////////////////////////////////
		// Code based in code snippet from tinyobjloader repository README 
		// https://github.com/syoyo/tinyobjloader/blob/master/README.md
		// Visited on: February 11th, 2020

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		if (tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, mesh_path.c_str()))
		{
			// For each tinyobj shape 
			for (size_t s = 0; s < shapes.size(); ++s)
			{
				size_t index_offset = 0;

				std::vector<int> vertices_indices;
				std::vector<int> normals_indices;
				std::vector<int> textures_coord_indices;				

				// For each face in the shape
				for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
				{
					int fv = shapes[s].mesh.num_face_vertices[f];					

					// For each vertex
					for (size_t v = 0; v < fv; ++v)
					{
						tinyobj::index_t	idx = shapes[s].mesh.indices[index_offset + v];
						tinyobj::real_t		vx  = attrib.vertices[3 * idx.vertex_index + 0];
						tinyobj::real_t		vy  = attrib.vertices[3 * idx.vertex_index + 1];
						tinyobj::real_t		vz  = attrib.vertices[3 * idx.vertex_index + 2];
						tinyobj::real_t		nx  = attrib.normals[3 * idx.normal_index + 0];
						tinyobj::real_t		ny  = attrib.normals[3 * idx.normal_index + 1];
						tinyobj::real_t		nz  = attrib.normals[3 * idx.normal_index + 2];
						tinyobj::real_t		tx  = attrib.texcoords[2 * idx.texcoord_index + 0];
						tinyobj::real_t		ty  = attrib.texcoords[2 * idx.texcoord_index + 1];	
												
						original_vertices			.push_back	({ { vx, vy, vz, 1	} });
						original_normals			.push_back	({ { nx, ny, nz, 1	} });
						original_texture_coordinates.push_back	({ { tx, ty, 1		} });

						vertices_indices			.push_back(idx.vertex_index);
						normals_indices				.push_back(idx.normal_index);
						textures_coord_indices		.push_back(idx.texcoord_index);
					}

					index_offset += fv;
					shapes[s].mesh.material_ids[f];
				}

				meshes.push_back(std::make_shared<Mesh>(vertices_indices, normals_indices, textures_coord_indices));

			}
		}


		/////////////////////////////////////////////////////////////////////////////////////
	}

	void Model::Update(float delta)
	{
		static float angle = 0.f;

		// To rotate the model in runtime
		//	angle += 0.025f 

		// Transformations matrices

		toolkit::Scaling3f scaling(0.2f);
		toolkit::Rotation3f rotation_x;
		toolkit::Rotation3f rotation_y;
		toolkit::Translation3f translation(0, 0, 0); // Modify to translate the model 
	}
}