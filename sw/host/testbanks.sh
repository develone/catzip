 #!/bin/bash
 ./arm-wbregs ramscope 0x8
 ./arm-sdramscope
 ./arm-wbregs 0x01000004 0x55aaaa55
 ./arm-sdramscope
 ./arm-wbregs 0x01000004
 
 ./arm-wbregs 0x01400004 0x66bbbb66
 ./arm-wbregs 0x01400004
 
  ./arm-wbregs 0x01800004 0x77cccc77
 ./arm-wbregs 0x01800004
 
  ./arm-wbregs 0x01c00004 0x88dddd88
 ./arm-wbregs 0x01c00004
