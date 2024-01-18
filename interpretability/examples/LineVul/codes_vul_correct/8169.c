// commit message FFmpeg@073c2593c9 (target=1, prob=0.5855508, correct=True): Memory leak fix patch by (Burkhard Plaum <plaum >at< ipf.uni-stuttgart )dot( de>)
/*0   */ void ff_mpeg1_encode_init(MpegEncContext *s)                                      // (9) 0.03516
/*2   */ {                                                                                 // (33) 0.001953
/*4   */     static int done=0;                                                            // (19) 0.01758
/*8   */     common_init(s);                                                               // (20) 0.01758
/*12  */     if(!done){                                                                    // (23) 0.01562
/*14  */         int f_code;                                                               // (14) 0.02344
/*16  */         int mv;                                                                   // (15) 0.02148
/*18  */ 	int i;                                                                           // (27) 0.007812
/*22  */         done=1;                                                                   // (17) 0.02148
/*24  */         init_rl(&rl_mpeg1);                                                       // (10) 0.03125
/*28  */ 	for(i=0; i<64; i++)                                                              // (12) 0.02539
/*30  */ 	{                                                                                // (29) 0.003906
/*32  */ 		mpeg1_max_level[0][i]= rl_mpeg1.max_level[0][i];                                // (3) 0.05273
/*34  */ 		mpeg1_index_run[0][i]= rl_mpeg1.index_run[0][i];                                // (4) 0.05273
/*36  */ 	}                                                                                // (30) 0.003906
/*38  */                                                                                   // (24) 0.01562
/*40  */         init_uni_ac_vlc(&rl_mpeg1, uni_mpeg1_ac_vlc_bits, uni_mpeg1_ac_vlc_len);  // (0) 0.0918
/*44  */ 	/* build unified dc encoding tables */                                           // (21) 0.01563
/*46  */ 	for(i=-255; i<256; i++)                                                          // (13) 0.02539
/*48  */ 	{                                                                                // (31) 0.003906
/*50  */ 		int adiff, index;                                                               // (22) 0.01562
/*52  */ 		int bits, code;                                                                 // (26) 0.01367
/*54  */ 		int diff=i;                                                                     // (25) 0.01367
/*58  */ 		adiff = ABS(diff);                                                              // (18) 0.01758
/*60  */ 		if(diff<0) diff--;                                                              // (16) 0.02148
/*62  */ 		index = av_log2(2*adiff);                                                       // (11) 0.02734
/*66  */ 		bits= vlc_dc_lum_bits[index] + index;                                           // (7) 0.03711
/*68  */ 		code= (vlc_dc_lum_code[index]<<index) + (diff & ((1 << index) - 1));            // (2) 0.0625
/*70  */ 		mpeg1_lum_dc_uni[i+255]= bits + (code<<8);                                      // (5) 0.04492
/*72  */ 		                                                                                // (32) 0.003906
/*74  */ 		bits= vlc_dc_chroma_bits[index] + index;                                        // (8) 0.03711
/*76  */ 		code= (vlc_dc_chroma_code[index]<<index) + (diff & ((1 << index) - 1));         // (1) 0.0625
/*78  */ 		mpeg1_chr_dc_uni[i+255]= bits + (code<<8);                                      // (6) 0.04492
/*80  */ 	}                                                                                // (28) 0.003906
/*84  */         mv_penalty= av_mallocz( sizeof(uint8_t)*(MAX_FCODE+1)*(2*MAX_MV+1) );     // 0.0
/*88  */         for(f_code=1; f_code<=MAX_FCODE; f_code++){                               // 0.0
/*90  */             for(mv=-MAX_MV; mv<=MAX_MV; mv++){                                    // 0.0
/*92  */                 int len;                                                          // 0.0
/*96  */                 if(mv==0) len= mbMotionVectorTable[0][1];                         // 0.0
/*98  */                 else{                                                             // 0.0
/*100 */                     int val, bit_size, range, code;                               // 0.0
/*104 */                     bit_size = f_code - 1;                                        // 0.0
/*106 */                     range = 1 << bit_size;                                        // 0.0
/*110 */                     val=mv;                                                       // 0.0
/*112 */                     if (val < 0)                                                  // 0.0
/*114 */                         val = -val;                                               // 0.0
/*116 */                     val--;                                                        // 0.0
/*118 */                     code = (val >> bit_size) + 1;                                 // 0.0
/*120 */                     if(code<17){                                                  // 0.0
/*122 */                         len= mbMotionVectorTable[code][1] + 1 + bit_size;         // 0.0
/*124 */                     }else{                                                        // 0.0
/*126 */                         len= mbMotionVectorTable[16][1] + 2 + bit_size;           // 0.0
/*128 */                     }                                                             // 0.0
/*130 */                 }                                                                 // 0.0
/*134 */                 mv_penalty[f_code][mv+MAX_MV]= len;                               // 0.0
/*136 */             }                                                                     // 0.0
/*138 */         }                                                                         // 0.0
/*140 */                                                                                   // 0.0
/*144 */         for(f_code=MAX_FCODE; f_code>0; f_code--){                                // 0.0
/*146 */             for(mv=-(8<<f_code); mv<(8<<f_code); mv++){                           // 0.0
/*148 */                 fcode_tab[mv+MAX_MV]= f_code;                                     // 0.0
/*150 */             }                                                                     // 0.0
/*152 */         }                                                                         // 0.0
/*154 */     }                                                                             // 0.0
/*156 */     s->me.mv_penalty= mv_penalty;                                                 // 0.0
/*158 */     s->fcode_tab= fcode_tab;                                                      // 0.0
/*160 */     if(s->codec_id == CODEC_ID_MPEG1VIDEO){                                       // 0.0
/*162 */         s->min_qcoeff=-255;                                                       // 0.0
/*164 */         s->max_qcoeff= 255;                                                       // 0.0
/*166 */     }else{                                                                        // 0.0
/*168 */         s->min_qcoeff=-2047;                                                      // 0.0
/*170 */         s->max_qcoeff= 2047;                                                      // 0.0
/*172 */     }                                                                             // 0.0
/*174 */     s->intra_ac_vlc_length=                                                       // 0.0
/*176 */     s->inter_ac_vlc_length=                                                       // 0.0
/*178 */     s->intra_ac_vlc_last_length=                                                  // 0.0
/*180 */     s->inter_ac_vlc_last_length= uni_mpeg1_ac_vlc_len;                            // 0.0
/*182 */ }                                                                                 // 0.0
