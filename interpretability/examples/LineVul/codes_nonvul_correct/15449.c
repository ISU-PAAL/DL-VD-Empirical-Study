// commit message qemu@a2db2a1edd (target=0, prob=0.42138118, correct=True): xen: Switch to libxenevtchn interface for compat shims.
/*0   */ static struct XenDevice *xen_be_get_xendev(const char *type, int dom, int dev,  // (5) 0.05273
/*2   */                                            struct XenDevOps *ops)               // (0) 0.0957
/*4   */ {                                                                               // (25) 0.001953
/*6   */     struct XenDevice *xendev;                                                   // (19) 0.02148
/*10  */     xendev = xen_be_find_xendev(type, dom, dev);                                // (9) 0.04492
/*12  */     if (xendev) {                                                               // (20) 0.01953
/*14  */         return xendev;                                                          // (17) 0.02344
/*16  */     }                                                                           // (23) 0.007812
/*20  */     /* init new xendev */                                                       // (21) 0.01953
/*22  */     xendev = g_malloc0(ops->size);                                              // (10) 0.0332
/*24  */     xendev->type  = type;                                                       // (18) 0.02344
/*26  */     xendev->dom   = dom;                                                        // (15) 0.02539
/*28  */     xendev->dev   = dev;                                                        // (16) 0.02539
/*30  */     xendev->ops   = ops;                                                        // (14) 0.02539
/*34  */     snprintf(xendev->be, sizeof(xendev->be), "backend/%s/%d/%d",                // (1) 0.06445
/*36  */              xendev->type, xendev->dom, xendev->dev);                           // (2) 0.05859
/*38  */     snprintf(xendev->name, sizeof(xendev->name), "%s-%d",                       // (6) 0.05078
/*40  */              xendev->type, xendev->dev);                                        // (8) 0.04688
/*44  */     xendev->debug      = debug;                                                 // (11) 0.03125
/*46  */     xendev->local_port = -1;                                                    // (13) 0.02734
/*50  */     xendev->evtchndev = xen_xc_evtchn_open(NULL, 0);                            // (7) 0.05078
/*52  */     if (xendev->evtchndev == XC_HANDLER_INITIAL_VALUE) {                        // (4) 0.05469
/*54  */         xen_be_printf(NULL, 0, "can't open evtchn device\n");                   // (3) 0.05469
/*56  */         g_free(xendev);                                                         // (12) 0.0293
/*58  */         return NULL;                                                            // (22) 0.01953
/*60  */     }                                                                           // (24) 0.007812
/*62  */     fcntl(xc_evtchn_fd(xendev->evtchndev), F_SETFD, FD_CLOEXEC);                // 0.0
/*66  */     if (ops->flags & DEVOPS_FLAG_NEED_GNTDEV) {                                 // 0.0
/*68  */         xendev->gnttabdev = xen_xc_gnttab_open(NULL, 0);                        // 0.0
/*70  */         if (xendev->gnttabdev == XC_HANDLER_INITIAL_VALUE) {                    // 0.0
/*72  */             xen_be_printf(NULL, 0, "can't open gnttab device\n");               // 0.0
/*74  */             xc_evtchn_close(xendev->evtchndev);                                 // 0.0
/*76  */             g_free(xendev);                                                     // 0.0
/*78  */             return NULL;                                                        // 0.0
/*80  */         }                                                                       // 0.0
/*82  */     } else {                                                                    // 0.0
/*84  */         xendev->gnttabdev = XC_HANDLER_INITIAL_VALUE;                           // 0.0
/*86  */     }                                                                           // 0.0
/*90  */     QTAILQ_INSERT_TAIL(&xendevs, xendev, next);                                 // 0.0
/*94  */     if (xendev->ops->alloc) {                                                   // 0.0
/*96  */         xendev->ops->alloc(xendev);                                             // 0.0
/*98  */     }                                                                           // 0.0
/*102 */     return xendev;                                                              // 0.0
/*104 */ }                                                                               // 0.0
