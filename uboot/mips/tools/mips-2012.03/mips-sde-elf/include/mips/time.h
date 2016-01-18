/*
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
 * Copyright (c) 2010 CodeSourcery, Inc.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *      copyright
 *        notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with
 *        the distribution.
 *      * Neither the name of MIPS Technologies Inc. nor the names of its
 *        contributors may be used to endorse or promote products derived
 *        from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * sys/time.h : SDE timer definitions
 */


#ifndef __SYS_TIME_H
#ifdef __cplusplus
extern "C" {
#endif
#define __SYS_TIME_H

#include <machine/ansi.h>

struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};


struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};


#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)	\
	(((tvp)->tv_sec == (uvp)->tv_sec) ? \
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) : \
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
#define	timeradd(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000L) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000L;			\
		}							\
	} while (0)
#define	timersub(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000L;			\
		}							\
	} while (0)

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define ITIMER_REAL	0
#define ITIMER_VIRTUAL	1
#define ITIMER_PROF	2
#define ITIMER_USER	3
#define NITIMER		4

struct xcptcontext;

struct itimerval {
    struct timeval	it_interval;	/* timer interval */
    struct timeval	it_value;	/* current value */
    void		(*it_func)(struct timeval *, struct xcptcontext *);
};

int setitimer (unsigned int, struct itimerval *, struct itimerval *);
int getitimer (unsigned int, struct itimerval *);
int gettimeofday (struct timeval *, struct timezone *);
int settimeofday (const struct timeval *, const struct timezone *);

/* POSIX.4 stuff */
#if defined(_POSIX_TIMERS) || defined(_KERNEL)
struct timespec {
    long	 	tv_sec;		/* seconds */
    long 		tv_nsec;	/* and nanoseconds */
};

struct itimerspec {
    struct timespec	it_value;
    struct timespec	it_interval;
};

/* Operations on timespecs. */
#define	timespecclear(tsp)		(tsp)->tv_sec = (tsp)->tv_nsec = 0
#define	timespecisset(tsp)		((tsp)->tv_sec || (tsp)->tv_nsec)
#define	timespeccmp(tsp, usp, cmp)					\
	(((tsp)->tv_sec == (usp)->tv_sec) ?				\
	    ((tsp)->tv_nsec cmp (usp)->tv_nsec) :			\
	    ((tsp)->tv_sec cmp (usp)->tv_sec))
#define	timespecadd(tsp, usp, vsp)					\
	do {								\
		(vsp)->tv_sec = (tsp)->tv_sec + (usp)->tv_sec;		\
		(vsp)->tv_nsec = (tsp)->tv_nsec + (usp)->tv_nsec;	\
		if ((vsp)->tv_nsec >= 1000000000L) {			\
			(vsp)->tv_sec++;				\
			(vsp)->tv_nsec -= 1000000000L;			\
		}							\
	} while (0)
#define	timespecsub(tsp, usp, vsp)					\
	do {								\
		(vsp)->tv_sec = (tsp)->tv_sec - (usp)->tv_sec;		\
		(vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec;	\
		if ((vsp)->tv_nsec < 0) {				\
			(vsp)->tv_sec--;				\
			(vsp)->tv_nsec += 1000000000L;			\
		}							\
	} while (0)

#ifdef	_CLOCKID_T_
typedef	_CLOCKID_T_	clockid_t;
#undef	_CLOCKID_T_
#endif

#define CLOCK_REALTIME	0
#define CLOCK_IDLETIME	1		/* XXX non standard */
#define CLOCK_PROCTIME	2		/* XXX non standard */
#define CLOCK_MONOTONIC	3

int	clock_getres (clockid_t, struct timespec *);
int	clock_gettime (clockid_t, struct timespec *);
int	clock_settime (clockid_t, const struct timespec *);
int	nanosleep (const struct timespec *, struct timespec *);

struct sigevent;

#define TIMER_ABSTIME	1

#ifdef	_TIMER_T_
typedef	_TIMER_T_	timer_t;
#undef	_TIMER_T_
#endif

int	timer_create (clockid_t, struct sigevent *, timer_t *);
int	timer_delete (timer_t);
int	timer_getoverrun (timer_t);
int	timer_gettime (timer_t, struct itimerspec *);
int	timer_settime (timer_t, int, const struct itimerspec *,
		       struct itimerspec *);

#endif /* _POSIX_TIMERS */

#ifdef __cplusplus
}
#endif
#endif
