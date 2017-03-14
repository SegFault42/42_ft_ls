#include "../include/ft_ls.h"

/*static void	fill_argp(char *param, char *description, int index)*/
/*{*/
	/*g_argp[index].description = ft_strdup(description);*/
	/*g_argp[index].sign = ft_strdup(param);*/
	/*g_argp[index].active = 0;*/
	/*if (g_argp[index].sign == NULL || g_argp[index].description == NULL)*/
		/*ft_error(MALLOC_ERROR);*/
/*}*/
/*
** init_argp sert a remplir tout les champs de g_argp
*/
/*static void	init_argp()*/
/*{*/
	/*ft_memset(g_argp, 0, sizeof(g_argp));*/
	/*fill_argp("a", "Print hide file", MINUS_A);*/
	/*fill_argp("1", "One file per line", ONE);*/
	/*fill_argp("R", "List subdirectory recursively", UPPER_R);*/
	/*fill_argp("r", "reverse sort", MINUS_R);*/
	/*fill_argp("t", "sort by time (new first)", MINUS_T);*/
	/*fill_argp("l", "print full info", MINUS_L);*/
	/*fill_argp("--", "end getting option", END_OPTION);*/
/*}*/
/*
** la fonction init sert a initialiser la structure de controle
** et la variable globale g_argp
*/
void		init(t_ctrl *ctrl)
{
	ft_memset(ctrl, 0, sizeof(t_ctrl));
	/*init_argp();*/
}
