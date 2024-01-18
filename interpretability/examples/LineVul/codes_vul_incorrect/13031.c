// commit message qemu@2f9606b373 (target=1, prob=0.36699337, correct=False): Add SASL authentication support ("Daniel P. Berrange")
/*0 */ static int buffer_empty(Buffer *buffer)  // (0) 0.3333
/*2 */ {                                        // (2) 0.03333
/*4 */     return buffer->offset == 0;          // (1) 0.3333
/*6 */ }                                        // (3) 0.03333
