// commit message qemu@0e01b76e7c (target=1, prob=0.9992009, correct=True): qemu-io: Fix memory leak in 'aio_write -z'
/*0   */ static int aio_write_f(BlockBackend *blk, int argc, char **argv)          // (2) 0.04883
/*2   */ {                                                                         // (30) 0.001953
/*4   */     int nr_iov, c;                                                        // (20) 0.02148
/*6   */     int pattern = 0xcd;                                                   // (25) 0.01953
/*8   */     struct aio_ctx *ctx = g_new0(struct aio_ctx, 1);                      // (3) 0.04687
/*12  */     ctx->blk = blk;                                                       // (17) 0.02344
/*14  */     while ((c = getopt(argc, argv, "CqP:z")) != -1) {                     // (0) 0.05469
/*16  */         switch (c) {                                                      // (18) 0.02344
/*18  */         case 'C':                                                         // (22) 0.02148
/*20  */             ctx->Cflag = 1;                                               // (9) 0.03711
/*22  */             break;                                                        // (13) 0.02539
/*24  */         case 'q':                                                         // (23) 0.02148
/*26  */             ctx->qflag = 1;                                               // (8) 0.03711
/*28  */             break;                                                        // (14) 0.02539
/*30  */         case 'P':                                                         // (21) 0.02148
/*32  */             pattern = parse_pattern(optarg);                              // (5) 0.03906
/*34  */             if (pattern < 0) {                                            // (10) 0.03516
/*37  */                 return 0;                                                 // (11) 0.03516
/*39  */             }                                                             // (19) 0.02344
/*41  */             break;                                                        // (15) 0.02539
/*43  */         case 'z':                                                         // (24) 0.02148
/*45  */             ctx->zflag = 1;                                               // (7) 0.03711
/*47  */             break;                                                        // (16) 0.02539
/*49  */         default:                                                          // (26) 0.01758
/*52  */             return qemuio_command_usage(&aio_write_cmd);                  // (1) 0.05469
/*54  */         }                                                                 // (27) 0.01562
/*56  */     }                                                                     // (28) 0.007812
/*60  */     if (optind > argc - 2) {                                              // (12) 0.02734
/*63  */         return qemuio_command_usage(&aio_write_cmd);                      // (4) 0.04687
/*65  */     }                                                                     // (29) 0.007812
/*69  */     if (ctx->zflag && optind != argc - 2) {                               // (6) 0.03711
/*71  */         printf("-z supports only a single length parameter\n");           // 0.0
/*74  */         return 0;                                                         // 0.0
/*76  */     }                                                                     // 0.0
/*80  */     if (ctx->zflag && ctx->Pflag) {                                       // 0.0
/*82  */         printf("-z and -P cannot be specified at the same time\n");       // 0.0
/*85  */         return 0;                                                         // 0.0
/*87  */     }                                                                     // 0.0
/*91  */     ctx->offset = cvtnum(argv[optind]);                                   // 0.0
/*93  */     if (ctx->offset < 0) {                                                // 0.0
/*95  */         print_cvtnum_err(ctx->offset, argv[optind]);                      // 0.0
/*98  */         return 0;                                                         // 0.0
/*100 */     }                                                                     // 0.0
/*102 */     optind++;                                                             // 0.0
/*106 */     if (ctx->offset & 0x1ff) {                                            // 0.0
/*108 */         printf("offset %" PRId64 " is not sector aligned\n",              // 0.0
/*110 */                ctx->offset);                                              // 0.0
/*112 */         block_acct_invalid(blk_get_stats(blk), BLOCK_ACCT_WRITE);         // 0.0
/*115 */         return 0;                                                         // 0.0
/*117 */     }                                                                     // 0.0
/*121 */     if (ctx->zflag) {                                                     // 0.0
/*123 */         int64_t count = cvtnum(argv[optind]);                             // 0.0
/*125 */         if (count < 0) {                                                  // 0.0
/*127 */             print_cvtnum_err(count, argv[optind]);                        // 0.0
/*130 */             return 0;                                                     // 0.0
/*132 */         }                                                                 // 0.0
/*136 */         ctx->qiov.size = count;                                           // 0.0
/*138 */         blk_aio_write_zeroes(blk, ctx->offset >> 9, count >> 9, 0,        // 0.0
/*140 */                              aio_write_done, ctx);                        // 0.0
/*142 */     } else {                                                              // 0.0
/*144 */         nr_iov = argc - optind;                                           // 0.0
/*146 */         ctx->buf = create_iovec(blk, &ctx->qiov, &argv[optind], nr_iov,   // 0.0
/*148 */                                 pattern);                                 // 0.0
/*150 */         if (ctx->buf == NULL) {                                           // 0.0
/*152 */             block_acct_invalid(blk_get_stats(blk), BLOCK_ACCT_WRITE);     // 0.0
/*155 */             return 0;                                                     // 0.0
/*157 */         }                                                                 // 0.0
/*161 */         gettimeofday(&ctx->t1, NULL);                                     // 0.0
/*163 */         block_acct_start(blk_get_stats(blk), &ctx->acct, ctx->qiov.size,  // 0.0
/*165 */                          BLOCK_ACCT_WRITE);                               // 0.0
/*169 */         blk_aio_writev(blk, ctx->offset >> 9, &ctx->qiov,                 // 0.0
/*171 */                        ctx->qiov.size >> 9, aio_write_done, ctx);         // 0.0
/*173 */     }                                                                     // 0.0
/*175 */     return 0;                                                             // 0.0
/*177 */ }                                                                         // 0.0
