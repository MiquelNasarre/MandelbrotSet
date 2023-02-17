# MandelbrotSet
This small project contains a set of functions to generate data files of the Mandelbrot set that you can then plot 
and color with GnuPlot.
## How it works
The Mandelbrot set is a mathematical set of points in the complex plane. Those points are defined as the points $c\in \mathbb{C}$ 
for which the iteration  $z_{n+1}=z_n^2+c$  starting at  $z_0 = 0$  does not diverge as $n$ approaxes infinity. All of this points end 
up converging in different orbits of different periods in different regions of the set, and because this different region 
characteristics are really similar, this set ends up creating a really beautiful fractal.

Most representations of the fractal also include some type of color gradient, because it's prettier that way I guess, 
so this one does as well. The different shades of blue have nothing to do with the definition of the fractal, instead 
they represent the time it takes for that point to diverge further than a certain value from the origin.

To make this program work it has a function that returns $0$ if the point does not diverge after a certain amount of 
iterations and if it does diverge it returns the number of iterations it took that point to diverge. Then there's 
some other functions that create the amount of files specified for the divergence intervals specified, and the 
corresponding gnuplot file to visualize the data files.

![GnuPlot plot example](https://user-images.githubusercontent.com/124403865/219103347-cd51ca5a-bd91-43a0-a778-d13f17d62772.PNG)

Here you can see an example of the kind of plots you can obtain from the program.

At the time it's probably not the most efficient way to visualize or even to calculate all the points in the set. 
Currently it only uses one optimization to reduce the number of points to calculate. It generates a bigger grid around
the region you want to paint and decides which regions of the grid is gonna calculate each pixel and which regions it's 
probably going to be all the same color so it doesn't bother calculating each point (so you can sacrifice accuracy for speed).

## Requirements
- [Visual Studio 2022](https://visualstudio.com)
- [GnuPlot 5.4](http://www.gnuplot.info/)
## How to use it
Once you've cloned you can already compile and run the program and it will create the DataFiles folder inside the solution folder. 
In that folder they will appear all the different plots you created with this program, to visualize them you just need to enter 
inside their folders and open the GnuPlotFile.plt with gnuplot. The initial plot generated will be the one you see above.

In order to modify the variables to plot different parts of the fractal or change certain settings you can do it all from the header 
file. There you will find a lot of macros defining different settings and variables from the program that you may wanna change, there's 
a lot of them but their names are mostly self explanatory so it shouldn't be hard to get used to them.
## Additional
Last and also least important is the fact that the project also contains some older functions. They do a black and white color plot of 
the set, but they also allow to print more precise plots in the boundaries of the set without filling the files with useless points, using 
a technique similar to the grid we see in the color plot. It's probably not very efficient but I didn't want to remove it from the project 
so it's also available.

Also there's another implementation I tried in order to improve the performance, which consists in looking if the points fall in an orbit 
and if they do then break the iterations, but I ended up commenting it because when you zoom most of the orbits are really large and it's 
not worth it to keep track of all them. But the code and its macros are still in the project.
