// commit message FFmpeg@7a206eb32f (target=0, prob=0.5133088, correct=False): alac: fix check for valid max_samples_per_frame
/*0  */ static int alac_set_info(ALACContext *alac)                    // (18) 0.03125
/*2  */ {                                                              // (21) 0.001953
/*4  */     GetByteContext gb;                                         // (19) 0.01758
/*8  */     bytestream2_init(&gb, alac->avctx->extradata,              // (11) 0.04297
/*10 */                      alac->avctx->extradata_size);             // (2) 0.0625
/*14 */     bytestream2_skipu(&gb, 12); // size:4, alac:4, version:4   // (4) 0.05469
/*18 */     alac->max_samples_per_frame = bytestream2_get_be32u(&gb);  // (5) 0.05469
/*20 */     if (alac->max_samples_per_frame >= UINT_MAX/4){            // (9) 0.04687
/*22 */         av_log(alac->avctx, AV_LOG_ERROR,                      // (10) 0.04492
/*24 */                "max_samples_per_frame too large\n");           // (6) 0.05469
/*26 */         return AVERROR_INVALIDDATA;                            // (17) 0.0332
/*28 */     }                                                          // (20) 0.007812
/*30 */     bytestream2_skipu(&gb, 1);  // compatible version          // (16) 0.03711
/*32 */     alac->sample_size          = bytestream2_get_byteu(&gb);   // (3) 0.06055
/*34 */     alac->rice_history_mult    = bytestream2_get_byteu(&gb);   // (7) 0.05273
/*36 */     alac->rice_initial_history = bytestream2_get_byteu(&gb);   // (8) 0.04687
/*38 */     alac->rice_limit           = bytestream2_get_byteu(&gb);   // (1) 0.0625
/*40 */     alac->channels             = bytestream2_get_byteu(&gb);   // (0) 0.06445
/*42 */     bytestream2_get_be16u(&gb); // maxRun                      // (15) 0.03712
/*44 */     bytestream2_get_be32u(&gb); // max coded frame size        // (12) 0.04102
/*46 */     bytestream2_get_be32u(&gb); // average bitrate             // (14) 0.03906
/*48 */     bytestream2_get_be32u(&gb); // samplerate                  // (13) 0.03906
/*52 */     return 0;                                                  // 0.0
/*54 */ }                                                              // 0.0
