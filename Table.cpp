//
// Created by avishai on 11/5/18.
//

#include <iostream>
#include "Customer.cpp"
#include <vector>
#include "Table.h"


Table::Table(int t_capacity) {
    capacity = t_capacity;
    open = false;
};

int Table::getCapacity() const {
    return capacity;
};

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);
};

//Todo: Needs to check if erase method is working properly, memory wise.
//Todo: if its not ok, create a new vector and copy to it. afterword clear the first one.
void Table::removeCustomer(int id) {
    if (customersList.size() > 0) {
        for (int i = 0; i < customersList.size(); ++i) {
            if (customersList.at(i)->getId() == id){
                delete (customersList.at(i));
                customersList.at(i) = nullptr;
                customersList.erase((customersList.begin() + i));
            }
        }
    }
    if(orderList.size() > 0) {
        for (int j = 0; j < orderList.size(); ++j) {
            if (orderList.at(j).first == id) {
                orderList.back().first;
                orderList.back().second;
                orderList.pop_back();
            }
        }
    }
};

Customer *Table::getCustomer(int id) {
    if (customersList.size() > 0) {
        for (int i = 0; i < customersList.size(); ++i) {
            if (customersList.at(i)->getId() == id) {
                return customersList.at(i);
            }
        }
    }
    return nullptr;
};

std::vector<Customer *> &Table::getCustomers() {
    return  customersList;
};

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
};


//TODO : save the orders
void Table::order(const std::vector<Dish> &menu) {
    for (int i = 0; i < customersList.size(); ++i) {
        customersList.at(i)->order(menu);
    }
};

void Table::openTable(){
    open = true;
};

//Todo: Needs to check if erase method is working properly, memory wise.
void Table::closeTable() {
    open = false;
    for (int i = 0; i < customersList.size(); ++i) {
        delete customersList.at(i);
    }
    orderList.clear();
    customersList.clear();
};

int Table::getBill() {
    int billSum = 0;
    for (int i = 0; i < orderList.size(); i++) {
        billSum += orderList.at(i).second.getPrice();
    }
    return billSum;
};

bool Table::isOpen() {
    return open;
};
