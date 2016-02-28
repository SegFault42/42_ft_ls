#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR *rep = NULL;
	struct dirent *fichierlu = NULL;
	int i = 0;

	if (argc == 1 && (rep = opendir("./")) != NULL)
	{
		while((fichierlu = readdir(rep)) != NULL)
			ft_putendl(fichierlu->d_name);
	}
	/*if (argc == 2 && (rep = opendir(argv[1])) == NULL)*/
	/*{*/
		/*perror("Error ");*/
		/*return(EXIT_FAILURE);*/
	/*}*/
	/*else if (argc == 2 && (rep = opendir(argv[1])) == NULL)*/
	/*{*/
		/*perror("Error ");*/
		/*return(EXIT_FAILURE);*/
	/*}*/
	/*while((fichierlu = readdir(rep)) != NULL)*/
		/*ft_putendl(fichierlu->d_name);*/
	if (closedir(rep) == -1)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	return 0;
}
