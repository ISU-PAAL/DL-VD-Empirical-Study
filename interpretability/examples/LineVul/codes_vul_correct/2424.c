// commit message FFmpeg@b9fa32082c (target=1, prob=0.5127449, correct=True): exploit mdct symmetry 2% faster vorbis on conroe, k8. 7% on celeron.
/*0   */ static int vorbis_parse_id_hdr(vorbis_context *vc){                                                                                                                     // (12) 0.03907
/*2   */     GetBitContext *gb=&vc->gb;                                                                                                                                          // (16) 0.02734
/*4   */     uint_fast8_t bl0, bl1;                                                                                                                                              // (15) 0.0293
/*8   */     if ((get_bits(gb, 8)!='v') || (get_bits(gb, 8)!='o') ||                                                                                                             // (4) 0.05859
/*10  */     (get_bits(gb, 8)!='r') || (get_bits(gb, 8)!='b') ||                                                                                                                 // (6) 0.05664
/*12  */     (get_bits(gb, 8)!='i') || (get_bits(gb, 8)!='s')) {                                                                                                                 // (5) 0.05859
/*14  */         av_log(vc->avccontext, AV_LOG_ERROR, " Vorbis id header packet corrupt (no vorbis signature). \n");                                                             // (0) 0.08203
/*16  */         return 1;                                                                                                                                                       // (19) 0.01953
/*18  */     }                                                                                                                                                                   // (21) 0.007813
/*22  */     vc->version=get_bits_long(gb, 32);    //FIXME check 0                                                                                                               // (8) 0.05078
/*24  */     vc->audio_channels=get_bits(gb, 8);   //FIXME check >0                                                                                                              // (7) 0.05273
/*26  */     vc->audio_samplerate=get_bits_long(gb, 32);   //FIXME check >0                                                                                                      // (3) 0.05859
/*28  */     vc->bitrate_maximum=get_bits_long(gb, 32);                                                                                                                          // (11) 0.04102
/*30  */     vc->bitrate_nominal=get_bits_long(gb, 32);                                                                                                                          // (9) 0.04297
/*32  */     vc->bitrate_minimum=get_bits_long(gb, 32);                                                                                                                          // (10) 0.04102
/*34  */     bl0=get_bits(gb, 4);                                                                                                                                                // (18) 0.02734
/*36  */     bl1=get_bits(gb, 4);                                                                                                                                                // (17) 0.02734
/*38  */     vc->blocksize[0]=(1<<bl0);                                                                                                                                          // (14) 0.0332
/*40  */     vc->blocksize[1]=(1<<bl1);                                                                                                                                          // (13) 0.0332
/*42  */     if (bl0>13 || bl0<6 || bl1>13 || bl1<6 || bl1<bl0) {                                                                                                                // (2) 0.0625
/*44  */         av_log(vc->avccontext, AV_LOG_ERROR, " Vorbis id header packet corrupt (illegal blocksize). \n");                                                               // (1) 0.07813
/*46  */         return 3;                                                                                                                                                       // (20) 0.01953
/*48  */     }                                                                                                                                                                   // 0.0
/*50  */     // output format int16                                                                                                                                              // 0.0
/*52  */     if (vc->blocksize[1]/2 * vc->audio_channels * 2 >                                                                                                                   // 0.0
/*54  */                                              AVCODEC_MAX_AUDIO_FRAME_SIZE) {                                                                                            // 0.0
/*56  */         av_log(vc->avccontext, AV_LOG_ERROR, "Vorbis channel count makes "                                                                                              // 0.0
/*58  */                "output packets too large.\n");                                                                                                                          // 0.0
/*60  */         return 4;                                                                                                                                                       // 0.0
/*62  */     }                                                                                                                                                                   // 0.0
/*64  */     vc->win[0]=ff_vorbis_vwin[bl0-6];                                                                                                                                   // 0.0
/*66  */     vc->win[1]=ff_vorbis_vwin[bl1-6];                                                                                                                                   // 0.0
/*70  */     if(vc->exp_bias){                                                                                                                                                   // 0.0
/*72  */         int i, j;                                                                                                                                                       // 0.0
/*74  */         for(j=0; j<2; j++){                                                                                                                                             // 0.0
/*76  */             float *win = av_malloc(vc->blocksize[j]/2 * sizeof(float));                                                                                                 // 0.0
/*78  */             for(i=0; i<vc->blocksize[j]/2; i++)                                                                                                                         // 0.0
/*80  */                 win[i] = vc->win[j][i] * (1<<15);                                                                                                                       // 0.0
/*82  */             vc->win[j] = win;                                                                                                                                           // 0.0
/*84  */         }                                                                                                                                                               // 0.0
/*86  */     }                                                                                                                                                                   // 0.0
/*90  */     if ((get_bits1(gb)) == 0) {                                                                                                                                         // 0.0
/*92  */         av_log(vc->avccontext, AV_LOG_ERROR, " Vorbis id header packet corrupt (framing flag not set). \n");                                                            // 0.0
/*94  */         return 2;                                                                                                                                                       // 0.0
/*96  */     }                                                                                                                                                                   // 0.0
/*100 */     vc->channel_residues= av_malloc((vc->blocksize[1]/2)*vc->audio_channels * sizeof(float));                                                                           // 0.0
/*102 */     vc->channel_floors  = av_malloc((vc->blocksize[1]/2)*vc->audio_channels * sizeof(float));                                                                           // 0.0
/*104 */     vc->saved           = av_mallocz((vc->blocksize[1]/2)*vc->audio_channels * sizeof(float));                                                                          // 0.0
/*106 */     vc->ret             = av_malloc((vc->blocksize[1]/2)*vc->audio_channels * sizeof(float));                                                                           // 0.0
/*108 */     vc->buf             = av_malloc( vc->blocksize[1]                       * sizeof(float));                                                                           // 0.0
/*110 */     vc->buf_tmp         = av_malloc( vc->blocksize[1]                       * sizeof(float));                                                                           // 0.0
/*112 */     vc->previous_window=0;                                                                                                                                              // 0.0
/*116 */     ff_mdct_init(&vc->mdct[0], bl0, 1);                                                                                                                                 // 0.0
/*118 */     ff_mdct_init(&vc->mdct[1], bl1, 1);                                                                                                                                 // 0.0
/*122 */     AV_DEBUG(" vorbis version %d \n audio_channels %d \n audio_samplerate %d \n bitrate_max %d \n bitrate_nom %d \n bitrate_min %d \n blk_0 %d blk_1 %d \n ",           // 0.0
/*124 */             vc->version, vc->audio_channels, vc->audio_samplerate, vc->bitrate_maximum, vc->bitrate_nominal, vc->bitrate_minimum, vc->blocksize[0], vc->blocksize[1]);  // 0.0
/*128 */ /*                                                                                                                                                                      // 0.0
/*130 */     BLK=vc->blocksize[0];                                                                                                                                               // 0.0
/*132 */     for(i=0;i<BLK/2;++i) {                                                                                                                                              // 0.0
/*134 */         vc->win[0][i]=sin(0.5*3.14159265358*(sin(((float)i+0.5)/(float)BLK*3.14159265358))*(sin(((float)i+0.5)/(float)BLK*3.14159265358)));                             // 0.0
/*136 */     }                                                                                                                                                                   // 0.0
/*138 */ */                                                                                                                                                                      // 0.0
/*142 */     return 0;                                                                                                                                                           // 0.0
/*144 */ }                                                                                                                                                                       // 0.0
