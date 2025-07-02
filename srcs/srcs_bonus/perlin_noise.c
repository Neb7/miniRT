/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:12:33 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 13:50:38 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief	This function take coordinates and hash 
 * it with the permutation table to get a gradient.
 * 
 * @param	i The x coordinate
 * @param	y The y coordinate
 * @param	iz The z coordinate
 * @return	t_vec3 The gradient vector
 */
static t_vec3	get_gradient(int x, int y, int z)
{
	static const int	perm[256] = {\
13, 80, 133, 82, 184, 247, 124, 176, 94, 173, 154, 43, 138, 40, 14, 16, \
159, 128, 35, 99, 96, 107, 235, 42, 17, 253, 255, 1, 48, 166, 50, 98, \
18, 86, 234, 245, 178, 63, 240, 61, 177, 248, 84, 6, 67, 149, 11, 93, \
62, 180, 20, 172, 121, 229, 218, 153, 182, 7, 125, 123, 126, 198, 242, 171, \
151, 101, 9, 58, 219, 187, 231, 252, 49, 69, 31, 53, 34, 215, 157, 51, \
214, 206, 165, 104, 38, 105, 78, 250, 3, 100, 0, 188, 230, 8, 232, 164, \
233, 194, 223, 160, 55, 2, 54, 37, 130, 209, 21, 10, 119, 224, 70, 28, \
251, 102, 146, 140, 132, 106, 142, 136, 30, 200, 108, 216, 189, 118, 45, 227, \
237, 243, 236, 217, 185, 225, 72, 115, 110, 85, 116, 66, 152, 77, 196, 39, \
162, 36, 145, 59, 120, 24, 76, 112, 111, 26, 137, 174, 220, 56, 19, 92, \
161, 204, 32, 87, 158, 179, 148, 141, 195, 109, 210, 205, 135, 156, 190, 97, \
144, 71, 228, 208, 47, 41, 75, 191, 5, 155, 202, 91, 57, 113, 246, 192, \
213, 139, 207, 175, 183, 143, 170, 150, 181, 27, 23, 52, 212, 25, 169, 12, \
193, 46, 73, 89, 60, 199, 244, 88, 186, 117, 241, 167, 122, 64, 254, 222, \
81, 4, 134, 29, 201, 74, 79, 226, 129, 211, 127, 65, 131, 95, 33, 168, \
249, 68, 238, 147, 15, 221, 203, 22, 90, 197, 114, 103, 83, 239, 163, 44 \
};
	static const t_vec3	grad[12] = {\
		{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, \
		{1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, \
		{0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1} \
	};

	return (grad[(perm[(perm[(perm[x & 255] + y) & 255] + z) & 255]) % 12]);
}

/**
 * @brief	Calculate the dot product for all corners of the cube
 * 
 * @param	dots Array of all the dot product for each corner
 * @param	pos The position of the cube
 * @param	fpos The position of the point inside the cube
 */
static void	get_dots(float dots[8], t_vec3 pos, t_vec3 fpos)
{
	int		i;
	int		j;
	int		k;
	t_vec3	gradient;
	t_vec3	distance;

	i = -1;
	while (++i <= 1)
	{
		j = -1;
		while (++j <= 1)
		{
			k = -1;
			while (++k <= 1)
			{
				gradient = get_gradient(pos.x + i, pos.y + j, pos.z + k);
				distance = (t_vec3){fpos.x - i, fpos.y - j, fpos.z - k};
				dots[i * 4 + j * 2 + k] = vec3_dot(gradient, distance);
			}
		}
	}
}

/**
 * @brief	Calculate the value of the noise at a given point
 * 
 * This function calculates weight for each axis using the
 * perlin_noise_interpolation function.
 * 
 * The value is calculated by interpolating the dot product
 * for each corner of the cube using the weights.
 * 
 * @param	dots The dot product for each corner of the cube
 * @param	fpos The position of the point inside the cubes
 * @return	float The value of the noise at the given point
 */
static float	get_value(const float dots[8], t_vec3 fpos)
{
	const t_vec3	weight = (t_vec3){perlin_noise_interpolation(fpos.x), \
							perlin_noise_interpolation(fpos.y), \
							perlin_noise_interpolation(fpos.z)};
	const float		x[4] = {
		lerp(dots[0], dots[1], weight.z), \
		lerp(dots[2], dots[3], weight.z), \
		lerp(dots[4], dots[5], weight.z), \
		lerp(dots[6], dots[7], weight.z)};
	const float		y[2] = {lerp(x[0], x[1], weight.y), \
						lerp(x[2], x[3], weight.y)};

	return (lerp(y[0], y[1], weight.x));
}

/**
 * @brief	Calculate the perlin noise at a given point
 * 
 * @param	p The point to calculate the noise at
 * @return	float The value of the noise at the given point
 */
float	perlin_noise_at_point(t_vec3 p)
{
	float			value;
	const t_vec3	pos = {floorf(p.x), floorf(p.y), floorf(p.z)};
	const t_vec3	fpos = (t_vec3){p.x - pos.x, p.y - pos.y, p.z - pos.z};
	float			dots[8];

	get_dots(dots, pos, fpos);
	value = get_value(dots, fpos);
	return ((value + 1.0f) * 0.5f);
}
