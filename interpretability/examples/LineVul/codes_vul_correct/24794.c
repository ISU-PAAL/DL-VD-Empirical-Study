// commit message qemu@1f51470d04 (target=1, prob=0.5993009, correct=True): Revert "qemu-char: Print strerror message on failure" and deps
/*0  */ static int qemu_chr_open_win_file_out(QemuOpts *opts, CharDriverState **_chr)  // (1) 0.1553
/*2  */ {                                                                              // (9) 0.004566
/*4  */     const char *file_out = qemu_opt_get(opts, "path");                         // (4) 0.1096
/*6  */     HANDLE fd_out;                                                             // (7) 0.05023
/*10 */     fd_out = CreateFile(file_out, GENERIC_WRITE, FILE_SHARE_READ, NULL,        // (2) 0.137
/*12 */                         OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);             // (0) 0.1826
/*14 */     if (fd_out == INVALID_HANDLE_VALUE) {                                      // (5) 0.09132
/*16 */         return -EIO;                                                           // (6) 0.05479
/*18 */     }                                                                          // (8) 0.01826
/*22 */     return qemu_chr_open_win_file(fd_out, _chr);                               // (3) 0.1142
/*24 */ }                                                                              // (10) 0.004566
