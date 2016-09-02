/*
** sockets.c for  in /home/mart_4/rendu/PSU_2015_myftp
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Wed May  4 23:55:16 2016 Thomas Martins
** Last update Sun May 15 11:15:34 2016 Thomas Martins
*/

#include <sys/wait.h>
#include "../struct.h"

static t_server	*create_server(t_server *server,
			       t_sockets __attribute__((unused))*socks)
{
  if (NULL == (server = malloc(sizeof(*server))))
    return (NULL);
  server->sockets_client = 0;
  server->pid_client = 0;
  return (server);
}

static int	init_structure(struct sockaddr_in *serv, t_sockets *o)
{
  bzero((char *)serv, sizeof(*serv));
  serv->sin_family = AF_INET;
  serv->sin_addr.s_addr = INADDR_ANY;
  serv->sin_port = htons(o->port);
  return (EXIT_SUCCESS);
}

static int	init_server(t_sockets *o, int *fd, struct sockaddr_in *server)
{
  *fd = socket(AF_INET, SOCK_STREAM, 0);
  init_structure(server, o);
  if (bind(*fd, (struct sockaddr *)server, sizeof(*server)) < 0)
    return (EXIT_FAILURE);
  if ((listen(*fd, CLIENT)) != 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	get_new_clients(int fd, t_sockets *socks)
{
  t_server	*server;
  t_cmd		*cmd;

  server = NULL;
  cmd = NULL;
  if (NULL == (server = create_server(server, socks)))
    return (EXIT_FAILURE);
  while (RUNNING)
    {
      server->sockets_client =
	accept(fd, (struct sockaddr *)&server->addr_client,
	       &server->lenght_client);
      waitpid(-1, NULL, WNOHANG);
      if ((server->pid_client = fork()) == 0)
	set_clients(server, socks, cmd);
      else
	close (server->sockets_client);
    }
  free(server);
  free(cmd);
  server = NULL;
  cmd = NULL;
  return (EXIT_SUCCESS);
}

int			start_sockets(t_sockets *socks)
{
  int			fd;
  struct sockaddr_in	server;

  fd = 0;
  if (EXIT_FAILURE == (init_server(socks, &fd, &server)))
    return (EXIT_FAILURE);
  if (EXIT_FAILURE == (get_new_clients(fd, socks)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
