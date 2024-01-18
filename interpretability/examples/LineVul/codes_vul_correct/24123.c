// commit message qemu@025b168ca6 (target=1, prob=0.8422052, correct=True): usb-ehci: split trace calls to handle arg count limits
/*0  */ static void ehci_trace_qtd(EHCIQueue *q, target_phys_addr_t addr, EHCIqtd *qtd)  // (9) 0.07883
/*2  */ {                                                                                // (11) 0.002252
/*4  */     trace_usb_ehci_qtd(q, addr, qtd->next, qtd->altnext,                         // (10) 0.06306
/*6  */                        get_field(qtd->token, QTD_TOKEN_TBYTES),                  // (0) 0.09459
/*8  */                        get_field(qtd->token, QTD_TOKEN_CPAGE),                   // (1) 0.09234
/*10 */                        get_field(qtd->token, QTD_TOKEN_CERR),                    // (2) 0.09234
/*12 */                        get_field(qtd->token, QTD_TOKEN_PID),                     // (4) 0.09009
/*14 */                        (bool)(qtd->token & QTD_TOKEN_IOC),                       // (6) 0.08784
/*16 */                        (bool)(qtd->token & QTD_TOKEN_ACTIVE),                    // (7) 0.08784
/*18 */                        (bool)(qtd->token & QTD_TOKEN_HALT),                      // (8) 0.08784
/*20 */                        (bool)(qtd->token & QTD_TOKEN_BABBLE),                    // (5) 0.09009
/*22 */                        (bool)(qtd->token & QTD_TOKEN_XACTERR));                  // (3) 0.09234
/*24 */ }                                                                                // (12) 0.002252
