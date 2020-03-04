/*
 * File: Transform.cpp
 * File Created: 27th February 2020
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

#include <Transform.hpp>

namespace Rendering3D
{
    /**
    @brief Updates the transform
    */
    void Transform::update_transform()
    {
        scaling.set(scale);
                
        rot_speed += angular_speed;

        rotation_x.set<toolkit::Rotation3f::AROUND_THE_X_AXIS>(initial_rotation.coordinates().get_values()[0] + rot_speed * rotation_axis.coordinates().get_values()[0]);
        rotation_y.set<toolkit::Rotation3f::AROUND_THE_Y_AXIS>(initial_rotation.coordinates().get_values()[1] + rot_speed * rotation_axis.coordinates().get_values()[1]);
        rotation_z.set<toolkit::Rotation3f::AROUND_THE_Z_AXIS>(initial_rotation.coordinates().get_values()[2] + rot_speed * rotation_axis.coordinates().get_values()[2]);
                
        tran_speed += translation_speed;

        toolkit::Vector3f new_position{ {
                                            initial_position.coordinates().get_values()[0] + tran_speed * translation_axis.coordinates().get_values()[0],
                                            initial_position.coordinates().get_values()[1] + tran_speed * translation_axis.coordinates().get_values()[1],
                                            initial_position.coordinates().get_values()[2] + tran_speed * translation_axis.coordinates().get_values()[2]
                                        } };
        translation.set(new_position);

        if (parent != nullptr)
        {
            transformation = parent->get_transformation() * translation * rotation_x * rotation_y * rotation_z * scaling;
        }
        else
        {
            transformation = translation * rotation_x * rotation_y * rotation_z * scaling;
        }
    }

    /**
    @brief Calculates the inverse transformation
    */
    void Transform::calculate_inverse_transformation()
    {
        toolkit::Matrix44f transformation_copy(transformation);

        float matrix[16]
        {
            { transformation_copy[0][0] },{ transformation_copy[0][1] },{ transformation_copy[0][2] },{ transformation_copy[0][3] },
            { transformation_copy[1][0] },{ transformation_copy[1][1] },{ transformation_copy[1][2] },{ transformation_copy[1][3] },
            { transformation_copy[2][0] },{ transformation_copy[2][1] },{ transformation_copy[2][2] },{ transformation_copy[2][3] },
            { transformation_copy[3][0] },{ transformation_copy[3][1] },{ transformation_copy[3][2] },{ transformation_copy[3][3] }
        };

        float inverse[16], determinant;

        inverse[0] =    matrix[5]  * matrix[10] * matrix[15] -
                        matrix[5]  * matrix[11] * matrix[14] -
                        matrix[9]  * matrix[6]  * matrix[15] +
                        matrix[9]  * matrix[7]  * matrix[14] +
                        matrix[13] * matrix[6]  * matrix[11] -
                        matrix[13] * matrix[7]  * matrix[10];

        inverse[4] =  - matrix[4]  * matrix[10] * matrix[15] +
                        matrix[4]  * matrix[11] * matrix[14] +
                        matrix[8]  * matrix[6]  * matrix[15] -
                        matrix[8]  * matrix[7]  * matrix[14] -
                        matrix[12] * matrix[6]  * matrix[11] +
                        matrix[12] * matrix[7]  * matrix[10];

        inverse[8] =    matrix[4]  * matrix[9]  * matrix[15] -
                        matrix[4]  * matrix[11] * matrix[13] -
                        matrix[8]  * matrix[5]  * matrix[15] +
                        matrix[8]  * matrix[7]  * matrix[13] +
                        matrix[12] * matrix[5]  * matrix[11] -
                        matrix[12] * matrix[7]  * matrix[9];

        inverse[12] =  -matrix[4]  * matrix[9]  * matrix[14] +
                        matrix[4]  * matrix[10] * matrix[13] +
                        matrix[8]  * matrix[5]  * matrix[14] -
                        matrix[8]  * matrix[6]  * matrix[13] -
                        matrix[12] * matrix[5]  * matrix[10] +
                        matrix[12] * matrix[6]  * matrix[9];

        inverse[1] =   -matrix[1]  * matrix[10] * matrix[15] +
                        matrix[1]  * matrix[11] * matrix[14] +
                        matrix[9]  * matrix[2]  * matrix[15] -
                        matrix[9]  * matrix[3]  * matrix[14] -
                        matrix[13] * matrix[2]  * matrix[11] +
                        matrix[13] * matrix[3]  * matrix[10];

        inverse[5] =    matrix[0]  * matrix[10] * matrix[15] -
                        matrix[0]  * matrix[11] * matrix[14] -
                        matrix[8]  * matrix[2]  * matrix[15] +
                        matrix[8]  * matrix[3]  * matrix[14] +
                        matrix[12] * matrix[2]  * matrix[11] -
                        matrix[12] * matrix[3]  * matrix[10];

        inverse[9] =   -matrix[0]  * matrix[9]  * matrix[15] +
                        matrix[0]  * matrix[11] * matrix[13] +
                        matrix[8]  * matrix[1]  * matrix[15] -
                        matrix[8]  * matrix[3]  * matrix[13] -
                        matrix[12] * matrix[1]  * matrix[11] +
                        matrix[12] * matrix[3]  * matrix[9];

        inverse[13] =   matrix[0]  * matrix[9]  * matrix[14] -
                        matrix[0]  * matrix[10] * matrix[13] -
                        matrix[8]  * matrix[1]  * matrix[14] +
                        matrix[8]  * matrix[2]  * matrix[13] +
                        matrix[12] * matrix[1]  * matrix[10] -
                        matrix[12] * matrix[2]  * matrix[9];

        inverse[2] =    matrix[1]  * matrix[6] * matrix[15] -
                        matrix[1]  * matrix[7] * matrix[14] -
                        matrix[5]  * matrix[2] * matrix[15] +
                        matrix[5]  * matrix[3] * matrix[14] +
                        matrix[13] * matrix[2] * matrix[7] -
                        matrix[13] * matrix[3] * matrix[6];

        inverse[6] =   -matrix[0]  * matrix[6] * matrix[15] +
                        matrix[0]  * matrix[7] * matrix[14] +
                        matrix[4]  * matrix[2] * matrix[15] -
                        matrix[4]  * matrix[3] * matrix[14] -
                        matrix[12] * matrix[2] * matrix[7] +
                        matrix[12] * matrix[3] * matrix[6];

        inverse[10] =   matrix[0]  * matrix[5] * matrix[15] -
                        matrix[0]  * matrix[7] * matrix[13] -
                        matrix[4]  * matrix[1] * matrix[15] +
                        matrix[4]  * matrix[3] * matrix[13] +
                        matrix[12] * matrix[1] * matrix[7] -
                        matrix[12] * matrix[3] * matrix[5];

        inverse[14] =  -matrix[0]  * matrix[5] * matrix[14] +
                        matrix[0]  * matrix[6] * matrix[13] +
                        matrix[4]  * matrix[1] * matrix[14] -
                        matrix[4]  * matrix[2] * matrix[13] -
                        matrix[12] * matrix[1] * matrix[6] +
                        matrix[12] * matrix[2] * matrix[5];

        inverse[3] =   -matrix[1] * matrix[6] * matrix[11] +
                        matrix[1] * matrix[7] * matrix[10] +
                        matrix[5] * matrix[2] * matrix[11] -
                        matrix[5] * matrix[3] * matrix[10] -
                        matrix[9] * matrix[2] * matrix[7] +
                        matrix[9] * matrix[3] * matrix[6];

        inverse[7] =    matrix[0] * matrix[6] * matrix[11] -
                        matrix[0] * matrix[7] * matrix[10] -
                        matrix[4] * matrix[2] * matrix[11] +
                        matrix[4] * matrix[3] * matrix[10] +
                        matrix[8] * matrix[2] * matrix[7] -
                        matrix[8] * matrix[3] * matrix[6];

        inverse[11] =  -matrix[0] * matrix[5] * matrix[11] +
                        matrix[0] * matrix[7] * matrix[9] +
                        matrix[4] * matrix[1] * matrix[11] -
                        matrix[4] * matrix[3] * matrix[9] -
                        matrix[8] * matrix[1] * matrix[7] +
                        matrix[8] * matrix[3] * matrix[5];

        inverse[15] =   matrix[0] * matrix[5] * matrix[10] -
                        matrix[0] * matrix[6] * matrix[9] -
                        matrix[4] * matrix[1] * matrix[10] +
                        matrix[4] * matrix[2] * matrix[9] +
                        matrix[8] * matrix[1] * matrix[6] -
                        matrix[8] * matrix[2] * matrix[5];

        determinant = matrix[0] * inverse[0] + matrix[1] * inverse[4] + matrix[2] * inverse[8] + matrix[3] * inverse[12];
        determinant = 1.0f / determinant;

        inverse_transformation[0][0] = inverse[0] * determinant;
        inverse_transformation[0][1] = inverse[1] * determinant;
        inverse_transformation[0][2] = inverse[2] * determinant;
        inverse_transformation[0][3] = inverse[3] * determinant;
        inverse_transformation[1][0] = inverse[4] * determinant;
        inverse_transformation[1][1] = inverse[5] * determinant;
        inverse_transformation[1][2] = inverse[6] * determinant;
        inverse_transformation[1][3] = inverse[7] * determinant;
        inverse_transformation[2][0] = inverse[8] * determinant;
        inverse_transformation[2][1] = inverse[9] * determinant;
        inverse_transformation[2][2] = inverse[10] * determinant;
        inverse_transformation[2][3] = inverse[11] * determinant;
        inverse_transformation[3][0] = inverse[12] * determinant;
        inverse_transformation[3][1] = inverse[13] * determinant;
        inverse_transformation[3][2] = inverse[14] * determinant;
        inverse_transformation[3][3] = inverse[15] * determinant;        
    }   
}