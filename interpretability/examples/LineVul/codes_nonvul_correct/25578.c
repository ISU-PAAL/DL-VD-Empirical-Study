// commit message qemu@e1f7b4812e (target=0, prob=0.090326786, correct=True): virtio: limit avail bytes lookahead
/*0  */ static size_t get_request_size(VirtQueue *vq)  // (1) 0.2537
/*2  */ {                                              // (4) 0.01493
/*4  */     unsigned int in, out;                      // (2) 0.1343
/*8  */     virtqueue_get_avail_bytes(vq, &in, &out);  // (0) 0.3284
/*10 */     return in;                                 // (3) 0.08955
/*12 */ }                                              // (5) 0.01493
