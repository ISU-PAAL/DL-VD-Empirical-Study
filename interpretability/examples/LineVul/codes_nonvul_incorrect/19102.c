// commit message qemu@031380d877 (target=0, prob=0.50345397, correct=False): block: replace unchecked strdup/malloc/calloc with glib
/*0  */ static void aio_read_done(void *opaque, int ret)                          // (10) 0.0334
/*2  */ {                                                                         // (30) 0.001965
/*4  */     struct aio_ctx *ctx = opaque;                                         // (13) 0.02554
/*6  */     struct timeval t2;                                                    // (22) 0.01768
/*10 */     gettimeofday(&t2, NULL);                                              // (14) 0.02554
/*14 */     if (ret < 0) {                                                        // (19) 0.01965
/*16 */         printf("readv failed: %s\n", strerror(-ret));                     // (6) 0.04715
/*18 */         goto out;                                                         // (20) 0.01965
/*20 */     }                                                                     // (25) 0.007859
/*24 */     if (ctx->Pflag) {                                                     // (17) 0.02161
/*26 */         void *cmp_buf = malloc(ctx->qiov.size);                           // (7) 0.04519
/*30 */         memset(cmp_buf, ctx->pattern, ctx->qiov.size);                    // (4) 0.05305
/*32 */         if (memcmp(ctx->buf, cmp_buf, ctx->qiov.size)) {                  // (2) 0.05894
/*34 */             printf("Pattern verification failed at offset %"              // (8) 0.03929
/*36 */                    PRId64 ", %zd bytes\n", ctx->offset, ctx->qiov.size);  // (0) 0.08251
/*38 */         }                                                                 // (23) 0.01572
/*40 */         free(cmp_buf);                                                    // (15) 0.02554
/*42 */     }                                                                     // (26) 0.007859
/*46 */     if (ctx->qflag) {                                                     // (16) 0.02161
/*48 */         goto out;                                                         // (21) 0.01965
/*50 */     }                                                                     // (27) 0.007859
/*54 */     if (ctx->vflag) {                                                     // (18) 0.02161
/*56 */         dump_buffer(ctx->buf, ctx->offset, ctx->qiov.size);               // (3) 0.05501
/*58 */     }                                                                     // (28) 0.007859
/*62 */     /* Finally, report back -- -C gives a parsable format */              // (11) 0.0334
/*64 */     t2 = tsub(t2, ctx->t1);                                               // (9) 0.03536
/*66 */     print_report("read", &t2, ctx->offset, ctx->qiov.size,                // (5) 0.05108
/*68 */                  ctx->qiov.size, 1, ctx->Cflag);                          // (1) 0.06287
/*70 */ out:                                                                      // (29) 0.003929
/*72 */     qemu_io_free(ctx->buf);                                               // (12) 0.02947
/*74 */     free(ctx);                                                            // (24) 0.01375
/*76 */ }                                                                         // (31) 0.001965
