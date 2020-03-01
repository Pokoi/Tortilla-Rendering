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

#include <vector>			// For collections
#include <memory>			// For shared_ptr
#include <Material.hpp>		// For Material reference
#include <Point.hpp>        // For frontface check


namespace Rendering3D
{
    /**
    @brief Class that manages meshs
    */
	class Mesh
	{
        /**
        @brief The collection of indices of this mesh   
        */
		std::vector<int> indices;		
		
        /**
        @brief The material to apply to this mesh
        */
		Material		material;

        /**
        @brief A pointer to the model this mesh belongs to
        */
		class Model*	model;
			

	public:

        /**
        @brief Creates an instance of this class.
        @param indices The collecion of indices
        @param owner  A pointer to the model this mesh belongs to
        */
		Mesh (
				std::vector<int>	indices,				
				class Model    *	owner
			);

        /**
        @brief Render the mesh
        @param view A view reference this mesh belongs to
        */
		void Render(class View & view);

        /**
        @brief Sets the material
        @param material The given material
        */
		void set_material(Material material)
		{
			this->material = material;
		}

        /**
        @brief Gets a refence to the material
        @return A reference to the material
        */
		Material& get_material()
		{
			return material;
		}

    private:

        /**
        @brief Calculates if the polygon is frontface 
        @param projected_vertices the vertices of the polygon
        @param indices the indices
        @return True if is frontface, false otherwise
        */
        bool is_frontface(const toolkit::Point4f* const projected_vertices, const int* const indices);
        
        /**
        @brief Illuminate the mesh
        @param view The reference to the view
        */
        void illuminate(class View& view);        
        
        /**
        @brief Transform to normalize device coordinates
        */
        void NDC_transformation();

        /**
        @brief Transform coordinates to display coordinates
        @param width The width of the screen
        @param height The height of the screen
        */
        void display_coordinates_transformation(size_t width, size_t height);


	};
}