// commit message FFmpeg@0eaec10550 (target=1, prob=0.61287045, correct=True): fixing overflow in 16->8 bit conversion, patch by (Nikolai Zhubr <s001 at hotbox dot ru>)
/*0   */ static int pcm_encode_frame(AVCodecContext *avctx,                          // (4) 0.03516
/*2   */ 			    unsigned char *frame, int buf_size, void *data)                      // (1) 0.03906
/*4   */ {                                                                           // (33) 0.001953
/*6   */     int n, sample_size, v;                                                  // (22) 0.02344
/*8   */     short *samples;                                                         // (27) 0.01562
/*10  */     unsigned char *dst;                                                     // (23) 0.01758
/*14  */     switch(avctx->codec->id) {                                              // (18) 0.02734
/*16  */     case CODEC_ID_PCM_S16LE:                                                // (8) 0.0332
/*18  */     case CODEC_ID_PCM_S16BE:                                                // (11) 0.0332
/*20  */     case CODEC_ID_PCM_U16LE:                                                // (14) 0.0332
/*22  */     case CODEC_ID_PCM_U16BE:                                                // (12) 0.0332
/*24  */         sample_size = 2;                                                    // (20) 0.02539
/*26  */         break;                                                              // (25) 0.01758
/*28  */     default:                                                                // (31) 0.009766
/*30  */         sample_size = 1;                                                    // (21) 0.02539
/*32  */         break;                                                              // (26) 0.01758
/*34  */     }                                                                       // (32) 0.007812
/*36  */     n = buf_size / sample_size;                                             // (19) 0.02539
/*38  */     samples = data;                                                         // (30) 0.01367
/*40  */     dst = frame;                                                            // (29) 0.01367
/*44  */     switch(avctx->codec->id) {                                              // (17) 0.02734
/*46  */     case CODEC_ID_PCM_S16LE:                                                // (9) 0.0332
/*48  */         for(;n>0;n--) {                                                     // (5) 0.03516
/*50  */             v = *samples++;                                                 // (15) 0.0332
/*52  */             dst[0] = v & 0xff;                                              // (0) 0.04102
/*54  */             dst[1] = v >> 8;                                                // (2) 0.03906
/*56  */             dst += 2;                                                       // (16) 0.0293
/*58  */         }                                                                   // (28) 0.01562
/*60  */         break;                                                              // (24) 0.01758
/*62  */     case CODEC_ID_PCM_S16BE:                                                // (10) 0.0332
/*64  */         for(;n>0;n--) {                                                     // (6) 0.03516
/*66  */             v = *samples++;                                                 // (13) 0.0332
/*68  */             dst[0] = v >> 8;                                                // (3) 0.03906
/*70  */             dst[1] = v;                                                     // (7) 0.03516
/*72  */             dst += 2;                                                       // 0.0
/*74  */         }                                                                   // 0.0
/*76  */         break;                                                              // 0.0
/*78  */     case CODEC_ID_PCM_U16LE:                                                // 0.0
/*80  */         for(;n>0;n--) {                                                     // 0.0
/*82  */             v = *samples++;                                                 // 0.0
/*84  */             v += 0x8000;                                                    // 0.0
/*86  */             dst[0] = v & 0xff;                                              // 0.0
/*88  */             dst[1] = v >> 8;                                                // 0.0
/*90  */             dst += 2;                                                       // 0.0
/*92  */         }                                                                   // 0.0
/*94  */         break;                                                              // 0.0
/*96  */     case CODEC_ID_PCM_U16BE:                                                // 0.0
/*98  */         for(;n>0;n--) {                                                     // 0.0
/*100 */             v = *samples++;                                                 // 0.0
/*102 */             v += 0x8000;                                                    // 0.0
/*104 */             dst[0] = v >> 8;                                                // 0.0
/*106 */             dst[1] = v;                                                     // 0.0
/*108 */             dst += 2;                                                       // 0.0
/*110 */         }                                                                   // 0.0
/*112 */         break;                                                              // 0.0
/*114 */     case CODEC_ID_PCM_S8:                                                   // 0.0
/*116 */         for(;n>0;n--) {                                                     // 0.0
/*118 */             v = *samples++;                                                 // 0.0
/*120 */             dst[0] = (v + 128) >> 8;                                        // 0.0
/*122 */             dst++;                                                          // 0.0
/*124 */         }                                                                   // 0.0
/*126 */         break;                                                              // 0.0
/*128 */     case CODEC_ID_PCM_U8:                                                   // 0.0
/*130 */         for(;n>0;n--) {                                                     // 0.0
/*132 */             v = *samples++;                                                 // 0.0
/*134 */             dst[0] = ((v + 128) >> 8) + 128;                                // 0.0
/*136 */             dst++;                                                          // 0.0
/*138 */         }                                                                   // 0.0
/*140 */         break;                                                              // 0.0
/*142 */     case CODEC_ID_PCM_ALAW:                                                 // 0.0
/*144 */         for(;n>0;n--) {                                                     // 0.0
/*146 */             v = *samples++;                                                 // 0.0
/*148 */             dst[0] = linear_to_alaw[(v + 32768) >> 2];                      // 0.0
/*150 */             dst++;                                                          // 0.0
/*152 */         }                                                                   // 0.0
/*154 */         break;                                                              // 0.0
/*156 */     case CODEC_ID_PCM_MULAW:                                                // 0.0
/*158 */         for(;n>0;n--) {                                                     // 0.0
/*160 */             v = *samples++;                                                 // 0.0
/*162 */             dst[0] = linear_to_ulaw[(v + 32768) >> 2];                      // 0.0
/*164 */             dst++;                                                          // 0.0
/*166 */         }                                                                   // 0.0
/*168 */         break;                                                              // 0.0
/*170 */     default:                                                                // 0.0
/*172 */         return -1;                                                          // 0.0
/*174 */     }                                                                       // 0.0
/*176 */     avctx->key_frame = 1;                                                   // 0.0
/*178 */     //avctx->frame_size = (dst - frame) / (sample_size * avctx->channels);  // 0.0
/*182 */     return dst - frame;                                                     // 0.0
/*184 */ }                                                                           // 0.0
