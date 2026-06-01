#include "Market.h"
// using namespace std;
// #include <string>
// #include <fstream>
// #include <iostream>

int main(int argc, char* argv[]) {
    // check if inputfile is pressent
    if (argc < 2) {
        cerr << "Error: No input file specified." << endl;
        return 1;
    }

    string input_file = argv[1];
    // add the inputfile number to the output
    string output_file = "output" + input_file.substr(5); 
    // Read the input file
    ifstream ifs(input_file);
    // check if inputfile is pressent
    if (!ifs.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    double last_traded_price;
    ifs >> last_traded_price; // add the firstline to the variable

    // Create Market object
    Market market(last_traded_price);

    string line;
    getline(ifs, line); // Skip the first line

    while (getline(ifs, line)) {
        stringstream iss(line);
        string order_id;
        char order_type;
        int quantity;
        double price = -1;

        iss >> order_id >> order_type >> quantity;
        if (iss >> price) {
            price = (price < 0) ? -1 : price;
        } else {
            price = -1; // Market order
        }
        market.add_order(Order(order_id, order_type, quantity, price));
    }

    market.unexecuted_orders();
    ifs.close();
    market.write_to_file(output_file);

    return 0;
}
