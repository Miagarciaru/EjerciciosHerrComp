set term pngcairo size 1280, 960	
set out 'image.png'
set yrange [] reverse
set palette rgbformula -7,2,-7
plot 'exampledata.txt' matrix with image
#set pm3d map
#splot 'exampledata.txt' matrix