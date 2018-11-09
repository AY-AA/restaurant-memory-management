//
// Created by alex on 11/5/18.
//

#include <iostream>
#include <vector>
#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include "Dish.h"

BaseAction::BaseAction() {};

ActionStatus BaseAction::getStatus() const
{
    return status;
};

void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
};

void BaseAction::error(std::string errorMsg)
{
    this->errorMsg = errorMsg;
    this->status = ActionStatus::ERROR;
};

std::string BaseAction::getErrorMsg() const
{
    if (!errorMsg.empty())
        return errorMsg;
    return NULL;
};

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList) {};

void OpenTable::act(Restaurant &restaurant){
    Table* tableToOpen = restaurant.getTable(tableId);
    if(tableToOpen != nullptr && tableToOpen->getCapacity() >= customers.size() && !tableToOpen->isOpen()) {
        tableToOpen->openTable();
        for (int i = 0; i < customers.size(); ++i) {
            tableToOpen->addCustomer(customers.at(i));
        }
    }
    else{
        std::cout<< "Table does not exist or is already open";
    }
}

std::string OpenTable::toString() const{
    //Todo: Implement!
}


//Order

Order::Order(int id) : tableId(id) {};


//TODO :  check if customer is being deleted from restaurant's table's vector
void Order::act(Restaurant &restaurant)
{
    Table *tmpTable = restaurant.getTable(tableId);
    if (tmpTable != nullptr)
    {
        tmpTable->order(restaurant.getMenu());
        std::vector<OrderPair> orders = tmpTable->getOrders();
        for (int i = 0; i < orders.size(); ++i)
        {
            std::pair<int, Dish> currPair = orders.at(i);
            Customer* tmpCustomer = restaurant.getTable(tableId)->getCustomer(currPair.first);
            std::cout << tmpCustomer->getName() << " ordered " << currPair.second.getName() << std::endl;
            delete tmpCustomer;
        }
    }
    else
    {
        this->error("Table does not exist or is not open");
    }

};


// TODO :: insert correct string
std::string Order::toString() const
{
    return std::string ("");
};

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTable(src), dstTable(dst), id(customerId) {};

void MoveCustomer::act(Restaurant &restaurant) {
    Table* srcT = restaurant.getTable(srcTable);
    Table* dstT = restaurant.getTable(dstTable);
    Customer *c = srcT->getCustomer(id);
    if(srcT != nullptr && srcT->isOpen() && dstT != nullptr && dstT->isOpen() && c != nullptr && dstT->getCustomers().size() < dstT->getCapacity()) {
        srcT->removeCustomer(id);
        dstT->addCustomer(c);
    }
    else{
        std::cout<< "Cannot move customer";
    }
};


std::string MoveCustomer::toString() const{
    //Todo: Implement!
}
