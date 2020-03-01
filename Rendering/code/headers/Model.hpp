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
#include <Vector.hpp>					// For normals

#include <string>						// For path and name
#include <memory>						// For shared_ptr
#include <Mesh.hpp>						// For collection of meshes

#include <Transformation.hpp>

namespace Rendering3D
{
	struct Transform;

    /**
    @brief Model class    
    */
	class Model
	{
        /**
        @brief The collection of meshes of this model
        */
		std::vector<std::shared_ptr<Mesh>>			meshes;
		
        /**
        @brief The collection of original vertices
        */
		std::vector<toolkit::Point4f>				original_vertices;
        /**
        @brief The collection of original normals
        */
		std::vector<toolkit::Vector4f>				original_normals;        
        /**
        @brief The collection of transformed vertices
        */
        std::vector<toolkit::Point4f>				transformed_vertices;
        /**
        @brief The collection of transformed normals
        */
        std::vector<toolkit::Vector4f>              transformed_normals;
        /**
        @brief The display vertices collection
        */
        std::vector<toolkit::Point4i>				display_vertices;
        /**
        @brief The model parent
        */
        std::shared_ptr<Model>						parent;
        /**
        @brief The transform of the model
        */
		Transform 		*							transform;
        /**
        @brief The transformation of the model
        */
        toolkit::Transformation3f                   transformation;

	public:

        /**
        @brief Creates a instance of model
        @param mesh_path The path of the mesh
        */
		Model(std::string mesh_path);

        /**
        @brief Sets the parent
        @param model The parent model
        */
		void set_parent(Model& model) 
		{
			parent = std::make_shared<Model>(model);
		}

        /**
        @brief Gets the display vertices reference
        @return The display vertices reference
        */
		std::vector<toolkit::Point4i> & get_display_vertices()
		{
			return display_vertices;
		}

        /**
        @brief Gets the transform reference
        @return The transform reference
        */
		Transform & get_transform();

        /**
        @brief Gets the original vertices reference
        @return The original vertices reference
        */
        std::vector<toolkit::Point4f>& get_original_vertices()
        {
            return original_vertices;
        }

        /**
        @brief Gets the transformed vertices reference
        @return The transformed vertices reference
        */
        std::vector<toolkit::Point4f> & get_transformed_vertices()
        {
            return transformed_vertices;
        }

        /**
        @brief Gets the original normals reference
        @return The original normals reference
        */
        std::vector<toolkit::Vector4f> & get_original_normals()
        {
            return original_normals;
        }

        /**
        @brief Gets the transformed normals reference
        @return The transformed normals reference
        */
        std::vector<toolkit::Vector4f> & get_transformed_normals()
        {
            return transformed_normals;
        }      

        /**
        @brief Update the model
        @param delta The delta time
        @param view The view reference
        */
		void Update(float delta, class View& view);		

        /**
        @brief Render the model
        @param view The view reference
        */
        void Render(class View& view);

        /**
        @brief Gets the material reference of the given mesh by index
        @param index The index of the mesh to get the material attached to
        @return The material reference
        */
		class Material& get_material(size_t index);
	
	};
}
