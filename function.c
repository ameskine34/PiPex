/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:36:51 by ameskine          #+#    #+#             */
/*   Updated: 2025/02/05 06:47:31 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if ((s[i] == '\0'))
		{
			return (0);
		}
		i++;
	}
	return ((char *)&s[i]);
}

void	ft_free_all(char **f)
{
	size_t	i;

	i = 0;
	while (f[i])
	{
		free(f[i]);
		i++;
	}
	free(f);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char *path, char *cmd)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(path, "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(exec, F_OK | X_OK) == 0)
		return (exec);
	else
	{
		free(exec);
		return (NULL);
	}
}

char	*get_path(char **after_cmd_split, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;

	if (ft_strchr(after_cmd_split[0], '/'))
		return (after_cmd_split[0]);
	i = 0;
	allpath = ft_split(get_env("PATH", env), ':');
	if (allpath)
	{
		while (allpath[i++])
		{
			exec = get_exec_path(allpath[i], after_cmd_split[0]);
			if (exec != NULL)
			{
				ft_free_all(allpath);
				return (exec);
			}
		}
		ft_free_all(allpath);
	}
	return (after_cmd_split[0]);
}
