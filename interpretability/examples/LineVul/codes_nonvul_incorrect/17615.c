// commit message FFmpeg@582552fb56 (target=0, prob=0.80838484, correct=False): postproc/yuv2rgb_altivec.c compile fix yuv2rgb_altivec_init_tables does initialize the SwsContext vectors. missing vec_splat. patch by (Luca Barbato <lu_zero at gentoo dot org>) and (Romain Dolbeau <dolbeau at irisa dot fr>)
/*0   */ static int altivec_uyvy_rgb32 (SwsContext *c,                          // (10) 0.03711
/*2   */ 			       unsigned char **in, int *instrides,                          // (8) 0.03906
/*4   */ 			       int srcSliceY,	int srcSliceH,                                // (3) 0.04297
/*6   */ 			       unsigned char **oplanes, int *outstrides)                    // (4) 0.04102
/*8   */ {                                                                      // (30) 0.001953
/*10  */   int w = c->srcW;                                                     // (23) 0.01758
/*12  */   int h = srcSliceH;                                                   // (24) 0.01758
/*14  */   int i,j;                                                             // (29) 0.01172
/*16  */   vector unsigned char uyvy;                                           // (25) 0.01562
/*18  */   vector signed   short Y,U,V;                                         // (17) 0.02344
/*20  */   vector signed   short vx,ux,uvx;                                     // (15) 0.02734
/*22  */   vector signed   short R0,G0,B0,R1,G1,B1;                             // (2) 0.04688
/*24  */   vector unsigned char  R,G,B;                                         // (22) 0.02148
/*26  */   vector unsigned char *out;                                           // (27) 0.01367
/*28  */   ubyte *img;                                                          // (28) 0.01172
/*32  */   img = in[0];                                                         // (26) 0.01367
/*34  */   out = (vector unsigned char *)(oplanes[0]+srcSliceY*outstrides[0]);  // (1) 0.04883
/*38  */   for (i=0;i<h;i++) {                                                  // (14) 0.02734
/*40  */     for (j=0;j<w/16;j++) {                                             // (11) 0.03516
/*42  */       uyvy = vec_ld (0, img);                                          // (12) 0.0332
/*44  */       U = (vector signed short)                                        // (21) 0.02344
/*46  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_u);                  // (5) 0.03906
/*50  */       V = (vector signed short)                                        // (18) 0.02344
/*52  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_v);                  // (6) 0.03906
/*56  */       Y = (vector signed short)                                        // (19) 0.02344
/*58  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_y);                  // (7) 0.03906
/*62  */       cvtyuvtoRGB (c, Y,U,V,&R0,&G0,&B0);                              // (0) 0.0625
/*66  */       uyvy = vec_ld (16, img);                                         // (13) 0.0332
/*68  */       U = (vector signed short)                                        // (16) 0.02344
/*70  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_u);                  // (9) 0.03906
/*74  */       V = (vector signed short)                                        // (20) 0.02344
/*76  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_v);                  // 0.0
/*80  */       Y = (vector signed short)                                        // 0.0
/*82  */ 	vec_perm (uyvy, (vector unsigned char)(0), demux_y);                  // 0.0
/*86  */       cvtyuvtoRGB (c, Y,U,V,&R1,&G1,&B1);                              // 0.0
/*90  */       R  = vec_packclp (R0,R1);                                        // 0.0
/*92  */       G  = vec_packclp (G0,G1);                                        // 0.0
/*94  */       B  = vec_packclp (B0,B1);                                        // 0.0
/*98  */       //      vec_mstbgr24 (R,G,B, out);                               // 0.0
/*100 */       out_rgba (R,G,B,out);                                            // 0.0
/*104 */       img += 32;                                                       // 0.0
/*106 */     }                                                                  // 0.0
/*108 */   }                                                                    // 0.0
/*110 */   return srcSliceH;                                                    // 0.0
/*112 */ }                                                                      // 0.0
