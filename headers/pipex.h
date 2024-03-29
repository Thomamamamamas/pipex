/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:27:07 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/17 11:02:05 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "fcntl.h"
# include "../srcs/libftprintf/ft_printf.h" 
# include "../srcs/get_next_line/get_next_line.h"

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		fd_infile;
	int		fd_outfile;
	char	**path;
	char	***cmd;
	int		nb_cmd;
	int		is_heredoc;
	int		no_infile;
}			t_pipex;

//pipex
int		first_child_process_exec(t_pipex *t_px, int *fd, char **envp);
int		parent_process_exec(t_pipex *t_px, int *fd, char **envp);
int		single_fork(t_pipex *t_px, char **envp);
//parsing
void	parse_arg(t_pipex *t_px, int argc, char **argv, char **envp);
int		get_file_descriptor(t_pipex *t_px, char *file_name, int mode);
char	**get_path_variable(char **envp);
char	*get_correct_path(t_pipex *t_px, char **env, int nb_cmd);
//utils
void	free_t_pipex(t_pipex *t_px);
void	free_2d_str(char **str);
void	free_2d_int(int **array, int len);
//errors_gestion
void	end_pipex(t_pipex *t_px, int code);
int		check_cmd_file_valid(char *file_name);
int		error_management(int code);
int		check_file_valid(t_pipex *t_px);
//BONUS
//pipex_multi_pipes
int		multiple_fork(t_pipex *t_px, char **envp);
int		process_multi(t_pipex *t_px, int n, int **fds, char **envp);
//parsing_bonus
void	parse_arg_bonus(t_pipex *t_px, int argc, char **argv, char **envp);
void	check_mode(t_pipex *t_px);
int		get_file_descriptor_bonus(t_pipex *t_px, char *file_name, int mode);
int		check_file_valid_bonus(t_pipex *t_px);
//utils_multi_pipes
void	close_unused(t_pipex *t_px, int i, int **fds);
void	end_close_pipes(t_pipex *t_px, int n, int **fds);
int		dup_correct_fd(t_pipex *t_px, int **fds, int n);
int		**malloc_2d_array(int col, int line);
int		wait_subprocesses(t_pipex *t_px, int n, int **fds);
//utils2_multi_pipes
int		**pipes_2d_fd(t_pipex *t_px);
int		**heredoc_pipes_2d_fd(void);
void	heredoc_close_unused(t_pipex *t_px, int i, int **fds);
void	heredoc_end_close_pipes(t_pipex *t_px, int n, int **fds);

#endif
