// commit message qemu@6e99c631f1 (target=0, prob=0.010873011, correct=True): net/socket: Drop net_socket_can_send
/*0  */ static int net_socket_can_send(void *opaque)  // (1) 0.2632
/*2  */ {                                             // (3) 0.01754
/*4  */     NetSocketState *s = opaque;               // (2) 0.193
/*8  */     return qemu_can_send_packet(&s->nc);      // (0) 0.3333
/*10 */ }                                             // (4) 0.01754
