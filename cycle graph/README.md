The output that we get after running the program for different values of number of vertices in cycle graph is summarised in the table below:

| Number of Vertices in cycle graph | Number of distinct representations | Number of circularly distinct representations |
|:---------------------------------:|:----------------------------------:|:---------------------------------------------:|
|                 3                 |                  6                 |                       2                       |
|                 4                 |                 16                 |                       2                       |
|                 5                 |                 20                 |                       2                       |
|                 6                 |                 24                 |                       2                       |

We can make the following observations from the above data.
1. Number of circularly distinct representations = 2 for all values of number of vertices in cycle graph.
2. For n ≥ 4, Number of distinct representations = Number of circularly distinct representations * (2 * Number of Vertices in cycle graph) = 4n
3. For n ≥ 4, Number of distinct representations = Number of circularly distinct representations * (Length of string representing the cycle graph)
4. For n ≥ 4, all words representing the cycle graph are primitive words.
