/*
** settings.c for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sat May  7 23:44:57 2016 Thomas Martins
** Last update Sun May 15 11:12:47 2016 Thomas Martins
*/

#include "../struct.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

static int	manage_user(t_cmd *cmd, t_server *serv)
{
  dprintf(serv->sockets_client, "331 Password required for %s\r\n",
	  cmd->command);
  serv->connection = 1;
  return (EXIT_SUCCESS);
}

static int	manage_process(t_cmd *cmd, t_list *list, t_server *serv)
{
  (void)list;
  if (cmd->content == NULL)
    return (errors_client(serv->sockets_client,
			  "500 USER: Command requires a parameter"));
  manage_user(cmd, serv);
  serv->save = strdup(cmd->content);
  return (EXIT_SUCCESS);
}

static int	manage_commands(t_cmd *cmd, t_server *serv, t_list *list)
{
  int		(*commands)(t_cmd *, t_server *);

  commands = get_matchs(cmd->command, list);
  if (NULL != commands)
    return (commands(cmd, serv));
  return (EXIT_SUCCESS);
}

static int	send_reply(t_cmd *cmd, t_server *serv, t_list *list)
{
  printf("the command is : (%s) ", cmd->command);
  printf("the content is : (%s)\n", cmd->content);
  if (strcmp(cmd->command, "USER") == 0)
    return (manage_process(cmd, list, serv));
  if (strcmp(cmd->command, "PASS") == 0)
    return (manage_pass(cmd, list, serv));
  if ((serv->connection == 2 || strcmp(cmd->command, "QUIT") == 0)
      && get_matchs(cmd->command, list) != NULL)
    return (manage_commands(cmd, serv, list));
  else if (get_matchs(cmd->command, list) != NULL)
    return (errors_client(serv->sockets_client,
			  "530 Please login with USER and PASS"));
  else
    return (errors_client(serv->sockets_client, "500 Unknown command"));
  return (EXIT_SUCCESS);
}

int		set_clients(t_server *server, t_sockets *socks, t_cmd *cmd)
{
  t_list	*list;

  list = NULL;
  if (NULL == (list = create_list()))
    return (errors("cannot malloc linked list"));
  if (NULL == (list = get_commander(list)))
    return (errors("cannot get the linked list"));
  server->mode = UNDEFINED;
  server->path = strdup(socks->path);
  dprintf(server->sockets_client, "220 Welcome to my FTP.\r\n");
  server->connection = 0;
  while (10)
    {
      cmd = write_cmd(server, socks, cmd);
      if (cmd != NULL && cmd->command != NULL)
	{
	  if ((send_reply(cmd, server, list)) == 10)
	    break;
	}
    }
  free_cmd(cmd, list);
  close(server->sockets_client);
  exit(0);
  return (EXIT_SUCCESS);
}
