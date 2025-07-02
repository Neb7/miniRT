/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mlx_moi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:18:45 by benpicar          #+#    #+#             */
/*   Updated: 2025/04/29 12:02:51 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MOI_H
# define MLX_MOI_H

void	main_loop(void *param);
void	resize(int32_t width, int32_t height, void *param);
void	my_keyhook(mlx_key_data_t keydata, void *param);

#endif