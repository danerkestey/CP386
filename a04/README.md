## Project title

### CP386 Assignment 4: Banker's Algorithm

## Motivation

This is a required assignment for the operating systems course with implementing and using
Banker's Algorithm, to practice the concept of deadlock avoidance.

## Installation

Start by cloning the repo. After that is done, enter the following commands in a gcc compiler:

gcc bankers.c -o bankers
./bankers 10 5 7 8 [or any list of resources, in this case we are using 10 5 7 8]

To exit: use command "exit" on the enter command line, or ctrl+C

## Features

List of Commands:

    RQ      -   for requesting resources (remember threads cannot request more than maximum number of resource for that thread)
                the command would fill the allocation array.
                the customer would use ‘RQ’ to request for the resources for all the customers/thread
                ex: RQ 0 3 1 2 1

    RL      -   for releasing resources -> ex: RL 4 1 2 3 1

    Status  -   would  output  the current  stateof the available, maximum, allocation, and need arrays

    Run     -   find the safe sequence and run each thread
                The command would execute the safe sequence based on the current state and all the threads would be run same function code and prints

## Tests

Tested with the gcc compiler (version 5.4.0) in a Linux enviroment using a sample input:

```
6,4,7,3
4,2,3,2
2,5,3,3
6,3,3,2
5,6,7,5
```

## Code Example

```
C (using gcc):
<gcc bankers.c -o bankers>
<./bankers 10 5 7 8>
Enter command: <RQ 1 1 1 1 1>
-> does stuff
// OR
Enter command: <RL 1 1 1 1 1>
-> does stuff
// OR
Enter command: <Status>
-> does stuff
// OR
Enter command: <Run>
-> does stuff
// OR
Enter command: <Exit>
-> does stuff

```

## Screenshots

![Alt text](./example.jpg?raw=true "Example 1")
![Alt text](./example2.jpg?raw=true "Example 2")

## Individual Contribution (Function-wise)

We used pair programming for this assignment, it is hard to pin point who did what,
as we used LiveShare and jumped between functions alot. The individual contribution was
50-50 and fairly split.

## Authors

Daner Yasin | 190773490

Jacob Goldman | 190509690

## Credits

Chapter 8 Slides

## License

MIT License

Copyright (c) 2021 Daner Yasin & Jacob Goldman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
