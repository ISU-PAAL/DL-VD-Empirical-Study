// commit message qemu@c0c24b9554 (target=1, prob=0.9992106, correct=True): xen/9pfs: fix two resource leaks on error paths, discovered by Coverity
/*0   */ static int xen_9pfs_connect(struct XenDevice *xendev)                             // (13) 0.03516
/*2   */ {                                                                                 // (20) 0.001953
/*4   */     int i;                                                                        // (18) 0.01172
/*6   */     Xen9pfsDev *xen_9pdev = container_of(xendev, Xen9pfsDev, xendev);             // (4) 0.06641
/*8   */     V9fsState *s = &xen_9pdev->state;                                             // (12) 0.03906
/*10  */     QemuOpts *fsdev;                                                              // (14) 0.02344
/*14  */     if (xenstore_read_fe_int(&xen_9pdev->xendev, "num-rings",                     // (6) 0.06055
/*16  */                              &xen_9pdev->num_rings) == -1 ||                      // (1) 0.08594
/*18  */         xen_9pdev->num_rings > MAX_RINGS || xen_9pdev->num_rings < 1) {           // (3) 0.06836
/*20  */         return -1;                                                                // (16) 0.02148
/*22  */     }                                                                             // (19) 0.007812
/*26  */     xen_9pdev->rings = g_malloc0(xen_9pdev->num_rings * sizeof(Xen9pfsRing));     // (2) 0.07227
/*28  */     for (i = 0; i < xen_9pdev->num_rings; i++) {                                  // (10) 0.04687
/*30  */         char *str;                                                                // (17) 0.02148
/*32  */         int ring_order;                                                           // (15) 0.02344
/*36  */         xen_9pdev->rings[i].priv = xen_9pdev;                                     // (7) 0.04883
/*38  */         xen_9pdev->rings[i].evtchn = -1;                                          // (9) 0.04687
/*40  */         xen_9pdev->rings[i].local_port = -1;                                      // (11) 0.04687
/*44  */         str = g_strdup_printf("ring-ref%u", i);                                   // (8) 0.04883
/*46  */         if (xenstore_read_fe_int(&xen_9pdev->xendev, str,                         // (5) 0.0625
/*48  */                                  &xen_9pdev->rings[i].ref) == -1) {               // (0) 0.09961
/*51  */             goto out;                                                             // 0.0
/*53  */         }                                                                         // 0.0
/*56  */         str = g_strdup_printf("event-channel-%u", i);                             // 0.0
/*58  */         if (xenstore_read_fe_int(&xen_9pdev->xendev, str,                         // 0.0
/*60  */                                  &xen_9pdev->rings[i].evtchn) == -1) {            // 0.0
/*63  */             goto out;                                                             // 0.0
/*65  */         }                                                                         // 0.0
/*70  */         xen_9pdev->rings[i].intf =  xengnttab_map_grant_ref(                      // 0.0
/*72  */                 xen_9pdev->xendev.gnttabdev,                                      // 0.0
/*74  */                 xen_9pdev->xendev.dom,                                            // 0.0
/*76  */                 xen_9pdev->rings[i].ref,                                          // 0.0
/*78  */                 PROT_READ | PROT_WRITE);                                          // 0.0
/*80  */         if (!xen_9pdev->rings[i].intf) {                                          // 0.0
/*82  */             goto out;                                                             // 0.0
/*84  */         }                                                                         // 0.0
/*86  */         ring_order = xen_9pdev->rings[i].intf->ring_order;                        // 0.0
/*88  */         if (ring_order > MAX_RING_ORDER) {                                        // 0.0
/*90  */             goto out;                                                             // 0.0
/*92  */         }                                                                         // 0.0
/*94  */         xen_9pdev->rings[i].ring_order = ring_order;                              // 0.0
/*96  */         xen_9pdev->rings[i].data = xengnttab_map_domain_grant_refs(               // 0.0
/*98  */                 xen_9pdev->xendev.gnttabdev,                                      // 0.0
/*100 */                 (1 << ring_order),                                                // 0.0
/*102 */                 xen_9pdev->xendev.dom,                                            // 0.0
/*104 */                 xen_9pdev->rings[i].intf->ref,                                    // 0.0
/*106 */                 PROT_READ | PROT_WRITE);                                          // 0.0
/*108 */         if (!xen_9pdev->rings[i].data) {                                          // 0.0
/*110 */             goto out;                                                             // 0.0
/*112 */         }                                                                         // 0.0
/*114 */         xen_9pdev->rings[i].ring.in = xen_9pdev->rings[i].data;                   // 0.0
/*116 */         xen_9pdev->rings[i].ring.out = xen_9pdev->rings[i].data +                 // 0.0
/*118 */                                        XEN_FLEX_RING_SIZE(ring_order);            // 0.0
/*122 */         xen_9pdev->rings[i].bh = qemu_bh_new(xen_9pfs_bh, &xen_9pdev->rings[i]);  // 0.0
/*124 */         xen_9pdev->rings[i].out_cons = 0;                                         // 0.0
/*126 */         xen_9pdev->rings[i].out_size = 0;                                         // 0.0
/*128 */         xen_9pdev->rings[i].inprogress = false;                                   // 0.0
/*134 */         xen_9pdev->rings[i].evtchndev = xenevtchn_open(NULL, 0);                  // 0.0
/*136 */         if (xen_9pdev->rings[i].evtchndev == NULL) {                              // 0.0
/*138 */             goto out;                                                             // 0.0
/*140 */         }                                                                         // 0.0
/*142 */         fcntl(xenevtchn_fd(xen_9pdev->rings[i].evtchndev), F_SETFD, FD_CLOEXEC);  // 0.0
/*144 */         xen_9pdev->rings[i].local_port = xenevtchn_bind_interdomain               // 0.0
/*146 */                                             (xen_9pdev->rings[i].evtchndev,       // 0.0
/*148 */                                              xendev->dom,                         // 0.0
/*150 */                                              xen_9pdev->rings[i].evtchn);         // 0.0
/*152 */         if (xen_9pdev->rings[i].local_port == -1) {                               // 0.0
/*154 */             xen_pv_printf(xendev, 0,                                              // 0.0
/*156 */                           "xenevtchn_bind_interdomain failed port=%d\n",          // 0.0
/*158 */                           xen_9pdev->rings[i].evtchn);                            // 0.0
/*160 */             goto out;                                                             // 0.0
/*162 */         }                                                                         // 0.0
/*164 */         xen_pv_printf(xendev, 2, "bind evtchn port %d\n", xendev->local_port);    // 0.0
/*166 */         qemu_set_fd_handler(xenevtchn_fd(xen_9pdev->rings[i].evtchndev),          // 0.0
/*168 */                 xen_9pfs_evtchn_event, NULL, &xen_9pdev->rings[i]);               // 0.0
/*170 */     }                                                                             // 0.0
/*174 */     xen_9pdev->security_model = xenstore_read_be_str(xendev, "security_model");   // 0.0
/*176 */     xen_9pdev->path = xenstore_read_be_str(xendev, "path");                       // 0.0
/*178 */     xen_9pdev->id = s->fsconf.fsdev_id =                                          // 0.0
/*180 */         g_strdup_printf("xen9p%d", xendev->dev);                                  // 0.0
/*182 */     xen_9pdev->tag = s->fsconf.tag = xenstore_read_fe_str(xendev, "tag");         // 0.0
/*184 */     v9fs_register_transport(s, &xen_9p_transport);                                // 0.0
/*186 */     fsdev = qemu_opts_create(qemu_find_opts("fsdev"),                             // 0.0
/*188 */             s->fsconf.tag,                                                        // 0.0
/*190 */             1, NULL);                                                             // 0.0
/*192 */     qemu_opt_set(fsdev, "fsdriver", "local", NULL);                               // 0.0
/*194 */     qemu_opt_set(fsdev, "path", xen_9pdev->path, NULL);                           // 0.0
/*196 */     qemu_opt_set(fsdev, "security_model", xen_9pdev->security_model, NULL);       // 0.0
/*198 */     qemu_opts_set_id(fsdev, s->fsconf.fsdev_id);                                  // 0.0
/*200 */     qemu_fsdev_add(fsdev);                                                        // 0.0
/*202 */     v9fs_device_realize_common(s, NULL);                                          // 0.0
/*206 */     return 0;                                                                     // 0.0
/*210 */ out:                                                                              // 0.0
/*212 */     xen_9pfs_free(xendev);                                                        // 0.0
/*214 */     return -1;                                                                    // 0.0
/*216 */ }                                                                                 // 0.0
