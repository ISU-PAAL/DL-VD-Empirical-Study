// commit message qemu@b6866fee58 (target=0, prob=0.4368263, correct=True): virtio-scsi: Implement hotplug support for virtio-scsi
/*0  */ static void virtio_scsi_parse_req(VirtIOSCSI *s, VirtQueue *vq,   // (7) 0.0587
/*2  */                                   VirtIOSCSIReq *req)             // (0) 0.09348
/*4  */ {                                                                 // (17) 0.002174
/*6  */     assert(req->elem.out_num && req->elem.in_num);                // (10) 0.05
/*8  */     req->vq = vq;                                                 // (12) 0.02391
/*10 */     req->dev = s;                                                 // (14) 0.01957
/*12 */     req->sreq = NULL;                                             // (13) 0.02174
/*14 */     req->req.buf = req->elem.out_sg[0].iov_base;                  // (8) 0.05217
/*16 */     req->resp.buf = req->elem.in_sg[0].iov_base;                  // (9) 0.05217
/*20 */     if (req->elem.out_num > 1) {                                  // (11) 0.03696
/*22 */         qemu_sgl_init_external(&req->qsgl, &req->elem.out_sg[1],  // (5) 0.07609
/*24 */                                &req->elem.out_addr[1],            // (1) 0.0913
/*26 */                                req->elem.out_num - 1);            // (3) 0.08913
/*28 */     } else {                                                      // (15) 0.01304
/*30 */         qemu_sgl_init_external(&req->qsgl, &req->elem.in_sg[1],   // (6) 0.07609
/*32 */                                &req->elem.in_addr[1],             // (2) 0.0913
/*34 */                                req->elem.in_num - 1);             // (4) 0.08913
/*36 */     }                                                             // (16) 0.008696
/*38 */ }                                                                 // (18) 0.002174
