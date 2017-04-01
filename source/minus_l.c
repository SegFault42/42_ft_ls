#include "../include/ft_ls.h"

char	g_info[255] = {0};
size_t	g_nb_blocks = 0;

static void	get_chmod(char **info, struct stat *file_stat)
{
	if (S_ISDIR(file_stat->st_mode))
		ft_strcat(*info, "d");
	else if (S_ISLNK(file_stat->st_mode))
		ft_strcat(*info, "l");
	else if (S_ISCHR(file_stat->st_mode))
		ft_strcat(*info, "c");
	else if (S_ISBLK(file_stat->st_mode))
		ft_strcat(*info, "b");
	else if (S_ISSOCK(file_stat->st_mode))
		ft_strcat(*info, "s");
	else if (S_ISFIFO(file_stat->st_mode))
		ft_strcat(*info, "p");
	else
		ft_strcat(*info, "-");
	ft_strcat(*info, (file_stat->st_mode & S_IRUSR)  ? "r" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IWUSR) ? "w" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IXUSR) ? "x" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IRGRP) ? "r" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IWGRP) ? "w" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IXGRP) ? "x" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IROTH) ? "r" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IWOTH) ? "w" : "-");
	ft_strcat(*info, (file_stat->st_mode & S_IXOTH) ? "x" : "-");
}

static void	get_acl(char *file, char **info)
{
	if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_strcat(*info, "@ ");
	else if (acl_get_file(file, ACL_TYPE_EXTENDED))
		ft_strcat(*info, "+ ");
	else
		ft_strcat(*info, "| ");// le pipe sera remplacer par un espace.
}

static void	get_link_groupe(char **info, struct stat *file_stat)
{
	struct passwd	*name;
	struct group	*groupe;
	char			*itoa;
	char			**split;
	int				six_month;

	six_month = 15778476; // 6 month in second
	name = getpwuid(file_stat->st_uid);
	groupe = getgrgid(file_stat->st_gid);
	itoa = ft_itoa(file_stat->st_nlink);
	ft_strcat(*info, itoa);
	ft_strdel(&itoa);
	ft_strcat(*info, " ");
	ft_strcat(*info, name->pw_name);
	ft_strcat(*info, " ");
	ft_strcat(*info, groupe->gr_name);
	ft_strcat(*info, " ");
	itoa = ft_itoa(file_stat->st_size);
	ft_strcat(*info, itoa);
	ft_strdel(&itoa);
	ft_strcat(*info, " ");
	split = ft_strsplit(ctime(&file_stat->st_mtime), ' ');
	ft_strcat(*info, split[1]);
	ft_strcat(*info, " ");
	ft_strcat(*info, split[2]);
	ft_strcat(*info, " ");
	if (file_stat->st_mtime > time(0))
		ft_strccat(*info, split[4], '\n');
	else if (file_stat->st_mtime < (time(0) - six_month))
		ft_strccat(*info, split[4], '\n');
	else
		ft_strncat(*info, split[3], 5);
	ft_strcat(*info, " ");
	ft_2d_tab_free(split);
}

void	minus_l(char *file, t_env *env)
{
	struct stat		file_stat;

	if ((env->file.info = (char *)ft_memalloc(sizeof(char) * 256)) == NULL)
		ft_critical_error(MALLOC_ERROR);
	ft_memset(g_info, 0, 255);
	lstat(file, &file_stat);
	get_chmod(&env->file.info, &file_stat);
	get_acl(file, &env->file.info);
	get_link_groupe(&env->file.info, &file_stat);
	ft_memcpy(g_info, env->file.info, 255);
	if (env->file.info != NULL)
		free(env->file.info);
	g_nb_blocks += file_stat.st_blocks;
}
