clear
fid = fopen('dwt8.bin','r'); im7= fread(fid, [256,inf], 'char'); fclose(fid);figure;
imagesc(im7);
colorbar;