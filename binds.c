/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 10:23:45 by psaprono          #+#    #+#             */
/*   Updated: 2018/05/28 10:23:47 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

void		move_fd(int k, t_woof *wof)
{
	if (k == 13)
	{
		if (!wof->map->map[(int)(wof->play.pos[0] + wof->play.dir[0] * wof->play.speed[0] * 7) * wof->map->height + (int)wof->play.pos[1]])
			wof->play.pos[0] += wof->play.dir[0] * wof->play.speed[0];
		if (!wof->map->map[(int)(wof->play.pos[1] + wof->play.dir[1] * wof->play.speed[0] * 7) + (int)wof->play.pos[0] * wof->map->height])
			wof->play.pos[1] += wof->play.dir[1] * wof->play.speed[0];
	}
	else if (k == 1)
	{
		if (!wof->map->map[(int)(wof->play.pos[0] - wof->play.dir[0] * wof->play.speed[0]) * wof->map->height + (int)wof->play.pos[1]])
			wof->play.pos[0] -= wof->play.dir[0] * wof->play.speed[0];
		if (!wof->map->map[(int)(wof->play.pos[1] - wof->play.dir[1] * wof->play.speed[0]) + (int)wof->play.pos[0] * wof->map->height])
			wof->play.pos[1] -= wof->play.dir[1] * wof->play.speed[0];
	}
	lets_play(wof);
}

void		move_lr(int k, t_woof *wof)
{
	t_fdot2	old_dir;
	t_fdot2	old_plane;

	old_dir = wof->play.dir;
	old_plane = wof->play.plane;
	if (k == 2)
	{
		wof->play.dir[0] = wof->play.dir[0] * cos(-wof->play.speed[1]) - wof->play.dir[1] * sin(-wof->play.speed[1]);
		wof->play.dir[1] = old_dir[0] * sin(-wof->play.speed[1]) + wof->play.dir[1] * cos(-wof->play.speed[1]);
		wof->play.plane[0] = wof->play.plane[0] * cos(-wof->play.speed[1]) - wof->play.plane[1] * sin(-wof->play.speed[1]);
		wof->play.plane[1] = old_plane[0] * sin(-wof->play.speed[1]) + wof->play.plane[1] * cos(-wof->play.speed[1]);
	}
	else if (k == 0)
	{
		wof->play.dir[0] = wof->play.dir[0] * cos(wof->play.speed[1]) - wof->play.dir[1] * sin(wof->play.speed[1]);
		wof->play.dir[1] = old_dir[0] * sin(wof->play.speed[1]) + wof->play.dir[1] * cos(wof->play.speed[1]);
		wof->play.plane[0] = wof->play.plane[0] * cos(wof->play.speed[1]) - wof->play.plane[1] * sin(wof->play.speed[1]);
		wof->play.plane[1] = old_plane[0] * sin(wof->play.speed[1]) + wof->play.plane[1] * cos(wof->play.speed[1]);
	}
	lets_play(wof);
}

static int	choice(int k, t_woof *wof)
{
	if (k == 53)
		exit(1);
	else if (k == 0 || k == 2)
		move_lr(k, wof);
	if (k == 1 || k == 13)
		move_fd(k, wof);
	return (1);
}

static int	exit_press(void)
{
	exit(1);
	return (1);
}

void		init_binds(t_woof *wof)
{
	mlx_hook(wof->wnd, 17, 1L << 17, exit_press, wof);
	mlx_hook(wof->wnd, 2, 5, choice, wof);
}	
