HOMEWORK 5: LINKED TRAIN CARS


NAME:  < Dong Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30 hours >



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.

First, due to the equation I can figure out the ratio between the total
freight weight( without engine ) and the number of engines, then I determine
for every train, I will add one engine first, and then using the average
freight num per previous engine to determine wheter its optimum to add
one more engine, and that optimize the assignment of the freight.


DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritze between these goals.  Describe your priorization and your
implementation.

I first seperate the train first using the function I wrote previously,
 and then if the engine is in the middle of the train, that indicates 
some of the passenger car cannot reach it(most likely), so I move the 
engine to the two side of the train ( depends on which side is closer), 
then if one of the train doesn't contain any of the dining or sleeping, 
just move it from one train to the other, if the sleeping car is too 
close to the engine, just switch it with the furthest car to ensure it 
is away from the engine.

I did finish the case where there has dining cars, since the submitty
tests also the sleeping cars so My program terminates, but my student
case proves that my program works for the dining cars has the least cost.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


