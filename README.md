![preview of cube](https://github.com/karolgotow/spinning-cube/blob/main/preview/preview.GIF?raw=true)

# Compiling
gcc spinning_cube.c -lm

# Running
./a.out

# Changes
-fixed compilation errors  
-fixed directories  
-added build  
-added colors to output  
-added interaction via unblocking stdio  
-fixed buffer size glitching  
-changed fps to liek 15  
-reduced cube count to 1  

original author: saatvikrao/Spinning-Cube
# Spinning-Cube
This is a C language code to visualize a spinning cube using just ASCII characters. Follow the guide to know more aobut the working and possible modifications. 

---

### Tools: 
Symbolab - to solve the matrix operations and functions 

### Modifications: 
#### cubeWidth
  - Sets the length of one side of the cube 
  - Change this (along with 'horizontalOffset') to get cubes of different sizes 

#### backgroundASCIICode 
  - To change the background on which the cube spins in the terminal 
  - For aesthetics -> set as ' ' 

### Working: 
Open the terminal (in mac) or command prompt (in windows). <br/>
Go to directory in which the spinning_cube.c file is located. <br/>
Run the following commands in order: 
  - gcc spinning_cube.c
  - ls (to check if 'a.out' file is created)
  - ./a.outYou can see 
<br/>
Voila! You can see your spinning cube.
