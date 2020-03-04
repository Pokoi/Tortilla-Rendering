![alt text](https://github.com/Pokoi/Tortilla-Rendering/blob/master/Screenshots/Dithering_1.png "Dithering example 1")    

# Tortilla Rendering

Custom rendering model for [TortillaEngine](https://github.com/Pokoi/TortillaEngine)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Some Microsoft Visual Studio projects are given for development and testing. [Microsoft Visual Studio](https://visualstudio.microsoft.com/es/) must be installed to compile the project.

All the needed libraries are included in the projects.


### Installing

If you don`t have git in your machine you can follow the steps given in the [git site](https://git-scm.com/).  

Once you have git installed, you can download the repo by command line typing the following line:

```
git clone https://github.com/Pokoi/Tortilla-Rendering.git
```

And that's it. No more steps are needed.


## Compiling the project and modifying it

Into the ``` \Rendering\projects ``` folder, some Visual Studio projects are given.  
The projects dependencies are included in the project settings. The code is divided in ``` headers ``` and ``` sources ``` filters/folders.  

## Data model explanation

The render model includes the following data model structure:  
🥔 *View*: A class that contains the scene to render info. This class keeps the camera, rasterizer, lights and models references. Also contains the ambient color (if exists).    
🥚 *Camera*: The object with the camera information (transformation matrix, projection matrix).    
🧅 *Model*: A model contains the information about 3D model with at least 1 mesh, it's vertices coordinates, normals and materials.    
🥔 *Mesh*: A mesh contains the indices references and the material of the mesh.    
🥚 *Lighting*: Tortilla Rendering model supports two types of lights: directional lights and point lights.   
🧅 *Material*: Materials contains the info about diffuse color and the factor components of ambience, diffuse and light for rendering.  

For more documentation, check [the doc](https://pokoi.github.io/Tortilla-Rendering/).  

## Supported features

🥔 3D .obj assets loading  
🥚 Dynamic lighting  
🧅 Dynamic models  
🥔 Dynamic camera  
🥚 Scene hierarchy graph  
🧅 Polygon clipping  
🥔 Dithering post-processing efect (optional, not a requisite for render)  

## Screenshots of examples 

![alt text](https://github.com/Pokoi/Tortilla-Rendering/blob/master/Screenshots/Dithering_1.png "Dithering example 1")  
![alt text](https://github.com/Pokoi/Tortilla-Rendering/blob/master/Screenshots/Dithering_2.png "Dithering example 2")  
![alt text](https://github.com/Pokoi/Tortilla-Rendering/blob/master/Screenshots/Dithering_3.png "Dithering example 3")  
![alt text](https://github.com/Pokoi/Tortilla-Rendering/blob/master/Screenshots/NoDithering.png "No dithering example 1")


## Built With

🥔 [TinyObjLoader](https://github.com/tinyobjloader/tinyobjloader) - For .obj mesh assets loading.  
🥚 [SFML](https://www.sfml-dev.org/) - For window events in the test. This doesn't affect to the render model.  
🧅 [Cpp toolkit](https://bitbucket.org/angel-esne/cpp-toolkit/src/default/) - For maths operations and data models.  
🥔 [OpenGL](https://www.opengl.org/) - Only used to change the window pixel-buffer, not for rendering operations.


## Authors

* **Jesús Fermín Villar Ramírez `Pokoidev'** - *Project development* - [GitHub profile](https://github.com/Pokoi)
* **Ángel Rodríguez Ballesteros** - *Mentor and creator of cpp toolkit* - [Bitbucket profile](https://bitbucket.org/%7B553856ff-3963-48f2-ba1b-43fc6b6acebf%7D/)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


