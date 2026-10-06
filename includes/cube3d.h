/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:19:31 by schouite          #+#    #+#             */
/*   Updated: 2026/10/06 20:14:30 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#ifndef CUBE3D_H
# define CUBE3D_H

# define READ_SIZE 4096
# define WIDTH 800
# define HEIGHT 600
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_pixel
{
	int			colore;
	int			wall_y;
	double		ratio;
	int			tex_y;
}				t_pixel;

typedef struct s_wall
{
	int			height;
	int			width;
	int			start;
	int			end;

}				t_wall;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_lenght;
	int			endian;
}				t_data;

typedef struct s_texture
{
	int			width;
	int			height;
	t_data		data;
}				t_texture;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	double		perp;
	double		camera_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_ray;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			map_width;
	int			map_height;
	char		*tex[4];
	int			floor;
	int			ceiling;
	t_wall		wall;
	t_player	player;
	t_data		data;
	t_ray		ray;
	t_texture	texture[4];
}				t_game;

int				init_one_texture(t_game *game, int tex);
int				init_texture(t_game *game);
int				get_texture_face(t_game *game);
int				get_texture_pixel(t_game *game, int tex_x, int tex_y, int face);
int				parse_file(char *path, t_game *game);
int				parse_elements(char **lines, t_game *game);
int				parse_color(char *s, int *dst);
int				parse_map(char **lines, t_game *game);
int				check_walls(t_game *game);
char			*read_file(char *path);
char			**split_lines(char *s);
int				parse_error(char *msg);
int				is_blank(char *line);
int				has_extension(char *path, char *ext);
void			free_tab(char **tab);
void			free_game(t_game *game);
void			dda(t_game *game);
int				handle_key(int keycode, void *param);
void			draw_wall(t_game *game, int x);
void			raycast(t_game *game);
int				rendering(t_game *game);
int				init_mlx(t_game *game);
void			my_mlx_put_to_pixel(t_game *game, int x, int y, int pxl);
#endif