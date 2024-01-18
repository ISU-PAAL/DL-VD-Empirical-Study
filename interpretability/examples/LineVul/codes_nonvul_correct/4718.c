// commit message FFmpeg@292850b634 (target=0, prob=0.0049816463, correct=True): tiff: add smarter checks if there is enough data left
/*0 */ static double tget_double(GetByteContext *gb, int le)                                   // (1) 0.2051
/*2 */ {                                                                                       // (3) 0.01282
/*4 */     av_alias64 i = { .u64 = le ? bytestream2_get_le64(gb) : bytestream2_get_be64(gb)};  // (0) 0.5385
/*6 */     return i.f64;                                                                       // (2) 0.1154
/*8 */ }                                                                                       // (4) 0.01282
