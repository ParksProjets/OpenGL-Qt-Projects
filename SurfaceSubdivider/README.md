SurfaceSubdivider
-----------------

The goal of this project was to implement a subdivision scheme for subdividing 
a polyhedron.  The demo application therefore starts with a polyhedron and 
then provides the user with a button to initiate subdivision.  A button is 
also provided to undo subdivision.

The [Catmull-Clark subdivision method](http://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface) 
was chosen.

Example
-------
Here are some screenshots put into a GIF showing subdivision of a cube
(and then reversal of the process).

![Subdividing cube](/docs/subdivide.gif?raw=true "Subdividing cube")

Build and Run
-------------
Building uses cmake.

* Run the application with ```run.sh```
* Run the tests with ```test.sh```
