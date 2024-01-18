// commit message FFmpeg@d2ee495fb2 (target=1, prob=0.026853913, correct=False): configure: Drop check for availability of ten assembler operands.
/*0  */ void ff_mlp_init_x86(DSPContext* c, AVCodecContext *avctx)  // (0) 0.3165
/*2  */ {                                                           // (4) 0.01266
/*4  */ #if HAVE_7REGS && HAVE_TEN_OPERANDS                         // (2) 0.2025
/*6  */     c->mlp_filter_channel = mlp_filter_channel_x86;         // (1) 0.2785
/*8  */ #endif                                                      // (3) 0.02532
/*10 */ }                                                           // (5) 0.01266
