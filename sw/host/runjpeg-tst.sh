#!/bin/bash
./arm-wbregs 0x01401000 0x2
./arm-wbregs 0x01401004 0x1
./arm-zipload -v ../board/jpeg
./arm-wrsdram rgb_pack.bin
./arm-zipdbg

#	inpbuf		./arm-wbregs 0x0200f148
#	0200f148 (        ) : [."$|] 0e22247c

#	flag ./arm-wbregs 0x0201f14c
#	0201f14c (        ) : [.@.L] 0a40f04c

#	w ./arm-wbregs 0x0201f150
#	0201f150 (        ) : [.P.N] 0a50fc4e

# 	*red./arm-wbregs 0x0201f154
	0201f154 (        ) : [...N] 0a81084e
#	*grn./arm-wbregs 0x0201f158
#	0201f158 (        ) : [.P.J] 0a50f04a

#	*blu./arm-wbregs 0x0201f15c
#	0201f15c (        ) : [...W] 0aa10457

#	*alt./arm-wbregs 0x0201f160
#	0201f160 (        ) : [.q.O] 0a71084f

#	*ptr_blkram_flag ./arm-wbregs 0x0201f164
#	0201f164 (        ) : [.p.L] 0a70fc4c

# 	*ptr_blkram_invfwd./arm-wbregs 0x0201f168
#	0201f168 (        ) : [...Q] 0ac10051

#	 ./arm-wbregs 0x01401000
#	01401000 (        ) : [....] 00000002

#	 ./arm-wbregs 0x01401004
#	01401004 (        ) : [....] 00000001
