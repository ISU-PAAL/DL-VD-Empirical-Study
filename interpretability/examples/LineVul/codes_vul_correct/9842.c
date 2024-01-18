// commit message FFmpeg@5b0ad91b99 (target=1, prob=0.85532284, correct=True): - Fix memory leak and others bugs for ppmpipe. Thanks to Rudolf Opalla.
/*0   */ static int img_write_packet(AVFormatContext *s, int stream_index,  // (3) 0.03906
/*2   */                             UINT8 *buf, int size)                  // (0) 0.07031
/*4   */ {                                                                  // (29) 0.001953
/*6   */     VideoData *img = s->priv_data;                                 // (17) 0.02734
/*8   */     AVStream *st = s->streams[stream_index];                       // (8) 0.0332
/*10  */     ByteIOContext pb1, *pb;                                        // (20) 0.02539
/*12  */     AVPicture picture;                                             // (25) 0.01758
/*14  */     int width, height, ret, size1;                                 // (21) 0.02539
/*16  */     char filename[1024];                                           // (27) 0.01563
/*20  */     width = st->codec.width;                                       // (24) 0.02344
/*22  */     height = st->codec.height;                                     // (23) 0.02344
/*26  */     switch(st->codec.pix_fmt) {                                    // (9) 0.0332
/*28  */     case PIX_FMT_YUV420P:                                          // (16) 0.0293
/*30  */         size1 = (width * height * 3) / 2;                          // (5) 0.03906
/*32  */         if (size != size1)                                         // (19) 0.02734
/*34  */             return -EIO;                                           // (15) 0.03125
/*36  */                                                                    // (28) 0.01562
/*38  */         picture.data[0] = buf;                                     // (12) 0.03125
/*40  */         picture.data[1] = picture.data[0] + width * height;        // (2) 0.04883
/*42  */         picture.data[2] = picture.data[1] + (width * height) / 4;  // (1) 0.05664
/*44  */         picture.linesize[0] = width;                               // (10) 0.0332
/*46  */         picture.linesize[1] = width >> 1;                          // (4) 0.03906
/*48  */         picture.linesize[2] = width >> 1;                          // (6) 0.03711
/*50  */         break;                                                     // (26) 0.01758
/*52  */     case PIX_FMT_RGB24:                                            // (22) 0.02539
/*54  */         size1 = (width * height * 3);                              // (11) 0.0332
/*56  */         if (size != size1)                                         // (18) 0.02734
/*58  */             return -EIO;                                           // (14) 0.03125
/*60  */         picture.data[0] = buf;                                     // (13) 0.03125
/*62  */         picture.linesize[0] = width * 3;                           // (7) 0.03711
/*64  */         break;                                                     // 0.0
/*66  */     default:                                                       // 0.0
/*68  */         return -EIO;                                               // 0.0
/*70  */     }                                                              // 0.0
/*72  */                                                                    // 0.0
/*74  */     if (get_frame_filename(filename, sizeof(filename),             // 0.0
/*76  */                            img->path, img->img_number) < 0)        // 0.0
/*78  */         return -EIO;                                               // 0.0
/*82  */     if (!img->is_pipe) {                                           // 0.0
/*84  */         pb = &pb1;                                                 // 0.0
/*86  */         if (url_fopen(pb, filename, URL_WRONLY) < 0)               // 0.0
/*88  */             return -EIO;                                           // 0.0
/*90  */     } else {                                                       // 0.0
/*92  */         pb = &s->pb;                                               // 0.0
/*94  */     }                                                              // 0.0
/*96  */     switch(img->img_fmt) {                                         // 0.0
/*98  */     case IMGFMT_PGMYUV:                                            // 0.0
/*100 */         ret = pgm_save(&picture, width, height, pb, 1);            // 0.0
/*102 */         break;                                                     // 0.0
/*104 */     case IMGFMT_PGM:                                               // 0.0
/*106 */         ret = pgm_save(&picture, width, height, pb, 0);            // 0.0
/*108 */         break;                                                     // 0.0
/*110 */     case IMGFMT_YUV:                                               // 0.0
/*112 */         ret = yuv_save(&picture, width, height, filename);         // 0.0
/*114 */         break;                                                     // 0.0
/*116 */     case IMGFMT_PPM:                                               // 0.0
/*118 */         ret = ppm_save(&picture, width, height, pb);               // 0.0
/*120 */         break;                                                     // 0.0
/*122 */     }                                                              // 0.0
/*124 */     if (!img->is_pipe) {                                           // 0.0
/*126 */         url_fclose(pb);                                            // 0.0
/*128 */     }                                                              // 0.0
/*132 */     img->img_number++;                                             // 0.0
/*134 */     return 0;                                                      // 0.0
/*136 */ }                                                                  // 0.0
