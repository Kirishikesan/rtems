/*
 *  COPYRIGHT (c) 1989-2015
 *  On-Line Applications Research Corporation (OAR).
 */

#include <sys/types.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <rtems.h>
#include <rtems/test.h>
#include <rtems/score/threadimpl.h>

/*
 * This is the entry point automatically generated by GNAT.
 */
extern int gnat_main ( int argc, char **argv, char **envp );

static void *POSIX_Init(
  void *argument
)
{
  (void) gnat_main ( 0, 0, 0 );

  exit( 0 );
}

/*
 *  Prototypes for various test support routines. Since these are bound to
 *  from Ada, there are no external .h files even though they must be public.
 */
void ada_test_begin(void);
void ada_test_end(void);
uint32_t milliseconds_per_tick(void);
uint32_t ticks_per_second(void);
size_t work_space_size(void);
uint32_t is_configured_multiprocessing(void);
uint32_t get_node(void);
rtems_id tcb_to_id(Thread_Control *tcb);
void check_type(long type, long size, long alignment);

/*
 *  By putting this in brackets rather than quotes, we get the search
 *  path and can get this file from ".." in the mptests.
 */
#define CONFIGURE_INIT

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#include <rtems/confdefs.h>

const char rtems_test_name[] = ADA_TEST_NAME;

void ada_test_begin(void)
{
  rtems_test_begin(rtems_test_name, RTEMS_TEST_STATE_PASS);
}

void ada_test_end(void)
{
  fsync(STDOUT_FILENO);
  rtems_test_end(rtems_test_name);
}

rtems_id tcb_to_id(
  Thread_Control *tcb
)
{
  return tcb->Object.id; /* Only for sp04 */
}

uint32_t milliseconds_per_tick(void)
{
  return CONFIGURE_MICROSECONDS_PER_TICK / 1000;
}

uint32_t ticks_per_second(void)
{
  return rtems_clock_get_ticks_per_second();
}

size_t work_space_size(void)
{
  return rtems_configuration_get_work_space_size()
    + rtems_configuration_get_stack_space_size();
}

uint32_t is_configured_multiprocessing(void)
{
#if defined(RTEMS_MULTIPROCESSING)
  return 1;
#else
  return 0;
#endif
}

uint32_t get_node(void)
{
  return rtems_object_get_local_node();
}

typedef struct {
  const char *name;
  long size;
  long alignment;
} type_spec;

#define TYPE_SPEC(t) { #t, sizeof(t) * CHAR_BIT, _Alignof(t) }

static const type_spec types[] = {
  TYPE_SPEC(clockid_t),
  TYPE_SPEC(pid_t),
  TYPE_SPEC(pthread_attr_t),
  TYPE_SPEC(pthread_condattr_t),
  TYPE_SPEC(pthread_cond_t),
  TYPE_SPEC(pthread_key_t),
  TYPE_SPEC(pthread_mutexattr_t),
  TYPE_SPEC(pthread_mutex_t),
  TYPE_SPEC(pthread_rwlockattr_t),
  TYPE_SPEC(pthread_rwlock_t),
  TYPE_SPEC(pthread_t),
  TYPE_SPEC(rtems_id),
  TYPE_SPEC(sigset_t),
  TYPE_SPEC(stack_t),
  TYPE_SPEC(struct sched_param),
  TYPE_SPEC(struct sigaction),
  TYPE_SPEC(struct timespec)
};

void check_type(long type, long size, long alignment)
{
  if (type >= 0 && type < (long) RTEMS_ARRAY_SIZE(types)) {
    const type_spec *ts;

    ts = &types[type];
    printf(
      "%s: size %li == %li, alignment %li == %li\n",
      ts->name,
      ts->size,
      size,
      ts->alignment,
      alignment
    );
    if (ts->size != size || ts->alignment != alignment) {
      exit(0);
    }
  } else {
    exit(0);
  }
}
