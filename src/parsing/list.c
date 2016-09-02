/*
** list.c for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Mon May  9 22:39:11 2016 Thomas Martins
** Last update Sun May 15 11:17:21 2016 Thomas Martins
*/

#include "../struct.h"

int		printf_list_fd(t_list *root, const int sock)
{
  t_list	*tmp;
  int		i;

  tmp = root;
  i = 0;
  dprintf(sock, "214-The following commands are recognized.\r\n");
  while (tmp->next != root)
    {
      dprintf(sock, " %s", tmp->next->name);
      if ((i % 4) == 0)
	dprintf(sock, "\r\n");
      ++i;
      tmp = tmp->next;
    }
  dprintf(sock, "\r\n214 Help OK.\r\n");
  return (EXIT_SUCCESS);
}

int		printf_list(t_list *root)
{
  t_list	*tmp;

  tmp = root;
  while (tmp->next != root)
    {
      printf("function : %s\n", tmp->next->name);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

static int	add_list(t_list *elem, int (*fptr)(t_cmd *, t_server*),
			 char *name, int connection)
{
  t_list	*new_elem;

  new_elem = NULL;
  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    return (EXIT_FAILURE);
  new_elem->name = name;
  new_elem->connection = connection;
  new_elem->func = fptr;
  new_elem->prev = elem->prev;
  new_elem->next = elem;
  elem->prev->next = new_elem;
  elem->prev = new_elem;
  return (EXIT_SUCCESS);
}

t_list		*create_list(void)
{
  t_list	*root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

t_list		*get_commander(t_list *list)
{
  if (list == NULL)
    return (NULL);
  if (add_list(list, &server_quit, "QUIT", 0) == EXIT_FAILURE
      || add_list(list, &server_help, "HELP", 0) == EXIT_FAILURE
      || add_list(list, &server_pwd, "PWD", 0) == EXIT_FAILURE
      || add_list(list, &server_noop, "NOOP", 0) == EXIT_FAILURE
      || add_list(list, &server_list, "LIST", 0) == EXIT_FAILURE
      || add_list(list, &server_cwd, "CWD", 0) == EXIT_FAILURE
      || add_list(list, &server_cdup, "CDUP", 0) == EXIT_FAILURE
      || add_list(list, &server_remove, "DELE", 0) == EXIT_FAILURE
      || add_list(list, &server_pasv, "PASV", 0) == EXIT_FAILURE
      || add_list(list, &server_port, "PORT", 0) == EXIT_FAILURE
      || add_list(list, &server_retr, "RETR", 0) == EXIT_FAILURE
      || add_list(list, &server_stor, "STOR", 0) == EXIT_FAILURE)
    return (NULL);
  return (list);
}
