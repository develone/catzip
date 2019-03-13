clear
fid = fopen('red-out.8','r'); im7= fread(fid, [256,inf], 'char'); fclose(fid);
fid = fopen('grn-out.8','r'); im8= fread(fid, [256,inf], 'char'); fclose(fid);
fid = fopen('blu-out.8','r'); im9= fread(fid, [256,inf], 'char'); fclose(fid);

figure;
imagesc(im7);
colorbar;

figure;
imagesc(im8);
colorbar;

figure;
imagesc(im9);
colorbar;