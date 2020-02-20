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

#include <string>						// For path and name
#include <memory>						// For shared_ptr
#include <Mesh.hpp>						// For collection of meshes

#include <Transformation.hpp>

namespace Rendering3D
{
	struct Transform;

	class Model
	{
		std::vector<std::shared_ptr<Mesh>>			meshes;
		
		std::vector<toolkit::Point4f>				original_vertices;
		std::vector<toolkit::Point4f>				original_normals;
		std::vector<toolkit::Point3f>				original_texture_coordinates;
		
        std::vector<toolkit::Point4f>				transformed_vertices;
        std::vector<toolkit::Point4f>               transformed_normals;
        
        std::vector<toolkit::Point4i>				display_vertices;
		
        std::shared_ptr<Model>						parent;

		Transform 		*							transform;

        toolkit::Transformation3f                   transformation;

	public:

		Model(std::string mesh_path);

		void set_parent(Model& model) 
		{
			parent = std::make_shared<Model>(model);
		}

		std::vector<toolkit::Point4i> & get_display_vertices()
		{
			return display_vertices;
		}

		Transform get_transform();

        std::vector<toolkit::Point4f>& get_original_vertices()
        {
            return original_vertices;
        }

        std::vector<toolkit::Point4f> & get_transformed_vertices()
        {
            return transformed_vertices;
        }

        std::vector<toolkit::Point4f> & get_original_normals()
        {
            return original_normals;
        }

        std::vector<toolkit::Point4f> & get_transformed_normals()
        {
            return transformed_normals;
        }

        toolkit::Transformation3f get_transformation()
        {
            return transformation;
        }

		void Update(float delta, class View& view);		

        void Render(class View& view);
	
	};
}
