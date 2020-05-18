set term pngcairo size 1280, 960	
set out 'imagedata_128_0.580000_10.png'
set yrange [] reverse
set palette defined (0 "black")
set palette rgb 33,13,10 #rainbow
#set palette rgbformula 30,31,32
plot 'data_128_0.580000_10.txt' matrix with image
