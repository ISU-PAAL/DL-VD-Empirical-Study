// commit message qemu@ef546f1275 (target=0, prob=0.52382505, correct=False): virtio: add feature checking helpers
/*0  */ bool vring_should_notify(VirtIODevice *vdev, Vring *vring)            // (5) 0.06143
/*2  */ {                                                                     // (23) 0.002457
/*4  */     uint16_t old, new;                                                // (14) 0.02703
/*6  */     bool v;                                                           // (19) 0.01474
/*8  */     /* Flush out used index updates. This is paired                   // (11) 0.0344
/*10 */      * with the barrier that the Guest executes when enabling         // (10) 0.0344
/*12 */      * interrupts. */                                                 // (17) 0.01966
/*14 */     smp_mb();                                                         // (18) 0.01966
/*18 */     if ((vdev->guest_features & (1 << VIRTIO_F_NOTIFY_ON_EMPTY)) &&   // (1) 0.07862
/*20 */         unlikely(!vring_more_avail(vdev, vring))) {                   // (6) 0.06143
/*22 */         return true;                                                  // (15) 0.02457
/*24 */     }                                                                 // (20) 0.009828
/*28 */     if (!(vdev->guest_features & (1 << VIRTIO_RING_F_EVENT_IDX))) {   // (0) 0.08108
/*30 */         return !(vring_get_avail_flags(vdev, vring) &                 // (3) 0.06634
/*32 */                  VRING_AVAIL_F_NO_INTERRUPT);                         // (2) 0.07862
/*34 */     }                                                                 // (21) 0.009828
/*36 */     old = vring->signalled_used;                                      // (12) 0.03194
/*38 */     v = vring->signalled_used_valid;                                  // (8) 0.03686
/*40 */     new = vring->signalled_used = vring->last_used_idx;               // (7) 0.05651
/*42 */     vring->signalled_used_valid = true;                               // (9) 0.03686
/*46 */     if (unlikely(!v)) {                                               // (13) 0.02948
/*48 */         return true;                                                  // (16) 0.02457
/*50 */     }                                                                 // (22) 0.009828
/*54 */     return vring_need_event(vring_used_event(&vring->vr), new, old);  // (4) 0.06634
/*56 */ }                                                                     // (24) 0.002457
