/*
 * File: Clipping.hpp
 * File Created: 14th February 2020
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

#include <Point.hpp>


namespace Rendering3D
{
    enum class LimitTypes {horizontal, vertical, diagonal};

    struct Limit
    {
        toolkit::Point4i origin;
        toolkit::Point4i end;
        LimitTypes type;

        Limit(toolkit::Point4i origin, toolkit::Point4i end, LimitTypes type) : origin{ origin }, end{ end }, type{ type }
        {  }

        bool intersects(toolkit::Point4i other_origin, toolkit::Point4i other_end)
        {
            return (*this < other_origin && *this > other_end) || (*this > other_origin && *this < other_end);
        }

        bool operator < (toolkit::Point4i point)
        {
            if (type == LimitTypes::horizontal)
            {
                return origin.coordinates().get_values()[1] <= point.coordinates().get_values()[1];
            }
            else if (type == LimitTypes::vertical)
            {
                return origin.coordinates().get_values()[0] <= point.coordinates().get_values()[0];
            }
            else if (type == LimitTypes::diagonal)
            {
                // To implement
                return false;
            }
        }

        bool operator > (toolkit::Point4i point)
        {
            if (type == LimitTypes::horizontal)
            {
                return origin.coordinates().get_values()[1] > point.coordinates().get_values()[1];
            }
            else if (type == LimitTypes::vertical)
            {
                return origin.coordinates().get_values()[0] > point.coordinates().get_values()[0];
            }
            else if (type == LimitTypes::diagonal)
            {
                // To implement
                return false;
            }
        }

		toolkit::Point4i intersection_point(toolkit::Point4i other_origin, toolkit::Point4i other_end)
		{
			// Line of this limit is a1x + b1y = c1
			double a1 = end.coordinates().get_values()[1] - origin.coordinates().get_values()[1];
			double b1 = origin.coordinates().get_values()[0] - end.coordinates().get_values()[0];
			double c1 = a1 * (origin.coordinates().get_values()[0]) + b1 * (origin.coordinates().get_values()[1]);
		
			// Line between the given point is a2x + b2y = c2
			double a2 = other_end.coordinates().get_values()[1] - other_origin.coordinates().get_values()[1];
			double b2 = other_origin.coordinates().get_values()[0] - other_end.coordinates().get_values()[0];
			double c2 = a2 * (other_origin.coordinates().get_values()[0]) + b2 * (other_origin.coordinates().get_values()[1]);

			double determinant = a1 * b2 - a2 * b1;
			
			double x = (b2 * c1 - b1 * c2) / determinant;
			double y = (a1 * c2 - a2 * c1) / determinant;

			// Calculate the z coordinate in base of interpolation progress
			double z = other_origin.coordinates().get_values()[2] + (x / (other_end.coordinates().get_values()[0] - other_origin.coordinates().get_values()[0]))* (other_end.coordinates().get_values()[2] - other_origin.coordinates().get_values()[2]);

			return { {(int)x,(int)y,(int)z,1} };
		
		}

    };

    class Clipping
    {

    public:

        static Clipping& get()
        {
            static Clipping instance = Clipping();
            return instance;            
        }


    private:

        Clipping() {}

    public:

        int polygon_clipper(
            toolkit::Point4i           *    vertices,
            const int                  *    first,
            const int                  *    last,
            const int	                    viewport_width,
            const int	                    viewport_height,
            std::vector<toolkit::Point4i> & clipped_vertices
        )
        {
            std::vector<toolkit::Point4i> input;
            std::vector<toolkit::Point4i> output;
            
            // Set the first input with all the vertices of the polygon
            for (const int* index = first; index < last; ++index)
            {
                input.push_back(vertices[*index]);
            }
            
            // Bottom limit check
            check_bottom_limit(input, output, { { {0, 0, 0, 1} }, { { viewport_width, 0, 0, 1 } }, LimitTypes::horizontal });
            reset_input_output(input, output);

            // Right limit check
			check_right_limit(input, output, { { {viewport_width, 0, 0, 1} }, { { viewport_width, viewport_height, 0, 1 } }, LimitTypes::vertical });
			reset_input_output(input, output);
			
            // Top limit check
			check_top_limit(input, output, { { {0, viewport_height, 0, 1} }, { { viewport_width, viewport_height, 0, 1 } }, LimitTypes::horizontal });
			reset_input_output(input, output);

            // Left limit check
			check_left_limit(input, output, { { {0, 0, 0, 1} }, { { 0, viewport_height, 0, 1 } }, LimitTypes::vertical });
			reset_input_output(input, output);

            // Copy to clipped_vertices
            for (toolkit::Point4i vertex : input)
            {
                clipped_vertices.push_back(vertex);
            }

            return clipped_vertices.size();
        }

        void check_bottom_limit   (
                                        std::vector<toolkit::Point4i>& input,
                                        std::vector<toolkit::Point4i>& output,
                                        Limit limit
                                   )
        {           
            if (input.size() > 0)
            {

                for (int index = 0; index < input.size() - 1; ++index)
                {           
                    // Check if point is inside
                    if (limit < input[index])
                    {
                        output.push_back(input[index]);
                    }

                    // Check if point and next point intersects limit                
                    if (limit.intersects(input[index], input[index + 1]))
                    {
					    output.push_back(limit.intersection_point(input[index], input[index + 1]));
                    }                   

                }

                // Check if last point is inside
                if (limit < input[input.size() - 1])
                {
                    output.push_back(input[input.size() - 1]);
                }

                // Check if last point and first point intersects limit                
                if (limit.intersects(input[input.size() - 1], input[0]))
                {
				    output.push_back(limit.intersection_point(input[input.size() - 1], input[0]));
                }         
                
            }
        }

		void check_right_limit(
			std::vector<toolkit::Point4i>& input,
			std::vector<toolkit::Point4i>& output,
			Limit limit
		)
		{
            if (input.size() > 0)
            {
                for (int index = 0; index < input.size() - 1; ++index)
                {
                    // Check if point is inside
                    if (limit > input[index])
                    {
                        output.push_back(input[index]);
                    }

                    // Check if point and next point intersects limit                
                    if (limit.intersects(input[index], input[index + 1]))
                    {
                        output.push_back(limit.intersection_point(input[index], input[index + 1]));
                    }
                }

                // Check if last point is inside
                if (limit > input[input.size() - 1])
                {
                    output.push_back(input[input.size() - 1]);
                }

                // Check if last point and first point intersects limit                
                if (limit.intersects(input[input.size() - 1], input[0]))
                {
                    output.push_back(limit.intersection_point(input[input.size() - 1], input[0]));
                }
            }
		}

		void check_top_limit(
			std::vector<toolkit::Point4i>& input,
			std::vector<toolkit::Point4i>& output,
			Limit limit
		)
		{
            if (input.size() > 0)
            {

			    for (int index = 0; index < input.size() - 1; ++index)
			    {
				    // Check if point is inside
				    if (limit > input[index])
				    {
					    output.push_back(input[index]);
				    }

				    // Check if point and next point intersects limit                
				    if (limit.intersects(input[index], input[index + 1]))
				    {
					    output.push_back(limit.intersection_point(input[index], input[index + 1]));
				    }		

			    }

			    // Check if last point is inside
			    if (limit > input[input.size() - 1])
			    {
				    output.push_back(input[input.size() - 1]);
			    }

			    // Check if last point and first point intersects limit                
			    if (limit.intersects(input[input.size() - 1], input[0]))
			    {
				    output.push_back(limit.intersection_point(input[input.size() - 1], input[0]));
			    }
            }
		}

		void check_left_limit(
			std::vector<toolkit::Point4i>& input,
			std::vector<toolkit::Point4i>& output,
			Limit limit
		)
		{
            if (input.size() > 0)
            {

			    for (int index = 0; index < input.size() - 1; ++index)
			    {
				    // Check if point is inside
				    if (limit < input[index])
				    {
					    output.push_back(input[index]);
				    }

				    // Check if point and next point intersects limit                
				    if (limit.intersects(input[index], input[index + 1]))
				    {
					    output.push_back(limit.intersection_point(input[index], input[index + 1]));
				    }				
			    }

			    // Check if last point is inside
			    if (limit < input[input.size() - 1])
			    {
				    output.push_back(input[input.size() - 1]);
			    }

			    // Check if last point and first point intersects limit                
			    if (limit.intersects(input[input.size() - 1], input[0]))
			    {
				    output.push_back(limit.intersection_point(input[input.size() - 1], input[0]));
			    }

            }
		}
        
        void reset_input_output(std::vector<toolkit::Point4i>& input, std::vector<toolkit::Point4i>& output)
        {
            input.swap(output);
            output.clear();
        }

    };
}