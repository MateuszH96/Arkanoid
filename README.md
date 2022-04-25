# Arkanoid
Arkanoid in OpenGL 


## Table of Contents
* [Technologies Used](#technologies-used)
* [Usage](#usage)
* [Contact](#contact)


## Technologies Used
- C++ 14
- OpenGL
- Library GLUT
- Library GLM


## Usage
1. Clone the repository by running the command below on your git terminal
```
git clone https://github.com/Mat16eusz/Arkanoid-OpenGL.git
```
2. Open the project in VisualStudio.
3. Download the ``glutdlls37beta.zip`` file from https://www.opengl.org/resources/libraries/glut/glut_downloads.php and https://github.com/g-truc/glm
4. After this, we have to copy the file as instructed below:
   - First, paste ``glut.h`` file in:
     ``C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\include\gl``
   - Then paste ``glut.lib`` in:
	 ``C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\lib\x64``
   - Then paste the ``glut32.lib`` in:
	 ``C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\lib\x86``
   - Then paste ``glut.dll`` and ``glut32.dll`` in:
     ``C:\Windows\SysWOW64``
   - Finally copy ``glut32.dll`` to:
     ``C:\Windows\System32``
5. The next step is to add GLM library header files in the project properties.
   Section: Project -> Properties -> VC++ directories -> Header Files Directories -> edit -> "&lt;GLM directory path&gt;\GLM"
6. Run the project build.


## Contact
Created by Mateusz [Mat16eusz](https://github.com/Mat16eusz/) Jasiak mateusz.jasiak.dev@gmail.com - feel free to contact me!
