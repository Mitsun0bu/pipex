/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:34:16 by llethuil          #+#    #+#             */
/*   Updated: 2022/02/08 17:39:46 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*joined;
	int		i_1;
	int		i_2;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * len + 1);
	if (joined == NULL)
		return (NULL);
	j = 0;
	i_1 = 0;
	while (s1[i_1])
		joined[j++] = s1[i_1++];
	i_2 = 0;
	while (s2[i_2])
		joined[j++] = s2[i_2++];
	joined[j] = '\0';
	return (joined);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			k = i;
			while ((haystack[k] == needle[j] && k < len) || needle[j] == '\0')
			{
				if (needle[j] == '\0')
					return ((char *)haystack + i);
				k ++;
				j ++;
			}
		}
		i ++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
	{
		substr[i] = '\0';
		return (substr);
	}
	while (s[start] && i < len)
	{
		substr[i] = s[start];
		start ++;
		i ++;
	}
	substr[i] = '\0';
	return (substr);
}

void	error_handler(char **av, char *err)
{
	if (err == ERR_INPUT)
		ft_putstr_fd("Invalid number of arguments: 5 arguments required\n", 1);
	else if (err == ERR_INFILE)
	{
		perror(av[1]);
		exit(0);
	}
	else if (err == ERR_CMD_1)
	{
		ft_putstr_fd(av[2], 1);
		ft_putstr_fd(": command not found\n", 1);
		return ;
	}
	else if (err == ERR_CMD_2)
	{
		ft_putstr_fd(av[3], 1);
		ft_putstr_fd(": command not found\n", 1);
		exit (127);
	}
	else if (err == ERR_OUTFILE)
		perror(av[4]);
	else if (err == ERR_PIPE || err == ERR_FORK)
		perror("");
	exit (1);
}

void	free_cmd(char **av, t_cmd *cmd)
{
	ft_free(cmd->paths_tab);
	ft_free(cmd->name_1);
	ft_free(cmd->name_2);
	if (cmd->path_1 && cmd->path_1 != av[2])
		free(cmd->path_1);
	if (cmd->path_2 && cmd->path_2 != av[3])
		free(cmd->path_2);
}
