The output that we get after running the program for different values of number of vertices in tree is summarised in the table below:

| Number of Vertices in tree | Number of trees on n labeled vertices (n<sup>n-2</sup>) | Number of distinct representations | Number of circularly distinct representations |
|:--------------------------:|:-------------------------------------------------------:|:----------------------------------:|:---------------------------------------------:|
|              3             |                            3                            |                 18                 |                       3                       |
|              4             |                            16                           |                 288                |                       36                      |
|              5             |                           125                           |                6600                |                      660                      |
|              6             |                           1296                          |               196560               |                     16380                     |
|              7             |                          16807                          |               7197120              |                     514080                    |

We can make the following observations from the above data.
1. Number of distinct representations = Number of circularly distinct representations * (2 * Number of Vertices in tree)
2. Number of distinct representations = Number of circularly distinct representations * (Length of string representing the tree)
3. All words representing trees are primitive words.
