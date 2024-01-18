// commit message FFmpeg@2f996b8397 (target=0, prob=0.1216548, correct=True): split stream into valid mp3 frames, at least flv & nut absolutely need this, but probably most other formats too
/*0  */ int MP3lame_encode_frame(AVCodecContext *avctx,                                // (7) 0.04987
/*2  */                      unsigned char *frame, int buf_size, void *data)           // (2) 0.08924
/*4  */ {                                                                              // (21) 0.002625
/*6  */ 	Mp3AudioContext *s = avctx->priv_data;                                        // (10) 0.03937
/*8  */ 	int num, i;                                                                   // (15) 0.01575
/*10 */ //av_log(avctx, AV_LOG_DEBUG, "%X %d %X\n", (int)frame, buf_size, (int)data);  // (0) 0.09711
/*12 */ //        if(data==NULL)                                                       // (11) 0.03675
/*14 */ //            return lame_encode_flush(s->gfp, frame, buf_size);               // (3) 0.08136
/*18 */ 	/* lame 3.91 dies on '1-channel interleaved' data */                          // (8) 0.04724
/*20 */ 	if (s->stereo) {                                                              // (13) 0.02362
/*22 */ 		num = lame_encode_buffer_interleaved(s->gfp, data,                           // (6) 0.05774
/*24 */ 			MPA_FRAME_SIZE, frame, buf_size);                                           // (9) 0.04462
/*26 */ 	} else {                                                                      // (16) 0.0105
/*28 */ 		num = lame_encode_buffer(s->gfp, data, data, MPA_FRAME_SIZE,                 // (4) 0.07349
/*30 */ 			frame, buf_size);                                                           // (14) 0.02362
/*34 */ /*av_log(avctx, AV_LOG_DEBUG, "in:%d out:%d\n", MPA_FRAME_SIZE, num);          // (1) 0.09449
/*36 */ for(i=0; i<num; i++){                                                          // (12) 0.03412
/*38 */     av_log(avctx, AV_LOG_DEBUG, "%2X ", frame[i]);                             // (5) 0.06299
/*40 */ }*/                                                                            // (18) 0.005249
/*42 */ 	}                                                                             // (19) 0.005249
/*46 */ 	return num;                                                                   // (17) 0.0105
/*48 */ }                                                                              // (20) 0.002625
