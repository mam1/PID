#ifndef PIDTEST_H_
#define PIDTEST_H_

/* pid control block */
typedef struct {
	double windup_guard;
	double proportional_gain;
	double integral_gain;
	double derivative_gain;
	double prev_error;
	double int_error;
	double control;
} PID;

/* Forward declarations */
void pid_zeroize(PID* pid);
void pid_update(PID* pid, double curr_error, double dt);

#endif /* PIDTEST_H_ */