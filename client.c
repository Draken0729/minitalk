/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:05:23 by quentin           #+#    #+#             */
/*   Updated: 2025/03/12 10:09:37 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bits(pid_t server_pid, char c)
{
    int i;
    
    i = 0;
    while (i < 8)
    {
        if ((c >> i) & 1)
            kill(server_pid, SIGUSR2);
        else
            kill(server_pid, SIGUSR1);

        usleep(350);
        i++;
    }
}

/*void send_message(pid_t server_pid, char *message)
{
    int i = 0;
    while (message[i])
    {
        send_bits(server_pid, message[i]);
        i++;
    }
    send_bits(server_pid, '\0');
}*/

int main(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc != 3)
	{
        ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);

    ft_printf("Envoi du message : \"%s\" au PID %d\n", argv[2], server_pid);
//    send_message(server_pid, argv[2]);
    send_bits(server_pid, c);

    return 0;
}
