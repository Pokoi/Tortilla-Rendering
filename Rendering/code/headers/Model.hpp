/*
 * File: Model.hpp
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

#include <vector>						// For collections
#include <Point.hpp>					// For collections
#include <Color_Buffer_Rgba8888.hpp>	// For colors
#include <string>						// For path and name
#include <memory>						// For shared_ptr
#include <Mesh.hpp>						// For collection of meshes

namespace Rendering3D
{
	struct Transform;

	class Model
	{
		std::vector<std::shared_ptr<Mesh>>			meshes;
		
		std::vector<toolkit::Point4f>				original_vertices;
		std::vector<toolkit::Point4f>				original_normals;
		std::vector<toolkit::Point3f>				original_texture_coordinates;
		std::vector<Color_Buffer_Rgba8888::Color>	original_colors;
		std::vector<toolkit::Point4f>				transformed_vertices;
		std::shared_ptr<Model>						parent;

		Transform *									transform;

	public:

		Model(std::string mesh_path);

		void set_parent(Model& model) 
		{
			parent = std::make_shared<Model>(model);
		}

		const Transform get_transform();

		void Update(float delta);		

		void Render()
		{
			for (std::shared_ptr <Mesh> mesh : meshes)
			{
				mesh->Render();
			}
		}

		~Model() 
		{
			delete transform;
		}
	};
}
