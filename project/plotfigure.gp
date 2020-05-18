set term pngcairo size 1280, 960	
set out 'imagedata_128_0.570000_10.png'
set yrange [] reverse
#load 'magma.pal'
set palette defined (0 "black")
set palette rgb 33,13,10 #rainbow
#set palette rgbformula 30,31,32
#set palette grey
plot 'data_128_0.570000_10.txt' matrix with image
#set pm3d map
#splot 'exampledata.txt' matrix