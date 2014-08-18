Polygonizer2D
-------------

This project was an exercise in developing a system for rendering implicit surfaces
(implicit surfaces are defined by an 
[implicit function](http://en.wikipedia.org/wiki/Implicit_function)). 
Implicit surfaces can be rendered using either:

1. Ray tracing
2. Surface tiling/polygonization

In this project the polygonization approach is taken.  Only 2-dimensional implicit
surfaces are handled.

The application was developed using OpenGL and Qt5.

Example
-------
The example UI which allows creating circles of various radii and modifying
various parameters is shown below.

![Polygonized circles](/docs/polygonizer2dui.png?raw=true "Polygonized circles")

Build and Run
-------------
Building uses cmake.

* Run the application with ```run.sh```
* Run the tests with ```test.sh```

Core Features:

- [x] Allow user to enter point sources
- [x] Find and draw the 2D outlines that represent the iso-surface

Enhancement Features:

- [ ] Weighted colors by field value
- [x] Pick and move primitives
- [x] Change radius of spheres
- [ ] Animate the balls
- [ ] CSG Union, Intersection and Difference operators
- [x] Ricci blend instead of basic summation blend
- [ ] Line skeleton instead of point (cylinder)
- [ ] Other primitives
- [x] Change the scale weight c value in /sum{cFi}
