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

- main.cpp : The entry point of the software, where we create the *QApplication*, the *MainWindow* and handle potential arguments passed to the program
- MainWindow.hpp/.cpp : The Qt window, where we handle user interface actions, such as load a file, export a file and exit the program. This class contains a *Viewer* object
  


TODO : Expliquer structure du code (Diagramme?) 

D'ailleurs, je suis assez pour qu'on fasse un dossier include avec tous les .hpp, ça sera plus facile pour le prof de se familiariser avec l'architecture en regardant que les .hpp

  



