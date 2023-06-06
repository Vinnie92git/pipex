/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:02:41 by vinni             #+#    #+#             */
/*   Updated: 2023/05/29 16:33:34 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>

void	ft_free_child(t_process *process)
{
	int	i;

	i = 0;
	while (process->cmd_args[i])
	{
		free(process->cmd_args[i]);
		i++;
	}
	free(process->cmd_args);
	free(process->command);
}

void	ft_free_parent(t_process *process)
{
	int i;

	i = 0;
	close(process->infile_fd);
	close(process->outfile_fd);
	while (process->cmd_paths[i])
	{
		free(process->cmd_paths[i]);
		i++;
	}
	free(process->cmd_paths);
}

int	ft_error_message(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}

int	ft_put_error(char *s, char *t)
{
	if (!s)
		return (2);
	if (t)
	{
		write(2, "-bash: ", 7);
		write(2, t, ft_strlen(t));
		write(2, ": ", 2);
	}
	while (*s)
	{
		write(2, &(*s), 1);
		s++;
	}
	write(2, "\n", 1);
	return (2);
}
