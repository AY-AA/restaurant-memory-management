//
// Created by alex on 11/5/18.
//
#include <iostream>
#include <vector>

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
#include "Dish.h"


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


Order::Order(int id) : tableId(id) {};


//TODO :  check if customer is being deleted from restaurant's table's vector
void Order::act(Restaurant &restaurant)
{
    Table *tmpTable = restaurant.getTable(tableId);
    if (tmpTable->isOpen())
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