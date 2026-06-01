#ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "Order.h" // Include the Order header

using namespace std;

class Market {
public:
    explicit Market(double initial_price);

    void add_order(Order order);
    void unexecuted_orders();
    void write_to_file(const string& output_file) const;
    double last_traded_price;

public:
    // variable
    

    struct CompareBuyOrder { // compare buying order for the priority queue
        bool operator()(const Order& a, const Order& b);
    };

    struct CompareSellOrder { // compare selling order for the priority queue
        bool operator()(const Order& a, const Order& b);
    };

    struct CompareByArrivalTime { // compare buying and selling order by arriving time in the priority queue
        bool operator()(const Order& a, const Order& b);
    };

    priority_queue<Order, vector<Order>, CompareBuyOrder> buy_queue; // priority queue for buying order
    priority_queue<Order, vector<Order>, CompareSellOrder> sell_queue; // priority queue for selling order
    priority_queue<Order, vector<Order>, CompareByArrivalTime> temp_buy_queue; // priority queue for unexcuted buying order
    priority_queue<Order, vector<Order>, CompareByArrivalTime> temp_sell_queue; // priority queue for unexcuted selling order

    vector<string> order_Book; // contains all excutted orders and unexcuted orders 
    

    static string format_price(double price); // function to format price to two decimal points
    void execute_order(Order& buy_order, Order& sell_order); // function that execute matching orders


    void print_queue( priority_queue<Order, vector<Order>, CompareBuyOrder> buy_queue,
                  priority_queue<Order, vector<Order>, CompareSellOrder> sell_queue,
                 double last_traded_price);



    bool is_match(Order& buy_order, Order& sell_order); // check if order matches
    void match_orders();
};


#endif // MARKET_H
