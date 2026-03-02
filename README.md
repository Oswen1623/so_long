This project has been created as part of the 42 curriculum by lucinguy.

Description 

The goal of this exercise is to create a basic graphic project, using the school's graphical library, MiniLibX. This library includes basic necessary tools to open a window, create images and deal with keyboard and mouse events. We must create a 2D view (top-down or profile) game in which a character must be able to navigate through the map with the WASD or arrow keys, go left, right, up and down, get every collectible before reaching the exit, without going through walls. At every move, the current number of movementsmust be displayed in the shell. 

Instructions 

The program must comply with the following rules : 

- Only the following functions are allowed : 
    • open, close, read, write, malloc, free, perror, strerror, exit 
    • All functions of the math library (-lm compiler option, man man 3 math) 
    • All functions of the MiniLibX 
    • gettimeofday() 
    • ft_printf and any equivalent we coded

- It should take a map in a .ber format as an argument. The map can be composed of only these 5 characters : 
0 for an empty space, 
1 for a wall, 
C for a collectible, 
E for a map exit, 
P for the player’s starting position. 

- To be valid, a map must be rectangular, contain 1 exit, 1 starting position and at least 1 collectible, all accessible, surrounded by walls. If any misconfiguration is encountered in the file, the program must exit cleanly, and return "Error\n" followed by an explicit error message of your choice. 

- The program must display an image in a window whose management shall remain smooth (switching to another window, minimizing, ...). The window should close upon pressing the ESC key or clicking on the window's cross, and quit the program in a clean way. 

- The use of the images from the MiniLibX is mandatory. 

Resources 

MiniLibX provided by 42Paris. 

Usage examples 

```make #Compile the sources``` 

```./so_long [map.ber] #Run the program with the [map.ber] being the map provided by the user.``` 