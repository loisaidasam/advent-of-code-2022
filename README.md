# advent-of-code-2022

Sam's trials

## Day 6: Tuning Trouble

> How many characters need to be processed before the first start-of-packet marker is detected?

- sets

check out this neat XOR trick:

- https://www.mattkeeter.com/blog/2022-12-10-xor/

## Day 7: No Space Left On Device

change directories, sum file sizes, etc.

- traversing trees, parent-child relationships
- classes
- pointers
- stringstream for splitting strings
- recursion

## Day 8: Treetop Tree House

walk around grid looking at tree heights

- 2d arrays
- char to int

## Day 14: Regolith Reservoir

draw a grid with some boundaries, drop sand into it, see how it falls

- classes
- sparse matrices (in theory, i got it to work without actually using one)

Note: I modified the inputs to just be space-separated ints instead of parsing all the nonsense

> Drawing rock as #, air as ., and the source of the sand as +, this becomes:

```
  4     5  5
  9     0  0
  4     0  3
0 ......+...
1 ..........
2 ..........
3 ..........
4 ....#...##
5 ....#...#.
6 ..###...#.
7 ........#.
8 ........#.
9 #########.
```

...

> Once all 24 units of sand shown above have come to rest, all further sand flows out the bottom, falling into the endless void. Just for fun, the path any new sand takes before falling forever is shown here with ~:

```
.......+...
.......~...
......~o...
.....~ooo..
....~#ooo##
...~o#ooo#.
..~###ooo#.
..~..oooo#.
.~o.ooooo#.
~#########.
~..........
~..........
~..........
```
