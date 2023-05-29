/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:08:09 by vinni             #+#    #+#             */
/*   Updated: 2023/05/29 16:36:49 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>

char	*ft_get_command(char **paths, char *command_name)
{
	char	*temp;
	char	*command;
	
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, command_name);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	ft_first_command(t_process process, char **argv, char **envp)
{
	close(process.pipe_fd[0]);
	dup2(process.pipe_fd[1], STDOUT_FILENO);
	dup2(process.infile_fd, STDIN_FILENO);
	process.cmd_args = ft_split(argv[2], ' ');
	process.command = ft_get_command(process.cmd_paths, process.cmd_args[0]);
	if (!process.command)
	{
		ft_free_child(&process);
		ft_error_message("Command not found\n");
		exit(1);
	}
	execve(process.command, process.cmd_args, envp);
}

void	ft_second_command(t_process process, char **argv, char **envp)
{
	close(process.pipe_fd[1]);
	dup2(process.pipe_fd[0], STDIN_FILENO);
	dup2(process.outfile_fd, STDOUT_FILENO);
	process.cmd_args = ft_split(argv[3], ' ');
	process.command = ft_get_command(process.cmd_paths, process.cmd_args[0]);
	if (!process.command)
	{
		ft_free_child(&process);
		ft_error_message("Command not found\n");
		exit(1);
	}
	execve(process.command, process.cmd_args, envp);
}
