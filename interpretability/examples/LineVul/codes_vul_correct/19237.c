// commit message qemu@a1c5975270 (target=1, prob=0.81052107, correct=True): virtio-serial: Fix check for 'assert'; prevent NULL derefs
/*0  */ static void flush_queued_data(VirtIOSerialPort *port, bool discard)     // (1) 0.2917
/*2  */ {                                                                       // (3) 0.01389
/*4  */     assert(port || discard);                                            // (2) 0.125
/*8  */     do_flush_queued_data(port, port->ovq, &port->vser->vdev, discard);  // (0) 0.4167
/*10 */ }                                                                       // (4) 0.01389
