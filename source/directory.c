#include "../include/ft_ls.h"

extern t_argp	g_argp[];

int8_t	open_directory(DIR **dir, char *directory)
{
	if ((*dir = opendir(directory)) == NULL)
	{
		ft_dprintf(2, "ls: %s: %s\n", directory, strerror(errno));
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

void	close_directory(DIR **dir)
{
	if (closedir(*dir) == -1)
	{
		ft_dprintf(STDERR_FILENO, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
}


void	print_directory(char *directory)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;
	/*struct stat		file_stat;*/

	content_dir = NULL;
	dir = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	if (g_argp[UPPER_R].active == 1)
		recursive(directory);
	else
	{
		while ((content_dir = readdir(dir)) != NULL)
		{
			if (check_minus_a(content_dir) == true)
				continue ;
			/*stat(content_dir->d_name, &file_stat);*/
			/*ft_dprintf(1, GREEN"%s\n", content_dir->d_name);*/
			/*ft_dprintf(1, YELLOW"atime = %s\n"END, ctime(&file_stat.st_atime));*/
			/*ft_dprintf(1, YELLOW"%s\n"END, file_stat.);*/
			sort_lst(&ctrl, content_dir);
		}
		print_lst(&ctrl);
		/*free_list(&ctrl);*/
	}
	close_directory(&dir);
}
