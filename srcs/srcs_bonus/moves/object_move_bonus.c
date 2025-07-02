/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:21:48 by llemmel           #+#    #+#             */
/*   Updated: 2025/05/22 13:49:16 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief	Check if two points are close
 */
bool	vec3_point_close(t_point a, t_point b, \
	t_object *object, float delta_time)
{
	const t_vec3	offset = vec3_mul_scalar(object->dir, \
		object->speed * delta_time);
	const t_vec3	next_pos = vec3_add(get_object_origin(object), offset);
	const float		lenght_1 = vec3_squarred_length(vec3_sub(a, b));
	const float		lenght_2 = vec3_squarred_length(vec3_sub(a, next_pos));

	return (lenght_1 < 0.5f || lenght_2 >= lenght_1);
}

/**
 * @brief	Get the object origin object
 * 
 * @param	object Object to get the origin from
 * @return	t_vec3 The origin of the object
 */
t_vec3	get_object_origin(const t_object *object)
{
	if (object->type == SPHERE)
		return (((t_sphere *)object->data)->origin);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->data)->pos);
	else if (object->type == PLANE)
		return (((t_plane *)object->data)->origin);
	else if (object->type == CONE)
		return (((t_cone *)object->data)->pos);
	else
		return ((t_vec3){0, 0, 0});
}

/**
 * @brief	Get direction of the object to the point.
 * 
 * @param	object	The object to get the direction from
 * @return	t_vec3	The direction vector
 */
t_vec3	get_dir(t_object *object)
{
	return (vec3_normalize(vec3_sub(object->pos_list[object->i], \
		get_object_origin(object))));
}

/**
 * @brief	Move all objects who have a routine.
 * 
 * @param	object	The object to move
 * @param	delta_time The time since the last frame
 */
void	move(t_object *object, float delta_time)
{
	const t_vec3	offset = vec3_mul_scalar(object->dir, \
		object->speed * delta_time);
	const t_vec3	origin = get_object_origin(object);
	t_vec3			new_pos;

	if (vec3_squarred_length(vec3_sub(origin, vec3_add(origin, offset))) \
		>= vec3_squarred_length(vec3_sub(origin, object->pos_list[object->i])))
		new_pos = object->pos_list[object->i];
	else
		new_pos = vec3_add(origin, offset);
	if (object->type == SPHERE)
		((t_sphere *)object->data)->origin = new_pos;
	else if (object->type == CYLINDER)
		((t_cylinder *)object->data)->pos = new_pos;
	else if (object->type == PLANE)
		((t_plane *)object->data)->origin = new_pos;
	else if (object->type == CONE)
		((t_cone *)object->data)->pos = new_pos;
}
