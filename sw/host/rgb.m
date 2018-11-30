clear
fid = fopen('red.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('grn.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('blu.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);

figure;
imagesc(im1);
colorbar;
title "red_bin catboard 0x20498b0 11/29/18"

figure;
imagesc(im2);
colorbar;
title "grn_bin catboard 0x210b638 11/29/18"

figure;
imagesc(im3);
colorbar;
title "blu_bin catboard 0x218b640 11/29/18"