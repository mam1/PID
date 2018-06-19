#include "pidtest.h"

void dpid(PID *p);

int get-value(void)
{
	int num, nitems;

	nitems = scanf("%d", &num);
	if (nitems == EOF) {
	    /* Handle EOF/Failure */
	} else if (nitems == 0) {
	    /* Handle no match */
	} else {
	    retun num;
	}
}

int main()
{
	PID 		pid;
	char 		*line


	pause(100);
	printf("playing with pid version %d.%d\n",v,sv);
	

	while(1)
	{
		line = getline
		if(strncmp("exit", line, 4) == 0)
		{
			printf("\nnormal termination\n");
			return 0;
		}
		if(strncmp("disp", line, 4) == 0)
		{
			dpid(pid);
		}
		else if(strncmp("windup", line, 6) == 0)
		{
			pid->windup_guard =  get-value
		}
		else if(strncmp("pro", line, 3) == 0)
		{

		}
		else if(strncmp("int", line, 3) == 0)
		{

		}
		else if(strncmp("derv", line, 4) == 0)
		{

		}
		else if(strncmp("windup", line, 6) == 0)
		{

		}
	}

	
	printf("\n ***** abnormal termination\n");
	return 1;
}

void dpid(PID *p)
{
	printf("  windup_guard <%d>\n  proportional_gain<%d>\n  integral_gain<%d>\n  derivative_gain<%d>\n  prev_error<%d>\n  int_error<%d>\n  control<%d>\n  ",
		p->windup_guard
		p->proportional_gain,
		p->integral_gain,
		p->derivative_gain,
		p->prev_error,
		p->int_error,
		p->control);
	return;	
}

char * getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}


void pid_zeroize(PID* pid) {
	// set prev and integrated error to zero
	pid->prev_error = 0;
	pid->int_error = 0;
}

void pid_update(PID* pid, double curr_error, double dt) {
	double diff;
	double p_term;
	double i_term;
	double d_term;

	// integration with windup guarding
	pid->int_error += (curr_error * dt);
	if (pid->int_error < -(pid->windup_guard))
		pid->int_error = -(pid->windup_guard);
	else if (pid->int_error > pid->windup_guard)
		pid->int_error = pid->windup_guard;

	// differentiation
	diff = ((curr_error - pid->prev_error) / dt);

	// scaling
	p_term = (pid->proportional_gain * curr_error);
	i_term = (pid->integral_gain     * pid->int_error);
	d_term = (pid->derivative_gain   * diff);

	// summation of terms
	pid->control = p_term + i_term + d_term;

	// save current error as previous error for next iteration
	pid->prev_error = curr_error;
}