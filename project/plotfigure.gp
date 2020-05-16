set term pngcairo size 1280, 960	
set out 'image.png'
set yrange [] reverse
set palette rgbformula 30,31,32
plot 'exampledata.txt' matrix with image
#set pm3d map
#splot 'exampledata.txt' matrix