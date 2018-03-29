// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
#include <vector>
using namespace std;

void PushBack(TrainCar* &train_head, TrainCar* tCar);
void DeleteAllCars( TrainCar* head );
void TotalWeightAndCountCars(TrainCar *train, int &total_weight, int &num_engines,
				int &num_freight_cars, int &num_passenger_cars,
				int &num_dining_cars, int &num_sleeping_cars);
				
float CalculateSpeed( TrainCar* head );
float AverageDistanceToDiningCar( TrainCar* head );

int totalWeightWithoutEngine( TrainCar* head, int &engines, int &length);
int ClosestEngineToSleeperCar( TrainCar* head );

void assignFreight(TrainCar* &f_ptr, float maxfWeightPerEngine, unsigned int &engineNum,
			int &engine_remain, unsigned int &freightNum, int max_cars_per_train);
						
vector<TrainCar*> ShipFreight( TrainCar* &all_engines, TrainCar* &all_freight, 
					int min_speed, int max_cars_per_train );

void Separate(TrainCar* &origin, TrainCar* &left, TrainCar* &right);

void SeparateComfort(TrainCar* &origin, TrainCar* &left, TrainCar* &right);
