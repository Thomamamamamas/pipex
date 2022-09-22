/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:27:07 by tcasale           #+#    #+#             */
/*   Updated: 2022/09/22 13:06:05 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "fcntl.h"
# include "../srcs/libftprintf/ft_printf.h" 

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		fd_infile;
	int		fd_outfile;
	char	**path;
	char	***cmd;
	int		nb_cmd;
}			t_pipex;

//pipex
int				first_child_process_exec(t_pipex *t_px, int *fd, char **envp);
int				parent_process_exec(t_pipex *t_px, int *fd, char **envp);
int				single_fork(t_pipex *t_px, char **envp);
int				multiple_fork(t_pipex *t_px, char **envp);
//pipex_utils1
t_pipex			parse_arg(int argc, char **argv, char **envp);
void			free_t_pipex(t_pipex *t_px);
void			free_2d_str(char **str);
char			*get_path(t_pipex *t_px, char **env, int nb_cmd);
//pipex_debug
void			print_t_pipex(t_pipex t_px);

#endif
