#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR *rep = NULL;
	struct dirent *fichierlu = NULL;
	int i = 1;

	if (argc != 1)
		while (argv[i])
			ft_putendl(argv[i++]);
	if (argc == 1 && (rep = opendir("./")) != NULL)
	{
		while((fichierlu = readdir(rep)) != NULL)
		{
			if (fichierlu->d_name[0] != '.')
				ft_putendl(fichierlu->d_name);
			/*printf("DT_BLK = %d\n",DT_BLK);*/
			/*printf("DT_CHR = %d\n",DT_CHR);*/
			/*printf("DT_DIR = %d\n",DT_DIR);*/
			/*printf("DT_FIFO = %d\n",DT_FIFO);*/
			/*printf("DT_LNK = %d\n",DT_LNK);*/
			/*printf("DT_REG = %d\n",DT_REG);*/
			/*printf("DT_SOCK = %d\n",DT_SOCK);*/
			/*printf("DT_UNKNOWN = %d\n",DT_UNKNOWN);*/
			/*printf("\n");*/
		}
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
		/*perror("Error ");*/
		return(EXIT_FAILURE);
	}
	return 0;
}
