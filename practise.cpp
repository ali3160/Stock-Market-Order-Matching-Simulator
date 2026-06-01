void Market::print_queue2(
    const priority_queue<Order, vector<Order>, CompareByArrivalTime>& unex_buy_queue,
    const priority_queue<Order, vector<Order>, CompareByArrivalTime>& unex_sell_queue,
    double last_traded_price) {
    
    auto copy_buy_queue = unex_buy_queue;
    auto copy_sell_queue = unex_sell_queue;

    int col1Header = 31;
    int col1Body = 10;
    int col2Body = 10;
    int col3Body = 11;

    int col2Header = 31;
    int col4Body = 10;
    int col5Body = 10;
    int col6Body = 11;
    void print_queue2(const priority_queue<Order, vector<Order>, CompareByArrivalTime>& unex_buy_queue,
                 const priority_queue<Order, vector<Order>, CompareByArrivalTime>& unex_sell_queue,
                 double last_traded_price);
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

    cout << setw(col1Header) << "==============================="
         << setw(col2Header) << "===============================" << endl << endl;
};


template <typename Queue>
void Market::print_queue(const Queue& queue) {
    // temp variable
    auto copy_queue = queue;
    int counter=1;
    // loop through the queue
    while (!copy_queue.empty()) {
        // print to the console
        cout << counter<<". ";
        Order order_queue = copy_queue.top();
        cout << order_queue.order_id<<"  " ;
        if (order_queue.price == -1) {cout << "M" << "   ";}
         else {cout << order_queue.price << "   ";}
         
        cout << order_queue.quantity << " shares  ";
        copy_queue.pop();
        counter++;
    }
    cout << "        ";
    
}

    template <typename Queue>
    void print_queue(const Queue& queue) ;