/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:08:40 by vinni             #+#    #+#             */
/*   Updated: 2023/05/24 21:22:08 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_process
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	char	*envp_path;
	char	*command;
	char	**cmd_paths;
	char	**cmd_args;
}	t_process;

void	ft_first_command(t_process process, char **argv, char **envp);
void	ft_second_command(t_process process, char **argv, char **envp);

char	*ft_find_path(char **envp);
char	*ft_get_command(char **paths, char *command_name);

#endif
