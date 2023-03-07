/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmds_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 13:00:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/02/09 14:46:08 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipex_bonus.h"

void	print_error(char *s1, int err)
{
	errno = err;
	ft_putstr_fd("pipex: ", 2);
	if (errno == 127)
	{
		ft_putstr_fd(s1, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
		perror(s1);
	exit(errno);
}

static char	**man_paths(void)
{
	const char	*paths[5] = {"/usr/local/bin", "/usr/bin", "/bin", \
							"/usr/sbin", "/sbin"};
	char		**arr;
	int			i;

	arr = ft_calloc(6, sizeof(char *));
	if (!arr)
		ft_error("pipex", ENOMEM);
	i = 0;
	while (i < 5)
	{
		arr[i] = (char *)paths[i];
		i++;
	}
	return (arr);
}

char	**get_paths(char **envp)
{
	if (!*envp)
		return (man_paths());
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split_args(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	**format_args(char **cmd_args)
{
	int		i;
	int		len;
	char	*new_arg;

	i = 0;
	if (!cmd_args)
		return (NULL);
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == 34 || cmd_args[i][0] == 39)
		{
			len = ft_strlen(cmd_args[i]);
			new_arg = ft_substr(cmd_args[i], 1, len - 2);
			if (!new_arg)
				return (ft_free_arr(cmd_args), NULL);
			free(cmd_args[i]);
			cmd_args[i] = new_arg;
		}
		i++;
	}
	return (cmd_args);
}

char	*get_cmd(char **paths, char *cmd_args)
{
	char	*tmp;
	char	*cmd;

	if (!cmd_args || !paths)
		print_error(cmd_args, 127);
	if (cmd_args[0] == '/' && access(cmd_args, F_OK) == 0)
		return (cmd_args);
	while (paths && *paths && cmd_args[0] != '/')
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			ft_error("pipex", errno);
		cmd = ft_strjoin(tmp, cmd_args);
		if (!cmd)
			ft_error("pipex", errno);
		free(tmp);
		if (!access(cmd, F_OK))
			return (cmd);
		free(cmd);
		paths++;
	}
	print_error(cmd_args, 127);
	return (NULL);
}
