fid = fopen('dwt.bin','r'); im4 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure;
imagesc(im4)
colorbar
%title "Red 1 level decomposition dwt.bin RPi  12/3/18"
%title "Red 2 level decomposition dwt.bin RPi  12/3/18"
title "blu 3 level decomposition dwt.bin RPi  12/3/18"