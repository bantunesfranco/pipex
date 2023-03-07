/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_fds_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 12:55:51 by bfranco       #+#    #+#                 */
/*   Updated: 2023/02/10 12:12:05 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipex_bonus.h"

static void	write_to_here_doc(char *del, int fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strncmp(del, line, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(del);
	close (fd);
}

static int	here_doc(char *delim)
{
	int		fd;
	char	*del;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_EXCL, 0000644);
	if (fd == -1)
		print_error("here_doc", errno);
	del = ft_strjoin(delim, "\n");
	if (!del)
		ft_error("pipex: ", ENOMEM);
	write_to_here_doc(del, fd);
	fd = open("here_doc", O_RDONLY);
	if (unlink("here_doc") == -1)
		ft_error("pipex: ", errno);
	return (fd);
}

void	open_fds(int argc, char **argv, t_pipe *tab)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		tab->index = 3;
		tab->start = 3;
		tab->infile = here_doc(argv[2]);
	}
	else
	{
		tab->index = 2;
		tab->start = 2;
		tab->infile = open(argv[1], O_RDONLY);
	}
	if (!ft_strncmp("here_doc", argv[1], 9))
		tab->outfile = open(argv[argc - 1], O_CREAT | O_RDWR \
		| O_APPEND, 0000644);
	else
		tab->outfile = open(argv[argc - 1], O_CREAT | O_RDWR \
		| O_TRUNC, 0000644);
	tab->end = argc - 1;
}
