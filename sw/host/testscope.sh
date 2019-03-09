 #!/bin/bash
 ./arm-wbregs ramscope 0x8
 ./arm-sdramscope
 ./arm-wbregs 0x01000004 0x55aaaa55
 ./arm-sdramscope
 ./arm-wbregs 0x01000004
