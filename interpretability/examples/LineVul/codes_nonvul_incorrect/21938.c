// commit message FFmpeg@8a9641a652 (target=0, prob=0.5044166, correct=False): bsf: check memory allocations
/*0  */ AVBitStreamFilterContext *av_bitstream_filter_init(const char *name)           // (3) 0.07326
/*2  */ {                                                                              // (14) 0.003663
/*4  */     AVBitStreamFilter *bsf = first_bitstream_filter;                           // (7) 0.06593
/*8  */     while (bsf) {                                                              // (10) 0.03297
/*10 */         if (!strcmp(name, bsf->name)) {                                        // (5) 0.07326
/*12 */             AVBitStreamFilterContext *bsfc =                                   // (4) 0.07326
/*14 */                 av_mallocz(sizeof(AVBitStreamFilterContext));                  // (1) 0.1099
/*16 */             bsfc->filter    = bsf;                                             // (2) 0.08425
/*18 */             bsfc->priv_data =                                                  // (6) 0.0696
/*20 */                 bsf->priv_data_size ? av_mallocz(bsf->priv_data_size) : NULL;  // (0) 0.1538
/*22 */             return bsfc;                                                       // (8) 0.05861
/*24 */         }                                                                      // (11) 0.0293
/*26 */         bsf = bsf->next;                                                       // (9) 0.05495
/*28 */     }                                                                          // (13) 0.01465
/*30 */     return NULL;                                                               // (12) 0.02198
/*32 */ }                                                                              // (15) 0.003663
