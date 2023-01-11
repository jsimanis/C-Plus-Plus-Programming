//Nick Dunne S2021
//CustomerData struct for the queue program

struct CustomerData {
    int customerNumber;
    int arrivalTime;
    int serviceTime;

    //Constructors
    CustomerData() {}
    CustomerData(int cust, int arr, int serv) : customerNumber(cust), arrivalTime(arr), serviceTime(serv) {}
};