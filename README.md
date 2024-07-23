# 42's fdf project

Luis Luque - 2024

Message to other 42 students: DO NOT COPY, get inspired!

## Introduction

Wireframe model of landscape representation in isometric projection

## Directory tree

    ./  
    ├── .gitignore				(to prevent undesired files to be stagged)  
    ├── Doxyfile				(doxygen config file for doc generation)  
    ├── Makefile				(use 'make help' for instructions)  
    ├── README.md				(brief documentation)  
    ├── doc/					(documentation extracted from comments in .h)  
    │   ├── html/				(html documentation)  
    │   │   ├── ...  
    │   │   ├── index.html		(entry point for html documentation)  
    │   │   ├── ...  
    │   └── man/				(man pages documentation)  
    │       └── man3/  
    │           └── ...			(example of use: 'man -l ft_string.h.3')  
    ├── include/				(directory for public header files (.h))  
    │   ├── ...  
    │   └── ...  
    ├── src/					(directory for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  				
    │   │   └── ...  
    │   └── ...					(may be structured in several directories)  
    │       ├── ...  
    │       └── ...  
    ├── lib/					(external libraries)  
    │   ├── ...  
    │   └── libft				(each library in its own directory)  
    ├── bin/					(directory for project's binaries and tester)  
    │   ├── ...  
    │   └── ...					(may be structured in several directories)  
    ├── obj/					(directory for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  
    │   │   └── ...  
    │   └── ...					(structured as in ./src)  
    │       ├── ...  
    │       └── ...  
    ├── data/					(directory for non-source files)  
    └── test/					(test program src code, compiles to .bin/tester)  
        ├── ...  
        ├── tester.c  
        └── ...  

## Compilation instructions
Use ‘make help’ for instructions.

## Program's data model
### Conventions adopted
* When rendering, the right-handed convention for drawing XYZ axis will be
used, which implies:  
```
        +Z  
         |
         |  
        / \  
       /   \  
     +X     +Y  
```
* Matrices nomenclature, i, j for m x n matrix, where:
    * i is ???
    * j is ???
    * m is ???
    * n is ???
* Linear representation of a matrix follows lexicographic... TODO

* From subject (HOWEVER read fdf_main.c comments):  
    * The horizontal position corresponds to its axis (X).
    * The vertical position corresponds to its ordinate (Y).

* TODO Por tanto, las coordenadas de las esquinas en el plano XY son:
B: (0,0)  
A: (xX,0)  
D: (0,yY)  
C: (xX, yX)  

* TODO Por tanto al leer del archivo:
```
TODO
            <<< X  
(xX,0) c0     cC (0,0)  
    r0  A .... B   Y  
        .      .   v  
        .      .   v  
    rR  C .... D   v  
(xX,yY)          (0,yY)  
```
* The GUI image own coordinate system TODO

### Data structures
    * Array of two matrices resulting from loading the .fdf map file. The first
    matrix contains altitude values (Z axis) while the second matrix contains
    color values (255 if map has no color info). The column and row in each
    matrix represents the X, Y coordinates. It was decided to adopt the
    following conventions:
        * The first value at the first line of the file corresponds to the
        element 0,0. That is, position (i, j) in a m x n matrix, where m is
        the number of rows and n the number of columns. This i, j pair matches
        spatial coordinates as X = ??? Y = ???.  
        * The last value at the first line of the file corresponds to the
        element ???. That is, same ??? position, hence same ??? coordinate, but
        ??? position and ??? coordinate.  
        * When rendering, it will be used the right-handed convention for
        drawing XYZ axis, which implies:  
            * Cordinate system origin (x, y) (0, 0) is represented by the ???
            matrix element.  
            * As row position increases from 0 to ???, ??? coordinate increases
            in the positive direction.  
            * As column position  increases from 0 to ???, ??? coordinate
            increases in the positive direction.  


## Program's internal working
### Core functions callings
* main() function does the following:
    * Checks validity of arguments.
    * Creates the fdf data structure which serves as an entry point to every
    other data.
    * Loads the .fdf file data into an array of two matrices (one for height or
    Z values and the other one for color values) by calling ft_mx_load_file().
    * Calls fdf_start_gui() which does the following:
        * fdf_start_gui() registers the hooks:
            * mlx_resize_hook() -> fdf_resizehook().
            * mlx_key_hook() -> fdf_keyhook().
            * mlx_close_hook() -> fdf_closehook().
            * mlx_loop_hook() -> fdf_generichook().
        * Creates the GUI: window, image, places the image on the window.
        * Then waits in the mlx_loop(). At this point (and until after the 
        window is closed or the ESCAPE key is pressed), only the hooks functions
        are called to act as a result of the GUI events.
            * When MLX loop breaks, fdf_start_gui() finishes the MLX clean up by
            calling mlx_terminate(). The MLX clean up process starts in the
            fdf_closehook() when it calls the fdf_exit_program() which calls
            the MLX functions mlx_delete_image() and mlx_close_window().  
      
  
*[...... while fdf_start_gui() is blocked in the MLX loop ......]*
* Asinchronously, fdf_generichook() is called on every MLX loop. This function
does the following:
    * Checks if the keys to translate/rotate/scale are pressed down. If any,
    this function updates the required transformation data through fdf structure 
    object member and sets a t_render_request level at the fdf structure if a
    render is required as a result of the keys events.
        * *NOTE: Other hooks such as fdf_resizehook() and fdf_keyhook() also can
        independently change transformation data and set a render request
        level.*
    * Calls fdf_render() every loop. *NOTE: fdf_generichook() is the only caller
    of fdf_render().* This function is the last one that is called with fdf as
    an argument, from now on, every function is called passing the fdf member
    object. fdf_render() function does the following:
        * Checks the fdf t_render_request member fdf->render_request.
        * According to the render request level, fdf_render() successively calls
        the following function BUT starting with the one that correspond to the
        request level. In this way, only those stages of the rendering process
        that need to be recalculated as per the request level are performed.
        The functions that perform each stage of the rendering process are (in
        the logical order of precedence) the following:
            * fdf_tesselate_map() when render_request <= FROM_MODEL.
                * Read "Rendering process" section for details.
            * fdf_setup_world() when render_request <= FROM_WORLD.
                * Read "Rendering process" section for details.
            * fdf_setup_camera() when render_request <= FROM_CAMERA.
                * Read "Rendering process" section for details.
            * fdf_setup_screen() when render_request <= FROM_SCREEN.
                * Read "Rendering process" section for details.
            * fdf_setup_image() when render_request <= FROM_IMAGE.
                * Read "Rendering process" section for details.
        * Finally, fdf_render() resets the render request level to NO_RENDER
        and returns to fdf_generichook().  
  
The next section details what the rendering process functions
(fdf_tesselate_map(), fdf_setup_world(), fdf_setup_camera(), fdf_setup_screen(),
and fdf_setup_image()) do at each stage of the rendering process.


### Rendering process
The rendering process entry point is the fdf_render() function, called from the
GUI loop hook fdf_generichook().

The rendering process has several stages, let's call them transformations,
which must be processed in this order, starting at the first stage that needs
to be re-calculated. The selection of the first stage is determined by the
render request level of fdf struct for each loop.

|Transformation | Details | Render level request | Associated function|
|---------------|---------|----------------------|--------------------|
|*file to array of altitude and color matrices that represents the map info*|*Not an actual part of the rendering process*|*doesn't apply*|ft_mx_load_file())|
|Map to 3D model|Either planar, spherical or cylindrical projection|<= FROM_MODEL|fdf_tesselate_map()|
|3D model to world| |<= FROM_WORLD|fdf_setup_world()|
|World to camera| |<= FROM_CAMERA|fdf_setup_camera()|
|Camera to screen| |<= FROM_SCREEN|fdf_setup_screen()|
|Screen to image| |<= FROM_IMAGE|fdf_setup_image()|
|Nothing to perform| |== NO_RENDER|return|
  
Not every rendering needs to go through all of these transformations,
but just need to start at one of them and perform the rest. The level from
which to start has to do with the requested actions:  
* *[Should the map change, it has to start with file-to-map level]*
* Should the projection type change, it has to start with map-to-model level.
* TODO

#### Loading the .fdf file

This is the process in which the .fdf file is parsed to create an array of two
matrices. Both matrices are of the same size, that is, rows and columns
positions representing the actual spatial 2D (XY plane) position of each
sample.

Each sample will be then transformed into a 3D vertex in the tesselation
stage.

There are two matrices because we need to storage two values for each point:
the altitude value (the Z component) and the color value.  
The function ft_mx_load_file() performs this stage, taking as argument the
filename for the .fdf map and the expected character separating the sample
information from the next sample information. The ft_mx_load_file() function
returns the array of the two matrices which will end up as the map_mx member
of the object struct that is the object member of the fdf struct.

A .fdf file may or may not have sample color information. The color information
is expected as a ',0xhhhhhh' string inmediately following each altitude value.
If no color information is found, ft_mx_load_file() initializes the color matrix
with FFFFFF for each sample.  

#### Tesselation: samples map to 3D model (where samples become vertices)
This is the stage where: (1) the samples obtained from loading the .fdf file
(2D position at XY plane + altitude) are used to create actual 3D XYZ points
in space, this is dependent upon the type of projection: planar, spherical,
or cylindrical; (2) the color information of the samples are used to create
an array of uint32_t to storage the color values of each vertex; (3) for each
of the samples (spatial-info-wise) a relationship is stablished with its
neighboring samples in the matrix, this relationship is represented in an
edge array and is the base for eventually drawing lines that connect each
vertex only to its orthogonal neighbor vertices (or, in bonus version, also to
its non-orthogonal neighbors that makes spatial sense; or to every neighbor).

In (1) one of this three functions: fdf_get_vertex_mx(),
fdf_get_vertex_mx_sph(), or fdf_get_vertex_mx_cyl() is used to create a matrix
in which each column ?????? is a XYZW 3D point in space (a vertex). This matrix
will become the model_mx member of the object, which is the object member
of fdf.

In (2) the ????? function creates the array of uint32_t holding the color
values. This is performed only once, when the model_mx member of the object
is NULL, since it will be the same for any tesselation projection type.

In (3) the fdf_get_edge() creates an array of edges, the later being a struct
type that has two key members: start and end. Each represent the index in the
vertex matrix of the starting vertex of the edge and the end vertex of the
edge. Clearly, each edge (if not hidden) will become a line in the image.
This is performed only once, when the model_mx member of the object
is NULL, since it will be the same for any tesselation projection type.             <<<<<<<<<<<< Aquí es un buen sitio para poner start_color y end_color 
 
Both the vertex matrix column ????? index (1), the color array index (2), and
the start/end members in the edges array indices (3) refer to the information
of the same 3D vertex.

The following transformation consist of succesively multiplying the previous
vertex matrix (that represents the same points but in a particular space:
he 3D object now placed in the world; the 3D object in the world but now from
the point of view from the camera; or the 2D projection of the later to the
screen) by different transformation matrices to generate a new vertex matrix of
the new space.

#### 3D model space to world space transformation
TODO

#### World space transformation to camera space transformation
TODO

#### Camera space to screen space transformation
TODO

#### Screen space to image space transformation
In this stage, the vertex matrix representing the screen space is used to,
finally, draw all the lines (edges) on the image. This job is ultimately perform
by the fdf_drw_edges() function.

The fdf_drw_edges() function takes the object and the image element of the GUI
and uses its auxiliary functions to draw each edge as a line onto the image.

##### Inner working of fdf_drw_edges() function
This function loops through the edges array skipping the edges flagged as hidden
and for each non-skipped edge:
* A line struct is created using fdf_create_line() function with the arguments:
X value of the edge starting vertex; Y value of the edge starting vertex;
X value of the edge end vertex; Y value of the edge end vertex.
* TODO fdf_set_line_color_info() TODO !!!!!!!!!!!!!!
* Finally, the fdf_drw_edges() calls the fdf_draw_line() which actually draws
the line.

The fdf_drw_edges() auxiliary functions inner workings are detailed in the
following sections.

*NOTE: Bonus version edge skipping process in fdf_drw_edges() is more or less
strict depending on the user's selection to draw or not valid non-orthogonal
edges or every non-orthogonal edges).*

###### Inner working of fdf_create_line() function
TODO

###### Inner working of fdf_set_line_color_info() function
TODO

###### Inner working of fdf_draw_line() function
TODO




