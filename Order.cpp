#include "Order.h"
#include <string>

using std::string;

// Default constructor
Order::Order(){}

//  constructor
Order::Order(const string& id, char type, int numShares, double sharePrice, int time)
    : order_id(id), order_type(type), quantity(numShares), price(sharePrice), arrival_time(time) {}
