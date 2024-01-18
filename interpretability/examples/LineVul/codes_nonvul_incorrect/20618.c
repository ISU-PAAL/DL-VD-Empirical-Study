// commit message FFmpeg@68f593b484 (target=0, prob=0.7703562, correct=False): GetBitContext.size is allways multiplied by 8 -> use size_in_bits to avoid useless *8 in a few inner loops
/*0   */ int ff_mpeg4_decode_picture_header(MpegEncContext * s, GetBitContext *gb)      // (5) 0.05078
/*2   */ {                                                                              // (24) 0.001953
/*4   */     int startcode, v;                                                          // (17) 0.01758
/*8   */     /* search next start code */                                               // (18) 0.01758
/*10  */     align_get_bits(gb);                                                        // (16) 0.02148
/*12  */     startcode = 0xff;                                                          // (19) 0.01758
/*14  */     for(;;) {                                                                  // (20) 0.01562
/*16  */         v = get_bits(gb, 8);                                                   // (13) 0.0332
/*18  */         startcode = ((startcode << 8) | v) & 0xffffffff;                       // (8) 0.04883
/*20  */                                                                                // (22) 0.01562
/*22  */         if(get_bits_count(gb) >= gb->size*8){                                  // (7) 0.04883
/*24  */             if(gb->size==1 && s->divx_version){                                // (6) 0.05078
/*26  */                 printf("frame skip %d\n", gb->size);                           // (2) 0.05664
/*28  */                 return FRAME_SKIPED; //divx bug                                // (4) 0.05273
/*30  */             }else                                                              // (15) 0.02539
/*32  */                 return -1; //end of stream                                     // (10) 0.04492
/*34  */         }                                                                      // (21) 0.01562
/*38  */         if((startcode&0xFFFFFF00) != 0x100)                                    // (12) 0.04492
/*40  */             continue; //no startcode                                           // (14) 0.0332
/*42  */                                                                                // (23) 0.01562
/*44  */         if(s->avctx->debug&FF_DEBUG_STARTCODE){                                // (9) 0.04687
/*46  */             printf("startcode: %3X ", startcode);                              // (11) 0.04492
/*48  */             if     (startcode<=0x11F) printf("Video Object Start");            // (0) 0.0625
/*50  */             else if(startcode<=0x12F) printf("Video Object Layer Start");      // (1) 0.0586
/*52  */             else if(startcode<=0x13F) printf("Reserved");                      // (3) 0.05469
/*54  */             else if(startcode<=0x15F) printf("FGS bp start");                  // 0.0
/*56  */             else if(startcode<=0x1AF) printf("Reserved");                      // 0.0
/*58  */             else if(startcode==0x1B0) printf("Visual Object Seq Start");       // 0.0
/*60  */             else if(startcode==0x1B1) printf("Visual Object Seq End");         // 0.0
/*62  */             else if(startcode==0x1B2) printf("User Data");                     // 0.0
/*64  */             else if(startcode==0x1B3) printf("Group of VOP start");            // 0.0
/*66  */             else if(startcode==0x1B4) printf("Video Session Error");           // 0.0
/*68  */             else if(startcode==0x1B5) printf("Visual Object Start");           // 0.0
/*70  */             else if(startcode==0x1B6) printf("Video Object Plane start");      // 0.0
/*72  */             else if(startcode==0x1B7) printf("slice start");                   // 0.0
/*74  */             else if(startcode==0x1B8) printf("extension start");               // 0.0
/*76  */             else if(startcode==0x1B9) printf("fgs start");                     // 0.0
/*78  */             else if(startcode==0x1BA) printf("FBA Object start");              // 0.0
/*80  */             else if(startcode==0x1BB) printf("FBA Object Plane start");        // 0.0
/*82  */             else if(startcode==0x1BC) printf("Mesh Object start");             // 0.0
/*84  */             else if(startcode==0x1BD) printf("Mesh Object Plane start");       // 0.0
/*86  */             else if(startcode==0x1BE) printf("Still Textutre Object start");   // 0.0
/*88  */             else if(startcode==0x1BF) printf("Textutre Spatial Layer start");  // 0.0
/*90  */             else if(startcode==0x1C0) printf("Textutre SNR Layer start");      // 0.0
/*92  */             else if(startcode==0x1C1) printf("Textutre Tile start");           // 0.0
/*94  */             else if(startcode==0x1C2) printf("Textutre Shape Layer start");    // 0.0
/*96  */             else if(startcode==0x1C3) printf("stuffing start");                // 0.0
/*98  */             else if(startcode<=0x1C5) printf("reserved");                      // 0.0
/*100 */             else if(startcode<=0x1FF) printf("System start");                  // 0.0
/*102 */             printf(" at %d\n", get_bits_count(gb));                            // 0.0
/*104 */         }                                                                      // 0.0
/*108 */         switch(startcode){                                                     // 0.0
/*110 */         case 0x120:                                                            // 0.0
/*112 */             decode_vol_header(s, gb);                                          // 0.0
/*114 */             break;                                                             // 0.0
/*116 */         case USER_DATA_STARTCODE:                                              // 0.0
/*118 */             decode_user_data(s, gb);                                           // 0.0
/*120 */             break;                                                             // 0.0
/*122 */         case GOP_STARTCODE:                                                    // 0.0
/*124 */             mpeg4_decode_gop_header(s, gb);                                    // 0.0
/*126 */             break;                                                             // 0.0
/*128 */         case VOP_STARTCODE:                                                    // 0.0
/*130 */             return decode_vop_header(s, gb);                                   // 0.0
/*132 */         default:                                                               // 0.0
/*134 */             break;                                                             // 0.0
/*136 */         }                                                                      // 0.0
/*140 */         align_get_bits(gb);                                                    // 0.0
/*142 */         startcode = 0xff;                                                      // 0.0
/*144 */     }                                                                          // 0.0
/*146 */ }                                                                              // 0.0
