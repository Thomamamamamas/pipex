/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:30 by tcasale           #+#    #+#             */
/*   Updated: 2022/06/24 18:02:33 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	first_child_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int		n;
	char	**env;
	char	*path;

	n = 0;
	if (dup2(t_px->fd_infile, 0) < 0 || dup2(fd[1], 1) < 0)
		return (-1);
	while (ft_strstr(envp[n], "PATH=") == 0)
		n++;
	env = ft_split(ft_substr(envp[n], 5, 500), ':');
	path = get_path(t_px, env, 0);
	if (path == NULL)
	{
		return (-1);
	}
	close(fd[0]);
	execve(path, t_px->cmd[0], envp);
	free(path);
	free_2d_str(env);
	exit(EXIT_FAILURE);
}

int	parent_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int		n;
	int		status;
	char	**env;
	char	*path;

	waitpid(-1, &status, 0);
	n = 0;
	if (dup2(fd[0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
		return (-1);
	while (ft_strstr(envp[n], "PATH=") == 0)
		n++;
	env = ft_split(ft_substr(envp[n], 5, 500), ':');
	path = get_path(t_px, env, t_px->nb_cmd - 1);
	if (path == NULL)
		return (-1);
	close(fd[1]);
	execve(path, t_px->cmd[t_px->nb_cmd - 1], envp);
	free_2d_str(env);
	free(path);
	exit(EXIT_FAILURE);
}

int	single_fork(t_pipex *t_px, char **envp)
{
	int	id;
	int	res;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id != 0)
	{
		res = parent_process_exec(t_px, fd, envp);
	}
	else
	{
		res = first_child_process_exec(t_px, fd, envp);
	}
	return (res);
}

int	multiple_fork(t_pipex *t_px, char **envp)
{
	printf("%s\n", t_px->cmd[0][0]);
	printf("%s\n", envp[0]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	int		res;

	if (argc >= 3)
	{
		t_px = parse_arg(argc, argv, envp);
		if (t_px.nb_cmd > 2)
			res = multiple_fork(&t_px, envp);
		else if (t_px.nb_cmd == 2)
			res = single_fork(&t_px, envp);
		else
			res = -1;
		free_t_pipex(&t_px);
	}
	else
		res = -1;
	if (res != 0)
	{
		perror("");
		return (-1);
	}
	return (0);
}
