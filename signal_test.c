#include "mini.h"
#include <signal.h>
#include <stdio.h>

// /* define a new mask set */
// sigset_t mask_set;
// /* first clear the set (i.e. make it contain no signal numbers) */
// sigemptyset(&mask_set);
// /* lets add the TSTP and INT signals to our mask set */
// sigaddset(&mask_set, SIGTSTP);
// sigaddset(&mask_set, SIGINT);
// /* and just for fun, lets remove the TSTP signal from the set. */
// sigdelset(&mask_set, SIGTSTP);
// /* finally, lets check if the INT signal is defined in our set */
// if (sigismember(&mask_set, SIGINT)
//     printf("signal INT is in our set\n");
// else
//     printf("signal INT is not in our set - how strange...\n");
// /* finally, lets make the set contain ALL signals available on our system */
// sigfillset(&mask_set)

int		main(void)
{
	sigset_t mask_set;

	mask_set = -1;
	printf("mask %d\n", (int)mask_set);
	return (0);
}