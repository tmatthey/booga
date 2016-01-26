#!/bin/sh

echo
echo "Compare the different versions relating to needed time for"
echo "[labeling &] thinning."
echo "The shown images indeed have three different categories of pixels:"
echo "- values > 0 should be interpreted as skeleton pixels"
echo "- background = 0"
echo "- values < 0 correspond to the number of the iteration they have been removed"
echo
echo "1. thinning w/o labeling (performed on original image)"
echo "   (same value for each skeleton pixel)"
echo
echo "thin demo-input.pixi | pixi2ppm > test1.ppm"

thin demo-input.pixi | pixi2ppm > test1.ppm
xv test1.ppm&

echo
echo
echo "2. labeling & thinning (result in channel)"
echo "   (3 objects => 3 different positive values of skeleton pixels)"
echo
echo "thin -w 1 demo-input.pixi | pixi2ppm > test2.ppm"

thin -w 1 demo-input.pixi | pixi2ppm > test2.ppm
xv test2.ppm&

echo
echo
echo "3. labeling & thinning (result in image)"
echo "   (3 objects => 3 different positive values of skeleton pixels)"
echo
echo "thin -w 0 demo-input.pixi | pixi2ppm > test3.ppm"

thin -w 0 demo-input.pixi | pixi2ppm > test3.ppm
xv test3.ppm&

echo
echo
echo "4. labeling (with background==1) & thinning (result in channel)"
echo "   (only 1 object)"
echo
echo "thin -b 1 -w 1 demo-input.pixi | pixi2ppm > test4.ppm"
thin -b 1 -w 1 demo-input.pixi | pixi2ppm > test4.ppm
xv test4.ppm&
echo
echo
echo "5. labeling (with background==1) & thinning (result in image)"
echo "   (only 1 object)"
echo
echo "thin -b 1 -w 0 demo-input.pixi | pixi2ppm > test5.ppm"

thin -b 1 -w 0 demo-input.pixi | pixi2ppm > test5.ppm
xv test5.ppm&

echo

