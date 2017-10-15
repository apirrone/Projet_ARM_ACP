# Projet_ARM_ACP
## M2 Project Acquisition Reconstruction Modélisation

To build, either : 
- Execute install.sh
- Create a folder (ex : "build"), execute "cmake .." inside that folder, then execute "make"
	
To execute the program : 
- ./VisioBrain
- ./VisioBrain < path to file to open >

If you launched the program without arguments, the view is empty. You can load a file using the "File" menu.

You can then navigate using the mouse to rotate view (left click) or to zoom (mouse wheel) and the arrow keys to move the object around.

Our software is organized as follows :

- **main.cpp** : The entry point of the software, where we create the *QApplication*, the *MainWindow* and handle potential arguments passed to the program
- **MainWindow.hpp/.cpp** : The Qt window, where we handle user interface actions, such as load a file, export a file and exit the program. This class contains a *Viewer* object.
- **Viewer.hpp/.cpp** : The 3D viewer, it extends *QOpenGLWidget*, contains the necessary structures for using *QOpenGL*, a *SatelliteCamera*, and a *VEF* object.
- **VEF.hpp/.cpp** : **V**ertex **E**dge **F**ace data structure, contains the necessary structures and functions to hold the data (received as a *.obj* file, or as a *.pgm3D* file, but we use the class *VoxelGrid*, that extends *VEF* to handle *.pgm3D* files) and draw it with QOpenGL (the *VEF* object can draw itself in a *Viewer*).
- **VoxelGrid.hpp/.cpp** : Class for holding voxel type data. Extends *VEF*, so can draw itself too.
- **PGM3D_Holder.hpp/.cpp** : Class for holding raw *.pgm3D* data. This raw data can then be used to construct a *VoxelGrid*.
- **SatelliteCamera.hpp/.cpp** : Camera implementation to easily rotate around a target point in space and still be looking at it.
  


TODO : Expliquer structure du code (Diagramme?) 

D'ailleurs, je suis assez pour qu'on fasse un dossier include avec tous les .hpp, ça sera plus facile pour le prof de se familiariser avec l'architecture en regardant que les .hpp

  



