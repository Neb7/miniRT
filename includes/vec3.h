/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:58:42 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/15 18:09:25 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec3	t_point;

// vec3/vec3_operator.c
extern t_vec3	vec3_div(t_vec3 a, t_vec3 b);
extern t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
extern t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
extern t_vec3	vec3_add(t_vec3 a, t_vec3 b);

// vec3/vec3_operator_scalar.c
extern t_vec3	vec3_sub_scalar(t_vec3 a, float scalar);
extern t_vec3	vec3_mul_scalar(t_vec3 a, float scalar);
extern t_vec3	vec3_div_scalar(t_vec3 a, float scalar);
extern t_vec3	vec3_add_scalar(t_vec3 a, float scalar);

// vec3/vec3_math.c
extern float	vec3_length(t_vec3 a);
extern float	vec3_squarred_length(t_vec3 a);
extern t_vec3	vec3_normalize(t_vec3 a);
extern float	vec3_dot(t_vec3 a, t_vec3 b);
extern t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
extern t_vec3	vec3_reflect(t_vec3 a, t_vec3 normal);
extern t_vec3	vec3_abs(t_vec3 a);

#endif