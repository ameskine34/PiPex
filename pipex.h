/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:28:11 by ameskine          #+#    #+#             */
/*   Updated: 2025/02/07 19:11:24 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

size_t	ft_strlen(const char *theString);
void	ft_free_all(char **f);
char	*get_exec_path(char *path, char *cmd);
char	*ft_strchr(const char *s, int c);
char	*get_env(char *name, char **env);
char	*get_path(char **after_cmd_split, char **env);

#endif
