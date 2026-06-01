#ifndef ORDER_H_
#define ORDER_H_

#include <string>
using std::string;

class Order {
public:
    // Default constructor
    Order();

    // Constructor for initialization
    Order(const string& id, char type, int qty, double prc = -1, int arrivalTime = 0);

    // Member variables
    string order_id;
    char order_type;  // 'B' for Buy, 'S' for Sell
    int quantity;     // shares
    double price;     // -1 represents a market order
    int arrival_time;
};

#endif // ORDER_H_
