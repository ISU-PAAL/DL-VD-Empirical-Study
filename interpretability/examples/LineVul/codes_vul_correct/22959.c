// commit message FFmpeg@9ec39937f9 (target=1, prob=0.68363464, correct=True): deshake: variable used uninitialized
/*0   */ static void find_motion(DeshakeContext *deshake, uint8_t *src1, uint8_t *src2,                                 // (4) 0.06045
/*2   */                         int width, int height, int stride, Transform *t)                                       // (1) 0.07019
/*4   */ {                                                                                                              // (24) 0.001958
/*6   */     int x, y;                                                                                                  // (18) 0.01559
/*8   */     IntMotionVector mv = {0, 0};                                                                               // (13) 0.02729
/*10  */     int counts[128][128];                                                                                      // (16) 0.01948
/*12  */     int count_max_value = 0;                                                                                   // (15) 0.02337
/*14  */     int contrast;                                                                                              // (22) 0.01169
/*18  */     int pos;                                                                                                   // (21) 0.01169
/*20  */     double *angles = av_malloc(sizeof(*angles) * width * height / (16 * deshake->blocksize));                  // (3) 0.06233
/*22  */     int center_x = 0, center_y = 0;                                                                            // (12) 0.03117
/*24  */     double p_x, p_y;                                                                                           // (14) 0.02338
/*28  */     // Reset counts to zero                                                                                    // (17) 0.01565
/*30  */     for (x = 0; x < deshake->rx * 2 + 1; x++) {                                                                // (8) 0.04676
/*32  */         for (y = 0; y < deshake->ry * 2 + 1; y++) {                                                            // (5) 0.05453
/*34  */             counts[x][y] = 0;                                                                                  // (10) 0.03895
/*36  */         }                                                                                                      // (19) 0.01558
/*38  */     }                                                                                                          // (23) 0.007796
/*42  */     pos = 0;                                                                                                   // (20) 0.01365
/*44  */     // Find motion for every block and store the motion vector in the counts                                   // (11) 0.0332
/*46  */     for (y = deshake->ry; y < height - deshake->ry - (deshake->blocksize * 2); y += deshake->blocksize * 2) {  // (0) 0.08773
/*48  */         // We use a width of 16 here to match the libavcodec sad functions                                     // (7) 0.04747
/*50  */         for (x = deshake->rx; x < width - deshake->rx - 16; x += 16) {                                         // (2) 0.06639
/*52  */             // If the contrast is too low, just skip this block as it probably                                 // (6) 0.05121
/*54  */             // won't be very useful to us.                                                                     // (9) 0.03933
/*56  */             contrast = block_contrast(src2, x, y, stride, deshake->blocksize);                                 // 0.0
/*58  */             if (contrast > deshake->contrast) {                                                                // 0.0
/*60  */                 //av_log(NULL, AV_LOG_ERROR, "%d\n", contrast);                                                // 0.0
/*62  */                 find_block_motion(deshake, src1, src2, x, y, stride, &mv);                                     // 0.0
/*64  */                 if (mv.x != -1 && mv.y != -1) {                                                                // 0.0
/*66  */                     counts[mv.x + deshake->rx][mv.y + deshake->ry] += 1;                                       // 0.0
/*68  */                     if (x > deshake->rx && y > deshake->ry)                                                    // 0.0
/*70  */                         angles[pos++] = block_angle(x, y, 0, 0, &mv);                                          // 0.0
/*74  */                     center_x += mv.x;                                                                          // 0.0
/*76  */                     center_y += mv.y;                                                                          // 0.0
/*78  */                 }                                                                                              // 0.0
/*80  */             }                                                                                                  // 0.0
/*82  */         }                                                                                                      // 0.0
/*84  */     }                                                                                                          // 0.0
/*88  */     pos = FFMAX(1, pos);                                                                                       // 0.0
/*92  */     center_x /= pos;                                                                                           // 0.0
/*94  */     center_y /= pos;                                                                                           // 0.0
/*98  */     t->angle = clean_mean(angles, pos);                                                                        // 0.0
/*100 */     if (t->angle < 0.001)                                                                                      // 0.0
/*102 */         t->angle = 0;                                                                                          // 0.0
/*106 */     // Find the most common motion vector in the frame and use it as the gmv                                   // 0.0
/*108 */     for (y = deshake->ry * 2; y >= 0; y--) {                                                                   // 0.0
/*110 */         for (x = 0; x < deshake->rx * 2 + 1; x++) {                                                            // 0.0
/*112 */             //av_log(NULL, AV_LOG_ERROR, "%5d ", counts[x][y]);                                                // 0.0
/*114 */             if (counts[x][y] > count_max_value) {                                                              // 0.0
/*116 */                 t->vector.x = x - deshake->rx;                                                                 // 0.0
/*118 */                 t->vector.y = y - deshake->ry;                                                                 // 0.0
/*120 */                 count_max_value = counts[x][y];                                                                // 0.0
/*122 */             }                                                                                                  // 0.0
/*124 */         }                                                                                                      // 0.0
/*126 */         //av_log(NULL, AV_LOG_ERROR, "\n");                                                                    // 0.0
/*128 */     }                                                                                                          // 0.0
/*132 */     p_x = (center_x - width / 2);                                                                              // 0.0
/*134 */     p_y = (center_y - height / 2);                                                                             // 0.0
/*136 */     t->vector.x += (cos(t->angle)-1)*p_x  - sin(t->angle)*p_y;                                                 // 0.0
/*138 */     t->vector.y += sin(t->angle)*p_x  + (cos(t->angle)-1)*p_y;                                                 // 0.0
/*142 */     // Clamp max shift & rotation?                                                                             // 0.0
/*144 */     t->vector.x = av_clipf(t->vector.x, -deshake->rx * 2, deshake->rx * 2);                                    // 0.0
/*146 */     t->vector.y = av_clipf(t->vector.y, -deshake->ry * 2, deshake->ry * 2);                                    // 0.0
/*148 */     t->angle = av_clipf(t->angle, -0.1, 0.1);                                                                  // 0.0
/*152 */     //av_log(NULL, AV_LOG_ERROR, "%d x %d\n", avg->x, avg->y);                                                 // 0.0
/*154 */     av_free(angles);                                                                                           // 0.0
/*156 */ }                                                                                                              // 0.0
