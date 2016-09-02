/*
** commands_options.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/server
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sun May 15 11:10:55 2016 Thomas Martins
** Last update Sun May 15 11:13:37 2016 Thomas Martins
*/

#include "../struct.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int	free_cmd(t_cmd *cmd, t_list *list)
{
  if (cmd->command != NULL)
    {
      free(cmd->command);
      cmd->command = NULL;
    }
  if (cmd->content != NULL)
    {
      free(cmd->content);
      cmd->content = NULL;
    }
  if (cmd != NULL)
    {
      free(cmd);
      cmd = NULL;
    }
  if (list != NULL)
    {
      free(list);
      list = NULL;
    }
  return (EXIT_SUCCESS);
}

int	manage_pass(t_cmd *cmd, t_list __attribute__((unused))*list,
		    t_server *serv)
{
  if (serv->connection != 1)
    return (errors_client(serv->sockets_client, "530 Login with USER first"));
  if (strcmp(serv->save, "Anonymous") != 0)
    return (errors_client(serv->sockets_client, "530 Login incorrect"));
  if (cmd->content != NULL || serv->right != 1)
    return (errors_client(serv->sockets_client, "530 wrong password"));
  dprintf(serv->sockets_client, "230 Login successful OK\r\n");
  serv->connection = 2;
  return (EXIT_SUCCESS);
}
