#ifndef SYSTEM_H
#define SYSTEM_H
#include"bsp.h"
# include "stddef.h"//size_t

	#define	HEAP_BYTES			8192

	#define	PRINT_ALLOCS


#define	COUNTOF(ARR)	(sizeof(ARR)/sizeof(*(ARR)))

void* acme_memset(void *dst, unsigned val, unsigned size);
void *acme_memcpy(void *dst, const void *src, unsigned bytesize);
void* acme_memmove(void *dst, const void *src, unsigned bytesize);
void memfill(void *dst, unsigned dstbytes, const void *src, unsigned srcbytes);
void printn(const char *str,int n);
void panic(void);
#define print_char	uart_putc
void print(const char *str);
int print_idec(int n);
int print_ihex(unsigned n);
int print_ihex2(unsigned n, int ndigits);
void print_memory(const char *header, const void *start, const void *end, int width);

void*	acme_malloc(unsigned size, unsigned align);
unsigned acme_msize(void *ptr);//takes non-negligible time
void*	acme_realloc(void *ptr, unsigned size, unsigned align);
void	acme_free(void *ptr);

#define memset	acme_memset
#define memcpy	acme_memcpy
#define	memmove	acme_memmove
#define	malloc	acme_malloc
#define	realloc	acme_realloc
#define	free	acme_free


void*	OS_newTask(int (*proc)(void*), void *param, unsigned stacksize, unsigned short priority, const char *name);
void	OS_deleteTask(void *hTask);
void	OS_startScheduler(int period, void (*idleHook)(void));

void*	OS_createSemaphore();
void	OS_takeSemaphore(void *hSemaphore);
void	OS_giveSemaphore(void *hSemaphore);

const char*		OS_getTaskName(void *hTask);
unsigned short	OS_getTaskPriority(void *hTask);
void			OS_setTaskPriority(void *hTask, unsigned short priority);

unsigned	OS_getTickCount(void);
void		OS_sleepUntil(unsigned tickstamp);

#endif
