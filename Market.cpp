#include "Market.h"
#include <cmath>

Market::Market(double initial_price) : last_traded_price(initial_price) {}


bool Market::CompareBuyOrder::operator()(const Order& a, const Order& b) {
   if (a.price == -1 && b.price != -1) {
                return false; // return false if older order is market order and new order is not a market order.
            }
            if (b.price == -1 && a.price != -1) {
                return true;  // return true if new order is market order and older order is not a market order.
            }

            if (a.price == b.price) {
                return a.arrival_time > b.arrival_time;  // Prioritize earlier arrivals in case of price equality
            }
            return a.price < b.price; // Higher prices for buy orders should be prioritized
        }


bool Market::CompareSellOrder::operator()(const Order& a, const Order& b) {
    if (a.price == -1 && b.price != -1) {
                return false;  // return false if older order is market order and new order is not a market order.
            }
            if (b.price == -1 && a.price != -1) {
                return true; // return true if new order is market order and older order is not a market order.
            }

            if (a.price == b.price) {
                return a.arrival_time > b.arrival_time;  // Prioritize earlier arrivals in case of price equality
            }
            return a.price > b.price; // Lower prices for sell orders should be prioritized
        }
    

bool Market::CompareByArrivalTime::operator()(const Order& a, const Order& b) {
    return a.arrival_time > b.arrival_time; // Prioritize errlier arrival.
}

void Market::execute_order(Order& buy_order, Order& sell_order) {
    double execution_price;

        if (buy_order.price == -1 && sell_order.price != -1) { 
            //check if buy order is market order and sell order is limit order
            execution_price = sell_order.price; // prioritze limit order 
        } else if (sell_order.price == -1 && buy_order.price != -1) {
             //check if sell order is market order and buy order is limit order
            execution_price = buy_order.price;// prioritze limit order 
        } else if (buy_order.price == -1 && sell_order.price == -1) {
            // Both are market orders, use the last traded price
            execution_price = last_traded_price;
        } else {
            // Both are limit orders, use the price of the older order
            if (buy_order.arrival_time < sell_order.arrival_time) {
                execution_price = buy_order.price;
            } else {
                execution_price = sell_order.price;
            }
        }

        // Calculate trade quantity, which is the smaller of the two orders' quantities
        int trade_quantity = min(buy_order.quantity, sell_order.quantity);

        // copy the ecxuted orders to the order book
        order_Book.push_back("order " + buy_order.order_id + " " + to_string(trade_quantity) +
                             " shares purchased at price " + format_price(execution_price));
        order_Book.push_back("order " + sell_order.order_id + " " + to_string(trade_quantity) +
                             " shares sold at price " + format_price(execution_price));


        // update the shares quantity
        buy_order.quantity -= trade_quantity;
        sell_order.quantity -= trade_quantity;

       // print to the console
       cout << "\nOrder Matched:"<< endl;

        cout<< buy_order.order_id << " purchased "<< trade_quantity<<" shares at price £"<< execution_price<< endl; 
        cout<< sell_order.order_id << " sold "<< trade_quantity<<" shares at price £"<< execution_price<< endl; 

        last_traded_price = execution_price; // updating last trading price

        // Only remove the order from the queue if it is fully executed
        if (buy_order.quantity == 0) {
            buy_queue.pop(); // Remove the buy order from the queue
        }
          if (buy_order.quantity > 0) {
        buy_queue.pop(); // Remove the top buy order
        buy_queue.push(buy_order); // Push the modified buy order back
    }
        if (sell_order.quantity == 0) {
            sell_queue.pop(); // Remove the sell order from the queue
        }
        if (sell_order.quantity > 0) {
        sell_queue.pop(); // Remove the top sell order
        sell_queue.push(sell_order); // Push the modified sell order back
    } 
    }

void Market::add_order(Order order) {
    static int order_counter = 0; // counter to keep track of arrival time
    order.arrival_time = order_counter++;

    if (order.order_type == 'B') {
        // if buy order add to the buy queue
        buy_queue.push(order);
    } else if (order.order_type == 'S') {
        // if sell order add to the buy queue
        sell_queue.push(order);
    }
       
    match_orders(); // check if the new order matches any erlier arrived order from the oppisite type
}

bool Market::is_match(Order& buy_order, Order& sell_order) {
    if (buy_order.price == -1 || sell_order.price == -1) {
            return true; // Market orders always match
        }
        return buy_order.price >= sell_order.price; // Limit buy orders should have higher or equal price than limit sell orders to match
    }

void Market::match_orders() {
        print_queue(buy_queue, sell_queue, last_traded_price);

        // loop through all buy and sell order and check if the new order match any previous order
    while (!buy_queue.empty() && !sell_queue.empty()) {
            
            // temp variables
            auto buy_order = buy_queue.top();
            auto sell_order = sell_queue.top();

            if (is_match(buy_order, sell_order)) {
                // if match excute the orders.
                execute_order(buy_order, sell_order);
            } else {
                break; // No more matching orders
            }

        }
    cout << setw(10) << "==============================="
     << setw(10) << "===============================" << endl << endl;    }

void Market::unexecuted_orders() {
    cout << "Unexecuted orders" << endl;
    cout << "Last trading price: £" << format_price(last_traded_price) << endl;

    // Prepare temporary queues for printing
    while (!buy_queue.empty()) {
        temp_buy_queue.push(buy_queue.top());
        buy_queue.pop();
    }
    while (!sell_queue.empty()) {
        temp_sell_queue.push(sell_queue.top());
        sell_queue.pop();
    }

    // Print to console
    cout << "Buy Orders                          Sell Orders" << endl;
    cout << "Id        Price     Quantity        Id        Price     Quantity" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Print buy and sell orders side by side
    while (!temp_buy_queue.empty() || !temp_sell_queue.empty()) {
        string buy_entry = "";
        string sell_entry = "";

        // Initialize orders
        Order buy_order, sell_order;
        bool has_buy_order = false, has_sell_order = false;

        // check buy orders if available
        if (!temp_buy_queue.empty()) {
            buy_order = temp_buy_queue.top();
            has_buy_order = true;
        }

        // check sell orders if available
        if (!temp_sell_queue.empty()) {
            sell_order = temp_sell_queue.top();
            has_sell_order = true;
        }

        //  push to order_Book based on arrival time
        if (has_buy_order && (!has_sell_order || buy_order.arrival_time <= sell_order.arrival_time)) {
            temp_buy_queue.pop();
            buy_entry = "order " + buy_order.order_id + " " + to_string(buy_order.quantity) + " shares unexecuted";
            cout << left << setw(10) << buy_order.order_id
                 << setw(10) << format_price(buy_order.price)
                 << setw(10) << buy_order.quantity;
            order_Book.push_back(buy_entry);  // Add buy order to order_Book
        } else {
            // Print empty space
            cout << setw(36) << " ";
        }

        if (has_sell_order && (!has_buy_order || sell_order.arrival_time < buy_order.arrival_time)) {
            temp_sell_queue.pop();
            sell_entry = "order " + sell_order.order_id + " " + to_string(sell_order.quantity) + " shares unexecuted";
            cout << setw(10) << sell_order.order_id
                 << setw(10) << format_price(sell_order.price)
                 << setw(10) << sell_order.quantity;
            order_Book.push_back(sell_entry);  // Add sell order to order_Book
        }

        cout << endl;
    }

    cout << endl;
}


string Market::format_price(double price) {
    ostringstream stream;
    
    if (price == -1) {
        return "M";  // Handle market price case
    }

    //  format the price to two decimal places 
    stream << fixed << setprecision(2) << price;
    
    return stream.str();

}

 void Market::print_queue(
     std::priority_queue<Order, std::vector<Order>, CompareBuyOrder> copy_buy_queue,
     std::priority_queue<Order, std::vector<Order>, CompareSellOrder> copy_sell_queue,
    double last_traded_price
){
    
    int col1Header = 31;
	int col1Body = 10;
	int col2Body = 10;
	int col3Body = 11;
	
	int col2Header = 31;
	int col4Body = 10;
	int col5Body = 10;
	int col6Body = 11;
    
    cout << left << fixed << setprecision(2);
	cout << "Last trading price: " << last_traded_price << endl;

    cout << setw(col1Header) << "-------------------------------" 
		<< setw(col2Header) << "-------------------------------" << endl;

    cout << setw(col1Header) << "Buy Orders" 
		<< setw(col2Header) << "Sell Orders" << endl;

	
	cout << setw(col1Body) << "Id" 
		<< setw(col2Body) << "Price"
		<< setw(col3Body) << "Quantity" 
		<< setw(col1Body) << "Id" 
		<< setw(col2Body) << "Price" 
		<< setw(col3Body) << "Quantity" << endl;

	cout << setw(col1Header) << "-------------------------------" 
		<< setw(col2Header) << "-------------------------------" << endl;

   while (!copy_buy_queue.empty() && !copy_sell_queue.empty()) {
    string buy_price = (copy_buy_queue.top().price == -1) ? "M" : format_price(copy_buy_queue.top().price);
    string sell_price = (copy_sell_queue.top().price == -1) ? "M" : format_price(copy_sell_queue.top().price);
    
    cout << setw(col1Body) << copy_buy_queue.top().order_id
         << setw(col2Body) << buy_price
         << setw(col3Body) << copy_buy_queue.top().quantity
         << setw(col1Body) << copy_sell_queue.top().order_id
         << setw(col2Body) << sell_price
         << setw(col3Body) << copy_sell_queue.top().quantity << endl;

    copy_buy_queue.pop();
    copy_sell_queue.pop();
}

while (!copy_buy_queue.empty()) {
    string buy_price = (copy_buy_queue.top().price == -1) ? "M" : format_price(copy_buy_queue.top().price);
    
    cout << setw(col1Body) << copy_buy_queue.top().order_id
         << setw(col2Body) << buy_price
         << setw(col3Body) << copy_buy_queue.top().quantity << endl;
    
    copy_buy_queue.pop();
}

while (!copy_sell_queue.empty()) {
    string sell_price = (copy_sell_queue.top().price == -1) ? "M" : format_price(copy_sell_queue.top().price);
    
    cout << setw(col1Header) << " "
         << setw(col4Body) << copy_sell_queue.top().order_id
         << setw(col5Body) << sell_price
         << setw(col6Body) << copy_sell_queue.top().quantity << endl;
    
    copy_sell_queue.pop();
}

}

void Market::write_to_file(const string& output_file) const {
    ofstream ofs(output_file);
    // loop through the order book (executed buy and sell orders and unexcuted orders)
    for (const auto& execution : order_Book) {
        ofs << execution << endl;
    }
    ofs.close();
}
