// commit message qemu@51b19ebe43 (target=0, prob=0.56789935, correct=False): virtio: move allocation to virtqueue_pop/vring_pop
/*0  */ static VirtIOBlockReq *virtio_blk_get_request(VirtIOBlock *s)  // (0) 0.192
/*2  */ {                                                              // (7) 0.008
/*4  */     VirtIOBlockReq *req = virtio_blk_alloc_request(s);         // (1) 0.184
/*8  */     if (!virtqueue_pop(s->vq, &req->elem)) {                   // (2) 0.176
/*10 */         virtio_blk_free_request(req);                          // (3) 0.152
/*12 */         return NULL;                                           // (4) 0.08
/*14 */     }                                                          // (6) 0.032
/*18 */     return req;                                                // (5) 0.048
/*20 */ }                                                              // (8) 0.008
