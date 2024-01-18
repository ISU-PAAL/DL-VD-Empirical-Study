// commit message FFmpeg@a28cccf6d6 (target=1, prob=0.5682592, correct=True): Fix memory leak in ATRAC3 decoder
/*0   */ static int decodeChannelSoundUnit (ATRAC3Context *q, GetBitContext *gb, channel_unit *pSnd, float *pOut, int channelNum, int codingMode)  // (0) 0.08203
/*2   */ {                                                                                                                                         // (22) 0.001953
/*4   */     int   band, result=0, numSubbands, lastTonal, numBands;                                                                               // (6) 0.04688
/*8   */     if (codingMode == JOINT_STEREO && channelNum == 1) {                                                                                  // (8) 0.04102
/*10  */         if (get_bits(gb,2) != 3) {                                                                                                        // (9) 0.04102
/*12  */             av_log(NULL,AV_LOG_ERROR,"JS mono Sound Unit id != 3.\n");                                                                    // (3) 0.06641
/*14  */             return -1;                                                                                                                    // (14) 0.0293
/*16  */         }                                                                                                                                 // (18) 0.01562
/*18  */     } else {                                                                                                                              // (20) 0.01172
/*20  */         if (get_bits(gb,6) != 0x28) {                                                                                                     // (7) 0.04492
/*22  */             av_log(NULL,AV_LOG_ERROR,"Sound Unit id != 0x28.\n");                                                                         // (5) 0.06641
/*24  */             return -1;                                                                                                                    // (15) 0.0293
/*26  */         }                                                                                                                                 // (19) 0.01562
/*28  */     }                                                                                                                                     // (21) 0.007812
/*32  */     /* number of coded QMF bands */                                                                                                       // (16) 0.02149
/*34  */     pSnd->bandsCoded = get_bits(gb,2);                                                                                                    // (12) 0.03711
/*38  */     result = decodeGainControl (gb, &(pSnd->gainBlock[pSnd->gcBlkSwitch]), pSnd->bandsCoded);                                             // (1) 0.07422
/*40  */     if (result) return result;                                                                                                            // (17) 0.01953
/*44  */     pSnd->numComponents = decodeTonalComponents (gb, pSnd->components, pSnd->bandsCoded);                                                 // (4) 0.06641
/*46  */     if (pSnd->numComponents == -1) return -1;                                                                                             // (11) 0.03906
/*50  */     numSubbands = decodeSpectrum (gb, pSnd->spectrum);                                                                                    // (10) 0.03906
/*54  */     /* Merge the decoded spectrum and tonal components. */                                                                                // (13) 0.0293
/*56  */     lastTonal = addTonalComponents (pSnd->spectrum, pSnd->numComponents, pSnd->components);                                               // (2) 0.06836
/*62  */     /* calculate number of used MLT/QMF bands according to the amount of coded spectral lines */                                          // 0.0
/*64  */     numBands = (subbandTab[numSubbands] - 1) >> 8;                                                                                        // 0.0
/*66  */     if (lastTonal >= 0)                                                                                                                   // 0.0
/*68  */         numBands = FFMAX((lastTonal + 256) >> 8, numBands);                                                                               // 0.0
/*74  */     /* Reconstruct time domain samples. */                                                                                                // 0.0
/*76  */     for (band=0; band<4; band++) {                                                                                                        // 0.0
/*78  */         /* Perform the IMDCT step without overlapping. */                                                                                 // 0.0
/*80  */         if (band <= numBands) {                                                                                                           // 0.0
/*82  */             IMLT(&(pSnd->spectrum[band*256]), pSnd->IMDCT_buf, band&1);                                                                   // 0.0
/*84  */         } else                                                                                                                            // 0.0
/*86  */             memset(pSnd->IMDCT_buf, 0, 512 * sizeof(float));                                                                              // 0.0
/*90  */         /* gain compensation and overlapping */                                                                                           // 0.0
/*92  */         gainCompensateAndOverlap (pSnd->IMDCT_buf, &(pSnd->prevFrame[band*256]), &(pOut[band*256]),                                       // 0.0
/*94  */                                     &((pSnd->gainBlock[1 - (pSnd->gcBlkSwitch)]).gBlock[band]),                                           // 0.0
/*96  */                                     &((pSnd->gainBlock[pSnd->gcBlkSwitch]).gBlock[band]));                                                // 0.0
/*98  */     }                                                                                                                                     // 0.0
/*102 */     /* Swap the gain control buffers for the next frame. */                                                                               // 0.0
/*104 */     pSnd->gcBlkSwitch ^= 1;                                                                                                               // 0.0
/*108 */     return 0;                                                                                                                             // 0.0
/*110 */ }                                                                                                                                         // 0.0
