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

#include "../../incs/pipex_bonus.h"

// void	*lks(void)
// {
// 	system("leaks -q pipex");
// 	return (NULL);
// }

static void	check_args(int argc, char **argv)
{
	if (argc >= 5)
	{
		if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
		{
			if (argc >= 6)
				return ;
		}
		else
		{
			if (argc >= 5)
				return ;
		}
	}
	ft_putendl_fd("pipex: Invalid number of arguments", 2);
	ft_putendl_fd("use: ./pipex infile cmd1 cmd2 ... outfile", 2);
	ft_putendl_fd("or ./pipex here_doc delimiter cmd1 cmd2 ... outfile", 2);
	exit(EXIT_FAILURE);
}

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
	else
	{	
		if (close(tube[1]) == -1)
			ft_error("pipex", errno);
		if (++tab->index < argc - 1)
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

	check_args(argc, argv);
	open_fds(argc, argv, &tab);
	tab.envp = envp;
	tab.paths = get_paths(tab.envp);
	exec_commands(argc, argv, &tab, tab.infile);
}
