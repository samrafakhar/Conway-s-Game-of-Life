# Conway-s-Game-of-Life

The game of life implemented in C 

It doesnt take any arguments. Using rand() it initiates board. the code for barrier is taken from the litle book of semaphores (reusable barrier). the board is allocated on heap so it becomes easier to use it whil e making threads and type casting.

![screenshot](https://user-images.githubusercontent.com/68819501/121777565-40fbf680-cbac-11eb-923d-7f57e0e50adc.PNG)

## How to run 

To compile the code, use the following command in your ubuntu terminal:

                gcc gameoflife.c -pthread

To execute it, enter the following command

                ./a.out input.txt

## Game of Life
Description of the Game of Life taken from Wikipedia: \
The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. 

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

1. Any live cell with two or three live neighbours survives.
2. Any dead cell with three live neighbours becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed, live or dead; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.



