/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:19:31 by schouite          #+#    #+#             */
/*   Updated: 2026/10/01 18:43:20 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define READ_SIZE 4096
# define WIDTH 800
# define HEIGHT 600
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_lenght;
	int			endian;
}				t_data;

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
	char		**map;
	int			map_width;
	int			map_height;
	char		*tex[4];
	int			floor;
	int			ceiling;
	t_player	player;
	t_data		data;
	t_ray		ray;
}				t_game;

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
int				init_mlx(t_data *img, void **mlx_ptr, void **win_ptr);
void			my_mlx_put_to_pixel(t_game *game, int x, int y, int pxl);
#endif