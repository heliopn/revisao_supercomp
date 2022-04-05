# revisao_supercomp

'''bash
g++ -g -Wall -O3 stocks.cpp -o stocks
./stocks < stocks.seq
'''



### Exploitation
Consiste em tomar a decisão assumida como otima, tendo em vista somente os dados em análise no mometo da comparação. Essa é uma estrategia segura pois evita ao máximo tomadas de decisões ruins, mas impede o seu programa de potencialmente achar soluções melhores.

### Exploration
Consiste em as vezes não tomar a devisão assumida como otima, dentro da logica de que só a situação observada no momento não é suficiente para identificar que não existe a possibilidade de ter uma melhor situação futura. Tem um risco muito maior pois pode levar a pessimas tomadas de decisão, mas também pode descobrir situações muito melhores que as encontradas em Exploitation, se existir alguma.

### Exploration vs Explotation
Epsilon-Greedy Action Selection
Epsilon-Greedy is a simple method to balance exploration and exploitation by choosing between exploration and exploitation randomly.
The epsilon-greedy, where epsilon refers to the probability of choosing to explore, exploits most of the time with a small chance of exploring.

### Valgrind

'''bash
valgrind --tool=callgrind ./sum
'''

As others have said, the issue is the store to the memory location in the array: x[i][j]. Here's a bit of insight why:

You have a 2-dimensional array, but memory in the computer is inherently 1-dimensional. So while you imagine your array like this:

0,0 | 0,1 | 0,2 | 0,3
----+-----+-----+----
1,0 | 1,1 | 1,2 | 1,3
----+-----+-----+----
2,0 | 2,1 | 2,2 | 2,3

Your computer stores it in memory as a single line:

0,0 | 0,1 | 0,2 | 0,3 | 1,0 | 1,1 | 1,2 | 1,3 | 2,0 | 2,1 | 2,2 | 2,3

In the 2nd example, you access the array by looping over the 2nd number first, i.e.:

x[0][0] 
        x[0][1]
                x[0][2]
                        x[0][3]
                                x[1][0] etc...

Meaning that you're hitting them all in order. Now look at the 1st version. You're doing:

x[0][0]
                                x[1][0]
                                                                x[2][0]
        x[0][1]
                                        x[1][1] etc...

Because of the way C laid out the 2-d array in memory, you're asking it to jump all over the place. But now for the kicker: Why does this matter? All memory accesses are the same, right?

No: because of caches. Data from your memory gets brought over to the CPU in little chunks (called 'cache lines'), typically 64 bytes. If you have 4-byte integers, that means you're geting 16 consecutive integers in a neat little bundle. It's actually fairly slow to fetch these chunks of memory; your CPU can do a lot of work in the time it takes for a single cache line to load.

Now look back at the order of accesses: The second example is (1) grabbing a chunk of 16 ints, (2) modifying all of them, (3) repeat 4000*4000/16 times. That's nice and fast, and the CPU always has something to work on.

The first example is (1) grab a chunk of 16 ints, (2) modify only one of them, (3) repeat 4000*4000 times. That's going to require 16 times the number of "fetches" from memory. Your CPU will actually have to spend time sitting around waiting for that memory to show up, and while it's sitting around you're wasting valuable time.

Important Note:

Now that you have the answer, here's an interesting note: there's no inherent reason that your second example has to be the fast one. For instance, in Fortran, the first example would be fast and the second one slow. That's because instead of expanding things out into conceptual "rows" like C does, Fortran expands into "columns", i.e.:

0,0 | 1,0 | 2,0 | 0,1 | 1,1 | 2,1 | 0,2 | 1,2 | 2,2 | 0,3 | 1,3 | 2,3

The layout of C is called 'row-major' and Fortran's is called 'column-major'. As you can see, it's very important to know whether your programming language is row-major or column-major! Here's a link for more info: http://en.wikipedia.org/wiki/Row-major_order

