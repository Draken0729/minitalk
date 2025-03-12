/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:09:05 by rabril-h          #+#    #+#             */
/*   Updated: 2025/03/12 10:03:37 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int sig, siginfo_t *info, void *context)
{
    static char c = 0;
    static int bit_index = 0;

    (void)context;

    if (sig == SIGUSR2)
        c |= (1 << bit_index);

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
    kill(info->si_pid, SIGUSR1);
}

int main(void)
{
    struct sigaction sa;
    
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);

    ft_printf("Serveur en attente... PID: %d\n", getpid());

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    while (1)
        pause();

    return 0;
}



