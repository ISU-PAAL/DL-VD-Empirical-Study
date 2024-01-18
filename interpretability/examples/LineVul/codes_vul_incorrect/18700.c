// commit message FFmpeg@e70fcf075b (target=1, prob=0.49668413, correct=False): suppressed memory leaks - added image conversion support if the codec does not support YUV420P - added raw output (any comments are welcome to simplify the API)
/*0   */ AVStream *add_audio_stream(AVFormatContext *oc, int codec_id)       // (5) 0.03906
/*2   */ {                                                                   // (35) 0.001954
/*4   */     AVCodec *codec;                                                 // (22) 0.01953
/*6   */     AVCodecContext *c;                                              // (23) 0.01953
/*8   */     AVStream *st;                                                   // (27) 0.01563
/*12  */     st = av_new_stream(oc, 1);                                      // (12) 0.0293
/*14  */     if (!st) {                                                      // (29) 0.01562
/*16  */         fprintf(stderr, "Could not alloc stream\n");                // (2) 0.04297
/*18  */         exit(1);                                                    // (20) 0.02148
/*20  */     }                                                               // (33) 0.007812
/*24  */     /* find the MP2 encoder */                                      // (17) 0.02148
/*26  */     codec = avcodec_find_encoder(codec_id);                         // (8) 0.03711
/*28  */     if (!codec) {                                                   // (25) 0.01758
/*30  */         fprintf(stderr, "codec not found\n");                       // (4) 0.04297
/*32  */         exit(1);                                                    // (21) 0.02148
/*34  */     }                                                               // (34) 0.007812
/*36  */     c = &st->codec;                                                 // (18) 0.02148
/*38  */     c->codec_type = CODEC_TYPE_AUDIO;                               // (9) 0.03711
/*42  */     /* put sample parameters */                                     // (28) 0.01562
/*44  */     c->bit_rate = 64000;                                            // (16) 0.02344
/*46  */     c->sample_rate = 44100;                                         // (15) 0.02344
/*48  */     c->channels = 2;                                                // (24) 0.01953
/*52  */     /* open it */                                                   // (30) 0.01367
/*54  */     if (avcodec_open(c, codec) < 0) {                               // (7) 0.03711
/*56  */         fprintf(stderr, "could not open codec\n");                  // (3) 0.04297
/*58  */         exit(1);                                                    // (19) 0.02148
/*60  */     }                                                               // (32) 0.007812
/*64  */     /* init signal generator */                                     // (26) 0.01563
/*66  */     t = 0;                                                          // (31) 0.01367
/*68  */     tincr = 2 * M_PI * 440.0 / c->sample_rate;                      // (1) 0.04492
/*72  */     audio_outbuf_size = 10000;                                      // (14) 0.02344
/*74  */     audio_outbuf = malloc(audio_outbuf_size);                       // (10) 0.03516
/*78  */     /* ugly hack for PCM codecs (will be removed ASAP with new PCM  // (6) 0.03906
/*80  */        support to compute the input frame size in samples */        // (11) 0.03125
/*82  */     if (c->frame_size <= 1) {                                       // (13) 0.02734
/*84  */         audio_input_frame_size = audio_outbuf_size / c->channels;   // (0) 0.05273
/*86  */         switch(st->codec.codec_id) {                                // 0.0
/*88  */         case CODEC_ID_PCM_S16LE:                                    // 0.0
/*90  */         case CODEC_ID_PCM_S16BE:                                    // 0.0
/*92  */         case CODEC_ID_PCM_U16LE:                                    // 0.0
/*94  */         case CODEC_ID_PCM_U16BE:                                    // 0.0
/*96  */             audio_input_frame_size >>= 1;                           // 0.0
/*98  */             break;                                                  // 0.0
/*100 */         default:                                                    // 0.0
/*102 */             break;                                                  // 0.0
/*104 */         }                                                           // 0.0
/*106 */     } else {                                                        // 0.0
/*108 */         audio_input_frame_size = c->frame_size;                     // 0.0
/*110 */     }                                                               // 0.0
/*112 */     samples = malloc(audio_input_frame_size * 2 * c->channels);     // 0.0
/*116 */     return st;                                                      // 0.0
/*118 */ }                                                                   // 0.0
