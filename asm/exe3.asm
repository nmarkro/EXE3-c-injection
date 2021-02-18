.definelabel g_Toolkit,         0x080004C0

.definelabel rng1,              0x02009730
.definelabel rng2,              0x02009800

// Free space in ERAM for exe3 struct
// without this global varibles will be placed in the ROM, which is read only
.definelabel exe3,              0x0203FC70