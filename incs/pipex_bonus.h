/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/26 21:19:32 by bfranco       #+#    #+#                 */
/*   Updated: 2022/11/26 21:19:32 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/incs/libft.h"

typedef struct s_pipe
{
	int		start;
	int		end;
	int		index;
	int		infile;
	int		outfile;
	char	*cmd;
	char	**envp;
	char	**paths;
	char	**cmd_args;
}	t_pipe;

void	open_fds(int argc, char **argv, t_pipe *tab);
void	child(char **argv, t_pipe *tab, int	*tube, int fd);
void	last(char **argv, t_pipe *tab, int *tube, int fd);
char	**get_paths(char **envp);
char	**format_args(char **cmd_args);
char	**ft_split_args(char *str, char sep);
char	*get_cmd(char **paths, char *cmd_args);
void	print_error(char *s1, int err);

#endif