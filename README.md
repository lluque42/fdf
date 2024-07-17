# 42's fdf project

Luis Luque - 2024

Message to other 42 students: DO NOT COPY, get inspired!

## Introduction

Wireframe model of landscape represantation in isometric projection

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

## Program's internal working
The rendering process has these levels, let's call them transformations
(which are processed in this order):  
    * [file to map        Not an actual part of the rendering process]  (ft_mx_load_file())
    * map to 3D model     Planar, spherical or cylindrical projection   (fdf_tesselate_map())  
    * 3D model to world  
    * world to camera  
    * camera to screen  
  
    Not every rendering needs to go through all of these transformations,
    but just need to start at one of them and perform the rest. The level from
    which to start has to do with the requested actions:  
    * [Should the map change, it has to start with file-to-map level]
    * Should the projection type change, it has to start with map-to-model level.
    * TODO
