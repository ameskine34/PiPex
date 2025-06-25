/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:08:11 by ameskine          #+#    #+#             */
/*   Updated: 2025/02/07 18:38:33 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**after_cmd_split;
	char	*path;

	if (ft_strlen(cmd) == 0)
	{
		write(2, "command not found", 17);
		exit(127);
	}
	after_cmd_split = ft_split(cmd, ' ');
	path = get_path(after_cmd_split, env);
	if (execve(path, after_cmd_split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, after_cmd_split[0], ft_strlen(after_cmd_split[0]));
		write(2, "\n", 1);
		ft_free_all(after_cmd_split);
	}
}

void	first_child(char **av, char **env, int *pp_fd)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		write(2, "error in fd creation", 20);
		exit(1);
	}
	if (dup2(fd, 0) == -1)
	{
		write(2, "redirection fall from stdin", 27);
		exit(1);
	}
	if (dup2(pp_fd[1], 1) == -1)
	{
		write(2, "redirection to pipe fall write", 30);
		exit(1);
	}
	close(pp_fd[0]);
	close(pp_fd[1]);
	exec(av[2], env);
	exit(0);
}

void	second_child(char **av, char **env, int *pp_fd)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "error in fd creation", 20);
		exit(1);
	}
	if (dup2(fd, 1) == -1)
	{
		write(2, "redirection fall from stdout", 28);
		exit(1);
	}
	if (dup2(pp_fd[0], 0) == -1)
	{
		write(2, "redirection to pipe fall read", 29);
		exit(1);
	}
	close(pp_fd[1]);
	close(pp_fd[0]);
	exec(av[3], env);
	exit(127);
}

void	child_proccesses(int ac, char **av, char **env, int *pp_fd)
{
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		(write(2, "arguments problem", 17), exit(1));
	if (pipe(pp_fd) == -1)
		write(2, "error creating a pipe", 21);
	pid1 = fork();
	if (pid1 == -1)
		write(2, "problm creating a first_child", 29);
	if (pid1 == 0)
		first_child(av, env, pp_fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			write(2, "problm creating a second_child", 30);
		if (pid2 == 0)
			second_child(av, env, pp_fd);
	}
}

int	main(int ac, char **av, char **env)
{
	int	pp_fd[2];
	int	status;

	child_proccesses(ac, av, env, pp_fd);
	close(pp_fd[0]);
	close(pp_fd[1]);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
	return (0);
}
