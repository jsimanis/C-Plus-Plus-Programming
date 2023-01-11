/* 
 *  Single Queue vs Multiple Queue Simulation
 *  by Jacquelyn Simanis and Mary Elaine Califf
 *  IT 279 
 * 
 *  This program is to show the average wait times
 *  for fast food registers is faster when fed
 *  by a single queue as opposed to multiple queues
 *  feeding an according register
*/
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

struct Register{
        int regNumber;
        int currCustNumber;
        int serviceTimeComplete;
        bool isEmpty = true;
        Register(int id){
            regNumber = id;
        }
};
struct Statistics{
        int totalWaitTime=0;
        int amountOfCustomers=0;
        int maxWaitTime=0;
        int maxLineLength=0;
    };

//checks if any registers are now open. if true, start servicing the next customer in the queue 
void checkRegister(Register& reg,  Queue& line, int currentMin, ofstream& out, Statistics& data );

//tries to add a new customer directly to the register. Returns false if registers are full.
bool addToRegister(Register reg[], CustomerData newCust, int currMin, ofstream& out, Statistics& data);

//displays simulation statistics
void getData(Statistics& data, ofstream& print);

int main(int argc, char **argv){

    if (argc < 3+1){
        cout<< "Invalid Usage"<<endl;
        exit(1);
    }
        //maximum time between customer arrival
    const int MAX_CUST_TIME = atoi(argv[1]);
        //maxium service time per customer
    const int MAX_SERVICE_TIME = atoi(argv[2]);
    int seed = atoi(argv[3]);
    if (seed==0){ 
        srand(time(nullptr));
    }
    else {
        srand(seed);
    }
    
    ofstream multPrint, singlePrint;
    multPrint.open("multiple_sim.txt");
    singlePrint.open("single_sim.txt");

    Statistics singleData, multData;

    Queue singleQueue = Queue();
    Register singleRegisters[3] = { Register(1), Register(2), Register(3)};

    Queue multQueues[3];
    Register multRegisters[3]= { Register(1), Register(2), Register(3)};

    const int EMPTY = 0;

    int arrivalTime = (rand() % MAX_CUST_TIME) +1 ;
    int custCounter= 1;


    //simulation start
    for (int currMin= arrivalTime; currMin<= 720; currMin++)
    {
    //if customer leaves cash register
        
        for (int i =0; i< 3; i++){
            checkRegister(multRegisters[i], multQueues[i], currMin, multPrint, multData);

            checkRegister(singleRegisters[i], singleQueue, currMin, singlePrint, singleData);
        
        }

    //checking if new customer has arrived
        if (currMin == arrivalTime){
            int custServiceTime = (rand() % MAX_SERVICE_TIME) +1;
            CustomerData newCust(custCounter,arrivalTime, custServiceTime );            
            singlePrint<<"Customer "<<newCust.customerNumber<< " arrived at minute " <<currMin<< "\n";
            multPrint<<"Customer "<<newCust.customerNumber<< " arrived at minute " <<currMin<< " \n";

            arrivalTime = currMin + ((rand() % MAX_CUST_TIME) +1) ; //for next customer
            custCounter++;
        //send customer to register or queue
            //single queue
            bool addedToRegister = addToRegister(singleRegisters, newCust, currMin, singlePrint  , singleData );
            if (addedToRegister == false) //then add to queue
            {
                singleQueue.enqueue(newCust);
                if (singleQueue.getSize() > singleData.maxLineLength)
                    singleData.maxLineLength = singleQueue.getSize();
            }

            //mult queue
            addedToRegister = addToRegister(multRegisters, newCust, currMin, multPrint, multData );
            if (addedToRegister == false) 
            {
                //find shortest queue
                int shortestQueue;
                int shortestQueueSize=99;
                for (int i =0; i< 3; i++){
                    Queue currQueue = multQueues[i];
                    if (currQueue.getSize() < shortestQueueSize){
                        shortestQueueSize = currQueue.getSize();
                        shortestQueue =i;
                    }
                }
                //add customer to shortest queue
                multQueues[shortestQueue].enqueue(newCust);
                if (multQueues[shortestQueue].getSize() > multData.maxLineLength)
                    multData.maxLineLength = multQueues[shortestQueue].getSize();
                multPrint<<"Customer "<< newCust.customerNumber<<" added to queue "<<shortestQueue+1<<endl;
            }
        }
    }
    singleData.amountOfCustomers = custCounter-1;
    multData.amountOfCustomers = custCounter-1;

    //print statistics
    getData(singleData, singlePrint);
    getData(multData, multPrint);

} //end of main

void checkRegister(Register& reg,  Queue& line, int currentMin, ofstream& out, Statistics& data ){
    if (reg.serviceTimeComplete==currentMin){ 

            out<<"Customer "<<reg.currCustNumber<<" has left register "<<reg.regNumber<<" at minute "<<currentMin<<"\n";
        if (line.isEmpty()){
            reg.isEmpty= true;
        }
        else{
            
            CustomerData nextInLine = line.dequeue();
            //compute wait time
            int custWaitTime = currentMin - nextInLine.arrivalTime;
            data.totalWaitTime += custWaitTime;
            if (custWaitTime> data.maxWaitTime)
                data.maxWaitTime = custWaitTime;
            reg.currCustNumber = nextInLine.customerNumber;
            reg.serviceTimeComplete = currentMin + nextInLine.serviceTime;
            out<<"Customer "<<nextInLine.customerNumber<< " served by Register "<<reg.regNumber<< " starting at minute "<<currentMin<<"\n";

        }
    }
}

bool addToRegister(Register reg[], CustomerData newCust, int currMin, ofstream& out, Statistics& data){
    bool toRegister =false;
            for (int i =0; i< 3; i++){
                if (reg[i].isEmpty){
                    toRegister = true;
                    reg[i].currCustNumber= newCust.customerNumber;
                    reg[i].serviceTimeComplete = currMin + newCust.serviceTime;
                    reg[i].isEmpty = false;
                    //wait time is 0;
                    out<<"Customer "<<newCust.customerNumber<< " served by Register " << reg[i].regNumber<< " at minute " << currMin<<"\n";
                    
                    return true;

                }
            }
            return false;
}

void getData(Statistics& data, ofstream& print){
    double avg = double(data.totalWaitTime) / data.amountOfCustomers;
    
    print<<"\nAverage wait time (mins): "<<fixed<<setprecision(2) <<avg;
    print<<"\nMaximum wait time (mins): "<<data.maxWaitTime;
    print<<"\nMaximum line length: "<<data.maxLineLength;
    print<<"\n";
}