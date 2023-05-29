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

int	main(int argc, char **argv, char **envp)
{
	t_process	process;

	if (argc < 5)
		return (ft_error_message("Invalid number of arguments\n"));
	process.infile_fd = open(argv[1], O_RDONLY);
	if (process.infile_fd < 0)
		ft_error(argv[1]);
	process.outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (process.outfile_fd < 0)
		ft_error(argv[4]);
	if (pipe(process.pipe_fd))
		ft_error("Pipe");
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
