// commit message qemu@42119fa356 (target=0, prob=0.8180644, correct=False): libcacard/vcard_emul_nss: Drop a redundant conditional
/*0   */ vcard_emul_mirror_card(VReader *vreader)                                      // (6) 0.0332
/*2   */ {                                                                             // (35) 0.001953
/*4   */     /*                                                                        // (30) 0.007812
/*6   */      * lookup certs using the C_FindObjects. The Stan Cert handle won't give  // (3) 0.04297
/*8   */      * us the real certs until we log in.                                     // (8) 0.02734
/*10  */      */                                                                       // (29) 0.009766
/*12  */     PK11GenericObject *firstObj, *thisObj;                                    // (7) 0.0293
/*14  */     int cert_count;                                                           // (25) 0.01562
/*16  */     unsigned char **certs;                                                    // (19) 0.01758
/*18  */     int *cert_len;                                                            // (20) 0.01758
/*20  */     VCardKey **keys;                                                          // (21) 0.01758
/*22  */     PK11SlotInfo *slot;                                                       // (14) 0.01953
/*24  */     VCard *card;                                                              // (26) 0.01562
/*28  */     slot = vcard_emul_reader_get_slot(vreader);                               // (4) 0.03906
/*30  */     if (slot == NULL) {                                                       // (15) 0.01953
/*32  */         return NULL;                                                          // (16) 0.01953
/*34  */     }                                                                         // (31) 0.007812
/*38  */     firstObj = PK11_FindGenericObjects(slot, CKO_CERTIFICATE);                // (2) 0.04688
/*40  */     if (firstObj == NULL) {                                                   // (12) 0.02148
/*42  */         return NULL;                                                          // (17) 0.01953
/*44  */     }                                                                         // (32) 0.007812
/*48  */     /* count the certs */                                                     // (27) 0.01562
/*50  */     cert_count = 0;                                                           // (22) 0.01758
/*52  */     for (thisObj = firstObj; thisObj;                                         // (9) 0.02734
/*54  */                              thisObj = PK11_GetNextGenericObject(thisObj)) {  // (0) 0.08398
/*56  */         cert_count++;                                                         // (13) 0.02148
/*58  */     }                                                                         // (33) 0.007812
/*62  */     if (cert_count == 0) {                                                    // (11) 0.02344
/*64  */         PK11_DestroyGenericObjects(firstObj);                                 // (5) 0.03516
/*66  */         return NULL;                                                          // (18) 0.01953
/*68  */     }                                                                         // (34) 0.007812
/*72  */     /* allocate the arrays */                                                 // (28) 0.01562
/*74  */     vcard_emul_alloc_arrays(&certs, &cert_len, &keys, cert_count);            // (1) 0.05664
/*78  */     /* fill in the arrays */                                                  // (23) 0.01758
/*80  */     cert_count = 0;                                                           // (24) 0.01758
/*82  */     for (thisObj = firstObj; thisObj;                                         // (10) 0.02734
/*84  */                              thisObj = PK11_GetNextGenericObject(thisObj)) {  // 0.0
/*86  */         SECItem derCert;                                                      // 0.0
/*88  */         CERTCertificate *cert;                                                // 0.0
/*90  */         SECStatus rv;                                                         // 0.0
/*94  */         rv = PK11_ReadRawAttribute(PK11_TypeGeneric, thisObj,                 // 0.0
/*96  */                                    CKA_VALUE, &derCert);                      // 0.0
/*98  */         if (rv != SECSuccess) {                                               // 0.0
/*100 */             continue;                                                         // 0.0
/*102 */         }                                                                     // 0.0
/*104 */         /* create floating temp cert. This gives us a cert structure even if  // 0.0
/*106 */          * the token isn't logged in */                                       // 0.0
/*108 */         cert = CERT_NewTempCertificate(CERT_GetDefaultCertDB(), &derCert,     // 0.0
/*110 */                                        NULL, PR_FALSE, PR_TRUE);              // 0.0
/*112 */         SECITEM_FreeItem(&derCert, PR_FALSE);                                 // 0.0
/*114 */         if (cert == NULL) {                                                   // 0.0
/*116 */             continue;                                                         // 0.0
/*118 */         }                                                                     // 0.0
/*122 */         certs[cert_count] = cert->derCert.data;                               // 0.0
/*124 */         cert_len[cert_count] = cert->derCert.len;                             // 0.0
/*126 */         keys[cert_count] = vcard_emul_make_key(slot, cert);                   // 0.0
/*128 */         cert_count++;                                                         // 0.0
/*130 */         CERT_DestroyCertificate(cert); /* key obj still has a reference */    // 0.0
/*132 */     }                                                                         // 0.0
/*136 */     /* now create the card */                                                 // 0.0
/*138 */     card = vcard_emul_make_card(vreader, certs, cert_len, keys, cert_count);  // 0.0
/*140 */     g_free(certs);                                                            // 0.0
/*142 */     g_free(cert_len);                                                         // 0.0
/*144 */     g_free(keys);                                                             // 0.0
/*148 */     return card;                                                              // 0.0
/*150 */ }                                                                             // 0.0
