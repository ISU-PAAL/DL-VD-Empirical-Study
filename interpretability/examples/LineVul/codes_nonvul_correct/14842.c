// commit message qemu@77eec1b3f1 (target=0, prob=0.033311673, correct=True): hw/9pfs: Improve portability to older systems
/*0 */ static inline int open_by_handle(int mountfd, const char *fh, int flags)  // (0) 0.44
/*2 */ {                                                                         // (4) 0.02
/*4 */     errno = ENOSYS;                                                       // (1) 0.2
/*6 */     return -1;                                                            // (2) 0.14
/*8 */ }                                                                         // (3) 0.02
