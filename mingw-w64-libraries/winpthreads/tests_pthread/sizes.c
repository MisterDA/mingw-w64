#define _WIN32_WINNT 0x400

#include <inttypes.h>
#include "test.h"

int
main(void)
{
  printf("Sizes of winpthreads structs\n");
  printf("-------------------------------\n");
  printf("%30s %4" PRIdPTR "\n", "pthread_t", sizeof(pthread_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_attr_t", sizeof(pthread_attr_t));
  /*  printf("%30s %4" PRIdPTR "\n", "sem_t", sizeof(struct sem_t)); */
  /* printf("%30s %4" PRIdPTR "\n", "mutex_t", sizeof(mutex_t)); */
  printf("%30s %4" PRIdPTR "\n", "pthread_mutexattr_t_", sizeof(pthread_mutexattr_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_barrier_t_", sizeof(barrier_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_barrierattr_t", sizeof(pthread_barrierattr_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_key_t", sizeof(pthread_key_t));
  printf("%30s %4" PRIdPTR "\n", "cond_t", sizeof(cond_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_condattr_t", sizeof(pthread_condattr_t));
  printf("%30s %4" PRIdPTR "\n", "rwlock_t", sizeof(rwlock_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_rwlockattr_t", sizeof(pthread_rwlockattr_t));
  printf("%30s %4" PRIdPTR "\n", "pthread_once_t", sizeof(pthread_once_t));
  /* printf("%30s %4" PRIdPTR "\n", "ptw32_cleanup_t", sizeof(struct ptw32_cleanup_t)); */
  /* printf("%30s %4" PRIdPTR "\n", "ptw32_mcs_node_t_", sizeof(struct ptw32_mcs_node_t_)); */
  printf("%30s %4" PRIdPTR "\n", "sched_param", sizeof(struct sched_param));
  printf("-------------------------------\n");

  return 0;
}
