/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:38:14 by vinni             #+#    #+#             */
/*   Updated: 2023/05/29 16:38:50 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	ft_close_pipe(t_process *process)
{
	close(process->pipe_fd[0]);
	close(process->pipe_fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_process	process;

	if (argc != 5)
		return (ft_put_error("Invalid number of arguments", 0));
	process.infile_fd = open(argv[1], O_RDONLY);
	if (process.infile_fd < 0)
		return (ft_put_error(strerror(errno), argv[1]));
	process.outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (process.outfile_fd < 0)
		return (ft_put_error(strerror(errno), argv[4]));
	pipe(process.pipe_fd);
	process.envp_path = ft_find_path(envp);
	process.cmd_paths = ft_split(process.envp_path, ':');
	process.pid_1 = fork();
	if (process.pid_1 == 0)
		ft_first_command(process, argv, envp);
	process.pid_2 = fork();
	if (process.pid_2 == 0)
		ft_second_command(process, argv, envp);
	ft_close_pipe(&process);
	waitpid(process.pid_1, NULL, 0);
	waitpid(process.pid_2, NULL, 0);
	ft_free_parent(&process);
	return (0);
}
