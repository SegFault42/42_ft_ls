#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR *ret = NULL;
	/*ptr_open = opendir("lol");*/
	if ((ret = opendir("lol")) == NULL)
		perror("Error ");
	else
		printf("Dossier ouvert.\n");
	if (closedir(ret) == -1)
		perror("Error ");
	else
		printf("Dossier fermer.\n");
	return 0;
}
