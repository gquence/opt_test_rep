/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <gquence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/07/31 16:52:44 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_julia(int x, int y, void *ptr_params)
{
	t_param_ptr	pr;

	pr = (t_param_ptr)ptr_params;
	if (pr->fractol == 2)
	{
		pr->c.r = x * 2 - (WIDTH / 2);
		pr->c.i = y * 2 - (WIDTH / 2);
		build_julia(ptr_params);
	}
	return (0);
}

void		julia_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.0;
	pr->pos.y = -2.0;
	pr->c.r = 0;
	pr->c.i = 1024;
	pr->max_iter = 50;
	pr->colour = green;
	build_julia((void *)pr);
}

t_complex	cc_add(t_complex a, t_complex b)
{
	t_complex res;

	res.r = a.r + b.r;
	res.i = a.i + b.i;
	return (res);
}

t_complex	cc_multiply(t_complex a, t_complex b)
{
	t_complex res;

	res.r = a.r * b.r - a.i * b.i;
	res.i = (a.r * b.i) + (b.r * a.i);
	return (res);
}

void	get_color_julia(t_point_2d *pos, t_param_ptr pr)
{
	int			it;
	t_complex	tmp;
	t_complex	z;

	it = 0;
	z.r = (double)(pos->x / pr->scale) + pr->pos.x;
	z.i = (double)(pos->y / pr->scale) + pr->pos.y;
	while (it < pr->max_iter && (z.r * z.r + z.i * z.i) < 8)
	{
		tmp.r = pr->c.r / (double)WIDTH - 0.5;
		tmp.i = pr->c.i / (double)WIDTH;
		z = cc_multiply(z, z);
		z = cc_add(z, tmp);
		it++;
	}
	if (it == pr->max_iter)
		pixelput_img(pr, pos, 0x000000);
	else
		pixelput_img(pr, pos, pr->colour * it);
}

int		build_julia(void *param)
{
	t_point_2d	pos;
	t_param		*pr;
	int			colour;

	pr = (t_param_ptr)param;
	pos.y = 0;
	while (pos.y++ < HEIGHT)
	{
		pos.x = 0;
		while (pos.x++ < WIDTH)
		{
			get_color_julia(&pos, pr);
		}
	}
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img, 0, 0);
	return (1);
}
