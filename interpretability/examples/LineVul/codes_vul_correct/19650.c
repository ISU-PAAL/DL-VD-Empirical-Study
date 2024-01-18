// commit message qemu@aec4b054ea (target=1, prob=0.99725866, correct=True): check-qjson: Test errors from qobject_from_json()
/*0 */ static void unterminated_array_comma(void)           // (1) 0.2321
/*2 */ {                                                    // (3) 0.01786
/*4 */     QObject *obj = qobject_from_json("[32,", NULL);  // (0) 0.375
/*6 */     g_assert(obj == NULL);                           // (2) 0.1964
/*8 */ }                                                    // (4) 0.01786
