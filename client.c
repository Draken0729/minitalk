/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:05:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/13 17:08:46 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bits(int server_pid, char c)
{
    int i;
    
    i = 0;
    while (i < 8)
    {
        if (c & (1 << (7 - i)))
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);

        usleep(350);
        i++;
    }
}

void send_message(int server_pid, char *msg)
{
    int i;

    i = 0;
    while (msg[i])
    {
        send_bits(server_pid, msg[i]);
        i++;
    }
    send_bits(server_pid, '\0');
}

int main(int argc, char **argv)
{

    if (argc < 3)
	{
        ft_printf("Error\n");
        return (0);
    }
    else
    { 
        int server_pid = atoi(argv[1]);
        if (server_pid <= 0)
        {
            ft_printf("invalid PID.\n");
            return 1;
        }
        char *message = argv[2];

        send_message(server_pid, message);
    }
    return 0;
}
