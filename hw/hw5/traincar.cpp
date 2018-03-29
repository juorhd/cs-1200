// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "traincar.h"
using namespace std;
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

//function takes in the head of a train 
//pushes the car to the end of this train
void PushBack( TrainCar* &head, TrainCar* tCar ){	
	// When train already has one or more than one car
	
	if( head != NULL ){  
		TrainCar* tail = head; 
		
		while ( tail->next != NULL) 
			tail = tail->next;
				
		tail->next = tCar;
		tCar->prev = tail;
		tCar->next = NULL;

	  
	// when train is empty
	} else {
		
		tCar->prev = NULL;
		tCar->next = NULL;
	    	head = tCar;  

		
	 }
}

//function takes in the head of a train
//deletes all the cars in that train
void DeleteAllCars( TrainCar* head ){
	//while its not the end of the train, keep looping over
	while ( head ){  
		TrainCar* tmp = head;
		head = head->next;
		delete tmp;
	}
	delete head;
}

//function takes in the head of a train
//changes the num of car of every type
void TotalWeightAndCountCars(TrainCar *train, int &total_weight, int &num_engines, 
				int &num_freight_cars,int &num_passenger_cars,
				int &num_dining_cars, int &num_sleeping_cars)
{
	TrainCar* ptr = train;
	total_weight = 0;
	num_engines = 0;
	num_freight_cars = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0;
	
	while ( ptr ) {  
		
		total_weight += ptr->getWeight();
		
		if( ptr -> isEngine() ) 	 	num_engines++;
		else if( ptr -> isFreightCar() ) 	num_freight_cars++;
		else if( ptr -> isPassengerCar() ) 	num_passenger_cars++;
		else if( ptr -> isDiningCar() ) 	num_dining_cars++;
		else if( ptr -> isSleepingCar() ) 	num_sleeping_cars++;
		
		ptr = ptr->next;
	}
}

//helper function to calculate total weight without engines
//modifies number of engines
int totalWeightWithoutEngine( TrainCar* head, int &engines, int &length){
	
	TrainCar* ptr;
	unsigned int total_weight = 0;
	engines = length = 0;
	
	for( ptr = head; ptr != NULL; ptr = ptr->next ) {
		// count engine num
		length++;
		if( ptr->isEngine() ){
			engines++;
		}
		// Calculate the weight of the FreightCar
		else total_weight += ptr->getWeight();   
	}
	return total_weight;
}

//function takes in the head of a train
//return the speed of that train
float CalculateSpeed( TrainCar* head ){
	
	int engines = 0;
	int len = 0;
	unsigned int total_weight = totalWeightWithoutEngine( head, engines, len) 
				    + engines*150;
				
	unsigned int totalHorsePower = engines*3000;

	//using the fomula to calculate speed
	float speed = (totalHorsePower*550*36*1.0)/(2*2*528*total_weight);
	return speed;
}

float AverageDistanceToDiningCar( TrainCar* head ){
	TrainCar* ptr = head;
	TrainCar* forward;
	TrainCar* backward;
	int dist;
	int p_count = 0;
	int count_backward, count_forward;
	float avgdist = 0;
	
	//calculate the average distance to dining 
	while ( ptr ){
		if ( ptr->isPassengerCar() ){
		 	
			p_count++;
			dist = -1;
			count_backward = count_forward = 0;
			backward = forward = ptr;
			
			//search backward
			while  ( backward -> prev ){
				backward = backward->prev;
				
				if ( backward->isEngine() )  break;
					
				count_backward++;
				if( backward->isDiningCar() ){
					dist = count_backward;
					break;
				}
			}
			
			//search forward
			while  ( forward -> next ){
				forward = forward->next;
				
				if ( forward->isEngine() )  break;

				count_forward++;
				if( forward->isDiningCar() ){
					if ( count_forward < dist || dist == -1 )
						dist = count_forward;
					break;
				}
			}
			if ( dist == -1 ) return -1;
			avgdist += dist;
		}
		ptr = ptr -> next;
	}
	
	return  roundf( (float) avgdist*10 / p_count) / 10;
}

//a function that calculate the closest engine to the sleeper Car
int ClosestEngineToSleeperCar( TrainCar* head ){
	TrainCar* ptr = head;
	TrainCar* forward;
	TrainCar* backward;
	int dist = 0;
	int minDist = 2147483647;
	int count_backward, count_forward;
	
	//calculate the shortest dist to engine 
	while ( ptr ){
		if ( ptr->isSleepingCar() ){
		 	
			dist = 0;
			count_backward = count_forward = 0;
			backward = forward = ptr;
			
			//search backward
			while  ( backward -> prev ){
				backward = backward->prev;
				count_backward++;
									
				if( backward->isEngine() ){
					dist = count_backward;
					break;
				}
			}
			
			//search forward
			while  ( forward -> next ){
				forward = forward->next;
				count_forward++;
				
				if( forward->isEngine() ){
					if ( count_forward < dist )
						dist = count_forward;
					break;
				}
			}
			//if closer, update the value
			if( dist < minDist )
				minDist = dist;	
		}
		ptr = ptr -> next;
	}
	return minDist;
}

//helper function to assign
void assignFreight(TrainCar* &f_ptr, float maxfWeightPerEngine, unsigned int &engineNum,
			int &engine_remain, unsigned int &freightNum, int max_cars_per_train){
				
	int currentEngineNum = engineNum;						
	int currentFreightWeight = 0;
	int currentTrainLength = 1;
	int remainingTrainLength;
	float MaxWeight;
	
	engine_remain--;
	
	//if there is still freight need to be distributed	
	while( f_ptr ){
		
		MaxWeight = maxfWeightPerEngine * currentEngineNum;
		
		//if the engine is still capable of adding more freight
		//and the train is not reaching maximum height
		if ( currentTrainLength < max_cars_per_train
		    && currentFreightWeight + f_ptr->getWeight() <= MaxWeight){
			
			currentTrainLength++;
			currentFreightWeight += f_ptr->getWeight();
			f_ptr = f_ptr->next;
			continue;
		}
		
		//determines whether still need to add more engine
		remainingTrainLength = max_cars_per_train - currentTrainLength;
		
		if ( remainingTrainLength >= currentTrainLength / currentEngineNum 
								&& engine_remain > 0 ){
			engine_remain--;
			currentEngineNum++;
			currentTrainLength += 2;
			currentFreightWeight += f_ptr->getWeight();
			f_ptr = f_ptr->next;
			continue;
		}
		break;
	}
	//modify values
	freightNum = currentTrainLength - currentEngineNum;
	engineNum = currentEngineNum;
}


vector<TrainCar*> ShipFreight( TrainCar* &all_engines, TrainCar* &all_freight, 
					int min_speed, int max_cars_per_train )
{
	vector<TrainCar*> trains;
	
	int engine_remain = 0;
	unsigned int engineNum;
	unsigned int freightNum = 0;
	unsigned int total_freight_weight = 0;
	
	//get freight number
	for( TrainCar* ptr = all_freight ; ptr != NULL; ptr = ptr->next ) {
		total_freight_weight += ptr->getWeight();  
		freightNum++; 
	}
	for( TrainCar* ptr = all_engines ; ptr != NULL; ptr = ptr->next ) 
		engine_remain++;
	
	//calculate the maximum freight weight affordable per engine
	int kappa = (3000*550*36) / (2*2*528);
	float maxfWeightPerEngine = kappa*1.0 / min_speed - 150; 

	
	
	TrainCar* ptr;
	TrainCar* newhead;
	TrainCar* tmp_fptr;
	TrainCar* tmp_eptr;

	//terminates when engine is used up or freight is all distributed
	while ( all_freight && engine_remain > 0 ){
		engineNum = 1;
		freightNum = 0;
		tmp_fptr = all_freight;
		assignFreight( all_freight, maxfWeightPerEngine, engineNum, engine_remain,
						 freightNum, max_cars_per_train);
		newhead = NULL;
		//add engines
		while ( engineNum > 0 ){
			tmp_eptr = all_engines;
			all_engines = all_engines->next;
			tmp_eptr->next = NULL;
			PushBack( newhead, tmp_eptr );
			engineNum--;
		}
		//add freights
		while ( freightNum > 0 ){
			ptr = tmp_fptr;
			tmp_fptr = tmp_fptr->next;
			ptr->next = NULL;
			PushBack( newhead, ptr );
			freightNum--;
		}
		trains.push_back(newhead);	
	}
	
	if ( all_engines != NULL )
		all_engines->prev = NULL;
	if ( all_freight != NULL )
		all_freight->prev = NULL;

	return trains;

}

void Separate(TrainCar* &origin, TrainCar* &left, TrainCar* &right) {
	
	// get data on the train
	int weight_without_engines, num_engines, length;
	num_engines = length = 0;
	weight_without_engines = totalWeightWithoutEngine(origin, num_engines, length);          

	// decide how many non engine cars are needed in each train to make them roughly equal
	int leftEngineNum = num_engines/2;
	int rightEngineNum = num_engines - leftEngineNum;
	float leftWeight = weight_without_engines * (leftEngineNum / float(num_engines));
	float rightWeight = weight_without_engines * (rightEngineNum / float(num_engines));

	// try each split point, searching for the best split
	TrainCar* best_split = NULL;
	int best_weight_error;
	int best_engines_to_move;
	TrainCar* current_split = origin -> next;
	int current_weight = ( origin -> isEngine() ) ? 0 : origin->getWeight();
	int current_engines = ( origin -> isEngine() ) ? 1 : 0;

	// consider every split in the chain
	while (current_split != NULL) {
		float weight_error;
		int engines_to_move;
		// determine how close this weight split is to the ideal weight
		// split and how many engines must be moved
		if ( fabs(current_weight-leftWeight) <= fabs(current_weight-rightWeight) ) {
			weight_error = fabs(current_weight-leftWeight);
			engines_to_move = current_engines-leftEngineNum;
		} else {
			weight_error = fabs(current_weight-rightWeight);
			engines_to_move = current_engines-rightEngineNum;
		}
		// keep track of the best split
		if ( best_split == NULL || weight_error < best_weight_error ||
				( fabs(weight_error - best_weight_error) < 0.001 &&
					abs(engines_to_move) < abs(best_engines_to_move) ) ) {
			best_split = current_split;
			best_weight_error = weight_error;
			best_engines_to_move = engines_to_move;
		}
		if ( current_split -> isEngine() ) {
			current_engines++;
		} else {
			current_weight += current_split->getWeight();
		}
		current_split = current_split->next;
	}


	// cut the train in half
	left = origin;
	right = best_split;
	TrainCar *left_end = best_split->prev;
	left_end->next = NULL;
	right->prev = NULL;
	origin = NULL;

	// move the necessary number of engines the least total distance
	while ( best_engines_to_move > 0 ) {
		
		// the engine is on the left, need to find the 
		// left most engine..
		TrainCar* tmp = left_end;
		while ( !tmp -> isEngine() )  
			tmp = tmp->prev; 

		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		right->prev = tmp;
		tmp->prev = NULL;
		tmp->next = right;
		right = tmp;
		best_engines_to_move--;
	}
	while (best_engines_to_move < 0) {
		
		// the engine is on the right, need to find the 
		// left most engine..
		TrainCar* tmp = right;
		while (!tmp->isEngine()) 
			tmp = tmp->next; 
			
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		left_end->next = tmp;
		tmp->prev = left_end;
		left_end = tmp;
		tmp->next = NULL;
		best_engines_to_move++;
	}

}

//helper function to exchange two cars in trains
void exchange( TrainCar* t1, TrainCar* t2 ){
	
	TrainCar* t1_prev=NULL;
	TrainCar* t1_next=NULL;
	TrainCar* t2_prev=NULL;
	TrainCar* t2_next=NULL;
	
	if ( t1->prev != NULL ) t1_prev = t1->prev;
	if ( t2->prev != NULL ) t2_prev = t2->prev;
	if ( t1->next != NULL ) t1_next = t1->next;
	if ( t2->next != NULL ) t2_next = t2->next;
	
	t1->prev = t2_prev;
	t2->prev = t1_prev;
	t1->next = t2_next;
	t2->next = t1_next;

	if ( t2_prev != NULL ) t2_prev->next = t1;
	if ( t1_prev != NULL ) t1_prev->next = t2;
	if ( t2_next != NULL ) t2_next->prev = t1;
	if ( t1_next != NULL ) t1_next->prev = t2;

}

//extra credit
void SeparateComfort(TrainCar* &origin, TrainCar* &left, TrainCar* &right){ 
	
	Separate(origin, left, right);

	int leftDiningCarNum, rightDiningCarNum;
	int leftSleepingCarNum, rightSleepingCarNum;
	int leftTrainlength, rightTrainlength;
	TrainCar* rightMostDiningCarOnLeft = NULL;
	TrainCar* leftMostDiningCarOnRight = NULL;
	TrainCar* rightMostSleepingCarOnLeft = NULL;
	TrainCar* leftMostSleepingCarOnRight = NULL;
	
	leftDiningCarNum = rightDiningCarNum = 0;
	leftSleepingCarNum = rightSleepingCarNum = 0;
	leftTrainlength = rightTrainlength = 0;
	
	for ( TrainCar* ptr = left; ptr != NULL; ptr = ptr->next ){
		if ( ptr->isDiningCar() ){
			leftDiningCarNum++;
			rightMostDiningCarOnLeft = ptr;	
		} 
		if ( ptr->isSleepingCar() ){
			leftSleepingCarNum++;
			rightMostSleepingCarOnLeft = ptr;
		} 
		leftTrainlength++;
	}
	
	TrainCar* rightEnd = right;

	while ( rightEnd->next ) rightEnd = rightEnd -> next;

	for ( TrainCar* ptr = rightEnd; ptr != NULL; ptr = ptr->prev ){
		if ( ptr->isDiningCar() ){
			rightDiningCarNum++;
			leftMostDiningCarOnRight = ptr;	
		} 
		if ( ptr->isSleepingCar() ){
			rightSleepingCarNum++;
			leftMostSleepingCarOnRight = ptr;
		} 
		if ( ptr->prev != NULL && ptr->next != NULL && ptr->isEngine() ){

			TrainCar* engineMoveBackward = ptr->prev;
			TrainCar* engineMoveForward = ptr->next;

			while ( engineMoveBackward->prev && engineMoveForward->next ){
				while ( engineMoveBackward->prev->isEngine() 
						|| engineMoveForward->next->isEngine()){
							
					engineMoveBackward = engineMoveBackward->prev;
					engineMoveForward = engineMoveForward->next;
				}
				
				if ( engineMoveBackward->prev == NULL ) break;
				if ( engineMoveForward->next == NULL ) break;

				engineMoveBackward = engineMoveBackward->prev;
				engineMoveForward = engineMoveForward->next;

			}

			if ( !engineMoveBackward->prev ) { exchange(ptr, engineMoveBackward); }
			else { exchange(ptr, engineMoveForward); }
			right = ptr;
		}
		rightTrainlength++;
	}
	
	TrainCar* leftFirstPassengerCar;
	TrainCar* rightFirstPassengerCar;
	int leftMiddle, rightMiddle;
	
		
		//move leftmost dining car on the right to left middle part
		if ( !leftDiningCarNum && rightDiningCarNum  ){
			leftMiddle = leftTrainlength/2;
			TrainCar* tmptr = left;
			
			//get to the middle of the left car
			while ( leftMiddle > 0 ){
				tmptr = tmptr->next;
				leftMiddle--;
			}
			leftFirstPassengerCar = rightFirstPassengerCar = tmptr;
		
			//find the nearest passenger car from the middle
			while ( !leftFirstPassengerCar->isPassengerCar() 
			 		&& !rightFirstPassengerCar->isPassengerCar() ){
			
				if ( leftFirstPassengerCar -> next != NULL )
					leftFirstPassengerCar = leftFirstPassengerCar -> prev;
				if ( rightFirstPassengerCar -> next != NULL )
					rightFirstPassengerCar = rightFirstPassengerCar -> next;
			}
			if ( leftFirstPassengerCar -> isPassengerCar() ){
				if ( rightFirstPassengerCar -> isPassengerCar() ){
					tmptr = rightFirstPassengerCar;
				} tmptr = leftFirstPassengerCar;
			}
			//exchange the dining car from the right part of seperated train;
			exchange(tmptr, leftMostDiningCarOnRight);
			leftMostDiningCarOnRight = tmptr;
		
		}
		
		if ( !rightDiningCarNum && leftDiningCarNum  ){
			rightMiddle = rightTrainlength/2;
			TrainCar* tmptr = right;
		
			//get to the middle of the left car
			while ( rightMiddle > 0 ){
				tmptr = tmptr->next;
				rightMiddle--;
			}
			leftFirstPassengerCar = rightFirstPassengerCar = tmptr;
		
			//find the nearest passenger car from the middle
			while ( !leftFirstPassengerCar->isPassengerCar() 
			 		&& !rightFirstPassengerCar->isPassengerCar() ){
			
				if ( leftFirstPassengerCar -> next != NULL )
					leftFirstPassengerCar = leftFirstPassengerCar -> prev;
				if ( rightFirstPassengerCar -> next != NULL )
					rightFirstPassengerCar = rightFirstPassengerCar -> next;
			}
			if ( rightFirstPassengerCar -> isPassengerCar() ){
				if ( leftFirstPassengerCar -> isPassengerCar() ){
					tmptr = leftFirstPassengerCar;
				} tmptr = rightFirstPassengerCar;
			}
			//exchange the dining car from the right part of seperated train;
			exchange(tmptr, rightMostDiningCarOnLeft);
			rightMostDiningCarOnLeft = tmptr;
		
		}
	
	
		TrainCar* leftFirstDiningCar;
		TrainCar* rightFirstDiningCar;
	
		leftMiddle = leftTrainlength/2;
		TrainCar* tmptrL = left;
	
		//get to the middle of the left car
		while ( leftMiddle > 0 ){
			tmptrL = tmptrL->next;
			leftMiddle--;
		}
	
		if ( !tmptrL->isDiningCar() ){
			leftFirstDiningCar = rightFirstDiningCar = tmptrL;
			while ( !leftFirstDiningCar->isDiningCar() 
			 		&& !rightFirstDiningCar->isDiningCar() ){
			
				if ( leftFirstDiningCar -> next != NULL )
					leftFirstDiningCar = leftFirstDiningCar -> prev;
				if ( rightFirstDiningCar -> next != NULL )
					rightFirstDiningCar = rightFirstDiningCar -> next;
			}
			if ( rightFirstDiningCar -> isDiningCar() )
				exchange(tmptrL, rightFirstDiningCar);
			else 
				exchange(tmptrL, leftFirstDiningCar);
		}
	
		rightMiddle = rightTrainlength/2;
		TrainCar* tmptrR = right;
	
		//get to the middle of the left car
		while ( rightMiddle > 0 ){
			tmptrR = tmptrR->next;
			rightMiddle--;
		}
	
		if ( !tmptrR->isDiningCar() ){
			leftFirstDiningCar = rightFirstDiningCar = tmptrR;
			while ( !leftFirstDiningCar->isDiningCar() 
			 		&& !rightFirstDiningCar->isDiningCar() ){
				
				if ( leftFirstDiningCar -> next != NULL )
					leftFirstDiningCar = leftFirstDiningCar -> prev;
				if ( rightFirstDiningCar -> next != NULL )
					rightFirstDiningCar = rightFirstDiningCar -> next;
			}
			if ( rightFirstDiningCar -> isDiningCar() )
				exchange(tmptrR, rightFirstDiningCar);
			else 
				exchange(tmptrR, leftFirstDiningCar);
		}
	
}








