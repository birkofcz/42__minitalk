/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SIGINTtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:28:55 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/11 13:36:18 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* In this program, we define a signal handler function sigint_handler() 
that simply prints a message and exits the program when the SIGINT signal is received. 

We then use the signal() function to set up this handler function for the SIGINT signal.

The program then enters an infinite loop, during which it periodically calls the sleep() 
function to pause for one second. This loop allows the program to continue running and 
waiting for the SIGINT signal to be sent.

To test this program, simply compile it and run it in a terminal. Then press Ctrl+C to 
send the SIGINT signal to the program and observe how the signal handler function is executed.
 */

void sigint_handler(void) 
{
    printf("Caught SIGINT, terminating...\n");
    exit(0);
}

/*

void sigint_handler(int signum) 
{
    printf("Caught SIGINT, terminating...\n");
    exit(0);
}

The int signum parameter is not actually used in the sigint_handler() 
function in the example programs I provided. The int signum parameter is meant to receive 
the signal number that triggered the signal handler, so that the handler can perform different
actions depending on the signal that was received.

In the case of the sigint_handler() function in these example programs, we know that it 
will only be called for the SIGINT signal, so we don't need to use the signum parameter. 
However, in more complex programs that handle multiple signals with different behaviors, 
it may be necessary to use the signum parameter to determine which signal triggered the handler.

In summary, the int signum parameter is optional and depends on the needs of your program. 
If your program only needs to handle a single type of signal and perform the same action 
regardless of which signal triggered the handler, you can omit the signum parameter from your 
handler function. However, if your program needs to handle multiple signals with different behaviors, 
you may need to use the signum parameter to determine which signal triggered the handler.
*/

int main() 
{
    // Set up signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    printf("Press Ctrl+C to send SIGINT...\n");

    // Loop forever
    while (1) 
	{
        sleep(1);
    }
    return 0;
}
