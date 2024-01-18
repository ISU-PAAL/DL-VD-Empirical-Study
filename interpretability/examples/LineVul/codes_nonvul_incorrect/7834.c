// commit message FFmpeg@a4c7a5ea27 (target=0, prob=0.5501155, correct=False): Call ff_fetch_timestamp() for mpeg1/2 when a picture start code is found instead of calling it at the end of a frame with a large negative offset. This significantly reduces the maximal distance in container packets between the point where the first byte of the "access unit" was stored and where we call ff_fetch_timestamp() thus reducing the constraints on our parser. Also change the parser from next_frame_offset to cur, this is needed because now the reference is from container packet start instead of frame start. (i previously misinterpreted this as bug)
/*0   */ int ff_mpeg1_find_frame_end(ParseContext *pc, const uint8_t *buf, int buf_size)                              // (4) 0.06055
/*2   */ {                                                                                                            // (25) 0.001953
/*4   */     int i;                                                                                                   // (21) 0.01172
/*6   */     uint32_t state= pc->state;                                                                               // (13) 0.02539
/*10  */     /* EOF considered as end of frame */                                                                     // (15) 0.02344
/*12  */     if (buf_size == 0)                                                                                       // (17) 0.02148
/*14  */         return 0;                                                                                            // (20) 0.01953
/*18  */ /*                                                                                                           // (24) 0.001953
/*20  */  0  frame start         -> 1/4                                                                               // (12) 0.03125
/*22  */  1  first_SEQEXT        -> 0/2                                                                               // (10) 0.03516
/*24  */  2  first field start   -> 3/0                                                                               // (18) 0.02148
/*26  */  3  second_SEQEXT       -> 2/0                                                                               // (11) 0.0332
/*28  */  4  searching end                                                                                            // (22) 0.007813
/*30  */ */                                                                                                           // (23) 0.001953
/*34  */     for(i=0; i<buf_size; i++){                                                                               // (9) 0.03516
/*36  */         assert(pc->frame_start_found>=0 && pc->frame_start_found<=4);                                        // (5) 0.06055
/*38  */         if(pc->frame_start_found&1){                                                                         // (8) 0.03711
/*40  */             if(state == EXT_START_CODE && (buf[i]&0xF0) != 0x80)                                             // (2) 0.07617
/*42  */                 pc->frame_start_found--;                                                                     // (7) 0.04688
/*44  */             else if(state == EXT_START_CODE+2){                                                              // (6) 0.05078
/*46  */                 if((buf[i]&3) == 3) pc->frame_start_found= 0;                                                // (3) 0.07227
/*48  */                 else                pc->frame_start_found= (pc->frame_start_found+1)&3;                      // (0) 0.1035
/*50  */             }                                                                                                // (16) 0.02344
/*52  */             state++;                                                                                         // (14) 0.02539
/*54  */         }else{                                                                                               // (19) 0.01953
/*56  */             i= ff_find_start_code(buf+i, buf+buf_size, &state) - buf - 1;                                    // (1) 0.07617
/*58  */             if(pc->frame_start_found==0 && state >= SLICE_MIN_START_CODE && state <= SLICE_MAX_START_CODE){  // 0.0
/*60  */                 i++;                                                                                         // 0.0
/*62  */                 pc->frame_start_found=4;                                                                     // 0.0
/*64  */             }                                                                                                // 0.0
/*66  */             if(state == SEQ_END_CODE){                                                                       // 0.0
/*68  */                 pc->state=-1;                                                                                // 0.0
/*70  */                 return i+1;                                                                                  // 0.0
/*72  */             }                                                                                                // 0.0
/*74  */             if(pc->frame_start_found==2 && state == SEQ_START_CODE)                                          // 0.0
/*76  */                 pc->frame_start_found= 0;                                                                    // 0.0
/*78  */             if(pc->frame_start_found<4 && state == EXT_START_CODE)                                           // 0.0
/*80  */                 pc->frame_start_found++;                                                                     // 0.0
/*82  */             if(pc->frame_start_found == 4 && (state&0xFFFFFF00) == 0x100){                                   // 0.0
/*84  */                 if(state < SLICE_MIN_START_CODE || state > SLICE_MAX_START_CODE){                            // 0.0
/*86  */                     pc->frame_start_found=0;                                                                 // 0.0
/*88  */                     pc->state=-1;                                                                            // 0.0
/*90  */                     return i-3;                                                                              // 0.0
/*92  */                 }                                                                                            // 0.0
/*94  */             }                                                                                                // 0.0
/*96  */         }                                                                                                    // 0.0
/*98  */     }                                                                                                        // 0.0
/*100 */     pc->state= state;                                                                                        // 0.0
/*102 */     return END_NOT_FOUND;                                                                                    // 0.0
/*104 */ }                                                                                                            // 0.0
