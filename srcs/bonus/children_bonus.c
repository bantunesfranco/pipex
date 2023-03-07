/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/27 16:29:20 by bfranco       #+#    #+#                 */
/*   Updated: 2022/11/27 16:29:20 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipex_bonus.h"

void	child(char **argv, t_pipe *tab, int	*tube, int fd)
{
	if (tab->index == tab->start && tab->infile == -1)
		print_error(argv[1], ENOENT);
	if (close(tube[0]) == -1)
		ft_error("pipex", errno);
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		ft_error("pipex", errno);
	if (dup2(tube[1], STDOUT_FILENO) == -1 || close(tube[1]) == -1)
		ft_error("pipex", errno);
	tab->cmd_args = format_args(ft_split_args(argv[tab->index], ' '));
	tab->cmd = get_cmd(tab->paths, tab->cmd_args[0]);
	execve(tab->cmd, tab->cmd_args, tab->envp);
	ft_error("pipex", errno);
}

void	last(char **argv, t_pipe *tab, int *tube, int fd)
{
	if (tab->outfile == -1)
		print_error(argv[tab->end], ENOENT);
	if (close(tube[0]) == -1 || close(tube[1] == -1))
		ft_error("pipex", errno);
	if (dup2(tab->outfile, STDOUT_FILENO) == -1 || close(tab->outfile) == -1)
		ft_error("pipex", errno);
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		ft_error("pipex", errno);
	tab->cmd_args = format_args(ft_split_args(argv[tab->index], ' '));
	tab->cmd = get_cmd(tab->paths, tab->cmd_args[0]);
	execve(tab->cmd, tab->cmd_args, tab->envp);
	ft_error("pipex", errno);
}
