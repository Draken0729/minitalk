/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:09:05 by rabril-h          #+#    #+#             */
/*   Updated: 2025/03/13 17:09:13 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int sig)
{
    static char c = 0;
    static int bit_index = 0;

    if (sig == SIGUSR1)
        c |= (1 << (7 - bit_index));
    bit_index++;
    
    if (bit_index == 8)
    {
        if (c == '\0')
            write(1, "\n", 1);
        else
            write(1, &c, 1);
        bit_index = 0;
        c = 0;
    }
    if (sig == SIGINT)
    {
        ft_printf("\nserver closed.\n");
        _exit(0);
    }
}

int main(void)
{
    struct sigaction sa;
    
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error\n");
        return (0);
    }
    
    signal(SIGINT, signal_handler);
    ft_printf("Server waiting... PID: %d\n", getpid());
    while (1)
        pause();
}



