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


//OpenTable

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList) {};

void OpenTable::act(Restaurant &restaurant){
    Table* tableToOpen = restaurant.getTable(tableId);
    if(tableToOpen != nullptr && tableToOpen->getCapacity() >= customers.size() && !tableToOpen->isOpen()) {
        tableToOpen->openTable();
        for (int i = 0; i < customers.size(); ++i) {
            tableToOpen->addCustomer(customers.at(i));
        }
        complete();
    }
    else{
        (*this).error("Table does not exist or is already open");
        std::cout<< getErrorMsg();
    }
}

std::string OpenTable::toString() const{
    //Todo implement!
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
        std::cout << getErrorMsg();
    }
};


// TODO :: insert correct string
std::string Order::toString() const
{
    return std::string ("");
};


//MoveCustomer

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
        (*this).error("Cannot move customer");
        std::cout << getErrorMsg();
    }
};

std::string MoveCustomer::toString() const{
    //Todo: Implement!
}


//Close

Close::Close(int id):tableId(id) {};

void Close::act(Restaurant &restaurant) {
    Table* tableToClose = restaurant.getTable(tableId);
    if(tableToClose != nullptr && tableToClose->isOpen()){
        std::cout << toString() + std::to_string(tableToClose->getBill()) + "\n";
        tableToClose->closeTable();
    }
    else{
        error("Table does not exist or is not open");
        std::cout<< getErrorMsg();
    }
};

std::string Close::toString() const{
   std::string str = "Table " + std::to_string(tableId) + "was closed. " + "Bill";
   return str;
};


//CloseAll

CloseAll::CloseAll() {};

void CloseAll::act(Restaurant &restaurant) {
    int restCapacity = restaurant.getNumOfTables();
    if(restCapacity > 0) {
        for (int i = 0; i < restCapacity; ++i) {
            restaurant.getTable(i)->closeTable();
        }
    }
    else{
        //Todo: need to close restaurant. bool open = false.
    }
};


//PrintMenu

PrintMenu::PrintMenu() {};

void PrintMenu::act(Restaurant &restaurant) {
    std::vector<Dish> menu = restaurant.getMenu();
    for (int i = 0; i < menu.size(); ++i) {
        std::cout  << menu.at(i).getName() << " " << menu.at(i).getType() << " " << menu.at(i).getPrice() << "\n";
    }
};

std::string PrintMenu::toString() const {
    return ""; //Todo:check why this method is necessary.
};


//PrintTableStatus

PrintTableStatus::PrintTableStatus(int id): tableId(id) {};

void PrintTableStatus::act(Restaurant &restaurant) {
    Table* tableToPrint = restaurant.getTable(tableId);
    if(tableToPrint == nullptr){
        return;
    }
    if(!tableToPrint->isOpen()){
        std::cout << "Table " << tableId << "status: " << "closed";
    }
    else{
        std::vector<Customer *>& tmpCust = tableToPrint->getCustomers();
        std::vector<OrderPair>& tmpOrds = tableToPrint->getOrders();
        std::cout << "Table " << tableId << "status: " << "open" << "\n";
        std::cout << "Customers:" << "\n";
        for (int i = 0; i < tmpCust.size(); ++i) {
            std::cout << tmpCust.at(i)->getId() << tmpCust.at(i)->getName() << "\n";
        }
        std::cout << "Orders:" << "\n";
        for (int i = 0; i < tmpCust.size(); ++i) {
            std::cout << tmpOrds.at(i).second.getName() << " " << tmpOrds.at(i).second.getPrice() << "NIS" << " " <<tmpOrds.at(i).first;
        }
    }
};


//PrintActionsLog

PrintActionsLog::PrintActionsLog() {};

void PrintActionsLog::act(Restaurant &restaurant) {
    std::vector<BaseAction*> actsLog = restaurant.getActionsLog();
    for (int i = 0; i < actsLog.size(); ++i) {
    }
};





























