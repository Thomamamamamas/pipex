/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:38 by tcasale           #+#    #+#             */
/*   Updated: 2022/09/22 13:27:29 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	free_t_pipex(t_pipex *t_px)
{
	int	n;

	n = 0;
	free(t_px->infile);
	free(t_px->outfile);
	while (n < t_px->nb_cmd)
		free(t_px->cmd[n++]);
	free(t_px->cmd);
}

void	free_2d_str(char **str)
{
	int	n;

	n = 0;
	while (str[n] == NULL)
	{
		free(str[n]);
		n++;
	}
	free(str);
}