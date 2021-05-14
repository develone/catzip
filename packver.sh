#!/bin/bash
date > ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'catzip' >> ../fpgapack.txt
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

cd ../autofpga
echo 'autofpga' >> ../fpgapack.txt
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'icestorm' >> ../fpgapack.txt
cd ../icestorm
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'nextpnr' >> ../fpgapack.txt
cd ../nextpnr
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'yosys' >> ../fpgapack.txt
cd ../yosys
echo 'yosys' >> ../fpgpack.txt
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'zipcpu' >> ../fpgapack.txt
cd ../zipcpu
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt
echo ""  >> ../fpgapack.txt

echo 'verilator' >> ../fpgapack.txt
cd ../verilator
git show HEAD >> ../fpgapack.txt
echo '************************************************' >> ../fpgapack.txt


