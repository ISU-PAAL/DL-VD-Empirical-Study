// commit message FFmpeg@e6bc38fd49 (target=1, prob=0.0151413195, correct=False): wmv2: move IDCT to its own DSP context.
/*0  */ av_cold void ff_wmv2_common_init(Wmv2Context * w){                                         // (2) 0.1594
/*2  */     MpegEncContext * const s= &w->s;                                                       // (3) 0.1159
/*6  */     ff_init_scantable(s->dsp.idct_permutation, &w->abt_scantable[0], ff_wmv2_scantableA);  // (0) 0.3261
/*8  */     ff_init_scantable(s->dsp.idct_permutation, &w->abt_scantable[1], ff_wmv2_scantableB);  // (1) 0.3261
/*10 */ }                                                                                          // (4) 0.007246
