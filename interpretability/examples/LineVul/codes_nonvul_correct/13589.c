// commit message qemu@1acae9f223 (target=0, prob=0.04317273, correct=True): linux-user: Fix sys_utimensat (would not compile on old glibc)
/*0  */ _syscall4(int,sys_utimensat,int,dirfd,const char *,pathname,       // (1) 0.1634
/*2  */           const struct timespec *,tsp,int,flags)                   // (2) 0.1438
/*4  */ #endif                                                             // (8) 0.01307
/*6  */ #endif /* CONFIG_UTIMENSAT  */                                     // (4) 0.07189
/*10 */ #ifdef CONFIG_INOTIFY                                              // (7) 0.05882
/*12 */ #include <sys/inotify.h>                                           // (5) 0.07189
/*16 */ #if defined(TARGET_NR_inotify_init) && defined(__NR_inotify_init)  // (0) 0.1765
/*18 */ static int sys_inotify_init(void)                                  // (3) 0.07844
/*20 */ {                                                                  // (9) 0.006538
/*22 */   return (inotify_init());                                         // (6) 0.05882
/*24 */ }                                                                  // (10) 0.006536
