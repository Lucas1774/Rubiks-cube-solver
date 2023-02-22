## Program

I wrote this around 6 months after my first ever hello world program, so I would change a lot today. It was also my very first contact with c++. I didn't know how to compile c++ code, in fact, I must have heard the word "compile" a couple of times before.
I added the parsing functions just now, since that sounded like too much for me to do back then, as well as the logic of the arguments (which I'm glad I could fit in with no work at all).
The program is definitely a little over the place and screams for some structuring, but it works like a clock. You can check it out [here](https://alg.cubing.net/).

It generates a Rubik's cube scramble and then solves it using an algorithm database and the "3-style" method, which is usually used by humans to solve it blindfolded. These algorithms are the ones I use, so the program pretty much solves it as I would. It could be possible to obtain these algorithms or the whole solution using pathfinding, but there is plenty of software that already does this. This is supposed to be a somewhat (not really) customizable humanlike solve generator.

To generate the scramble it uses two randomly generated seeds, one linked to the layer to turn, the other to the turn to make (CW, CCW or double). The scrambled state is obtained during the scramble, which is definitely an ugly solution.
Then, in a VERY oversimplified way, it observes the path that the pieces should follow for them to end up in their correct spot, and creates a vector of "targets". These target vectors are then interpreted to display their associated algorithms sequence.

Unfortunately, most of its customization is only possible within the code: the buffer choice, the letter key, the order in which the three tasks are done or the orientation method (and others I might be forgetting). There is too much style variety for me to make a "universal 3-style Rubik's cube solver". I am (was) a junior computer science student, after all, driven by the shame of not knowing a single programming language after a whole semester.

## Usage

It can be run without arguments or with one that should be the path of a one-line (I used to compile this data, that's why it's stored in a single line instead of in a table) CSV file with the memorization key. This key is based on the letter pair memorization technique, used also for memorizing cards. I won't share mine for reasons that you will find very reasonable if you think about it.  
The .csv files must be inside a "src" folder in the same directory as the executable.

## Key

I don't remember what order the values in the CSV files should follow. This is the key the program uses to define scrambled states and whatnot:

                         |-----||-----||-----|
                         |  22 ||  19 ||  20 |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  22 ||     ||  20 |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  11 ||  7  ||  7  |
                         |-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  23 ||  23 ||  10 ||  9  ||  6  ||  6  ||  8  ||  21 ||  19 |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  17 ||     ||  5  ||  4  ||     ||  2  ||  3  ||     ||  15 |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  13 ||  11 ||  5  ||  3  ||  0  ||  0  ||  1  ||  9  ||  17 |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
                         |-----||-----||-----|
                         |  4  ||  1  ||  2  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  10 ||     ||  8  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  14 ||  13 ||  16 |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  12 ||  12 ||  15 |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  16 ||     ||  14 |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  21 ||  18 ||  18 |
                         |-----||-----||-----|
    ________________________________________________________________

                         |-----||-----||-----|
                         |  H  ||  H  ||  D  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  L  ||     ||  D  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  L  ||  V  ||  V  |
                         |-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  Z  ||  Z  ||  N  ||  U  ||  U  ||  R  ||  P  ||  P  ||  K  |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  T  ||     ||  N  ||  M  ||     ||  R  ||  S  ||     ||  K  |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
    |  T  ||  B  ||  B  ||  M  ||  0  ||  0  ||  S  ||  J  ||  J  |
    |-----||-----||-----||-----||-----||-----||-----||-----||-----|
                         |-----||-----||-----|
                         |  X  ||  X  ||  F  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  C  ||     ||  F  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  C  ||  Y  ||  Y  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  I  ||  I  ||  O  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  A  ||     ||  O  |
                         |-----||-----||-----|
                         |-----||-----||-----|
                         |  A  ||  E  ||  E  |
                         |-----||-----||-----|
                         