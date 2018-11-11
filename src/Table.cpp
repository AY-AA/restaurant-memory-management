//
// Created by avishai on 11/5/18.
//

#include <iostream>
#include "../include/Customer.h"
#include <vector>
#include "../include/Table.h"


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

void Table::removeCustomer(int id) {
    if (!customersList.empty()) {
        for (int i = 0; i < customersList.size(); ++i) {
            if (customersList.at(i)->getId() == id){
                customersList.erase((customersList.begin() + i));
            }
        }
    }
    if(!orderList.empty()) {
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
    if (customersList.empty()) {
        return nullptr;
    }
    for (auto customer : customersList) {
        if (customer->getId() == id) {
            return customer;
        }
    }
};

std::vector<Customer *> &Table::getCustomers() {
    return  customersList;
};

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
};


//TODO : save the orders
void Table::order(const std::vector<Dish> &menu) {
    for (auto customer: customersList) {
//        Customer* currCustomer = customer;
        std::vector<int> orders = customer->order(menu);
        for (auto order : orders) {
            OrderPair x(customer->getId(), menu.at(order));
            orderList.push_back(x);
        }
    }
};

void Table::openTable(){
    open = true;
};

//Todo: Needs to check if erase method is working properly, memory wise.
void Table::closeTable() {
    open = false;
    for (auto customer : customersList) {
        delete customer;
    }
    orderList.clear();
    customersList.clear();
};

int Table::getBill() {
    int billSum = 0;
    for (auto order : orderList) {
        billSum += order.second.getPrice();
    }
    return billSum;
};

bool Table::isOpen() {
    return open;
};
