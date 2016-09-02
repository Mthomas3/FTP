/*
** server_options.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/commands
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sun May 15 11:22:05 2016 Thomas Martins
** Last update Sun May 15 19:10:12 2016 Thomas Martins
*/

#include "../struct.h"

int	server_quit(t_cmd __attribute__((unused))*cmd, t_server *server)
{
  dprintf(server->sockets_client, "221 Goodbye.\r\n");
  shutdown(server->sockets_client, SHUT_RDWR);
  close(server->sockets_client);
  server->connection = 0;
  return (EXIT_SUCCESS);
}

int		server_help(t_cmd __attribute__((unused))*cmd,
			    t_server *server)
{
  t_list	*list;

  list = create_list();
  if (list == NULL)
    return (EXIT_FAILURE);
  list = get_commander(list);
  printf_list_fd(list, server->sockets_client);
  free(list);
  return (EXIT_SUCCESS);
}

int		server_pwd(t_cmd __attribute__((unused))*cmd, t_server *server)
{
  char		buffer[1024];

  if (getcwd(buffer, 1024) == NULL)
    dprintf(server->sockets_client, "500 can't get the path.\r\n");
  dprintf(server->sockets_client, "257 \"%s\".\r\n", buffer);
  return (EXIT_SUCCESS);
}

int		server_noop(t_cmd __attribute__((unused))*cmd,
			    t_server *server)
{
  dprintf(server->sockets_client, "200 NOOP ok.\r\n");
  return (EXIT_SUCCESS);
}

int		server_list(t_cmd __attribute__((unused))*cmd,
			    t_server *server)
{
  DIR		*my_dir;
  struct dirent	*my_file;
  char		buffer[1024];

  if (server->mode == ACTIF || server->mode == PASSIVE)
    {
      my_dir = opendir(".");
      dprintf(server->sockets_client,
	      "150 Here comes the directory listing.\r\n");
      while ((my_file = readdir(my_dir)) != NULL)
	{
	  snprintf(buffer, 1024, "%s", my_file->d_name);
	  dprintf(server->socket, "%s\r\n", buffer);
	  close(server->socket);
	  server->socket = -1;
	}
      dprintf(server->sockets_client, "226 Directory send OK.\r\n");
    }
  else
    {
      dprintf(server->sockets_client, "425 Use PORT or PASV first\r\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
