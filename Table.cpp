//
// Created by avishai on 11/5/18.
//

#include <iostream>
#include "Customer.cpp"

#include <vector>

#include "Table.h"




Table::Table(int t_capacity)
{
    capacity = t_capacity;
};
int Table::getCapacity() const
{
    return capacity;
};
void Table::addCustomer(Customer* customer)
{


};
void Table::removeCustomer(int id)
{

};
Customer* Table::getCustomer(int id)
{

};
std::vector<Customer*>& Table::getCustomers()
{

};
std::vector<OrderPair>& Table::getOrders()
{

};
void Table::order(const std::vector<Dish> &menu)
{

};
void Table::openTable()
{

};
void Table::closeTable()
{

};
int Table::getBill()
{
    int bill = 0;
    for (int i = 0; i < orderList.size(); ++i) {

    }
};
bool Table::isOpen()
{
    return open;
};
