// commit message qemu@e3f5ec2b5e (target=0, prob=0.28900263, correct=True): net: pass VLANClientState* as first arg to receive handlers
/*0  */ qemu_deliver_packet(VLANClientState *sender, const uint8_t *buf, int size)  // (1) 0.2014
/*2  */ {                                                                           // (7) 0.006944
/*4  */     VLANClientState *vc;                                                    // (4) 0.06944
/*8  */     for (vc = sender->vlan->first_client; vc != NULL; vc = vc->next) {      // (0) 0.2083
/*10 */         if (vc != sender && !vc->link_down) {                               // (3) 0.1458
/*12 */             vc->receive(vc->opaque, buf, size);                             // (2) 0.1806
/*14 */         }                                                                   // (5) 0.05556
/*16 */     }                                                                       // (6) 0.02778
/*18 */ }                                                                           // (8) 0.006944
