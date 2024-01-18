// commit message qemu@ab03b63d7a (target=1, prob=0.04857859, correct=False): [virtio-9p] open should not return EBADF
/*0  */ static void v9fs_post_lcreate(V9fsState *s, V9fsLcreateState *vs, int err)  // (1) 0.09404
/*2  */ {                                                                           // (17) 0.003135
/*4  */     if (err == 0) {                                                         // (13) 0.03135
/*6  */         v9fs_string_copy(&vs->fidp->path, &vs->fullname);                   // (2) 0.09091
/*8  */         stat_to_qid(&vs->stbuf, &vs->qid);                                  // (4) 0.07837
/*10 */         vs->offset += pdu_marshal(vs->pdu, vs->offset, "Qd", &vs->qid,      // (0) 0.116
/*12 */                 &vs->iounit);                                               // (5) 0.06897
/*14 */         err = vs->offset;                                                   // (10) 0.04075
/*16 */     } else {                                                                // (14) 0.01881
/*18 */         vs->fidp->fid_type = P9_FID_NONE;                                   // (3) 0.08464
/*20 */         close(vs->fidp->fs.fd);                                             // (6) 0.05956
/*22 */         err = -errno;                                                       // (11) 0.04075
/*24 */     }                                                                       // (15) 0.01254
/*28 */     complete_pdu(s, vs->pdu, err);                                          // (7) 0.05329
/*30 */     v9fs_string_free(&vs->name);                                            // (9) 0.04702
/*32 */     v9fs_string_free(&vs->fullname);                                        // (8) 0.05016
/*34 */     qemu_free(vs);                                                          // (12) 0.03448
/*36 */ }                                                                           // (16) 0.003135
