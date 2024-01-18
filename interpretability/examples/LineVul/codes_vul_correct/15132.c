// commit message qemu@9e559533bd (target=1, prob=0.99924254, correct=True): qemu-io: Fix memory leaks
/*0  */ static void aio_read_done(void *opaque, int ret)                          // (10) 0.0332
/*2  */ {                                                                         // (30) 0.001953
/*4  */     struct aio_ctx *ctx = opaque;                                         // (14) 0.02539
/*6  */     struct timeval t2;                                                    // (22) 0.01758
/*10 */     gettimeofday(&t2, NULL);                                              // (15) 0.02539
/*14 */     if (ret < 0) {                                                        // (20) 0.01953
/*16 */         printf("readv failed: %s\n", strerror(-ret));                     // (7) 0.04687
/*18 */         goto out;                                                         // (19) 0.01953
/*20 */     }                                                                     // (25) 0.007812
/*24 */     if (ctx->Pflag) {                                                     // (16) 0.02148
/*26 */         void *cmp_buf = g_malloc(ctx->qiov.size);                         // (6) 0.04883
/*30 */         memset(cmp_buf, ctx->pattern, ctx->qiov.size);                    // (4) 0.05273
/*32 */         if (memcmp(ctx->buf, cmp_buf, ctx->qiov.size)) {                  // (2) 0.05859
/*34 */             printf("Pattern verification failed at offset %"              // (8) 0.03906
/*36 */                    PRId64 ", %zd bytes\n", ctx->offset, ctx->qiov.size);  // (0) 0.08203
/*38 */         }                                                                 // (24) 0.01562
/*40 */         g_free(cmp_buf);                                                  // (13) 0.0293
/*42 */     }                                                                     // (26) 0.007812
/*46 */     if (ctx->qflag) {                                                     // (17) 0.02148
/*48 */         goto out;                                                         // (21) 0.01953
/*50 */     }                                                                     // (27) 0.007812
/*54 */     if (ctx->vflag) {                                                     // (18) 0.02148
/*56 */         dump_buffer(ctx->buf, ctx->offset, ctx->qiov.size);               // (3) 0.05469
/*58 */     }                                                                     // (28) 0.007812
/*62 */     /* Finally, report back -- -C gives a parsable format */              // (11) 0.0332
/*64 */     t2 = tsub(t2, ctx->t1);                                               // (9) 0.03516
/*66 */     print_report("read", &t2, ctx->offset, ctx->qiov.size,                // (5) 0.05078
/*68 */                  ctx->qiov.size, 1, ctx->Cflag);                          // (1) 0.0625
/*70 */ out:                                                                      // (29) 0.003906
/*72 */     qemu_io_free(ctx->buf);                                               // (12) 0.0293
/*75 */     g_free(ctx);                                                          // (23) 0.01758
/*77 */ }                                                                         // 0.0
