// commit message FFmpeg@ebea370dc3 (target=0, prob=0.45983845, correct=True): ismindex: check mkdir()s return code
/*0  */ static int write_fragments(struct Tracks *tracks, int start_index,                // (9) 0.048
/*2  */                            AVIOContext *in)                                       // (2) 0.08533
/*4  */ {                                                                                 // (17) 0.002667
/*6  */     char dirname[100], filename[500];                                             // (12) 0.03467
/*8  */     int i, j;                                                                     // (13) 0.02133
/*12 */     for (i = start_index; i < tracks->nb_tracks; i++) {                           // (7) 0.05867
/*14 */         struct Track *track = tracks->tracks[i];                                  // (10) 0.048
/*16 */         const char *type    = track->is_video ? "video" : "audio";                // (5) 0.07467
/*18 */         snprintf(dirname, sizeof(dirname), "QualityLevels(%d)", track->bitrate);  // (4) 0.08267
/*20 */         mkdir(dirname, 0777);                                                     // (11) 0.04267
/*22 */         for (j = 0; j < track->chunks; j++) {                                     // (6) 0.06133
/*24 */             snprintf(filename, sizeof(filename), "%s/Fragments(%s=%"PRId64")",    // (0) 0.09333
/*26 */                      dirname, type, track->offsets[j].time);                      // (1) 0.09067
/*28 */             avio_seek(in, track->offsets[j].offset, SEEK_SET);                    // (3) 0.08533
/*30 */             write_fragment(filename, in);                                         // (8) 0.056
/*32 */         }                                                                         // (14) 0.02133
/*34 */     }                                                                             // (16) 0.01067
/*36 */     return 0;                                                                     // (15) 0.016
/*38 */ }                                                                                 // (18) 0.002667
