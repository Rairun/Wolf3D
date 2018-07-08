/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:07:51 by psaprono          #+#    #+#             */
/*   Updated: 2018/07/04 12:07:54 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

void	draw_line(t_woof *wof)
{
	for (int y = 0; y < HGT; y++)
	{
		for (int x = 0; x < WID; x++)
			put_pix_to_img(wof, x, y, wof->play.buffer[y * WID + x]);
	}
}

int		get_color_from_texture(t_texture texture, int position)
{
	return (*(int *)(texture.ims + position * 4));
}

void	lets_play(t_woof *wof)
{
	int x;
	for (int i = 0; i < HGT * WID; i++)
		wof->play.buffer[i] = 0;

	x = -1;
	while (++x < WID)
	{
		wof->play.camera[0] = 2 * x / (double)WID - 1;
		wof->play.ray_dir[0] = wof->play.dir[0] + wof->play.plane[0] * wof->play.camera[0];
		wof->play.ray_dir[1] = wof->play.dir[1] + wof->play.plane[1] * wof->play.camera[0];

		wof->play.map[0] = (int)wof->play.pos[0];
		wof->play.map[1] = (int)wof->play.pos[1];

		wof->play.delta_dist[0] = fabs(1.0 / wof->play.ray_dir[0]);
		wof->play.delta_dist[1] = fabs(1.0 / wof->play.ray_dir[1]);
		
		wof->play.hit = 0;

		if (wof->play.ray_dir[0] < 0)
		{
			wof->play.step[0] = -1;
			wof->play.side_dist[0] = (wof->play.pos[0] - wof->play.map[0]) * wof->play.delta_dist[0];
		}
		else
		{
			wof->play.step[0] = 1;
			wof->play.side_dist[0] = (wof->play.map[0] + 1.0 - wof->play.pos[0]) * wof->play.delta_dist[0];
		}

		if (wof->play.ray_dir[1] < 0)
		{
			wof->play.step[1] = -1;
			wof->play.side_dist[1] = (wof->play.pos[1] - wof->play.map[1]) * wof->play.delta_dist[1];
		}
		else
		{
			wof->play.step[1] = 1;
			wof->play.side_dist[1] = (wof->play.map[1] + 1.0 - wof->play.pos[1]) * wof->play.delta_dist[1];
		}

		while (wof->play.hit == 0)
		{
			if (wof->play.side_dist[0] < wof->play.side_dist[1])
			{
				wof->play.side_dist[0] += wof->play.delta_dist[0];
				wof->play.map[0] += wof->play.step[0];
				wof->play.side = 0;
			}
			else
			{
				wof->play.side_dist[1] += wof->play.delta_dist[1];
				wof->play.map[1] += wof->play.step[1];
				wof->play.side = 1;
			}
			if (wof->map->map[wof->play.map[0] * wof->map->width + wof->play.map[1]] > 0)
				wof->play.hit = 1;
		}
		if (wof->play.side == 0)
			wof->play.wall_dist = (wof->play.map[0] - wof->play.pos[0] + (1 - wof->play.step[0]) / 2) / wof->play.ray_dir[0];
		else
			wof->play.wall_dist = (wof->play.map[1] - wof->play.pos[1] + (1 - wof->play.step[1]) / 2) / wof->play.ray_dir[1];

		wof->play.line_height = (int)(HGT / wof->play.wall_dist);

		wof->play.draw[0] = -wof->play.line_height / 2 + HGT / 2;
		if (wof->play.draw[0] < 0)
			wof->play.draw[0] = 0;
		wof->play.draw[1] = wof->play.line_height / 2 + HGT / 2;
		if (wof->play.draw[1] >= HGT)
			wof->play.draw[1] = HGT - 1;
		int tex_num = wof->map->map[wof->play.map[0] * wof->map->width + wof->play.map[1]] - 1;
		double wall_x;
		if (wof->play.side == 0)
			wall_x = wof->play.pos[1] + wof->play.wall_dist * wof->play.ray_dir[1];
		else
			wall_x = wof->play.pos[0] + wof->play.wall_dist * wof->play.ray_dir[0];
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double)TEXW);
		if (wof->play.side == 0 && wof->play.ray_dir[0] > 0)
			tex_x = TEXW - tex_x - 1;
		if (wof->play.side == 1 && wof->play.ray_dir[1] < 0)
			tex_x = TEXW - tex_x - 1;
		for (int y = wof->play.draw[0]; y < wof->play.draw[1]; y++)
		{
			int d = y * 256 - HGT * 128 + wof->play.line_height * 128;
			int tex_y = ((d * TEXH) / wof->play.line_height) / 256;
			uint32_t color = get_color_from_texture(wof->play.texture[tex_num], TEXH * tex_y + tex_x);
			if (wof->play.side == 1)
				color = (color >> 1) & 8355711;
			wof->play.buffer[y * WID + x] = color;
		}
		
		double	flor_wall_x;
		double	flor_wall_y;

		if (wof->play.side == 0 && wof->play.ray_dir[0] > 0)
		{
			flor_wall_x = wof->play.map[0];
			flor_wall_y = wof->play.map[1] + wall_x;
		}
		else if (wof->play.side == 0 && wof->play.ray_dir[0] < 0)
		{
			flor_wall_x = wof->play.map[0] + 1.0;
			flor_wall_y = wof->play.map[1] + wall_x;
		}
		else if (wof->play.side == 1 && wof->play.ray_dir[1] > 0)
		{
			flor_wall_x = wof->play.map[0] + wall_x;
			flor_wall_y = wof->play.map[1];
		}
		else
		{
			flor_wall_x = wof->play.map[0] + wall_x;
			flor_wall_y = wof->play.map[1] + 1.0;
		}

		double	dist_wall;
		double	dist_player;
		double	curr_dist;
		double	weight;
		double	curr_flor_x;
		double	curr_flor_y;
		int		flor_tex_x;
		int		flor_tex_y;
		int		board;
		int		flor_texture;

		dist_wall = wof->play.wall_dist;
		dist_player = 0.0;

		if (wof->play.draw[1] < 0)
			wof->play.draw[1] = HGT;
		//если draw[0]
		for (int y = wof->play.draw[1] + 1; y < HGT; y++)
		{
			curr_dist = HGT / (2.0 * y - HGT);
			weight = (curr_dist - dist_player) / (dist_wall - dist_player);
			curr_flor_x = weight * flor_wall_x + (1.0 - weight) * wof->play.pos[0];
			curr_flor_y = weight * flor_wall_y + (1.0 - weight) * wof->play.pos[1];
			//can divide on number
			flor_tex_x = (int)(curr_flor_x * TEXW) % TEXW;
			flor_tex_y = (int)(curr_flor_y * TEXH) % TEXH;
			board = ((int)(curr_flor_x + curr_flor_y)) % 2;
			if (board == 0)
				flor_texture = 6;
			else
				flor_texture = 4;
			wof->play.buffer[y * WID + x] = (get_color_from_texture(wof->play.texture[flor_texture], TEXW * flor_tex_y + flor_tex_x) >> 1) & 8355711;
			wof->play.buffer[(HGT - y) * WID + x] = get_color_from_texture(wof->play.texture[flor_texture], TEXW * flor_tex_y + flor_tex_x);
		}
	}
	draw_line(wof);
	mlx_put_image_to_window(wof->mlx, wof->wnd, wof->imp, 0, 0);
}
