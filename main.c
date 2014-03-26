#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef struct		s_lexer
{
	char				*str;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}					t_lexer;

typedef struct		s_word
{
	char				*word;
	t_lexer				*posse;
	struct s_word		*next;
	struct s_word		*prev;
}					t_word;

typedef struct		s_lstar
{
	t_lexer				*dir;
	char				dir_flag;
	t_word				*word;
	t_lexer				*starz;
	struct s_lstar		*next;
	struct s_lstar		*prev;
}					t_lstar;

typedef struct		s_lword
{
	t_lstar			*first;
	t_lstar			*last;
}					t_lword;

void		treat_lstar(t_lstar *node)
{
	t_word	*word_ptr;

	word_ptr = node->word;
	get_first_dir(node);
	while (word_ptr)
	{
		if (word_ptr->prev)
			change_dir(word_ptr->prev, node);
}

t_word		*init_word(char *str)
{
	t_word		*new;

	if ((new = (t_word *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->word = ft_strdup(str);
	new->posse = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_word		*add_to_word(t_word *first, t_word *ptr)
{
	t_word		*bws_word;

	bwd_word = NULL;
	if (first == NULL)
		return (ptr);
	else
	{
		bws_word = first;
		while (bws_word->next)
			bws_word = bws_word->next;
		bws_word->next = ptr;
		ptr->prev = bws_word;
	}
	return (first);
}

t_word		*init_word_list(char *str)
{
	t_word	*first;
	t_word	*ptr;
	char	*split;
	int		i;

	i = 0;
	first = NULL;
	ptr = NULL;
	split = ft_strsplit(str, '/');
	while (split[i])
	{
		ptr = init_word(split[i]);
		first = add_to_word(first, ptr);
		i++;
	}
	ft_tabfree(&split);
	return (first);
}

t_lstar		*init_lstar(char *str)
{
	t_lstar		*new;

	if ((new = (t_lstar *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->dir = NULL;
	new->dir_flag = 0;
	new->word = init_word_list(str);
	new->starz = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lword	*init_lword(void)
{
	t_lword		*new;

	if ((new = (t_lword *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void	add_to_lword(char *str, t_lword *wordz)
{
	t_lstar		*node;

	node = init_lstar(str);
	if (wordz->first == NULL)
	{
		wordz->first = node;
		wordz->last = node;
	}
	else
	{
		wordz->last->next = node;
		node->prev = wordz->last;
		wordz->last = node;
	}
}

void	treat_lword(t_lword *wordz)
{
	t_lstar		*bws_lstar;

	bws_lstar = wordz->first;
	while (bws_lstar)
	{
		treat_lstar(bws_lstar);
		bws_lstar = bws_lstar->next;
	}
}

void	star_in_lx(char *str) //faire avec le node
{
	char		**spl_space;
	t_lword		*wordz;
	int			i;

	i = 0;
	if ((ft_strchr(str, '*') == NULL)) //faire un is_star avec les bslash
		return ;
	wordz = init_lword();
	spl_space = ft_strsplitspace(str);
	while (spl_space[i])
	{
		add_to_lword(spl_space[i], wordz);
		i++;
	}
	ft_tabfree(&spl_space);
	treat_lword(wordz);
//	add_to_node(wordz, node);
//	free_lword(wordz);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		write(1, "essayes encore\n", 15);
	else
		star_in_lx(argv[1]);
	return (0);
}
