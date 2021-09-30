The output that we get after running the program for different values of number of vertices in line graph is summarised in the table below:

| Number of Vertices in line graph | Number of distinct representations | Number of circularly distinct representations |
|:--------------------------------:|:----------------------------------:|:---------------------------------------------:|
|                 2                |                  2                 |                       1                       |
|                 3                |                  6                 |                       1                       |
|                 4                |                 16                 |                       2                       |
|                 5                |                 40                 |                       4                       |
|                 6                |                 96                 |                       8                       |
|                 7                |                 224                |                       16                      |
|                 8                |                 512                |                       32                      |
|                 9                |                1152                |                       64                      |
|                10                |                2560                |                      128                      |
|                11                |                5632                |                      256                      |
|                12                |                12288               |                      512                      |
|                13                |                26624               |                      1024                     |
|                14                |                57344               |                      2048                     |

We can make the following observations from the above data.
1. For n ≥ 3, Number of distinct representations = n.2<sup>n-2</sup>
2. For n ≥ 3, Number of circularly distinct representations = 2<sup>n-3</sup>
3. Number of distinct representations = Number of circularly distinct representations * (2 * Number of Vertices in line graph)
4. Number of distinct representations = Number of circularly distinct representations * (Length of string representing the line graph)
5. All words representing the line graph are primitive words.
