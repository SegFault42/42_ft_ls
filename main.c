#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR *rep = NULL;
	struct dirent *fichierlu = NULL;

	if ((rep = opendir("lol")) == NULL)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	else
		printf("Dossier ouvert.\n");
	fichierlu = readdir(rep);




if (closedir(rep) == -1)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	else
		printf("Dossier fermer.\n");
	return 0;
}
