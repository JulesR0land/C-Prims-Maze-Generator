# C-Prims-Maze-Generator
Maze generator using the Prim's algorithm in C language

The size of the maze is calculated using the empty blocks in the rows and column.
So a size of 3 will draw a maze like this:
```
   1 2 3
  XXXXXXX
1 S X   X
  X X XXX
2 X     X
  X X X X
3 X X X F
  XXXXXXX
```

The default size is 7 in height and width but they can be modified independently with the "--height *int*" and "--width *int*" options.
The minimum is 3 for both.

The default start and finish points are random but they can be modified
independently with the "--start *"X Y"* " and "--finish *"X Y"* " options.
If the finish is the same as start, it will be randomized.

The random seed is based on arc4random().