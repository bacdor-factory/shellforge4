
/* $Id$ */

#ifdef SF_USE_ERRNO

static int errno=1234;

#define __sfsyscall_return(type, res) \
do { \
        if ((unsigned long)(res) >= (unsigned long)(-125)) { \
                errno = -(res); \
                res = -1; \
        } \
        return (type) (res); \
} while (0)

#else /* SF_USE_ERRNO */

#define __sfsyscall_return(type, res) \
do { \
	return (type) (res); \
} while (0)

#endif /* SF_USE_ERRNO */


/* syscall macros */

#define _sfsyscall0(type, name) 						\
type name(void) {					\
	long __res;						\
	__asm__ volatile("###> " #name " <###\n\t"						\
		"syscall"					\
		: "=a" (__res)					\
		: "0" (__NR_##name)				\
		: "memory", "rcx", "r11", "cc"			\
	);							\
	__sfsyscall_return(type,__res);						\
}

#define _sfsyscall1(type, name, type1, arg1) 					\
type name(type1 arg1) {						\
	long __res;						\
	register type1 rdi asm("rdi");				\
	rdi = arg1;						\
	asm volatile("###> " #name "(%2) <###\n\t"						\
		"syscall"					\
		: "=a" (__res)					\
		: "0" (__NR_##name),				\
		  "r" (rdi)					\
		: "memory", "rcx", "r11", "cc"			\
	);							\
	__sfsyscall_return(type,__res);						\
}

#define _sfsyscall2(type, name, type1, arg1, type2, arg2) 				\
	type name(type1 arg1, type2 arg2) {				\
		long __res;						\
		register type1 rdi asm("rdi");				\
		register type2 rsi asm("rsi");				\
		rdi = arg1;						\
		rsi = arg2;						\
		__asm__ volatile("###> " #name "(%2, %3) <###\n\t" 						\
				"syscall"					\
				: "=a" (__res)					\
				: "0" (__NR_##name),				\
				"r" (rdi),					\
				"r" (rsi)					\
				: "memory", "rcx", "r11", "cc"			\
				);							\
		__sfsyscall_return(type, __res);						\
}

#define _sfsyscall3(type, name, type1, arg1, type2, arg2, type3, arg3) 			\
	type name(type1 arg1, type2 arg2, type3 arg3) {			\
		long __res;						\
		register type1 rdi asm("rdi");				\
		register type2 rsi asm("rsi");				\
		register type3 rdx asm("rdx");				\
		rdi = arg1;						\
		rsi = arg2;						\
		rdx = arg3;						\
		asm volatile("###> " #name "(%2, %3, %4) <###\n\t"						\
				"syscall"					\
				: "=a" (__res)					\
				: "0" (__NR_##name),				\
				"r" (rdi),					\
				"r" (rsi),					\
				"r" (rdx)					\
				: "memory", "rcx", "r11", "cc"			\
				);							\
		__sfsyscall_return(type, __res);						\
	}

#define _sfsyscall4(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4) 		\
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {	\
		long __res;						\
		register type1 rdi asm("rdi");				\
		register type2 rsi asm("rsi");				\
		register type3 rdx asm("rdx");				\
		register type4 r10 asm("r10");				\
		rdi = arg1;						\
		rsi = arg2;						\
		rdx = arg3;						\
		r10 = arg4;						\
		asm volatile("###> " #name "(%2, %3, %4, %5) <###\n\t"						\
				"syscall"					\
				: "=a" (__res)					\
				: "0" (__NR_##name),				\
				"r" (rdi),					\
				"r" (rsi),					\
				"r" (rdx),					\
				"r" (r10)					\
				: "memory", "rcx", "r11", "cc"			\
				);							\
		__sfsyscall_return(type, __res);						\
	}

#define _sfsyscall5(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) 	\
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
			type5 arg5) {						\
		long __res;						\
		register type1 rdi asm("rdi");				\
		register type2 rsi asm("rsi");				\
		register type3 rdx asm("rdx");				\
		register type4 r10 asm("r10");				\
		register type5 r8  asm("r8");				\
		rdi = arg1;						\
		rsi = arg2;						\
		rdx = arg3;						\
		r10 = arg4;						\
		r8  = arg5;						\
		asm volatile("###> " #name "(%2, %3, %4, %5, %6) <###\n\t"						\
				"syscall"					\
				: "=a" (__res)					\
				: "0" (__NR_##name),				\
				"r" (rdi),					\
				"r" (rsi),					\
				"r" (rdx),					\
				"r" (r10),					\
				"r" (r8)					\
				: "memory", "rcx", "r11", "cc"			\
				);							\
		__sfsyscall_return(type, __res);						\
	}

#define _sfsyscall6(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6)\
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
			type5 arg5, type6 arg6) {				\
		long __res;						\
		register type1 rdi asm("rdi");				\
		register type2 rsi asm("rsi");				\
		register type3 rdx asm("rdx");				\
		register type4 r10 asm("r10");				\
		register type5 r8  asm("r8");				\
		register type6 r9  asm("r9");				\
		rdi = arg1;						\
		rsi = arg2;						\
		rdx = arg3;						\
		r10 = arg4;						\
		r8  = arg5;						\
		r9  = arg6;						\
		asm volatile("###> " #name "(%2, %3, %4, %5, %6, %7) <###\n\t"						\
				"syscall"					\
				: "=a" (__res)					\
				: "0" (__NR_##name),				\
				"r" (rdi),					\
				"r" (rsi),					\
				"r" (rdx),					\
				"r" (r10),					\
				"r" (r8),					\
				"r" (r9)					\
				: "memory", "rcx", "r11", "cc"			\
				);							\
		__sfsyscall_return(type, __res);						\
	}
