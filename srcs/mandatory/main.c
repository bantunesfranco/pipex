/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/26 21:19:45 by bfranco       #+#    #+#                 */
/*   Updated: 2022/11/26 21:19:45 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipex.h"

// void	*lks(void)
// {
// 	system("leaks -q pipex");
// 	return (NULL);
// }

static int	pipe_and_fork(int	*tube)
{
	pid_t	id;

	if (pipe(tube) == -1)
		ft_error("pipex", errno);
	id = fork();
	if (id == -1)
		ft_error("pipex", errno);
	return (id);
}

static int	exec_commands(int argc, char **argv, t_pipe *tab, int fd)
{
	int		tube[2];
	pid_t	id;
	int		status;

	id = pipe_and_fork(tube);
	if (id == 0)
	{
		if (tab->index == argc - 2)
			last(argv, tab, tube, fd);
		child(argv, tab, tube, fd);
	}
	else if (tab->index < argc - 2)
	{	
		tab->index++;
		if (close(tube[1]) == -1)
			ft_error("pipex", errno);
		exec_commands(argc, argv, tab, tube[0]);
	}
	if (close(tube[0]) == -1)
		ft_error("pipex", errno);
	if (waitpid(id, &status, 0) == -1)
		ft_error("pipex", errno);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	tab;

	if (argc != 5)
	{
		ft_putendl_fd("pipex: Invalid number of arguments", 2);
		ft_putendl_fd("pipex: use: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	tab.index = 2;
	tab.infile = open(argv[1], O_RDONLY);
	tab.envp = envp;
	tab.paths = get_paths(tab.envp);
	exec_commands(argc, argv, &tab, tab.infile);
}
