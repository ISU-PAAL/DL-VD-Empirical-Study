// commit message qemu@9e559533bd (target=1, prob=0.32128435, correct=False): qemu-io: Fix memory leaks
/*0   */ static int writev_f(int argc, char **argv)                                   // (8) 0.03125
/*2   */ {                                                                            // (35) 0.001953
/*4   */     struct timeval t1, t2;                                                   // (17) 0.02344
/*6   */     int Cflag = 0, qflag = 0;                                                // (12) 0.02734
/*8   */     int c, cnt;                                                              // (27) 0.01758
/*10  */     char *buf;                                                               // (32) 0.01367
/*12  */     int64_t offset;                                                          // (28) 0.01758
/*14  */     /* Some compilers get confused and warn if this is not initialized.  */  // (4) 0.03711
/*16  */     int total = 0;                                                           // (30) 0.01562
/*18  */     int nr_iov;                                                              // (26) 0.01758
/*20  */     int pattern = 0xcd;                                                      // (24) 0.01953
/*22  */     QEMUIOVector qiov;                                                       // (20) 0.02148
/*26  */     while ((c = getopt(argc, argv, "CqP:")) != EOF) {                        // (0) 0.05273
/*28  */         switch (c) {                                                         // (18) 0.02344
/*30  */         case 'C':                                                            // (22) 0.02148
/*32  */             Cflag = 1;                                                       // (10) 0.03125
/*34  */             break;                                                           // (14) 0.02539
/*36  */         case 'q':                                                            // (21) 0.02148
/*38  */             qflag = 1;                                                       // (9) 0.03125
/*40  */             break;                                                           // (15) 0.02539
/*42  */         case 'P':                                                            // (23) 0.02148
/*44  */             pattern = parse_pattern(optarg);                                 // (3) 0.03906
/*46  */             if (pattern < 0) {                                               // (5) 0.03516
/*48  */                 return 0;                                                    // (6) 0.03516
/*50  */             }                                                                // (19) 0.02344
/*52  */             break;                                                           // (16) 0.02539
/*54  */         default:                                                             // (29) 0.01758
/*56  */             return command_usage(&writev_cmd);                               // (2) 0.04102
/*58  */         }                                                                    // (31) 0.01562
/*60  */     }                                                                        // (34) 0.007812
/*64  */     if (optind > argc - 2) {                                                 // (13) 0.02734
/*66  */         return command_usage(&writev_cmd);                                   // (7) 0.0332
/*68  */     }                                                                        // (33) 0.007812
/*72  */     offset = cvtnum(argv[optind]);                                           // (11) 0.0293
/*74  */     if (offset < 0) {                                                        // (25) 0.01953
/*76  */         printf("non-numeric length argument -- %s\n", argv[optind]);         // (1) 0.05273
/*78  */         return 0;                                                            // 0.0
/*80  */     }                                                                        // 0.0
/*82  */     optind++;                                                                // 0.0
/*86  */     if (offset & 0x1ff) {                                                    // 0.0
/*88  */         printf("offset %" PRId64 " is not sector aligned\n",                 // 0.0
/*90  */                offset);                                                      // 0.0
/*92  */         return 0;                                                            // 0.0
/*94  */     }                                                                        // 0.0
/*98  */     nr_iov = argc - optind;                                                  // 0.0
/*100 */     buf = create_iovec(&qiov, &argv[optind], nr_iov, pattern);               // 0.0
/*102 */     if (buf == NULL) {                                                       // 0.0
/*104 */         return 0;                                                            // 0.0
/*106 */     }                                                                        // 0.0
/*110 */     gettimeofday(&t1, NULL);                                                 // 0.0
/*112 */     cnt = do_aio_writev(&qiov, offset, &total);                              // 0.0
/*114 */     gettimeofday(&t2, NULL);                                                 // 0.0
/*118 */     if (cnt < 0) {                                                           // 0.0
/*120 */         printf("writev failed: %s\n", strerror(-cnt));                       // 0.0
/*122 */         goto out;                                                            // 0.0
/*124 */     }                                                                        // 0.0
/*128 */     if (qflag) {                                                             // 0.0
/*130 */         goto out;                                                            // 0.0
/*132 */     }                                                                        // 0.0
/*136 */     /* Finally, report back -- -C gives a parsable format */                 // 0.0
/*138 */     t2 = tsub(t2, t1);                                                       // 0.0
/*140 */     print_report("wrote", &t2, offset, qiov.size, total, cnt, Cflag);        // 0.0
/*142 */ out:                                                                         // 0.0
/*145 */     qemu_io_free(buf);                                                       // 0.0
/*147 */     return 0;                                                                // 0.0
/*149 */ }                                                                            // 0.0
