/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:46:34 by jgoo              #+#    #+#             */
/*   Updated: 2024/02/12 12:46:37 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	trans_hook(int keycode, t_var *var)
{
	mlx_destroy_image(var->mlx_ptr, var->image.img_ptr);
	if (keycode == KEY_LEFT)
	{
		translate_transform(var->map, -TRAN, 0);
		var->map->start_x -= TRAN;
	}
	else if (keycode == KEY_RIGHT)
	{
		translate_transform(var->map, TRAN, 0);
		var->map->start_x += TRAN;
	}
	else if (keycode == KEY_DOWN)
	{
		translate_transform(var->map, 0, TRAN);
		var->map->start_y += TRAN;
	}
	else if (keycode == KEY_UP)
	{
		translate_transform(var->map, 0, -TRAN);
		var->map->start_y -= TRAN;
	}
	set_image(var);
}

void	scale_hook(int keycode, t_var *var)
{
	mlx_destroy_image(var->mlx_ptr, var->image.img_ptr);
	if (keycode == KEY_PLUS)
	{
		scale_transform(var->map, RATIO_P);
		calculate_max(var->map);
		calculate_start_trans(var->map, var->map->start_x, var->map->start_y);
		translate_transform(var->map, var->map->start_x_trans, \
		var->map->start_y_trans);
		var->map->scale_cnt++;
	}
	else if (keycode == KEY_MINUS)
	{
		scale_transform(var->map, RATIO_M);
		calculate_max(var->map);
		calculate_start_trans(var->map, var->map->start_x, var->map->start_y);
		translate_transform(var->map, var->map->start_x_trans, \
		var->map->start_y_trans);
		var->map->uscale_cnt++;
	}
	set_image(var);
}

void	rotation_hook(int keycode, t_var *var)
{
	mlx_destroy_image(var->mlx_ptr, var->image.img_ptr);
	if (keycode == KEY_ROTATE_X)
		rotation_loop(var->map, X);
	else if (keycode == KEY_ROTATE_Y)
		rotation_loop(var->map, Y);
	else if (keycode == KEY_ROTATE_Z)
		rotation_loop(var->map, Z);
	set_image(var);
}

void	rotation_loop(t_map *map, int c)
{
	copy_matrix_values(map, &map->matrix, &map->back_up);
	if (c == X)
	{
		map->start_rot_x += M_PI / 6;
		init_rx_matrix(map->la_matrix->r_matrix, map->start_rot_x);
	}
	else if (c == Y)
	{
		map->start_rot_y += M_PI / 6;
		init_ry_matrix(map->la_matrix->r_matrix, map->start_rot_y);
	}
	else if (c == Z)
	{
		map->start_rot_z += M_PI / 6;
		init_rz_matrix(map->la_matrix->r_matrix, map->start_rot_z);
	}
	calculate_matrix(map, map->la_matrix->r_matrix);
	rscale_transform(map);
	calculate_max(map);
	calculate_start_trans(map, map->start_x, map->start_y);
	translate_transform(map, map->start_x_trans, map->start_y_trans);
}
