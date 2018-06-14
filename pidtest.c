#include "pidtest.h"

int main()
{
	PID 		pid;

	printf("  windup_guard <%d>\n  proportional_gain<%d>\n  integral_gain<%d>\n  derivative_gain<%d>\n  prev_error<%d>\n  int_error<%d>\n  control<%d>\n  ",
		pid.windup_guard
		pid.proportional_gain,
		pid.integral_gain,
		pid.derivative_gain,
		pid.prev_error,
		pid.int_error,
		pid.control);

	return 0;
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