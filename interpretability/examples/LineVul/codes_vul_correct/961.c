// commit message qemu@196fe23734 (target=1, prob=0.5606071, correct=True): spapr_vscsi: fix build error introduced by f19661c8
/*0  */ static void vscsi_process_login(VSCSIState *s, vscsi_req *req)                    // (6) 0.05952
/*2  */ {                                                                                 // (21) 0.002381
/*4  */     union viosrp_iu *iu = &req->iu;                                               // (9) 0.04286
/*6  */     struct srp_login_rsp *rsp = &iu->srp.login_rsp;                               // (5) 0.0619
/*8  */     uint64_t tag = iu->srp.rsp.tag;                                               // (8) 0.04762
/*12 */     trace_spapr_vscsi__process_login();                                           // (11) 0.04048
/*16 */     /* TODO handle case that requested size is wrong and                          // (13) 0.03333
/*18 */      * buffer format is wrong                                                     // (16) 0.02143
/*20 */      */                                                                           // (18) 0.0119
/*22 */     memset(iu, 0, sizeof(struct srp_login_rsp));                                  // (7) 0.05
/*24 */     rsp->opcode = SRP_LOGIN_RSP;                                                  // (10) 0.04286
/*26 */     /* Don't advertise quite as many request as we support to                     // (12) 0.03571
/*28 */      * keep room for management stuff etc...                                      // (14) 0.02857
/*30 */      */                                                                           // (19) 0.0119
/*32 */     rsp->req_lim_delta = cpu_to_be32(VSCSI_REQ_LIMIT-2);                          // (1) 0.07857
/*34 */     rsp->tag = tag;                                                               // (15) 0.02381
/*36 */     rsp->max_it_iu_len = cpu_to_be32(sizeof(union srp_iu));                       // (3) 0.07143
/*38 */     rsp->max_ti_iu_len = cpu_to_be32(sizeof(union srp_iu));                       // (4) 0.07143
/*40 */     /* direct and indirect */                                                     // (17) 0.01905
/*42 */     rsp->buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_DIRECT | SRP_BUF_FORMAT_INDIRECT);  // (0) 0.1024
/*46 */     vscsi_send_iu(s, req, sizeof(*rsp), VIOSRP_SRP_FORMAT);                       // (2) 0.07143
/*48 */ }                                                                                 // (20) 0.002381
