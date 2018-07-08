/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woof.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 10:34:15 by psaprono          #+#    #+#             */
/*   Updated: 2018/06/09 10:34:17 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOOF_H
# define WOOF_H
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdbool.h>
# include "get_next_line.h"
# define WID 800
# define HGT 800
# define TEXW 64
# define TEXH 64

typedef double	t_fdot2 __attribute__((vector_size(sizeof(double)*2)));
typedef int		t_idot2 __attribute__((vector_size(sizeof(int)*2)));

typedef struct	s_col
{
	double		r;
	double		g;
	double		b;
}				t_col;

typedef	struct	s_texture
{
	void		*imp;
	char		*ims;
}				t_texture;

typedef struct	s_play
{
	t_fdot2		pos;
	t_fdot2		dir;
	t_fdot2		plane;
	t_fdot2		camera;
	t_fdot2		ray_dir;
	t_idot2		map;
	t_fdot2		side_dist;
	t_fdot2		delta_dist;
	double		wall_dist;
	t_idot2		step;
	int			hit;
	int			side;
	int			line_height;
	t_idot2		draw;
	int			color;
	t_col		rgb;
	t_fdot2		speed;
	uint32_t	*buffer;
	t_texture	texture[8];
}				t_play;

typedef struct	s_map
{
	int			height;
	int			width;
	int			*map;
}				t_map;

typedef struct  s_woof
{
    void		*mlx;
	void		*wnd;
	void		*imp;
	char		*ims;
	int			fd;
	t_map		*map;
	t_play		play;
}               t_woof;

bool			check_arg(int argc, char **argv, int *fd);
bool			get_file_data(t_woof *wof);
bool			get_map_data(t_woof *wof, char *line);
bool			get_inside_data(t_woof *wof);

void			init_binds(t_woof *wof);

void    		init_default(t_woof *wof);

t_col			conv_to_rgb(int rgb);
int				conv_to_dec(t_col color);
void			put_pix_to_img(t_woof *w, int x, int y, int color);
void			lets_play(t_woof *wof);

#endif
