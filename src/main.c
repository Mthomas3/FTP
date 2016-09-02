/*
** main.c for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Mon May  2 22:29:39 2016 Thomas Martins
** Last update Sat May 14 16:38:55 2016 Thomas Martins
*/

#include "struct.h"

static t_sockets	*create_structure(t_sockets *socks, int port,
					  const char *path)
{
  if (NULL == (socks = malloc(sizeof(*socks))))
    return (NULL);
  socks->port = port;
  if (NULL == (socks->path = malloc(sizeof(char) * strlen(path) + 1)))
    return (NULL);
  strcpy(socks->path, path);
  return (socks);
}

int		main(int ac, const char **av)
{
  t_sockets	*socks;

  socks = NULL;
  if (EXIT_FAILURE == (get_errors(ac, av))
      || NULL == (socks = create_structure(socks, atoi(av[1]), av[2]))
      || EXIT_FAILURE == (start_sockets(socks)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
