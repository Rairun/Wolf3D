/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:20:10 by psaprono          #+#    #+#             */
/*   Updated: 2018/07/04 12:20:12 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

t_texture   new_texture(t_woof *wof, char *name)
{
	t_texture	texture;
	int		a[4];

	a[0] = 32;
	a[1] = 64;
	texture.imp = mlx_xpm_file_to_image(wof->mlx, name, &a[1], &a[1]);
	texture.ims = mlx_get_data_addr(texture.imp, &a[0], &a[2], &a[3]);
	return (texture);
}

void    init_default(t_woof *wof)
{
	int		a[3];

	a[0] = 32;
	wof->mlx = mlx_init();
	wof->wnd = mlx_new_window(wof->mlx, WID, HGT, "wolf3d");
	wof->imp = mlx_new_image(wof->mlx, WID, HGT);
	wof->ims = mlx_get_data_addr(wof->imp, &a[0], &a[1], &a[2]);
	wof->play.pos = (t_fdot2){22, 11.5};
	wof->play.dir = (t_fdot2){-1, 0};
	wof->play.plane = (t_fdot2){0, 0.66};
	wof->play.speed = (t_fdot2){0.08, 0.05};
	if ((wof->play.buffer = (uint32_t *)malloc(WID * HGT * sizeof(uint32_t))) == NULL)
		ft_putendl("Error malloc buffer");
	//Запротектить
	wof->play.texture[0] = new_texture(wof, "./textures/bluestone.XPM");
	wof->play.texture[1] = new_texture(wof, "./textures/colorstone.XPM");
	wof->play.texture[2] = new_texture(wof, "./textures/eagle.XPM");
	wof->play.texture[3] = new_texture(wof, "./textures/greystone.XPM");
	wof->play.texture[4] = new_texture(wof, "./textures/mossy.XPM");
	wof->play.texture[5] = new_texture(wof, "./textures/purplestone.XPM");
	wof->play.texture[6] = new_texture(wof, "./textures/redbrick.XPM");
	wof->play.texture[7] = new_texture(wof, "./textures/wood.XPM");
	init_binds(wof);
}
