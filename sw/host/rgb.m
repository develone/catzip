fid = fopen('red.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('grn.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('blu.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);

figure
imagesc(im1)

figure
imagesc(im2)

figure
imagesc(im3)
