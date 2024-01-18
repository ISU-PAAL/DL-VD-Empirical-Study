// commit message qemu@1dbd2fd9cb (target=0, prob=0.9141856, correct=False): migration/rdma: clean up qemu_rdma_dest_init a bit
/*0   */ static int qemu_rdma_dest_init(RDMAContext *rdma, Error **errp)                      // (1) 0.05273
/*2   */ {                                                                                    // (30) 0.001953
/*4   */     int ret = -EINVAL, idx;                                                          // (14) 0.02734
/*6   */     struct rdma_cm_id *listen_id;                                                    // (13) 0.0332
/*8   */     char ip[40] = "unknown";                                                         // (18) 0.02344
/*10  */     struct rdma_addrinfo *res;                                                       // (16) 0.02539
/*12  */     char port_str[16];                                                               // (22) 0.01953
/*16  */     for (idx = 0; idx < RDMA_WRID_MAX; idx++) {                                      // (2) 0.04883
/*18  */         rdma->wr_data[idx].control_len = 0;                                          // (4) 0.04687
/*20  */         rdma->wr_data[idx].control_curr = NULL;                                      // (3) 0.04883
/*22  */     }                                                                                // (29) 0.007812
/*26  */     if (rdma->host == NULL) {                                                        // (17) 0.02539
/*28  */         ERROR(errp, "RDMA host is not set!");                                        // (9) 0.04102
/*30  */         rdma->error_state = -EINVAL;                                                 // (10) 0.03906
/*32  */         return -1;                                                                   // (21) 0.02148
/*34  */     }                                                                                // (28) 0.007812
/*36  */     /* create CM channel */                                                          // (24) 0.01562
/*38  */     rdma->channel = rdma_create_event_channel();                                     // (12) 0.03711
/*40  */     if (!rdma->channel) {                                                            // (19) 0.02148
/*42  */         ERROR(errp, "could not create rdma event channel");                          // (5) 0.04297
/*44  */         rdma->error_state = -EINVAL;                                                 // (11) 0.03906
/*46  */         return -1;                                                                   // (20) 0.02148
/*48  */     }                                                                                // (27) 0.007812
/*52  */     /* create CM id */                                                               // (23) 0.01562
/*54  */     ret = rdma_create_id(rdma->channel, &listen_id, NULL, RDMA_PS_TCP);              // (0) 0.06641
/*56  */     if (ret) {                                                                       // (25) 0.01562
/*58  */         ERROR(errp, "could not create cm_id!");                                      // (8) 0.04102
/*60  */         goto err_dest_init_create_listen_id;                                         // (6) 0.04102
/*62  */     }                                                                                // (26) 0.007812
/*66  */     snprintf(port_str, 16, "%d", rdma->port);                                        // (7) 0.04102
/*68  */     port_str[15] = '\0';                                                             // (15) 0.02734
/*72  */     if (rdma->host && strcmp("", rdma->host)) {                                      // 0.0
/*74  */         struct rdma_addrinfo *e;                                                     // 0.0
/*78  */         ret = rdma_getaddrinfo(rdma->host, port_str, NULL, &res);                    // 0.0
/*80  */         if (ret < 0) {                                                               // 0.0
/*82  */             ERROR(errp, "could not rdma_getaddrinfo address %s", rdma->host);        // 0.0
/*84  */             goto err_dest_init_bind_addr;                                            // 0.0
/*86  */         }                                                                            // 0.0
/*90  */         for (e = res; e != NULL; e = e->ai_next) {                                   // 0.0
/*92  */             inet_ntop(e->ai_family,                                                  // 0.0
/*94  */                 &((struct sockaddr_in *) e->ai_dst_addr)->sin_addr, ip, sizeof ip);  // 0.0
/*96  */             trace_qemu_rdma_dest_init_trying(rdma->host, ip);                        // 0.0
/*98  */             ret = rdma_bind_addr(listen_id, e->ai_dst_addr);                         // 0.0
/*100 */             if (!ret) {                                                              // 0.0
/*102 */                 if (e->ai_family == AF_INET6) {                                      // 0.0
/*104 */                     ret = qemu_rdma_broken_ipv6_kernel(errp, listen_id->verbs);      // 0.0
/*106 */                     if (ret) {                                                       // 0.0
/*108 */                         continue;                                                    // 0.0
/*110 */                     }                                                                // 0.0
/*112 */                 }                                                                    // 0.0
/*114 */                                                                                      // 0.0
/*116 */                 goto listen;                                                         // 0.0
/*118 */             }                                                                        // 0.0
/*120 */         }                                                                            // 0.0
/*124 */         ERROR(errp, "Error: could not rdma_bind_addr!");                             // 0.0
/*126 */         goto err_dest_init_bind_addr;                                                // 0.0
/*128 */     } else {                                                                         // 0.0
/*130 */         ERROR(errp, "migration host and port not specified!");                       // 0.0
/*132 */         ret = -EINVAL;                                                               // 0.0
/*134 */         goto err_dest_init_bind_addr;                                                // 0.0
/*136 */     }                                                                                // 0.0
/*138 */ listen:                                                                              // 0.0
/*142 */     rdma->listen_id = listen_id;                                                     // 0.0
/*144 */     qemu_rdma_dump_gid("dest_init", listen_id);                                      // 0.0
/*146 */     return 0;                                                                        // 0.0
/*150 */ err_dest_init_bind_addr:                                                             // 0.0
/*152 */     rdma_destroy_id(listen_id);                                                      // 0.0
/*154 */ err_dest_init_create_listen_id:                                                      // 0.0
/*156 */     rdma_destroy_event_channel(rdma->channel);                                       // 0.0
/*158 */     rdma->channel = NULL;                                                            // 0.0
/*160 */     rdma->error_state = ret;                                                         // 0.0
/*162 */     return ret;                                                                      // 0.0
/*166 */ }                                                                                    // 0.0
