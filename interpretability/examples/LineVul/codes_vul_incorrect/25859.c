// commit message FFmpeg@feb13aed79 (target=1, prob=0.49033126, correct=False): avfilter/vf_signature: fix memory leaks in error cases
/*0   */ static int filter_frame(AVFilterLink *inlink, AVFrame *picref)                                                                                   // (7) 0.03711
/*2   */ {                                                                                                                                                // (19) 0.001953
/*4   */     AVFilterContext *ctx = inlink->dst;                                                                                                          // (11) 0.0293
/*6   */     SignatureContext *sic = ctx->priv;                                                                                                           // (13) 0.02539
/*8   */     StreamContext *sc = &(sic->streamcontexts[FF_INLINK_IDX(inlink)]);                                                                           // (5) 0.05664
/*10  */     FineSignature* fs;                                                                                                                           // (17) 0.01758
/*14  */     static const uint8_t pot3[5] = { 3*3*3*3, 3*3*3, 3*3, 3, 1 };                                                                                // (3) 0.07422
/*16  */     /* indexes of words : 210,217,219,274,334  44,175,233,270,273  57,70,103,237,269  100,285,295,337,354  101,102,111,275,296                   // (2) 0.1113
/*18  */     s2usw = sorted to unsorted wordvec: 44 is at index 5, 57 at index 10...                                                                      // (6) 0.05078
/*20  */     */                                                                                                                                           // (18) 0.007812
/*22  */     static const unsigned int wordvec[25] = {44,57,70,100,101,102,103,111,175,210,217,219,233,237,269,270,273,274,275,285,295,296,334,337,354};  // (1) 0.125
/*24  */     static const uint8_t      s2usw[25]   = { 5,10,11, 15, 20, 21, 12, 22,  6,  0,  1,  2,  7, 13, 14,  8,  9,  3, 23, 16, 17, 24,  4, 18, 19};  // (0) 0.1641
/*28  */     uint8_t wordt2b[5] = { 0, 0, 0, 0, 0 }; /* word ternary to binary */                                                                         // (4) 0.06641
/*30  */     uint64_t intpic[32][32];                                                                                                                     // (12) 0.02734
/*32  */     uint64_t rowcount;                                                                                                                           // (15) 0.01953
/*34  */     uint8_t *p = picref->data[0];                                                                                                                // (9) 0.0332
/*36  */     int inti, intj;                                                                                                                              // (14) 0.01953
/*38  */     int *intjlut;                                                                                                                                // (16) 0.01758
/*42  */     uint64_t conflist[DIFFELEM_SIZE];                                                                                                            // (8) 0.03516
/*44  */     int f = 0, g = 0, w = 0;                                                                                                                     // (10) 0.03125
/*46  */     int32_t dh1 = 1, dh2 = 1, dw1 = 1, dw2 = 1, a, b;                                                                                            // 0.0
/*48  */     int64_t denom;                                                                                                                               // 0.0
/*50  */     int i, j, k, ternary;                                                                                                                        // 0.0
/*52  */     uint64_t blocksum;                                                                                                                           // 0.0
/*54  */     int blocksize;                                                                                                                               // 0.0
/*56  */     int64_t th; /* threshold */                                                                                                                  // 0.0
/*58  */     int64_t sum;                                                                                                                                 // 0.0
/*62  */     int64_t precfactor = (sc->divide) ? 65536 : BLOCK_LCM;                                                                                       // 0.0
/*66  */     /* initialize fs */                                                                                                                          // 0.0
/*68  */     if (sc->curfinesig) {                                                                                                                        // 0.0
/*70  */         fs = av_mallocz(sizeof(FineSignature));                                                                                                  // 0.0
/*72  */         if (!fs)                                                                                                                                 // 0.0
/*74  */             return AVERROR(ENOMEM);                                                                                                              // 0.0
/*76  */         sc->curfinesig->next = fs;                                                                                                               // 0.0
/*78  */         fs->prev = sc->curfinesig;                                                                                                               // 0.0
/*80  */         sc->curfinesig = fs;                                                                                                                     // 0.0
/*82  */     } else {                                                                                                                                     // 0.0
/*84  */         fs = sc->curfinesig = sc->finesiglist;                                                                                                   // 0.0
/*86  */         sc->curcoarsesig1->first = fs;                                                                                                           // 0.0
/*88  */     }                                                                                                                                            // 0.0
/*92  */     fs->pts = picref->pts;                                                                                                                       // 0.0
/*94  */     fs->index = sc->lastindex++;                                                                                                                 // 0.0
/*98  */     memset(intpic, 0, sizeof(uint64_t)*32*32);                                                                                                   // 0.0
/*100 */     intjlut = av_malloc_array(inlink->w, sizeof(int));                                                                                           // 0.0
/*102 */     if (!intjlut)                                                                                                                                // 0.0
/*104 */         return AVERROR(ENOMEM);                                                                                                                  // 0.0
/*106 */     for (i = 0; i < inlink->w; i++) {                                                                                                            // 0.0
/*108 */         intjlut[i] = (i*32)/inlink->w;                                                                                                           // 0.0
/*110 */     }                                                                                                                                            // 0.0
/*114 */     for (i = 0; i < inlink->h; i++) {                                                                                                            // 0.0
/*116 */         inti = (i*32)/inlink->h;                                                                                                                 // 0.0
/*118 */         for (j = 0; j < inlink->w; j++) {                                                                                                        // 0.0
/*120 */             intj = intjlut[j];                                                                                                                   // 0.0
/*122 */             intpic[inti][intj] += p[j];                                                                                                          // 0.0
/*124 */         }                                                                                                                                        // 0.0
/*126 */         p += picref->linesize[0];                                                                                                                // 0.0
/*128 */     }                                                                                                                                            // 0.0
/*130 */     av_freep(&intjlut);                                                                                                                          // 0.0
/*134 */     /* The following calculates a summed area table (intpic) and brings the numbers                                                              // 0.0
/*136 */      * in intpic to the same denominator.                                                                                                        // 0.0
/*138 */      * So you only have to handle the numinator in the following sections.                                                                       // 0.0
/*140 */      */                                                                                                                                          // 0.0
/*142 */     dh1 = inlink->h / 32;                                                                                                                        // 0.0
/*144 */     if (inlink->h % 32)                                                                                                                          // 0.0
/*146 */         dh2 = dh1 + 1;                                                                                                                           // 0.0
/*148 */     dw1 = inlink->w / 32;                                                                                                                        // 0.0
/*150 */     if (inlink->w % 32)                                                                                                                          // 0.0
/*152 */         dw2 = dw1 + 1;                                                                                                                           // 0.0
/*154 */     denom = (sc->divide) ? dh1 * dh2 * dw1 * dw2 : 1;                                                                                            // 0.0
/*158 */     for (i = 0; i < 32; i++) {                                                                                                                   // 0.0
/*160 */         rowcount = 0;                                                                                                                            // 0.0
/*162 */         a = 1;                                                                                                                                   // 0.0
/*164 */         if (dh2 > 1) {                                                                                                                           // 0.0
/*166 */             a = ((inlink->h*(i+1))%32 == 0) ? (inlink->h*(i+1))/32 - 1 : (inlink->h*(i+1))/32;                                                   // 0.0
/*168 */             a -= ((inlink->h*i)%32 == 0) ? (inlink->h*i)/32 - 1 : (inlink->h*i)/32;                                                              // 0.0
/*170 */             a = (a == dh1)? dh2 : dh1;                                                                                                           // 0.0
/*172 */         }                                                                                                                                        // 0.0
/*174 */         for (j = 0; j < 32; j++) {                                                                                                               // 0.0
/*176 */             b = 1;                                                                                                                               // 0.0
/*178 */             if (dw2 > 1) {                                                                                                                       // 0.0
/*180 */                 b = ((inlink->w*(j+1))%32 == 0) ? (inlink->w*(j+1))/32 - 1 : (inlink->w*(j+1))/32;                                               // 0.0
/*182 */                 b -= ((inlink->w*j)%32 == 0) ? (inlink->w*j)/32 - 1 : (inlink->w*j)/32;                                                          // 0.0
/*184 */                 b = (b == dw1)? dw2 : dw1;                                                                                                       // 0.0
/*186 */             }                                                                                                                                    // 0.0
/*188 */             rowcount += intpic[i][j] * a * b * precfactor / denom;                                                                               // 0.0
/*190 */             if (i > 0) {                                                                                                                         // 0.0
/*192 */                 intpic[i][j] = intpic[i-1][j] + rowcount;                                                                                        // 0.0
/*194 */             } else {                                                                                                                             // 0.0
/*196 */                 intpic[i][j] = rowcount;                                                                                                         // 0.0
/*198 */             }                                                                                                                                    // 0.0
/*200 */         }                                                                                                                                        // 0.0
/*202 */     }                                                                                                                                            // 0.0
/*206 */     denom = (sc->divide) ? 1 : dh1 * dh2 * dw1 * dw2;                                                                                            // 0.0
/*210 */     for (i = 0; i < ELEMENT_COUNT; i++) {                                                                                                        // 0.0
/*212 */         const ElemCat* elemcat = elements[i];                                                                                                    // 0.0
/*214 */         int64_t* elemsignature;                                                                                                                  // 0.0
/*216 */         uint64_t* sortsignature;                                                                                                                 // 0.0
/*220 */         elemsignature = av_malloc_array(elemcat->elem_count, sizeof(int64_t));                                                                   // 0.0
/*222 */         if (!elemsignature)                                                                                                                      // 0.0
/*224 */             return AVERROR(ENOMEM);                                                                                                              // 0.0
/*226 */         sortsignature = av_malloc_array(elemcat->elem_count, sizeof(int64_t));                                                                   // 0.0
/*228 */         if (!sortsignature)                                                                                                                      // 0.0
/*230 */             return AVERROR(ENOMEM);                                                                                                              // 0.0
/*234 */         for (j = 0; j < elemcat->elem_count; j++) {                                                                                              // 0.0
/*236 */             blocksum = 0;                                                                                                                        // 0.0
/*238 */             blocksize = 0;                                                                                                                       // 0.0
/*240 */             for (k = 0; k < elemcat->left_count; k++) {                                                                                          // 0.0
/*242 */                 blocksum += get_block_sum(sc, intpic, &elemcat->blocks[j*elemcat->block_count+k]);                                               // 0.0
/*244 */                 blocksize += get_block_size(&elemcat->blocks[j*elemcat->block_count+k]);                                                         // 0.0
/*246 */             }                                                                                                                                    // 0.0
/*248 */             sum = blocksum / blocksize;                                                                                                          // 0.0
/*250 */             if (elemcat->av_elem) {                                                                                                              // 0.0
/*252 */                 sum -= 128 * precfactor * denom;                                                                                                 // 0.0
/*254 */             } else {                                                                                                                             // 0.0
/*256 */                 blocksum = 0;                                                                                                                    // 0.0
/*258 */                 blocksize = 0;                                                                                                                   // 0.0
/*260 */                 for (; k < elemcat->block_count; k++) {                                                                                          // 0.0
/*262 */                     blocksum += get_block_sum(sc, intpic, &elemcat->blocks[j*elemcat->block_count+k]);                                           // 0.0
/*264 */                     blocksize += get_block_size(&elemcat->blocks[j*elemcat->block_count+k]);                                                     // 0.0
/*266 */                 }                                                                                                                                // 0.0
/*268 */                 sum -= blocksum / blocksize;                                                                                                     // 0.0
/*270 */                 conflist[g++] = FFABS(sum * 8 / (precfactor * denom));                                                                           // 0.0
/*272 */             }                                                                                                                                    // 0.0
/*276 */             elemsignature[j] = sum;                                                                                                              // 0.0
/*278 */             sortsignature[j] = FFABS(sum);                                                                                                       // 0.0
/*280 */         }                                                                                                                                        // 0.0
/*284 */         /* get threshold */                                                                                                                      // 0.0
/*286 */         qsort(sortsignature, elemcat->elem_count, sizeof(uint64_t), (void*) cmp);                                                                // 0.0
/*288 */         th = sortsignature[(int) (elemcat->elem_count*0.333)];                                                                                   // 0.0
/*292 */         /* ternarize */                                                                                                                          // 0.0
/*294 */         for (j = 0; j < elemcat->elem_count; j++) {                                                                                              // 0.0
/*296 */             if (elemsignature[j] < -th) {                                                                                                        // 0.0
/*298 */                 ternary = 0;                                                                                                                     // 0.0
/*300 */             } else if (elemsignature[j] <= th) {                                                                                                 // 0.0
/*302 */                 ternary = 1;                                                                                                                     // 0.0
/*304 */             } else {                                                                                                                             // 0.0
/*306 */                 ternary = 2;                                                                                                                     // 0.0
/*308 */             }                                                                                                                                    // 0.0
/*310 */             fs->framesig[f/5] += ternary * pot3[f%5];                                                                                            // 0.0
/*314 */             if (f == wordvec[w]) {                                                                                                               // 0.0
/*316 */                 fs->words[s2usw[w]/5] += ternary * pot3[wordt2b[s2usw[w]/5]++];                                                                  // 0.0
/*318 */                 if (w < 24)                                                                                                                      // 0.0
/*320 */                     w++;                                                                                                                         // 0.0
/*322 */             }                                                                                                                                    // 0.0
/*324 */             f++;                                                                                                                                 // 0.0
/*326 */         }                                                                                                                                        // 0.0
/*328 */         av_freep(&elemsignature);                                                                                                                // 0.0
/*330 */         av_freep(&sortsignature);                                                                                                                // 0.0
/*332 */     }                                                                                                                                            // 0.0
/*336 */     /* confidence */                                                                                                                             // 0.0
/*338 */     qsort(conflist, DIFFELEM_SIZE, sizeof(uint64_t), (void*) cmp);                                                                               // 0.0
/*340 */     fs->confidence = FFMIN(conflist[DIFFELEM_SIZE/2], 255);                                                                                      // 0.0
/*344 */     /* coarsesignature */                                                                                                                        // 0.0
/*346 */     if (sc->coarsecount == 0) {                                                                                                                  // 0.0
/*348 */         if (sc->curcoarsesig2) {                                                                                                                 // 0.0
/*350 */             sc->curcoarsesig1 = av_mallocz(sizeof(CoarseSignature));                                                                             // 0.0
/*352 */             if (!sc->curcoarsesig1)                                                                                                              // 0.0
/*354 */                 return AVERROR(ENOMEM);                                                                                                          // 0.0
/*356 */             sc->curcoarsesig1->first = fs;                                                                                                       // 0.0
/*358 */             sc->curcoarsesig2->next = sc->curcoarsesig1;                                                                                         // 0.0
/*360 */             sc->coarseend = sc->curcoarsesig1;                                                                                                   // 0.0
/*362 */         }                                                                                                                                        // 0.0
/*364 */     }                                                                                                                                            // 0.0
/*366 */     if (sc->coarsecount == 45) {                                                                                                                 // 0.0
/*368 */         sc->midcoarse = 1;                                                                                                                       // 0.0
/*370 */         sc->curcoarsesig2 = av_mallocz(sizeof(CoarseSignature));                                                                                 // 0.0
/*372 */         if (!sc->curcoarsesig2)                                                                                                                  // 0.0
/*374 */             return AVERROR(ENOMEM);                                                                                                              // 0.0
/*376 */         sc->curcoarsesig2->first = fs;                                                                                                           // 0.0
/*378 */         sc->curcoarsesig1->next = sc->curcoarsesig2;                                                                                             // 0.0
/*380 */         sc->coarseend = sc->curcoarsesig2;                                                                                                       // 0.0
/*382 */     }                                                                                                                                            // 0.0
/*384 */     for (i = 0; i < 5; i++) {                                                                                                                    // 0.0
/*386 */         set_bit(sc->curcoarsesig1->data[i], fs->words[i]);                                                                                       // 0.0
/*388 */     }                                                                                                                                            // 0.0
/*390 */     /* assuming the actual frame is the last */                                                                                                  // 0.0
/*392 */     sc->curcoarsesig1->last = fs;                                                                                                                // 0.0
/*394 */     if (sc->midcoarse) {                                                                                                                         // 0.0
/*396 */         for (i = 0; i < 5; i++) {                                                                                                                // 0.0
/*398 */             set_bit(sc->curcoarsesig2->data[i], fs->words[i]);                                                                                   // 0.0
/*400 */         }                                                                                                                                        // 0.0
/*402 */         sc->curcoarsesig2->last = fs;                                                                                                            // 0.0
/*404 */     }                                                                                                                                            // 0.0
/*408 */     sc->coarsecount = (sc->coarsecount+1)%90;                                                                                                    // 0.0
/*412 */     /* debug printing finesignature */                                                                                                           // 0.0
/*414 */     if (av_log_get_level() == AV_LOG_DEBUG) {                                                                                                    // 0.0
/*416 */         av_log(ctx, AV_LOG_DEBUG, "input %d, confidence: %d\n", FF_INLINK_IDX(inlink), fs->confidence);                                          // 0.0
/*420 */         av_log(ctx, AV_LOG_DEBUG, "words:");                                                                                                     // 0.0
/*422 */         for (i = 0; i < 5; i++) {                                                                                                                // 0.0
/*424 */             av_log(ctx, AV_LOG_DEBUG, " %d:", fs->words[i] );                                                                                    // 0.0
/*426 */             av_log(ctx, AV_LOG_DEBUG, " %d", fs->words[i] / pot3[0] );                                                                           // 0.0
/*428 */             for (j = 1; j < 5; j++)                                                                                                              // 0.0
/*430 */                 av_log(ctx, AV_LOG_DEBUG, ",%d", fs->words[i] % pot3[j-1] / pot3[j] );                                                           // 0.0
/*432 */             av_log(ctx, AV_LOG_DEBUG, ";");                                                                                                      // 0.0
/*434 */         }                                                                                                                                        // 0.0
/*436 */         av_log(ctx, AV_LOG_DEBUG, "\n");                                                                                                         // 0.0
/*440 */         av_log(ctx, AV_LOG_DEBUG, "framesignature:");                                                                                            // 0.0
/*442 */         for (i = 0; i < SIGELEM_SIZE/5; i++) {                                                                                                   // 0.0
/*444 */             av_log(ctx, AV_LOG_DEBUG, " %d", fs->framesig[i] / pot3[0] );                                                                        // 0.0
/*446 */             for (j = 1; j < 5; j++)                                                                                                              // 0.0
/*448 */                 av_log(ctx, AV_LOG_DEBUG, ",%d", fs->framesig[i] % pot3[j-1] / pot3[j] );                                                        // 0.0
/*450 */         }                                                                                                                                        // 0.0
/*452 */         av_log(ctx, AV_LOG_DEBUG, "\n");                                                                                                         // 0.0
/*454 */     }                                                                                                                                            // 0.0
/*458 */     if (FF_INLINK_IDX(inlink) == 0)                                                                                                              // 0.0
/*460 */         return ff_filter_frame(inlink->dst->outputs[0], picref);                                                                                 // 0.0
/*462 */     return 1;                                                                                                                                    // 0.0
/*464 */ }                                                                                                                                                // 0.0
