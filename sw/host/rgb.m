clear
fid = fopen('red.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('grn.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('blu.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('dwt.bin','r'); im4 = fread(fid, [256,inf], 'int32'); fclose(fid);
figure;
imagesc(im1);
colorbar;
title "red split from packed rgb catboard 0x0100effc 04/01/19"

figure;
imagesc(im2);
colorbar;
title "grn split from packed rgb catboard 0x0100effc 04/01/19"

figure;
imagesc(im3);
colorbar;
title "blu split from packed rgb catboard 0x0100effc 04/01/19"

figure;
imagesc(im4);
colorbar;
title "dwt red sub band catboard 0x0100effc 04/01/19"
