/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:56:24 by psaprono          #+#    #+#             */
/*   Updated: 2018/07/04 14:56:47 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

t_col	conv_to_rgb(int rgb)
{
	t_col	color;

	color.b = rgb & 255;
	color.g = (rgb >> 8) & 255;
	color.r = (rgb >> 16) & 255;
	return (color);
}

int		conv_to_dec(t_col color)
{
	int	res;

	res = ((int)color.r << 16) + ((int)color.g << 8) + (int)color.b;
	return (res);
}

void		put_pix_to_img(t_woof *w, int x, int y, int color)
{
	if (x >= 0 && x < WID && y >= 0 && y < HGT)
		*(int *)(w->ims + ((x + y * WID) * 4)) = color;
}
