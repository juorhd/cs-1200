HOMEWORK 6: BATTLESHIP CONTEST


NAME:  < Dong Hu >



COLLABORATORS AND OTHER RESOURCES:
< None >



DESCRIPTION OF ANY PERFORMANCE IMPROVEMENTS/OPTIMIZATIONS:
(please be concise!)

use printf instead of cout for the most printing part
precheck the constraint violation
pregenerate the unknown ship set
precheck if the ship fit the col/row
precheck the ship suitable for the row/col cell num
use dynamic memory in class instead of vector 


DESCRIBE INTERESTING NEW PUZZLES YOU CREATED:

board 6 5
rows ? ? ? ? ? ?
cols ? ? ? ? ?
unknown
unknown
unknown
unknown
unknown
unknown
constraint 0 0 <

find 53288 solution(s)

real	0m3.417s
user	0m2.436s
sys	0m0.755s


SUMMARY OF YOUR PERFORMANCE ON ALL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.

time ./test puzzle10.txt find_all_solutions > out_puzzle10_find_all_solutions.txt

real	0m1.286s
user	0m0.895s
sys	0m0.384s

the rest test cases are all within 0.1s