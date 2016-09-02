/*
** server_deep.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/commands
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sun May 15 11:23:57 2016 Thomas Martins
** Last update Sun May 15 19:06:31 2016 Thomas Martins
*/

#include "../struct.h"

int		get_port(char *port)
{
  int		p1;
  int		p2;
  int		i;

  p1 = atoi(port);
  i = -1;
  while (port[++i] != '\0')
    {
      if (port[i] == ',')
	{
	  i++;
	  break;
	}
    }
  p2 = atoi(port + i);
  return (p1 * 256 + p2);
}

int			port_connect(char *ip, char *port)
{
  struct sockaddr_in	addr;
  struct protoent	*tcp;
  int			new_socket;
  int			flags;

  flags = 1;
  tcp = getprotobyname("TCP");
  if ((new_socket = socket(AF_INET, SOCK_STREAM, tcp->p_proto)) == -1)
    return (-1);
  if ((flags = setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR,
			  (const char *)&flags, sizeof(flags))) == -1)
    return (flags);
  addr.sin_port = htons(get_port(port));
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &(addr.sin_addr));
  if (connect(new_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    return (-1);
  return (new_socket);
}

int		server_port(t_cmd *cmd, t_server *serv)
{
  char		*ip;
  char		*port;

  ip = NULL;
  port = NULL;
  serv->mode = ACTIF;
  cmd->send->sockets = 0;
  if (cmd->content == NULL)
    {
      dprintf(serv->sockets_client, "501 invalied parameters for port\r\n");
      return (EXIT_FAILURE);
    }
  if (NULL == (ip = get_informations(cmd->content)))
    {
      dprintf(serv->sockets_client, "501 invalied parameters for port\r\n");
      return (EXIT_FAILURE);
    }
  if (NULL == (port = get_informations_port(cmd->content)))
    {
      dprintf(serv->sockets_client, "501 invalied parameters for port\r\n");
      return (EXIT_FAILURE);
    }
  dprintf(serv->sockets_client, "200 ok port on\r\n");
  serv->socket = port_connect(ip, port);
  return (EXIT_SUCCESS);
}

int		server_cwd(t_cmd __attribute__((unused))*cmd, t_server *server)
{
  if (cmd->content == NULL)
    {
      dprintf(server->sockets_client, "501 arguments failed\r\n");
      return (EXIT_FAILURE);
    }
  if (chdir(cmd->content) < 0)
    {
      dprintf(server->sockets_client, "550 cwd has failed\r\n");
      return (EXIT_FAILURE);
    }
  dprintf(server->sockets_client, "250 Directory successfully changed\r\n");
  return (EXIT_SUCCESS);
}

int		server_pasv(t_cmd __attribute__((unused))*cmd, t_server *serv)
{
  serv->mode = PASSIVE;
  dprintf(serv->sockets_client, "227 Entering Passive Mode\r\n");
  return (EXIT_SUCCESS);
}
