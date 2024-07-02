/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:49:58 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/24 16:58:25 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int keycode, t_var *var)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(var->mlx_ptr, var->win_ptr);
		exit(0);
	}
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		trans_hook(keycode, var);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		scale_hook(keycode, var);
	else if (keycode >= KEY_ROTATE_X && keycode <= KEY_ROTATE_Z)
		rotation_hook(keycode, var);
	return (0);
}

static int	exit_window(t_var *var)
{
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	exit(0);
}

void	set_image(t_var *var)
{
	var->image.img_ptr = mlx_new_image(var->mlx_ptr, WIN_W, WIN_H);
	var->image.addr = mlx_get_data_addr(var->image.img_ptr, \
	&var->image.bits_per_pixel, &var->image.size_line, &var->image.endian);
	draw_image(&var->image, var->map);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
	var->image.img_ptr, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_var	var;

	check_input_error(argc, argv[1]);
	var.map = init_map(argv[1]);
	transform_matrix(var.map);
	var.mlx_ptr = mlx_init();
	var.win_ptr = mlx_new_window(var.mlx_ptr, WIN_W, WIN_H, "FDF");
	set_image(&var);
	mlx_hook(var.win_ptr, 2, 0, key_hook, &var);
	mlx_hook(var.win_ptr, 17, 0, exit_window, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
