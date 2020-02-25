/*
 * File: Dither.cpp
 * File Created: 25th February 2020
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



#include <math.h>
#include <algorithm>  // For std::sort() 
#include <map>        // For associative container, std::map<> 

#include <Vector.hpp>

/*

// Threshold map
static const unsigned char map[8 * 8] = {
     0,48,12,60, 3,51,15,63,
    32,16,44,28,35,19,47,31,
     8,56, 4,52,11,59, 7,55,
    40,24,36,20,43,27,39,23,
     2,50,14,62, 1,49,13,61,
    34,18,46,30,33,17,45,29,
    10,58, 6,54, 9,57, 5,53,
    42,26,38,22,41,25,37,21 };

// Color palette
static const unsigned color_palette[16] =
{ 0x080000,0x201A0B,0x432817,0x492910, 0x234309,0x5D4F1E,0x9C6B20,0xA9220F,
  0x2B347C,0x2B7409,0xD0CA40,0xE8A077, 0x6A94AB,0xD5C4B3,0xFCE76E,0xFCFAE2 };

// Luminance for each palette entry, to be initialized as soon as the program begins
static unsigned luma[16];

bool PaletteCompareLuma(unsigned index1, unsigned index2)
{
    return luma[index1] < luma[index2];
}
double ColorCompare(int r1, int g1, int b1, int r2, int g2, int b2)
{
    double luma1 = (r1 * 299 + g1 * 587 + b1 * 114) / (255.0 * 1000);
    double luma2 = (r2 * 299 + g2 * 587 + b2 * 114) / (255.0 * 1000);
    double lumadiff = luma1 - luma2;
    double diffR = (r1 - r2) / 255.0, diffG = (g1 - g2) / 255.0, diffB = (b1 - b2) / 255.0;
    return (diffR * diffR * 0.299 + diffG * diffG * 0.587 + diffB * diffB * 0.114) * 0.75
        + lumadiff * lumadiff;
}
struct MixingPlan
{
    const unsigned n_colors = 16;
    unsigned colors[n_colors];
};
MixingPlan DeviseBestMixingPlan(unsigned color)
{
    MixingPlan result = { {0} };
    const unsigned src[3] = { color >> 16, (color >> 8) & 0xFF, color & 0xFF };
    unsigned proportion_total = 0;

    unsigned so_far[3] = { 0,0,0 };

    while (proportion_total < MixingPlan::n_colors)
    {
        unsigned chosen_amount = 1;
        unsigned chosen = 0;

        const unsigned max_test_count = std::max(1u, proportion_total);

        double least_penalty = -1;
        for (unsigned index = 0; index < 16; ++index)
        {
            const unsigned color = color_palette[index];
            unsigned sum[3] = { so_far[0], so_far[1], so_far[2] };
            unsigned add[3] = { color >> 16, (color >> 8) & 0xFF, color & 0xFF };
            for (unsigned p = 1; p <= max_test_count; p *= 2)
            {
                for (unsigned c = 0; c < 3; ++c) sum[c] += add[c];
                for (unsigned c = 0; c < 3; ++c) add[c] += add[c];
                unsigned t = proportion_total + p;
                unsigned test[3] = { sum[0] / t, sum[1] / t, sum[2] / t };
                double penalty = ColorCompare(src[0], src[1], src[2],
                    test[0], test[1], test[2]);
                if (penalty < least_penalty || least_penalty < 0)
                {
                    least_penalty = penalty;
                    chosen = index;
                    chosen_amount = p;
                }
            }
        }
        for (unsigned p = 0; p < chosen_amount; ++p)
        {
            if (proportion_total >= MixingPlan::n_colors) break;
            result.colors[proportion_total++] = chosen;
        }

        const unsigned color = color_palette[chosen];
        unsigned palcolor[3] = { color >> 16, (color >> 8) & 0xFF, color & 0xFF };

        for (unsigned c = 0; c < 3; ++c)
            so_far[c] += palcolor[c] * chosen_amount;
    }
    // Sort the colors according to luminance
    std::sort(result.colors, result.colors + MixingPlan::n_colors, PaletteCompareLuma);
    return result;
}

*/

