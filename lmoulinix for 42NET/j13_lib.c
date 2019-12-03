/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_btree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 15:05:48 by jhalford          #+#    #+#             */
/*   Updated: 2016/08/20 11:15:31 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifndef FT_BTREE_H
# define FT_BTREE_H
typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}				t_btree;
t_btree			*btree_create_node(void *item);
#endif

struct	s_printdata
{
	int		is_left;
	int		offset;
	int		depth;
	int		left;
	int		right;
};
typedef struct s_printdata	t_printdata;


static int	print_t2(t_printdata data, char s[20][255], char b[20])
{
	int		width;
	int		i;

	width = 5;
	i = -1;
	while (++i < width)
		s[2 * data.depth][data.offset + data.left + i] = b[i];
	i = -1;
	if (data.depth && data.is_left)
	{
		while (++i < width + data.right)
			s[2 * data.depth - 1]
				[data.offset + data.left + width / 2 + i] = '-';
		s[2 * data.depth - 1][data.offset + data.left + width / 2] = '+';
		s[2 * data.depth - 1]
			[data.offset + data.left + data.right + 3 * width / 2] = '+';
	}
	else if (data.depth && !data.is_left)
	{
		while (++i < width + data.left)
			s[2 * data.depth - 1][data.offset - width / 2 + i] = '-';
		s[2 * data.depth - 1][data.offset + data.left + width / 2] = '+';
		s[2 * data.depth - 1][data.offset - width / 2 - 1] = '+';
	}
	return (data.left + width + data.right);
}

static int	print_t(t_btree *tree,
		t_printdata data, char s[20][255], char *(*printer)(void *))
{
	char	b[20];
	int		width;

	width = 5;
	if (!tree)
		return (0);
	sprintf(b, "%5s", (char*)printer(tree->item));
	data.left = print_t(tree->left, (t_printdata){
			1, data.offset, data.depth + 1, data.left, data.right}, s, printer);
	data.right = print_t(tree->right, (t_printdata){
			0, data.offset + data.left + width, data.depth + 1,
			data.left, data.right}, s, printer);
	return (print_t2(data, s, b));
}

void		btree_print(int fd, t_btree *tree, char *(*printer)(void *))
{
	char	s[20][255];
	char	empty[255];
	int		i;

	i = -1;
	while (++i < 20)
		sprintf(s[i], "%80s", " ");
	sprintf(empty, "%80s", " ");
	print_t(tree, (t_printdata){0, 0, 0, 0, 0}, s, printer);
	i = -1;
	while (++i < 20)
	{
		if (strcmp(s[i], empty) == 0)
			break ;
		if (i == 0 && strcmp(s[1], empty) == 0)
			break ;
		dprintf(fd, "%s\n", s[i]);
	}
}

char	*myprinter(void *item)
{
	return (char*)item;
}

void	bst_print_ascii(t_btree* tree)
{
	btree_print(0, tree, myprinter);
}

int		my_strcmp(void *s1, void *s2)
{
	return (*((char *)s1) - *((char *)s2));
}

void	print_bylevel(void *item, int current_level, int is_first_elem)
{
	if (is_first_elem)
		printf("\n%d:", current_level);
	if (item)
		printf("%s ", (char*)item);
	else
		ft_putchar('.');
}


#ifndef ex00
t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	node->left = 0;
	node->right = 0;
	node->item = item;
	return (node);
}
#endif
