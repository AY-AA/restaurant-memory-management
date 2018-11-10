#include <iostream>
#include "../include/Restaurant.h"
#include "../include/Customer.h"
#include "../include/Table.h"
#include "../include/Dish.h"
#include <vector>

using namespace std;

Restaurant* backup = nullptr;


int main(int argc, char** argv){
    string configurationFile = "../config.txt";
    Restaurant rest(configurationFile);
    //    rest.start();


    // ------ TEST 1 ----------

    Customer* x = new VegetarianCustomer("Alex",10);
    Customer* y = new VegetarianCustomer("Avishai",1);
    Customer* z = new VegetarianCustomer("Shaked",2);
    std::vector<Customer*> customers = {x,y,z};
    //    customers.push_back()

    OpenTable open(2,customers);
    std::cout << open.toString() << endl;
    open.act(rest);

    Order order(2);
    std::cout << order.toString() << endl;
    order.act(rest);


    delete x;
    delete y;
    delete z;




    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }
    return 0;
}








