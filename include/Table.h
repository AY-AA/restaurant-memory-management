#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include "Customer.h"
#include "Dish.h"
using namespace std;

typedef std::pair<int, Dish> OrderPair;

class Table{
public:
    Table(int t_capacity);
    Table(const Table & talbe);
    Table & operator = (const Table & cst);
    Table( Table &&table);
    Table & operator = ( Table && tbl);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    void closetable2();
    Table* copy();
    ~Table();
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();

    ;
    int num_of_orders = 0;
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)

};


#endif