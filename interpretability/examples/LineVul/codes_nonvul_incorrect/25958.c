// commit message qemu@dc38852aaa (target=0, prob=0.5402681, correct=False): qemu-io: Use bool for command line flags
/*0   */ static int discard_f(BlockBackend *blk, int argc, char **argv)         // (6) 0.04297
/*2   */ {                                                                      // (32) 0.001953
/*4   */     struct timeval t1, t2;                                             // (16) 0.02344
/*6   */     int Cflag = 0, qflag = 0;                                          // (13) 0.02734
/*8   */     int c, ret;                                                        // (26) 0.01562
/*10  */     int64_t offset, count;                                             // (18) 0.02148
/*14  */     while ((c = getopt(argc, argv, "Cq")) != -1) {                     // (3) 0.04883
/*16  */         switch (c) {                                                   // (17) 0.02344
/*18  */         case 'C':                                                      // (19) 0.02148
/*20  */             Cflag = 1;                                                 // (8) 0.03125
/*22  */             break;                                                     // (14) 0.02539
/*24  */         case 'q':                                                      // (20) 0.02148
/*26  */             qflag = 1;                                                 // (9) 0.03125
/*28  */             break;                                                     // (15) 0.02539
/*30  */         default:                                                       // (25) 0.01758
/*32  */             return qemuio_command_usage(&discard_cmd);                 // (0) 0.05078
/*34  */         }                                                              // (27) 0.01562
/*36  */     }                                                                  // (29) 0.007812
/*40  */     if (optind != argc - 2) {                                          // (12) 0.02734
/*42  */         return qemuio_command_usage(&discard_cmd);                     // (7) 0.04297
/*44  */     }                                                                  // (30) 0.007812
/*48  */     offset = cvtnum(argv[optind]);                                     // (11) 0.0293
/*50  */     if (offset < 0) {                                                  // (23) 0.01953
/*52  */         print_cvtnum_err(offset, argv[optind]);                        // (5) 0.04492
/*54  */         return 0;                                                      // (24) 0.01953
/*56  */     }                                                                  // (31) 0.007812
/*60  */     optind++;                                                          // (28) 0.01172
/*62  */     count = cvtnum(argv[optind]);                                      // (10) 0.0293
/*64  */     if (count < 0) {                                                   // (21) 0.01953
/*66  */         print_cvtnum_err(count, argv[optind]);                         // (4) 0.04492
/*68  */         return 0;                                                      // (22) 0.01953
/*70  */     } else if (count >> BDRV_SECTOR_BITS > INT_MAX) {                  // (1) 0.04883
/*72  */         printf("length cannot exceed %"PRIu64", given %s\n",           // (2) 0.04883
/*74  */                (uint64_t)INT_MAX << BDRV_SECTOR_BITS,                  // 0.0
/*76  */                argv[optind]);                                          // 0.0
/*78  */         return 0;                                                      // 0.0
/*80  */     }                                                                  // 0.0
/*84  */     gettimeofday(&t1, NULL);                                           // 0.0
/*86  */     ret = blk_discard(blk, offset >> BDRV_SECTOR_BITS,                 // 0.0
/*88  */                       count >> BDRV_SECTOR_BITS);                      // 0.0
/*90  */     gettimeofday(&t2, NULL);                                           // 0.0
/*94  */     if (ret < 0) {                                                     // 0.0
/*96  */         printf("discard failed: %s\n", strerror(-ret));                // 0.0
/*98  */         goto out;                                                      // 0.0
/*100 */     }                                                                  // 0.0
/*104 */     /* Finally, report back -- -C gives a parsable format */           // 0.0
/*106 */     if (!qflag) {                                                      // 0.0
/*108 */         t2 = tsub(t2, t1);                                             // 0.0
/*110 */         print_report("discard", &t2, offset, count, count, 1, Cflag);  // 0.0
/*112 */     }                                                                  // 0.0
/*116 */ out:                                                                   // 0.0
/*118 */     return 0;                                                          // 0.0
/*120 */ }                                                                      // 0.0
