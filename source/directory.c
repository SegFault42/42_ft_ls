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
	struct stat		file_stat;

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
			if (file_stat.st_mode & S_IFLNK)
				lstat(content_dir->d_name, &file_stat);
			else
				stat(content_dir->d_name, &file_stat);
			if (g_argp[MINUS_T].active == 1)
			{
				sort_by_time(&ctrl, file_stat.st_mtimespec.tv_sec, content_dir->d_name);
			}
			else
				sort_lst(&ctrl, content_dir);
		}
		print_lst(&ctrl);
		/*free_list(&ctrl);*/
	}
	close_directory(&dir);
}
