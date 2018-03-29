HOMEWORK 6: BATTLESHIP RECURSION


NAME:  < Dong Hu >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of ships (s)? 
The total number of occupied cells (o) or open water (w)? 
The number of constraints (c)? 
The number of unknown sums (u) or unspecified ship types (t)? 
Etc. 

for cases with no unknown/constraints:

	for the dfs tree, traversed without repetition, 
	O(b^d) for implicit graphs with branching factor b searched to depth d
	
	here the branching factor is 3 because its whether to put the ship horizontally
	vertically or search for the next location and the depth is w*h because we at most
	search for w*h points..(Although I uses optimization pruning in my program but
	still we evaluate for the worst case ) so the runtime complexity is :
	
	O( (w*h) * 3^(w*h) ) ---- because we need extra w*h time to print the graph

for cases with only constraints:

	O( c * (w*h) * 3^(w*h) ) ---- checking board if it violates the constraints
	
for cases with only unknowns:

	O( (w*h) * 10^(w*h) ) ---- checking 7 ships to see if one fits the board
				   adding 7 more branches factor

for cases with unknown/constraints:
	O( c * (w*h) * 10^(w*h) )

Notice that my program will be much faster because I precheck the constraints condition
and pre-generate the unknown ship combinations, so the actual comolexity will be much 
smaller..

Space complexity is O( w*h )



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.

time ./test puzzle10.txt find_all_solutions > out_puzzle10_find_all_solutions.txt

real	0m1.286s
user	0m0.895s
sys	0m0.384s

the rest test cases are all within 0.1s


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


