// commit message FFmpeg@39bb30f664 (target=1, prob=0.60244, correct=True): Change all functions referenced in the mxf_metadata_read_table to use the same prototype and also always call them with exactly those arguments. The previous way seems to have worked on all supported platforms, however it was not strictly valid C and would crash e.g. with a compiler that uses stdcall by default. Also avoids warnings if -Wstrict-prototypes is used.
/*0  */ static int mxf_read_track(MXFTrack *track, ByteIOContext *pb, int tag)  // (0) 0.09756
/*2  */ {                                                                       // (17) 0.004065
/*4  */     switch(tag) {                                                       // (14) 0.03252
/*6  */     case 0x4801:                                                        // (7) 0.03659
/*8  */         track->track_id = get_be32(pb);                                 // (5) 0.0813
/*10 */         break;                                                          // (8) 0.03659
/*12 */     case 0x4804:                                                        // (9) 0.03659
/*14 */         get_buffer(pb, track->track_number, 4);                         // (3) 0.08537
/*16 */         break;                                                          // (10) 0.03659
/*18 */     case 0x4B01:                                                        // (6) 0.04065
/*20 */         track->edit_rate.den = get_be32(pb);                            // (1) 0.08943
/*22 */         track->edit_rate.num = get_be32(pb);                            // (2) 0.08943
/*24 */         break;                                                          // (11) 0.03659
/*26 */     case 0x4803:                                                        // (12) 0.03659
/*28 */         get_buffer(pb, track->sequence_ref, 16);                        // (4) 0.08537
/*30 */         break;                                                          // (13) 0.03659
/*32 */     }                                                                   // (16) 0.01626
/*34 */     return 0;                                                           // (15) 0.02439
/*36 */ }                                                                       // (18) 0.004065
