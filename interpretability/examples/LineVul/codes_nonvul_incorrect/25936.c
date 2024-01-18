// commit message FFmpeg@ac94b8bcc6 (target=0, prob=0.5479047, correct=False): adpcm: simplify packet size bounds checking in the ADPCM IMA QT decoder.
/*0    */ static int adpcm_decode_frame(AVCodecContext *avctx,                                                                    // (4) 0.03718
/*2    */                             void *data, int *data_size,                                                                 // (0) 0.07224
/*4    */                             AVPacket *avpkt)                                                                            // (1) 0.06836
/*6    */ {                                                                                                                       // (31) 0.001977
/*8    */     const uint8_t *buf = avpkt->data;                                                                                   // (9) 0.03319
/*10   */     int buf_size = avpkt->size;                                                                                         // (12) 0.02733
/*12   */     ADPCMDecodeContext *c = avctx->priv_data;                                                                           // (5) 0.0371
/*14   */     ADPCMChannelStatus *cs;                                                                                             // (18) 0.02149
/*16   */     int n, m, channel, i;                                                                                               // (15) 0.02347
/*18   */     int block_predictor[2];                                                                                             // (16) 0.02344
/*20   */     short *samples;                                                                                                     // (29) 0.01562
/*22   */     short *samples_end;                                                                                                 // (24) 0.01952
/*24   */     const uint8_t *src;                                                                                                 // (20) 0.02148
/*26   */     int st; /* stereo */                                                                                                // (25) 0.01758
/*30   */     /* DK3 ADPCM accounting variables */                                                                                // (17) 0.02343
/*32   */     unsigned char last_byte = 0;                                                                                        // (21) 0.02148
/*34   */     unsigned char nibble;                                                                                               // (28) 0.01562
/*36   */     int decode_top_nibble_next = 0;                                                                                     // (10) 0.02929
/*38   */     int diff_channel;                                                                                                   // (27) 0.01562
/*42   */     /* EA ADPCM state variables */                                                                                      // (19) 0.02148
/*44   */     uint32_t samples_in_chunk;                                                                                          // (13) 0.02733
/*46   */     int32_t previous_left_sample, previous_right_sample;                                                                // (7) 0.03709
/*48   */     int32_t current_left_sample, current_right_sample;                                                                  // (6) 0.03709
/*50   */     int32_t next_left_sample, next_right_sample;                                                                        // (8) 0.03709
/*52   */     int32_t coeff1l, coeff2l, coeff1r, coeff2r;                                                                         // (2) 0.05271
/*54   */     uint8_t shift_left, shift_right;                                                                                    // (11) 0.02929
/*56   */     int count1, count2;                                                                                                 // (23) 0.01952
/*58   */     int coeff[2][2], shift[2];//used in EA MAXIS ADPCM                                                                  // (3) 0.04686
/*62   */     if (!buf_size)                                                                                                      // (26) 0.01757
/*64   */         return 0;                                                                                                       // (22) 0.01952
/*68   */     //should protect all 4bit ADPCM variants                                                                            // (14) 0.02541
/*70   */     //8 is needed for CODEC_ID_ADPCM_IMA_WAV with 2 channels                                                            // 0.0
/*72   */     //                                                                                                                  // (30) 0.007822
/*74   */     if(*data_size/4 < buf_size + 8)                                                                                     // 0.0
/*76   */         return -1;                                                                                                      // 0.0
/*80   */     samples = data;                                                                                                     // 0.0
/*82   */     samples_end= samples + *data_size/2;                                                                                // 0.0
/*84   */     *data_size= 0;                                                                                                      // 0.0
/*86   */     src = buf;                                                                                                          // 0.0
/*90   */     st = avctx->channels == 2 ? 1 : 0;                                                                                  // 0.0
/*94   */     switch(avctx->codec->id) {                                                                                          // 0.0
/*96   */     case CODEC_ID_ADPCM_IMA_QT:                                                                                         // 0.0
/*98   */         n = buf_size - 2*avctx->channels;                                                                               // 0.0
/*100  */         for (channel = 0; channel < avctx->channels; channel++) {                                                       // 0.0
/*102  */             int16_t predictor;                                                                                          // 0.0
/*104  */             int step_index;                                                                                             // 0.0
/*106  */             cs = &(c->status[channel]);                                                                                 // 0.0
/*108  */             /* (pppppp) (piiiiiii) */                                                                                   // 0.0
/*112  */             /* Bits 15-7 are the _top_ 9 bits of the 16-bit initial predictor value */                                  // 0.0
/*114  */             predictor = AV_RB16(src);                                                                                   // 0.0
/*116  */             step_index = predictor & 0x7F;                                                                              // 0.0
/*118  */             predictor &= 0xFF80;                                                                                        // 0.0
/*122  */             src += 2;                                                                                                   // 0.0
/*126  */             if (cs->step_index == step_index) {                                                                         // 0.0
/*128  */                 int diff = (int)predictor - cs->predictor;                                                              // 0.0
/*130  */                 if (diff < 0)                                                                                           // 0.0
/*132  */                     diff = - diff;                                                                                      // 0.0
/*134  */                 if (diff > 0x7f)                                                                                        // 0.0
/*136  */                     goto update;                                                                                        // 0.0
/*138  */             } else {                                                                                                    // 0.0
/*140  */             update:                                                                                                     // 0.0
/*142  */                 cs->step_index = step_index;                                                                            // 0.0
/*144  */                 cs->predictor = predictor;                                                                              // 0.0
/*146  */             }                                                                                                           // 0.0
/*150  */             if (cs->step_index > 88){                                                                                   // 0.0
/*152  */                 av_log(avctx, AV_LOG_ERROR, "ERROR: step_index = %i\n", cs->step_index);                                // 0.0
/*154  */                 cs->step_index = 88;                                                                                    // 0.0
/*156  */             }                                                                                                           // 0.0
/*160  */             samples = (short*)data + channel;                                                                           // 0.0
/*164  */             for(m=32; n>0 && m>0; n--, m--) { /* in QuickTime, IMA is encoded by chuncks of 34 bytes (=64 samples) */   // 0.0
/*166  */                 *samples = adpcm_ima_qt_expand_nibble(cs, src[0] & 0x0F, 3);                                            // 0.0
/*168  */                 samples += avctx->channels;                                                                             // 0.0
/*170  */                 *samples = adpcm_ima_qt_expand_nibble(cs, src[0] >> 4  , 3);                                            // 0.0
/*172  */                 samples += avctx->channels;                                                                             // 0.0
/*174  */                 src ++;                                                                                                 // 0.0
/*176  */             }                                                                                                           // 0.0
/*178  */         }                                                                                                               // 0.0
/*180  */         if (st)                                                                                                         // 0.0
/*182  */             samples--;                                                                                                  // 0.0
/*184  */         break;                                                                                                          // 0.0
/*186  */     case CODEC_ID_ADPCM_IMA_WAV:                                                                                        // 0.0
/*188  */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*190  */             buf_size = avctx->block_align;                                                                              // 0.0
/*194  */ //        samples_per_block= (block_align-4*chanels)*8 / (bits_per_sample * chanels) + 1;                               // 0.0
/*198  */         for(i=0; i<avctx->channels; i++){                                                                               // 0.0
/*200  */             cs = &(c->status[i]);                                                                                       // 0.0
/*202  */             cs->predictor = *samples++ = (int16_t)bytestream_get_le16(&src);                                            // 0.0
/*206  */             cs->step_index = *src++;                                                                                    // 0.0
/*208  */             if (cs->step_index > 88){                                                                                   // 0.0
/*210  */                 av_log(avctx, AV_LOG_ERROR, "ERROR: step_index = %i\n", cs->step_index);                                // 0.0
/*212  */                 cs->step_index = 88;                                                                                    // 0.0
/*214  */             }                                                                                                           // 0.0
/*216  */             if (*src++) av_log(avctx, AV_LOG_ERROR, "unused byte should be null but is %d!!\n", src[-1]); /* unused */  // 0.0
/*218  */         }                                                                                                               // 0.0
/*222  */         while(src < buf + buf_size){                                                                                    // 0.0
/*224  */             for(m=0; m<4; m++){                                                                                         // 0.0
/*226  */                 for(i=0; i<=st; i++)                                                                                    // 0.0
/*228  */                     *samples++ = adpcm_ima_expand_nibble(&c->status[i], src[4*i] & 0x0F, 3);                            // 0.0
/*230  */                 for(i=0; i<=st; i++)                                                                                    // 0.0
/*232  */                     *samples++ = adpcm_ima_expand_nibble(&c->status[i], src[4*i] >> 4  , 3);                            // 0.0
/*234  */                 src++;                                                                                                  // 0.0
/*236  */             }                                                                                                           // 0.0
/*238  */             src += 4*st;                                                                                                // 0.0
/*240  */         }                                                                                                               // 0.0
/*242  */         break;                                                                                                          // 0.0
/*244  */     case CODEC_ID_ADPCM_4XM:                                                                                            // 0.0
/*246  */         cs = &(c->status[0]);                                                                                           // 0.0
/*248  */         c->status[0].predictor= (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*250  */         if(st){                                                                                                         // 0.0
/*252  */             c->status[1].predictor= (int16_t)bytestream_get_le16(&src);                                                 // 0.0
/*254  */         }                                                                                                               // 0.0
/*256  */         c->status[0].step_index= (int16_t)bytestream_get_le16(&src);                                                    // 0.0
/*258  */         if(st){                                                                                                         // 0.0
/*260  */             c->status[1].step_index= (int16_t)bytestream_get_le16(&src);                                                // 0.0
/*262  */         }                                                                                                               // 0.0
/*264  */         if (cs->step_index < 0) cs->step_index = 0;                                                                     // 0.0
/*266  */         if (cs->step_index > 88) cs->step_index = 88;                                                                   // 0.0
/*270  */         m= (buf_size - (src - buf))>>st;                                                                                // 0.0
/*272  */         for(i=0; i<m; i++) {                                                                                            // 0.0
/*274  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0], src[i] & 0x0F, 4);                                      // 0.0
/*276  */             if (st)                                                                                                     // 0.0
/*278  */                 *samples++ = adpcm_ima_expand_nibble(&c->status[1], src[i+m] & 0x0F, 4);                                // 0.0
/*280  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0], src[i] >> 4, 4);                                        // 0.0
/*282  */             if (st)                                                                                                     // 0.0
/*284  */                 *samples++ = adpcm_ima_expand_nibble(&c->status[1], src[i+m] >> 4, 4);                                  // 0.0
/*286  */         }                                                                                                               // 0.0
/*290  */         src += m<<st;                                                                                                   // 0.0
/*294  */         break;                                                                                                          // 0.0
/*296  */     case CODEC_ID_ADPCM_MS:                                                                                             // 0.0
/*298  */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*300  */             buf_size = avctx->block_align;                                                                              // 0.0
/*302  */         n = buf_size - 7 * avctx->channels;                                                                             // 0.0
/*304  */         if (n < 0)                                                                                                      // 0.0
/*306  */             return -1;                                                                                                  // 0.0
/*308  */         block_predictor[0] = av_clip(*src++, 0, 6);                                                                     // 0.0
/*310  */         block_predictor[1] = 0;                                                                                         // 0.0
/*312  */         if (st)                                                                                                         // 0.0
/*314  */             block_predictor[1] = av_clip(*src++, 0, 6);                                                                 // 0.0
/*316  */         c->status[0].idelta = (int16_t)bytestream_get_le16(&src);                                                       // 0.0
/*318  */         if (st){                                                                                                        // 0.0
/*320  */             c->status[1].idelta = (int16_t)bytestream_get_le16(&src);                                                   // 0.0
/*322  */         }                                                                                                               // 0.0
/*324  */         c->status[0].coeff1 = ff_adpcm_AdaptCoeff1[block_predictor[0]];                                                 // 0.0
/*326  */         c->status[0].coeff2 = ff_adpcm_AdaptCoeff2[block_predictor[0]];                                                 // 0.0
/*328  */         c->status[1].coeff1 = ff_adpcm_AdaptCoeff1[block_predictor[1]];                                                 // 0.0
/*330  */         c->status[1].coeff2 = ff_adpcm_AdaptCoeff2[block_predictor[1]];                                                 // 0.0
/*334  */         c->status[0].sample1 = bytestream_get_le16(&src);                                                               // 0.0
/*336  */         if (st) c->status[1].sample1 = bytestream_get_le16(&src);                                                       // 0.0
/*338  */         c->status[0].sample2 = bytestream_get_le16(&src);                                                               // 0.0
/*340  */         if (st) c->status[1].sample2 = bytestream_get_le16(&src);                                                       // 0.0
/*344  */         *samples++ = c->status[0].sample2;                                                                              // 0.0
/*346  */         if (st) *samples++ = c->status[1].sample2;                                                                      // 0.0
/*348  */         *samples++ = c->status[0].sample1;                                                                              // 0.0
/*350  */         if (st) *samples++ = c->status[1].sample1;                                                                      // 0.0
/*352  */         for(;n>0;n--) {                                                                                                 // 0.0
/*354  */             *samples++ = adpcm_ms_expand_nibble(&c->status[0 ], src[0] >> 4  );                                         // 0.0
/*356  */             *samples++ = adpcm_ms_expand_nibble(&c->status[st], src[0] & 0x0F);                                         // 0.0
/*358  */             src ++;                                                                                                     // 0.0
/*360  */         }                                                                                                               // 0.0
/*362  */         break;                                                                                                          // 0.0
/*364  */     case CODEC_ID_ADPCM_IMA_DK4:                                                                                        // 0.0
/*366  */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*368  */             buf_size = avctx->block_align;                                                                              // 0.0
/*372  */         c->status[0].predictor  = (int16_t)bytestream_get_le16(&src);                                                   // 0.0
/*374  */         c->status[0].step_index = *src++;                                                                               // 0.0
/*376  */         src++;                                                                                                          // 0.0
/*378  */         *samples++ = c->status[0].predictor;                                                                            // 0.0
/*380  */         if (st) {                                                                                                       // 0.0
/*382  */             c->status[1].predictor  = (int16_t)bytestream_get_le16(&src);                                               // 0.0
/*384  */             c->status[1].step_index = *src++;                                                                           // 0.0
/*386  */             src++;                                                                                                      // 0.0
/*388  */             *samples++ = c->status[1].predictor;                                                                        // 0.0
/*390  */         }                                                                                                               // 0.0
/*392  */         while (src < buf + buf_size) {                                                                                  // 0.0
/*394  */             uint8_t v = *src++;                                                                                         // 0.0
/*396  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0 ], v >> 4  , 3);                                          // 0.0
/*398  */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v & 0x0F, 3);                                          // 0.0
/*400  */         }                                                                                                               // 0.0
/*402  */         break;                                                                                                          // 0.0
/*404  */     case CODEC_ID_ADPCM_IMA_DK3:                                                                                        // 0.0
/*406  */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*408  */             buf_size = avctx->block_align;                                                                              // 0.0
/*412  */         if(buf_size + 16 > (samples_end - samples)*3/8)                                                                 // 0.0
/*414  */             return -1;                                                                                                  // 0.0
/*418  */         c->status[0].predictor  = (int16_t)AV_RL16(src + 10);                                                           // 0.0
/*420  */         c->status[1].predictor  = (int16_t)AV_RL16(src + 12);                                                           // 0.0
/*422  */         c->status[0].step_index = src[14];                                                                              // 0.0
/*424  */         c->status[1].step_index = src[15];                                                                              // 0.0
/*426  */         /* sign extend the predictors */                                                                                // 0.0
/*428  */         src += 16;                                                                                                      // 0.0
/*430  */         diff_channel = c->status[1].predictor;                                                                          // 0.0
/*434  */         /* the DK3_GET_NEXT_NIBBLE macro issues the break statement when                                                // 0.0
/*436  */          * the buffer is consumed */                                                                                    // 0.0
/*438  */         while (1) {                                                                                                     // 0.0
/*442  */             /* for this algorithm, c->status[0] is the sum channel and                                                  // 0.0
/*444  */              * c->status[1] is the diff channel */                                                                      // 0.0
/*448  */             /* process the first predictor of the sum channel */                                                        // 0.0
/*450  */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*452  */             adpcm_ima_expand_nibble(&c->status[0], nibble, 3);                                                          // 0.0
/*456  */             /* process the diff channel predictor */                                                                    // 0.0
/*458  */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*460  */             adpcm_ima_expand_nibble(&c->status[1], nibble, 3);                                                          // 0.0
/*464  */             /* process the first pair of stereo PCM samples */                                                          // 0.0
/*466  */             diff_channel = (diff_channel + c->status[1].predictor) / 2;                                                 // 0.0
/*468  */             *samples++ = c->status[0].predictor + c->status[1].predictor;                                               // 0.0
/*470  */             *samples++ = c->status[0].predictor - c->status[1].predictor;                                               // 0.0
/*474  */             /* process the second predictor of the sum channel */                                                       // 0.0
/*476  */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*478  */             adpcm_ima_expand_nibble(&c->status[0], nibble, 3);                                                          // 0.0
/*482  */             /* process the second pair of stereo PCM samples */                                                         // 0.0
/*484  */             diff_channel = (diff_channel + c->status[1].predictor) / 2;                                                 // 0.0
/*486  */             *samples++ = c->status[0].predictor + c->status[1].predictor;                                               // 0.0
/*488  */             *samples++ = c->status[0].predictor - c->status[1].predictor;                                               // 0.0
/*490  */         }                                                                                                               // 0.0
/*492  */         break;                                                                                                          // 0.0
/*494  */     case CODEC_ID_ADPCM_IMA_ISS:                                                                                        // 0.0
/*496  */         c->status[0].predictor  = (int16_t)AV_RL16(src + 0);                                                            // 0.0
/*498  */         c->status[0].step_index = src[2];                                                                               // 0.0
/*500  */         src += 4;                                                                                                       // 0.0
/*502  */         if(st) {                                                                                                        // 0.0
/*504  */             c->status[1].predictor  = (int16_t)AV_RL16(src + 0);                                                        // 0.0
/*506  */             c->status[1].step_index = src[2];                                                                           // 0.0
/*508  */             src += 4;                                                                                                   // 0.0
/*510  */         }                                                                                                               // 0.0
/*514  */         while (src < buf + buf_size) {                                                                                  // 0.0
/*516  */             uint8_t v1, v2;                                                                                             // 0.0
/*518  */             uint8_t v = *src++;                                                                                         // 0.0
/*520  */             /* nibbles are swapped for mono */                                                                          // 0.0
/*522  */             if (st) {                                                                                                   // 0.0
/*524  */                 v1 = v >> 4;                                                                                            // 0.0
/*526  */                 v2 = v & 0x0F;                                                                                          // 0.0
/*528  */             } else {                                                                                                    // 0.0
/*530  */                 v2 = v >> 4;                                                                                            // 0.0
/*532  */                 v1 = v & 0x0F;                                                                                          // 0.0
/*534  */             }                                                                                                           // 0.0
/*536  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0 ], v1, 3);                                                // 0.0
/*538  */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v2, 3);                                                // 0.0
/*540  */         }                                                                                                               // 0.0
/*542  */         break;                                                                                                          // 0.0
/*544  */     case CODEC_ID_ADPCM_IMA_WS:                                                                                         // 0.0
/*546  */         while (src < buf + buf_size) {                                                                                  // 0.0
/*548  */             uint8_t v = *src++;                                                                                         // 0.0
/*550  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],  v >> 4  , 3);                                          // 0.0
/*552  */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v & 0x0F, 3);                                          // 0.0
/*554  */         }                                                                                                               // 0.0
/*556  */         break;                                                                                                          // 0.0
/*558  */     case CODEC_ID_ADPCM_XA:                                                                                             // 0.0
/*560  */         while (buf_size >= 128) {                                                                                       // 0.0
/*562  */             xa_decode(samples, src, &c->status[0], &c->status[1],                                                       // 0.0
/*564  */                 avctx->channels);                                                                                       // 0.0
/*566  */             src += 128;                                                                                                 // 0.0
/*568  */             samples += 28 * 8;                                                                                          // 0.0
/*570  */             buf_size -= 128;                                                                                            // 0.0
/*572  */         }                                                                                                               // 0.0
/*574  */         break;                                                                                                          // 0.0
/*576  */     case CODEC_ID_ADPCM_IMA_EA_EACS:                                                                                    // 0.0
/*578  */         samples_in_chunk = bytestream_get_le32(&src) >> (1-st);                                                         // 0.0
/*582  */         if (samples_in_chunk > buf_size-4-(8<<st)) {                                                                    // 0.0
/*584  */             src += buf_size - 4;                                                                                        // 0.0
/*586  */             break;                                                                                                      // 0.0
/*588  */         }                                                                                                               // 0.0
/*592  */         for (i=0; i<=st; i++)                                                                                           // 0.0
/*594  */             c->status[i].step_index = bytestream_get_le32(&src);                                                        // 0.0
/*596  */         for (i=0; i<=st; i++)                                                                                           // 0.0
/*598  */             c->status[i].predictor  = bytestream_get_le32(&src);                                                        // 0.0
/*602  */         for (; samples_in_chunk; samples_in_chunk--, src++) {                                                           // 0.0
/*604  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],  *src>>4,   3);                                         // 0.0
/*606  */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], *src&0x0F, 3);                                         // 0.0
/*608  */         }                                                                                                               // 0.0
/*610  */         break;                                                                                                          // 0.0
/*612  */     case CODEC_ID_ADPCM_IMA_EA_SEAD:                                                                                    // 0.0
/*614  */         for (; src < buf+buf_size; src++) {                                                                             // 0.0
/*616  */             *samples++ = adpcm_ima_expand_nibble(&c->status[0], src[0] >> 4, 6);                                        // 0.0
/*618  */             *samples++ = adpcm_ima_expand_nibble(&c->status[st],src[0]&0x0F, 6);                                        // 0.0
/*620  */         }                                                                                                               // 0.0
/*622  */         break;                                                                                                          // 0.0
/*624  */     case CODEC_ID_ADPCM_EA:                                                                                             // 0.0
/*626  */         /* Each EA ADPCM frame has a 12-byte header followed by 30-byte pieces,                                         // 0.0
/*628  */            each coding 28 stereo samples. */                                                                            // 0.0
/*630  */         if (buf_size < 12) {                                                                                            // 0.0
/*632  */             av_log(avctx, AV_LOG_ERROR, "frame too small\n");                                                           // 0.0
/*634  */             return AVERROR(EINVAL);                                                                                     // 0.0
/*636  */         }                                                                                                               // 0.0
/*638  */         samples_in_chunk = AV_RL32(src);                                                                                // 0.0
/*640  */         if (samples_in_chunk / 28 > (buf_size - 12) / 30) {                                                             // 0.0
/*642  */             av_log(avctx, AV_LOG_ERROR, "invalid frame\n");                                                             // 0.0
/*644  */             return AVERROR(EINVAL);                                                                                     // 0.0
/*646  */         }                                                                                                               // 0.0
/*648  */         src += 4;                                                                                                       // 0.0
/*650  */         current_left_sample   = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*652  */         previous_left_sample  = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*654  */         current_right_sample  = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*656  */         previous_right_sample = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*660  */         for (count1 = 0; count1 < samples_in_chunk/28;count1++) {                                                       // 0.0
/*662  */             coeff1l = ea_adpcm_table[ *src >> 4       ];                                                                // 0.0
/*664  */             coeff2l = ea_adpcm_table[(*src >> 4  ) + 4];                                                                // 0.0
/*666  */             coeff1r = ea_adpcm_table[*src & 0x0F];                                                                      // 0.0
/*668  */             coeff2r = ea_adpcm_table[(*src & 0x0F) + 4];                                                                // 0.0
/*670  */             src++;                                                                                                      // 0.0
/*674  */             shift_left  = (*src >> 4  ) + 8;                                                                            // 0.0
/*676  */             shift_right = (*src & 0x0F) + 8;                                                                            // 0.0
/*678  */             src++;                                                                                                      // 0.0
/*682  */             for (count2 = 0; count2 < 28; count2++) {                                                                   // 0.0
/*684  */                 next_left_sample  = (int32_t)((*src & 0xF0) << 24) >> shift_left;                                       // 0.0
/*686  */                 next_right_sample = (int32_t)((*src & 0x0F) << 28) >> shift_right;                                      // 0.0
/*688  */                 src++;                                                                                                  // 0.0
/*692  */                 next_left_sample = (next_left_sample +                                                                  // 0.0
/*694  */                     (current_left_sample * coeff1l) +                                                                   // 0.0
/*696  */                     (previous_left_sample * coeff2l) + 0x80) >> 8;                                                      // 0.0
/*698  */                 next_right_sample = (next_right_sample +                                                                // 0.0
/*700  */                     (current_right_sample * coeff1r) +                                                                  // 0.0
/*702  */                     (previous_right_sample * coeff2r) + 0x80) >> 8;                                                     // 0.0
/*706  */                 previous_left_sample = current_left_sample;                                                             // 0.0
/*708  */                 current_left_sample = av_clip_int16(next_left_sample);                                                  // 0.0
/*710  */                 previous_right_sample = current_right_sample;                                                           // 0.0
/*712  */                 current_right_sample = av_clip_int16(next_right_sample);                                                // 0.0
/*714  */                 *samples++ = (unsigned short)current_left_sample;                                                       // 0.0
/*716  */                 *samples++ = (unsigned short)current_right_sample;                                                      // 0.0
/*718  */             }                                                                                                           // 0.0
/*720  */         }                                                                                                               // 0.0
/*724  */         if (src - buf == buf_size - 2)                                                                                  // 0.0
/*726  */             src += 2; // Skip terminating 0x0000                                                                        // 0.0
/*730  */         break;                                                                                                          // 0.0
/*732  */     case CODEC_ID_ADPCM_EA_MAXIS_XA:                                                                                    // 0.0
/*734  */         for(channel = 0; channel < avctx->channels; channel++) {                                                        // 0.0
/*736  */             for (i=0; i<2; i++)                                                                                         // 0.0
/*738  */                 coeff[channel][i] = ea_adpcm_table[(*src >> 4) + 4*i];                                                  // 0.0
/*740  */             shift[channel] = (*src & 0x0F) + 8;                                                                         // 0.0
/*742  */             src++;                                                                                                      // 0.0
/*744  */         }                                                                                                               // 0.0
/*746  */         for (count1 = 0; count1 < (buf_size - avctx->channels) / avctx->channels; count1++) {                           // 0.0
/*748  */             for(i = 4; i >= 0; i-=4) { /* Pairwise samples LL RR (st) or LL LL (mono) */                                // 0.0
/*750  */                 for(channel = 0; channel < avctx->channels; channel++) {                                                // 0.0
/*752  */                     int32_t sample = (int32_t)(((*(src+channel) >> i) & 0x0F) << 0x1C) >> shift[channel];               // 0.0
/*754  */                     sample = (sample +                                                                                  // 0.0
/*756  */                              c->status[channel].sample1 * coeff[channel][0] +                                           // 0.0
/*758  */                              c->status[channel].sample2 * coeff[channel][1] + 0x80) >> 8;                               // 0.0
/*760  */                     c->status[channel].sample2 = c->status[channel].sample1;                                            // 0.0
/*762  */                     c->status[channel].sample1 = av_clip_int16(sample);                                                 // 0.0
/*764  */                     *samples++ = c->status[channel].sample1;                                                            // 0.0
/*766  */                 }                                                                                                       // 0.0
/*768  */             }                                                                                                           // 0.0
/*770  */             src+=avctx->channels;                                                                                       // 0.0
/*772  */         }                                                                                                               // 0.0
/*774  */         break;                                                                                                          // 0.0
/*776  */     case CODEC_ID_ADPCM_EA_R1:                                                                                          // 0.0
/*778  */     case CODEC_ID_ADPCM_EA_R2:                                                                                          // 0.0
/*780  */     case CODEC_ID_ADPCM_EA_R3: {                                                                                        // 0.0
/*782  */         /* channel numbering                                                                                            // 0.0
/*784  */            2chan: 0=fl, 1=fr                                                                                            // 0.0
/*786  */            4chan: 0=fl, 1=rl, 2=fr, 3=rr                                                                                // 0.0
/*788  */            6chan: 0=fl, 1=c,  2=fr, 3=rl,  4=rr, 5=sub */                                                               // 0.0
/*790  */         const int big_endian = avctx->codec->id == CODEC_ID_ADPCM_EA_R3;                                                // 0.0
/*792  */         int32_t previous_sample, current_sample, next_sample;                                                           // 0.0
/*794  */         int32_t coeff1, coeff2;                                                                                         // 0.0
/*796  */         uint8_t shift;                                                                                                  // 0.0
/*798  */         unsigned int channel;                                                                                           // 0.0
/*800  */         uint16_t *samplesC;                                                                                             // 0.0
/*802  */         const uint8_t *srcC;                                                                                            // 0.0
/*804  */         const uint8_t *src_end = buf + buf_size;                                                                        // 0.0
/*808  */         samples_in_chunk = (big_endian ? bytestream_get_be32(&src)                                                      // 0.0
/*810  */                                        : bytestream_get_le32(&src)) / 28;                                               // 0.0
/*812  */         if (samples_in_chunk > UINT32_MAX/(28*avctx->channels) ||                                                       // 0.0
/*814  */             28*samples_in_chunk*avctx->channels > samples_end-samples) {                                                // 0.0
/*816  */             src += buf_size - 4;                                                                                        // 0.0
/*818  */             break;                                                                                                      // 0.0
/*820  */         }                                                                                                               // 0.0
/*824  */         for (channel=0; channel<avctx->channels; channel++) {                                                           // 0.0
/*826  */             int32_t offset = (big_endian ? bytestream_get_be32(&src)                                                    // 0.0
/*828  */                                          : bytestream_get_le32(&src))                                                   // 0.0
/*830  */                            + (avctx->channels-channel-1) * 4;                                                           // 0.0
/*834  */             if ((offset < 0) || (offset >= src_end - src - 4)) break;                                                   // 0.0
/*836  */             srcC  = src + offset;                                                                                       // 0.0
/*838  */             samplesC = samples + channel;                                                                               // 0.0
/*842  */             if (avctx->codec->id == CODEC_ID_ADPCM_EA_R1) {                                                             // 0.0
/*844  */                 current_sample  = (int16_t)bytestream_get_le16(&srcC);                                                  // 0.0
/*846  */                 previous_sample = (int16_t)bytestream_get_le16(&srcC);                                                  // 0.0
/*848  */             } else {                                                                                                    // 0.0
/*850  */                 current_sample  = c->status[channel].predictor;                                                         // 0.0
/*852  */                 previous_sample = c->status[channel].prev_sample;                                                       // 0.0
/*854  */             }                                                                                                           // 0.0
/*858  */             for (count1=0; count1<samples_in_chunk; count1++) {                                                         // 0.0
/*860  */                 if (*srcC == 0xEE) {  /* only seen in R2 and R3 */                                                      // 0.0
/*862  */                     srcC++;                                                                                             // 0.0
/*864  */                     if (srcC > src_end - 30*2) break;                                                                   // 0.0
/*866  */                     current_sample  = (int16_t)bytestream_get_be16(&srcC);                                              // 0.0
/*868  */                     previous_sample = (int16_t)bytestream_get_be16(&srcC);                                              // 0.0
/*872  */                     for (count2=0; count2<28; count2++) {                                                               // 0.0
/*874  */                         *samplesC = (int16_t)bytestream_get_be16(&srcC);                                                // 0.0
/*876  */                         samplesC += avctx->channels;                                                                    // 0.0
/*878  */                     }                                                                                                   // 0.0
/*880  */                 } else {                                                                                                // 0.0
/*882  */                     coeff1 = ea_adpcm_table[ *srcC>>4     ];                                                            // 0.0
/*884  */                     coeff2 = ea_adpcm_table[(*srcC>>4) + 4];                                                            // 0.0
/*886  */                     shift = (*srcC++ & 0x0F) + 8;                                                                       // 0.0
/*890  */                     if (srcC > src_end - 14) break;                                                                     // 0.0
/*892  */                     for (count2=0; count2<28; count2++) {                                                               // 0.0
/*894  */                         if (count2 & 1)                                                                                 // 0.0
/*896  */                             next_sample = (int32_t)((*srcC++ & 0x0F) << 28) >> shift;                                   // 0.0
/*898  */                         else                                                                                            // 0.0
/*900  */                             next_sample = (int32_t)((*srcC   & 0xF0) << 24) >> shift;                                   // 0.0
/*904  */                         next_sample += (current_sample  * coeff1) +                                                     // 0.0
/*906  */                                        (previous_sample * coeff2);                                                      // 0.0
/*908  */                         next_sample = av_clip_int16(next_sample >> 8);                                                  // 0.0
/*912  */                         previous_sample = current_sample;                                                               // 0.0
/*914  */                         current_sample  = next_sample;                                                                  // 0.0
/*916  */                         *samplesC = current_sample;                                                                     // 0.0
/*918  */                         samplesC += avctx->channels;                                                                    // 0.0
/*920  */                     }                                                                                                   // 0.0
/*922  */                 }                                                                                                       // 0.0
/*924  */             }                                                                                                           // 0.0
/*928  */             if (avctx->codec->id != CODEC_ID_ADPCM_EA_R1) {                                                             // 0.0
/*930  */                 c->status[channel].predictor   = current_sample;                                                        // 0.0
/*932  */                 c->status[channel].prev_sample = previous_sample;                                                       // 0.0
/*934  */             }                                                                                                           // 0.0
/*936  */         }                                                                                                               // 0.0
/*940  */         src = src + buf_size - (4 + 4*avctx->channels);                                                                 // 0.0
/*942  */         samples += 28 * samples_in_chunk * avctx->channels;                                                             // 0.0
/*944  */         break;                                                                                                          // 0.0
/*946  */     }                                                                                                                   // 0.0
/*948  */     case CODEC_ID_ADPCM_EA_XAS:                                                                                         // 0.0
/*950  */         if (samples_end-samples < 32*4*avctx->channels                                                                  // 0.0
/*952  */             || buf_size < (4+15)*4*avctx->channels) {                                                                   // 0.0
/*954  */             src += buf_size;                                                                                            // 0.0
/*956  */             break;                                                                                                      // 0.0
/*958  */         }                                                                                                               // 0.0
/*960  */         for (channel=0; channel<avctx->channels; channel++) {                                                           // 0.0
/*962  */             int coeff[2][4], shift[4];                                                                                  // 0.0
/*964  */             short *s2, *s = &samples[channel];                                                                          // 0.0
/*966  */             for (n=0; n<4; n++, s+=32*avctx->channels) {                                                                // 0.0
/*968  */                 for (i=0; i<2; i++)                                                                                     // 0.0
/*970  */                     coeff[i][n] = ea_adpcm_table[(src[0]&0x0F)+4*i];                                                    // 0.0
/*972  */                 shift[n] = (src[2]&0x0F) + 8;                                                                           // 0.0
/*974  */                 for (s2=s, i=0; i<2; i++, src+=2, s2+=avctx->channels)                                                  // 0.0
/*976  */                     s2[0] = (src[0]&0xF0) + (src[1]<<8);                                                                // 0.0
/*978  */             }                                                                                                           // 0.0
/*982  */             for (m=2; m<32; m+=2) {                                                                                     // 0.0
/*984  */                 s = &samples[m*avctx->channels + channel];                                                              // 0.0
/*986  */                 for (n=0; n<4; n++, src++, s+=32*avctx->channels) {                                                     // 0.0
/*988  */                     for (s2=s, i=0; i<8; i+=4, s2+=avctx->channels) {                                                   // 0.0
/*990  */                         int level = (int32_t)((*src & (0xF0>>i)) << (24+i)) >> shift[n];                                // 0.0
/*992  */                         int pred  = s2[-1*avctx->channels] * coeff[0][n]                                                // 0.0
/*994  */                                   + s2[-2*avctx->channels] * coeff[1][n];                                               // 0.0
/*996  */                         s2[0] = av_clip_int16((level + pred + 0x80) >> 8);                                              // 0.0
/*998  */                     }                                                                                                   // 0.0
/*1000 */                 }                                                                                                       // 0.0
/*1002 */             }                                                                                                           // 0.0
/*1004 */         }                                                                                                               // 0.0
/*1006 */         samples += 32*4*avctx->channels;                                                                                // 0.0
/*1008 */         break;                                                                                                          // 0.0
/*1010 */     case CODEC_ID_ADPCM_IMA_AMV:                                                                                        // 0.0
/*1012 */     case CODEC_ID_ADPCM_IMA_SMJPEG:                                                                                     // 0.0
/*1014 */         c->status[0].predictor = (int16_t)bytestream_get_le16(&src);                                                    // 0.0
/*1016 */         c->status[0].step_index = bytestream_get_le16(&src);                                                            // 0.0
/*1020 */         if (avctx->codec->id == CODEC_ID_ADPCM_IMA_AMV)                                                                 // 0.0
/*1022 */             src+=4;                                                                                                     // 0.0
/*1026 */         while (src < buf + buf_size) {                                                                                  // 0.0
/*1028 */             char hi, lo;                                                                                                // 0.0
/*1030 */             lo = *src & 0x0F;                                                                                           // 0.0
/*1032 */             hi = *src >> 4;                                                                                             // 0.0
/*1036 */             if (avctx->codec->id == CODEC_ID_ADPCM_IMA_AMV)                                                             // 0.0
/*1038 */                 FFSWAP(char, hi, lo);                                                                                   // 0.0
/*1042 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],                                                         // 0.0
/*1044 */                 lo, 3);                                                                                                 // 0.0
/*1046 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],                                                         // 0.0
/*1048 */                 hi, 3);                                                                                                 // 0.0
/*1050 */             src++;                                                                                                      // 0.0
/*1052 */         }                                                                                                               // 0.0
/*1054 */         break;                                                                                                          // 0.0
/*1056 */     case CODEC_ID_ADPCM_CT:                                                                                             // 0.0
/*1058 */         while (src < buf + buf_size) {                                                                                  // 0.0
/*1060 */             uint8_t v = *src++;                                                                                         // 0.0
/*1062 */             *samples++ = adpcm_ct_expand_nibble(&c->status[0 ], v >> 4  );                                              // 0.0
/*1064 */             *samples++ = adpcm_ct_expand_nibble(&c->status[st], v & 0x0F);                                              // 0.0
/*1066 */         }                                                                                                               // 0.0
/*1068 */         break;                                                                                                          // 0.0
/*1070 */     case CODEC_ID_ADPCM_SBPRO_4:                                                                                        // 0.0
/*1072 */     case CODEC_ID_ADPCM_SBPRO_3:                                                                                        // 0.0
/*1074 */     case CODEC_ID_ADPCM_SBPRO_2:                                                                                        // 0.0
/*1076 */         if (!c->status[0].step_index) {                                                                                 // 0.0
/*1078 */             /* the first byte is a raw sample */                                                                        // 0.0
/*1080 */             *samples++ = 128 * (*src++ - 0x80);                                                                         // 0.0
/*1082 */             if (st)                                                                                                     // 0.0
/*1084 */               *samples++ = 128 * (*src++ - 0x80);                                                                       // 0.0
/*1086 */             c->status[0].step_index = 1;                                                                                // 0.0
/*1088 */         }                                                                                                               // 0.0
/*1090 */         if (avctx->codec->id == CODEC_ID_ADPCM_SBPRO_4) {                                                               // 0.0
/*1092 */             while (src < buf + buf_size) {                                                                              // 0.0
/*1094 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1096 */                     src[0] >> 4, 4, 0);                                                                                 // 0.0
/*1098 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*1100 */                     src[0] & 0x0F, 4, 0);                                                                               // 0.0
/*1102 */                 src++;                                                                                                  // 0.0
/*1104 */             }                                                                                                           // 0.0
/*1106 */         } else if (avctx->codec->id == CODEC_ID_ADPCM_SBPRO_3) {                                                        // 0.0
/*1108 */             while (src < buf + buf_size && samples + 2 < samples_end) {                                                 // 0.0
/*1110 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1112 */                      src[0] >> 5        , 3, 0);                                                                        // 0.0
/*1114 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1116 */                     (src[0] >> 2) & 0x07, 3, 0);                                                                        // 0.0
/*1118 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1120 */                     src[0] & 0x03, 2, 0);                                                                               // 0.0
/*1122 */                 src++;                                                                                                  // 0.0
/*1124 */             }                                                                                                           // 0.0
/*1126 */         } else {                                                                                                        // 0.0
/*1128 */             while (src < buf + buf_size && samples + 3 < samples_end) {                                                 // 0.0
/*1130 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1132 */                      src[0] >> 6        , 2, 2);                                                                        // 0.0
/*1134 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*1136 */                     (src[0] >> 4) & 0x03, 2, 2);                                                                        // 0.0
/*1138 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*1140 */                     (src[0] >> 2) & 0x03, 2, 2);                                                                        // 0.0
/*1142 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*1144 */                     src[0] & 0x03, 2, 2);                                                                               // 0.0
/*1146 */                 src++;                                                                                                  // 0.0
/*1148 */             }                                                                                                           // 0.0
/*1150 */         }                                                                                                               // 0.0
/*1152 */         break;                                                                                                          // 0.0
/*1154 */     case CODEC_ID_ADPCM_SWF:                                                                                            // 0.0
/*1156 */     {                                                                                                                   // 0.0
/*1158 */         GetBitContext gb;                                                                                               // 0.0
/*1160 */         const int *table;                                                                                               // 0.0
/*1162 */         int k0, signmask, nb_bits, count;                                                                               // 0.0
/*1164 */         int size = buf_size*8;                                                                                          // 0.0
/*1168 */         init_get_bits(&gb, buf, size);                                                                                  // 0.0
/*1172 */         //read bits & initial values                                                                                    // 0.0
/*1174 */         nb_bits = get_bits(&gb, 2)+2;                                                                                   // 0.0
/*1176 */         //av_log(NULL,AV_LOG_INFO,"nb_bits: %d\n", nb_bits);                                                            // 0.0
/*1178 */         table = swf_index_tables[nb_bits-2];                                                                            // 0.0
/*1180 */         k0 = 1 << (nb_bits-2);                                                                                          // 0.0
/*1182 */         signmask = 1 << (nb_bits-1);                                                                                    // 0.0
/*1186 */         while (get_bits_count(&gb) <= size - 22*avctx->channels) {                                                      // 0.0
/*1188 */             for (i = 0; i < avctx->channels; i++) {                                                                     // 0.0
/*1190 */                 *samples++ = c->status[i].predictor = get_sbits(&gb, 16);                                               // 0.0
/*1192 */                 c->status[i].step_index = get_bits(&gb, 6);                                                             // 0.0
/*1194 */             }                                                                                                           // 0.0
/*1198 */             for (count = 0; get_bits_count(&gb) <= size - nb_bits*avctx->channels && count < 4095; count++) {           // 0.0
/*1200 */                 int i;                                                                                                  // 0.0
/*1204 */                 for (i = 0; i < avctx->channels; i++) {                                                                 // 0.0
/*1206 */                     // similar to IMA adpcm                                                                             // 0.0
/*1208 */                     int delta = get_bits(&gb, nb_bits);                                                                 // 0.0
/*1210 */                     int step = ff_adpcm_step_table[c->status[i].step_index];                                            // 0.0
/*1212 */                     long vpdiff = 0; // vpdiff = (delta+0.5)*step/4                                                     // 0.0
/*1214 */                     int k = k0;                                                                                         // 0.0
/*1218 */                     do {                                                                                                // 0.0
/*1220 */                         if (delta & k)                                                                                  // 0.0
/*1222 */                             vpdiff += step;                                                                             // 0.0
/*1224 */                         step >>= 1;                                                                                     // 0.0
/*1226 */                         k >>= 1;                                                                                        // 0.0
/*1228 */                     } while(k);                                                                                         // 0.0
/*1230 */                     vpdiff += step;                                                                                     // 0.0
/*1234 */                     if (delta & signmask)                                                                               // 0.0
/*1236 */                         c->status[i].predictor -= vpdiff;                                                               // 0.0
/*1238 */                     else                                                                                                // 0.0
/*1240 */                         c->status[i].predictor += vpdiff;                                                               // 0.0
/*1244 */                     c->status[i].step_index += table[delta & (~signmask)];                                              // 0.0
/*1248 */                     c->status[i].step_index = av_clip(c->status[i].step_index, 0, 88);                                  // 0.0
/*1250 */                     c->status[i].predictor = av_clip_int16(c->status[i].predictor);                                     // 0.0
/*1254 */                     *samples++ = c->status[i].predictor;                                                                // 0.0
/*1256 */                     if (samples >= samples_end) {                                                                       // 0.0
/*1258 */                         av_log(avctx, AV_LOG_ERROR, "allocated output buffer is too small\n");                          // 0.0
/*1260 */                         return -1;                                                                                      // 0.0
/*1262 */                     }                                                                                                   // 0.0
/*1264 */                 }                                                                                                       // 0.0
/*1266 */             }                                                                                                           // 0.0
/*1268 */         }                                                                                                               // 0.0
/*1270 */         src += buf_size;                                                                                                // 0.0
/*1272 */         break;                                                                                                          // 0.0
/*1274 */     }                                                                                                                   // 0.0
/*1276 */     case CODEC_ID_ADPCM_YAMAHA:                                                                                         // 0.0
/*1278 */         while (src < buf + buf_size) {                                                                                  // 0.0
/*1280 */             uint8_t v = *src++;                                                                                         // 0.0
/*1282 */             *samples++ = adpcm_yamaha_expand_nibble(&c->status[0 ], v & 0x0F);                                          // 0.0
/*1284 */             *samples++ = adpcm_yamaha_expand_nibble(&c->status[st], v >> 4  );                                          // 0.0
/*1286 */         }                                                                                                               // 0.0
/*1288 */         break;                                                                                                          // 0.0
/*1290 */     case CODEC_ID_ADPCM_THP:                                                                                            // 0.0
/*1292 */     {                                                                                                                   // 0.0
/*1294 */         int table[2][16];                                                                                               // 0.0
/*1296 */         unsigned int samplecnt;                                                                                         // 0.0
/*1298 */         int prev[2][2];                                                                                                 // 0.0
/*1300 */         int ch;                                                                                                         // 0.0
/*1304 */         if (buf_size < 80) {                                                                                            // 0.0
/*1306 */             av_log(avctx, AV_LOG_ERROR, "frame too small\n");                                                           // 0.0
/*1308 */             return -1;                                                                                                  // 0.0
/*1310 */         }                                                                                                               // 0.0
/*1314 */         src+=4;                                                                                                         // 0.0
/*1316 */         samplecnt = bytestream_get_be32(&src);                                                                          // 0.0
/*1320 */         for (i = 0; i < 32; i++)                                                                                        // 0.0
/*1322 */             table[0][i] = (int16_t)bytestream_get_be16(&src);                                                           // 0.0
/*1326 */         /* Initialize the previous sample.  */                                                                          // 0.0
/*1328 */         for (i = 0; i < 4; i++)                                                                                         // 0.0
/*1330 */             prev[0][i] = (int16_t)bytestream_get_be16(&src);                                                            // 0.0
/*1334 */         if (samplecnt >= (samples_end - samples) /  (st + 1)) {                                                         // 0.0
/*1336 */             av_log(avctx, AV_LOG_ERROR, "allocated output buffer is too small\n");                                      // 0.0
/*1338 */             return -1;                                                                                                  // 0.0
/*1340 */         }                                                                                                               // 0.0
/*1344 */         for (ch = 0; ch <= st; ch++) {                                                                                  // 0.0
/*1346 */             samples = (unsigned short *) data + ch;                                                                     // 0.0
/*1350 */             /* Read in every sample for this channel.  */                                                               // 0.0
/*1352 */             for (i = 0; i < samplecnt / 14; i++) {                                                                      // 0.0
/*1354 */                 int index = (*src >> 4) & 7;                                                                            // 0.0
/*1356 */                 unsigned int exp = 28 - (*src++ & 15);                                                                  // 0.0
/*1358 */                 int factor1 = table[ch][index * 2];                                                                     // 0.0
/*1360 */                 int factor2 = table[ch][index * 2 + 1];                                                                 // 0.0
/*1364 */                 /* Decode 14 samples.  */                                                                               // 0.0
/*1366 */                 for (n = 0; n < 14; n++) {                                                                              // 0.0
/*1368 */                     int32_t sampledat;                                                                                  // 0.0
/*1370 */                     if(n&1) sampledat=  *src++    <<28;                                                                 // 0.0
/*1372 */                     else    sampledat= (*src&0xF0)<<24;                                                                 // 0.0
/*1376 */                     sampledat = ((prev[ch][0]*factor1                                                                   // 0.0
/*1378 */                                 + prev[ch][1]*factor2) >> 11) + (sampledat>>exp);                                       // 0.0
/*1380 */                     *samples = av_clip_int16(sampledat);                                                                // 0.0
/*1382 */                     prev[ch][1] = prev[ch][0];                                                                          // 0.0
/*1384 */                     prev[ch][0] = *samples++;                                                                           // 0.0
/*1388 */                     /* In case of stereo, skip one sample, this sample                                                  // 0.0
/*1390 */                        is for the other channel.  */                                                                    // 0.0
/*1392 */                     samples += st;                                                                                      // 0.0
/*1394 */                 }                                                                                                       // 0.0
/*1396 */             }                                                                                                           // 0.0
/*1398 */         }                                                                                                               // 0.0
/*1402 */         /* In the previous loop, in case stereo is used, samples is                                                     // 0.0
/*1404 */            increased exactly one time too often.  */                                                                    // 0.0
/*1406 */         samples -= st;                                                                                                  // 0.0
/*1408 */         break;                                                                                                          // 0.0
/*1410 */     }                                                                                                                   // 0.0
/*1414 */     default:                                                                                                            // 0.0
/*1416 */         return -1;                                                                                                      // 0.0
/*1418 */     }                                                                                                                   // 0.0
/*1420 */     *data_size = (uint8_t *)samples - (uint8_t *)data;                                                                  // 0.0
/*1422 */     return src - buf;                                                                                                   // 0.0
/*1424 */ }                                                                                                                       // 0.0
