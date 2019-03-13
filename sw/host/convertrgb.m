clear
fid = fopen('red.bin','r'); im1 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('grn.bin','r'); im2 = fread(fid, [256,inf], 'int32'); fclose(fid);
fid = fopen('blu.bin','r'); im3 = fread(fid, [256,inf], 'int32'); fclose(fid);
for i = 1:256;
  
  for j = 1:256;
  im4(i,j) = cast(im1(i,j),'uint8'); 
  im5(i,j) = cast(im2(i,j),'uint8'); 
  im6(i,j) = cast(im3(i,j),'uint8'); 
  endfor; 
endfor;
fid = fopen('red-out.8','w'); count = fwrite(fid, im4, 'uint8'); fclose(fid);
fid = fopen('grn-out.8','w'); count = fwrite(fid, im5, 'uint8'); fclose(fid);
fid = fopen('blu-out.8','w'); count = fwrite(fid, im6, 'uint8'); fclose(fid);


figure;
imagesc(im1);

figure;
imagesc(im2);

figure;
imagesc(im3);


figure;
imagesc(im4);

figure;
imagesc(im5);

figure;
imagesc(im6);