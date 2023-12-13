# RayZ - a very very very very simple raytracer

![Multi-colored lights on a black background with some white dots](https://github.com/samidalil/Raytracing/blob/0a99d4e718ad9fa1f68ff273f1cb1e367683befc/resources/ExampleRenders/LightDisplay.jpg "Colored lights")

## Project description

This project showcases a little CPU-based raytracer that can be used to render a single image, using a custom rendering library we entirely made from scratch, `GLFW` for presentation, `ImGUI` for UI and `json` lib for scene files.

## Features

The self-made custom library highlights our intermediate C++ knowledge by including many components implemented during the development of our project :
- Vector and 4x4 matrix operations, transform matrix management obviously as well as raycasting/ray intersection
- 7 basic 3-dimensional primitives have been implemented, from a basic triangle to a cone by way of an infinte cylinder
- Every object can have a unique ID'd material associated with a texture or a color
- Different illumination models (Phong and Lambert) and shadow casting in general are included
- The renderer supports skybox mapping and Super-Sampling Anti-Antialiasing x1-x16 (SSAA)

We also included a basic UI on top of the rendered scene to play with rendering parameters.

## Scalability and performances

Since this project is currently mono-threaded, the drawing time approximately scales this way :  
`objects to render` x `lights` x `pixels to draw` x `subdivisions per pixel`

As right now, there are no huge optimisation processes implemented.

## Examples

As we did not really focus on the "beauty" aspect, please be lenient about the visual aspect of the rendered images.

### No SSAA + shadows + Phong illumination

![Some textured objects, aliased and really bright colors with a skybox in the background](https://github.com/samidalil/Raytracing/blob/0a99d4e718ad9fa1f68ff273f1cb1e367683befc/resources/ExampleRenders/Parameters/SSAA1.jpg "No SSAA + shadows + Phong illumination")

### SSAA x4 + shadows + Phong illumination

![Some textured objects with really bright colors and a skybox in the background ](https://github.com/samidalil/Raytracing/blob/0a99d4e718ad9fa1f68ff273f1cb1e367683befc/resources/ExampleRenders/Parameters/phong.jpg "SSAA x4 + shadows + Phong illumination")

### SSAA x4 + shadows + Lambert illumination

![Some textured objects with nice colors and a skybox in the background](https://github.com/samidalil/Raytracing/blob/0a99d4e718ad9fa1f68ff273f1cb1e367683befc/resources/ExampleRenders/Parameters/lambert.jpg "SSAA x4 + shadows + Lambert illumination")

### SSAA x4 + no shadows + Phong illumination

![Some textured objects with no shadow casting, really bright colors and a skybox in the background](https://github.com/samidalil/Raytracing/blob/0a99d4e718ad9fa1f68ff273f1cb1e367683befc/resources/ExampleRenders/Parameters/noShadow.jpg "SSAA x4 + no shadows + Phong illumination")

## Areas for improvement

Of course, there is a lot of room for improvement on this project, performance-wise and feature-wise.

Obviously, a major addition would be CPU multi-thread as it would speed up the drawing process.

A nice feature to add would be lens' aperture simulation / depth of field as it brings a nice aesthetic to rendered images.
