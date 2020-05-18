set term pngcairo size 1280, 960	
set out 'imagen-clusters.png'
set xrange [0:20]
set yrange [20:0]
#set key right
#rgb(r, g, b)=int(255*r)*65536+int(255*g)*256+int(255*b)
#do for [i=2:11732]{
  #myrand=rand(int(rand(0)*i*100)+i*100)
   #set style line i linecolor rgb rgb(rand(0),rand(0),rand(0))
#}
#set palette rgbformula 30,31,32
set palette defined (0 "black",2 "red", 750 "green", 1500 "blue", 2000 "yellow")
plot 'exampledata.txt' matrix with image
