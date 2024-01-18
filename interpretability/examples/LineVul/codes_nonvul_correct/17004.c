// commit message qemu@a2db2a1edd (target=0, prob=0.0069250553, correct=True): xen: Switch to libxenevtchn interface for compat shims.
/*0 */ int xen_be_send_notify(struct XenDevice *xendev)                     // (1) 0.3051
/*2 */ {                                                                    // (2) 0.01695
/*4 */     return xc_evtchn_notify(xendev->evtchndev, xendev->local_port);  // (0) 0.5254
/*6 */ }                                                                    // (3) 0.01695
