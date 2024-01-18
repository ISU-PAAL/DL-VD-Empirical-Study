// commit message FFmpeg@202a6697ba (target=0, prob=0.6567664, correct=False): Use named initializers and use new/free_context() instead of extradata() for context allocators. Patch by Colin McQuillan m niloc googlemail com.
/*0  */ rdt_free_extradata (PayloadContext *rdt)        // (6) 0.08081
/*2  */ {                                               // (12) 0.005051
/*4  */     int i;                                      // (10) 0.0303
/*8  */     for (i = 0; i < MAX_STREAMS; i++)           // (3) 0.09596
/*10 */         if (rdt->rmst[i]) {                     // (4) 0.09091
/*12 */             ff_rm_free_rmstream(rdt->rmst[i]);  // (0) 0.1414
/*14 */             av_freep(&rdt->rmst[i]);            // (1) 0.1212
/*16 */         }                                       // (9) 0.0404
/*18 */     if (rdt->rmctx)                             // (7) 0.05556
/*20 */         av_close_input_stream(rdt->rmctx);      // (2) 0.1061
/*22 */     av_freep(&rdt->mlti_data);                  // (5) 0.08586
/*24 */     av_free(rdt);                               // (8) 0.05051
/*26 */ }                                               // (11) 0.005051
