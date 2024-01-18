// commit message qemu@71b58b82da (target=0, prob=0.31757596, correct=True): qemu-io: add write -z option for bdrv_co_write_zeroes
/*0   */ static int write_f(int argc, char **argv)                                    // (11) 0.0293
/*2   */ {                                                                            // (35) 0.001953
/*4   */     struct timeval t1, t2;                                                   // (18) 0.02344
/*6   */     int Cflag = 0, pflag = 0, qflag = 0, bflag = 0;                          // (1) 0.04687
/*8   */     int c, cnt;                                                              // (27) 0.01758
/*10  */     char *buf;                                                               // (32) 0.01367
/*12  */     int64_t offset;                                                          // (29) 0.01758
/*14  */     int count;                                                               // (33) 0.01172
/*16  */     /* Some compilers get confused and warn if this is not initialized.  */  // (4) 0.03711
/*18  */     int total = 0;                                                           // (30) 0.01563
/*20  */     int pattern = 0xcd;                                                      // (26) 0.01953
/*24  */     while ((c = getopt(argc, argv, "bCpP:q")) != EOF) {                      // (0) 0.05664
/*26  */         switch (c) {                                                         // (19) 0.02344
/*28  */         case 'b':                                                            // (23) 0.02148
/*30  */             bflag = 1;                                                       // (7) 0.03125
/*32  */             break;                                                           // (16) 0.02539
/*34  */         case 'C':                                                            // (24) 0.02148
/*36  */             Cflag = 1;                                                       // (8) 0.03125
/*38  */             break;                                                           // (17) 0.02539
/*40  */         case 'p':                                                            // (25) 0.02148
/*42  */             pflag = 1;                                                       // (10) 0.03125
/*44  */             break;                                                           // (15) 0.02539
/*46  */         case 'P':                                                            // (21) 0.02148
/*48  */             pattern = parse_pattern(optarg);                                 // (3) 0.03906
/*50  */             if (pattern < 0) {                                               // (5) 0.03516
/*52  */                 return 0;                                                    // (6) 0.03516
/*54  */             }                                                                // (20) 0.02344
/*56  */             break;                                                           // (14) 0.02539
/*58  */         case 'q':                                                            // (22) 0.02148
/*60  */             qflag = 1;                                                       // (9) 0.03125
/*62  */             break;                                                           // (13) 0.02539
/*64  */         default:                                                             // (28) 0.01758
/*66  */             return command_usage(&write_cmd);                                // (2) 0.03906
/*68  */         }                                                                    // (31) 0.01562
/*70  */     }                                                                        // (34) 0.007813
/*74  */     if (optind != argc - 2) {                                                // (12) 0.02734
/*76  */         return command_usage(&write_cmd);                                    // 0.0
/*78  */     }                                                                        // 0.0
/*82  */     if (bflag && pflag) {                                                    // 0.0
/*84  */         printf("-b and -p cannot be specified at the same time\n");          // 0.0
/*86  */         return 0;                                                            // 0.0
/*88  */     }                                                                        // 0.0
/*92  */     offset = cvtnum(argv[optind]);                                           // 0.0
/*94  */     if (offset < 0) {                                                        // 0.0
/*96  */         printf("non-numeric length argument -- %s\n", argv[optind]);         // 0.0
/*98  */         return 0;                                                            // 0.0
/*100 */     }                                                                        // 0.0
/*104 */     optind++;                                                                // 0.0
/*106 */     count = cvtnum(argv[optind]);                                            // 0.0
/*108 */     if (count < 0) {                                                         // 0.0
/*110 */         printf("non-numeric length argument -- %s\n", argv[optind]);         // 0.0
/*112 */         return 0;                                                            // 0.0
/*114 */     }                                                                        // 0.0
/*118 */     if (!pflag) {                                                            // 0.0
/*120 */         if (offset & 0x1ff) {                                                // 0.0
/*122 */             printf("offset %" PRId64 " is not sector aligned\n",             // 0.0
/*124 */                    offset);                                                  // 0.0
/*126 */             return 0;                                                        // 0.0
/*128 */         }                                                                    // 0.0
/*132 */         if (count & 0x1ff) {                                                 // 0.0
/*134 */             printf("count %d is not sector aligned\n",                       // 0.0
/*136 */                    count);                                                   // 0.0
/*138 */             return 0;                                                        // 0.0
/*140 */         }                                                                    // 0.0
/*142 */     }                                                                        // 0.0
/*146 */     buf = qemu_io_alloc(count, pattern);                                     // 0.0
/*150 */     gettimeofday(&t1, NULL);                                                 // 0.0
/*152 */     if (pflag) {                                                             // 0.0
/*154 */         cnt = do_pwrite(buf, offset, count, &total);                         // 0.0
/*156 */     } else if (bflag) {                                                      // 0.0
/*158 */         cnt = do_save_vmstate(buf, offset, count, &total);                   // 0.0
/*160 */     } else {                                                                 // 0.0
/*162 */         cnt = do_write(buf, offset, count, &total);                          // 0.0
/*164 */     }                                                                        // 0.0
/*166 */     gettimeofday(&t2, NULL);                                                 // 0.0
/*170 */     if (cnt < 0) {                                                           // 0.0
/*172 */         printf("write failed: %s\n", strerror(-cnt));                        // 0.0
/*174 */         goto out;                                                            // 0.0
/*176 */     }                                                                        // 0.0
/*180 */     if (qflag) {                                                             // 0.0
/*182 */         goto out;                                                            // 0.0
/*184 */     }                                                                        // 0.0
/*188 */     /* Finally, report back -- -C gives a parsable format */                 // 0.0
/*190 */     t2 = tsub(t2, t1);                                                       // 0.0
/*192 */     print_report("wrote", &t2, offset, count, total, cnt, Cflag);            // 0.0
/*196 */ out:                                                                         // 0.0
/*198 */     qemu_io_free(buf);                                                       // 0.0
/*202 */     return 0;                                                                // 0.0
/*204 */ }                                                                            // 0.0
