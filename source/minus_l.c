#include "../include/ft_ls.h"

void	minus_l(char *file)
{
	struct stat	file_stat;

	stat(file, &file_stat);
	/*if (file_stat.st_mode & S_IFDIR)*/
		/*ft_dprintf(1, "d");*/
	/*else if (file_stat.st_mode & S_IFREG)*/
		/*ft_dprintf(1, "-");*/
	/*else if (file_stat.st_mode & S_IFLNK)*/
		/*ft_dprintf(1, "c");*/
	/*else if (file_stat.st_mode & S_IFLNK)*/
		/*ft_dprintf(1, "l");*/

	if (S_ISDIR(file_stat.st_mode))
		ft_dprintf(1, "d");
	else if (S_ISLNK(file_stat.st_mode))
		ft_dprintf(1, "l");
	else if (S_ISCHR(file_stat.st_mode))
		ft_dprintf(1, "c");
	else if (S_ISBLK(file_stat.st_mode))
		ft_dprintf(1, "b");
	else if (S_ISSOCK(file_stat.st_mode))
		ft_dprintf(1, "s");
	else if (S_ISFIFO(file_stat.st_mode))
		ft_dprintf(1, "p");
	else
		ft_dprintf(1, "-");

	ft_dprintf(1, (file_stat.st_mode & S_IRUSR) ? "r" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IWUSR) ? "w" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IXUSR) ? "x" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IRGRP) ? "r" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IWGRP) ? "w" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IXGRP) ? "x" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IROTH) ? "r" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IWOTH) ? "w" : "-");
	ft_dprintf(1, (file_stat.st_mode & S_IXOTH) ? "x" : "-");
	/*ft_dprintf(1, (file_stat.st_mode & S_ISVTX) ? "x" : "-");*/

	if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_dprintf(1, "@");
	else if (acl_get_file(file, ACL_TYPE_EXTENDED))
		ft_dprintf(1, "+");
	else
		ft_dprintf(1, " ");
	ft_dprintf(1, " ");
}
