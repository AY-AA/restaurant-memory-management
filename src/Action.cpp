//
// Created by alex on 11/5/18.
//

#include <iostream>
#include <vector>
#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"
#include "../include/Dish.h"

// ------------------ BaseAction

BaseAction::BaseAction()
{
    status = ActionStatus::PENDING;
};

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
    status = ActionStatus::ERROR;
};

std::string BaseAction::getErrorMsg() const
{
    if (!errorMsg.empty())
        return errorMsg;
    return "";
};



// ------------------ OpenTable

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList) {};

void OpenTable::act(Restaurant &restaurant){
    Table* tableToOpen = restaurant.getTable(tableId);
    if(tableToOpen != nullptr && tableToOpen->getCapacity() > customers.size() && !tableToOpen->isOpen()) {
        tableToOpen->openTable();
        for (int i = 0; i < customers.size(); ++i) {
            tableToOpen->addCustomer(customers.at(i));
        }
        complete();
    }
    else{
        error("Table does not exist or is already open");
        std::cout<< getErrorMsg();
    }
}

std::string OpenTable::toString() const{
    std::string msg("open " + std::to_string(tableId ) + " ");
    for (int i = 0; i < customers.size(); ++i) {
        msg.append(customers.at(i)->toString() + " ");
    }
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else if (getStatus() == ActionStatus::ERROR)
    {
        msg.append("Error: ");
        msg.append(getErrorMsg());
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
}



// ------------------ Order

Order::Order(int id) : tableId(id) {};

void Order::act(Restaurant &restaurant)
{
    Table *tmpTable = restaurant.getTable(tableId);
    if (tmpTable != nullptr && tmpTable->isOpen())
    {
        tmpTable->order(restaurant.getMenu());
        std::vector<OrderPair> orders = tmpTable->getOrders();
        for (int i = 0; i < orders.size(); ++i)
        {
            std::pair<int, Dish> currPair = orders.at(i);
//            std::string customersName = restaurant.getTable(tableId)->getCustomer(currPair.first)->getName();
            Customer* tmpCustomer = restaurant.getTable(tableId)->getCustomer(currPair.first);
            std::cout << tmpCustomer->getName() << " ordered " << currPair.second.getName() << std::endl;
        }
    }
    else
    {
        this->error("Table does not exist or is not open");
        std::cout << getErrorMsg();
    }
};

std::string Order::toString() const
{
    std::string msg("order " + std::to_string(tableId ) + " ");

    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else if (getStatus() == ActionStatus::ERROR)
    {
        msg.append("Error: ");
        msg.append(getErrorMsg());
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ MoveCustomer

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
        error("Cannot move customer");
        std::cout << getErrorMsg();
    }
};

std::string MoveCustomer::toString() const{
    std::string msg("move " + std::to_string(srcTable) + " " + std::to_string(dstTable) + " " + std::to_string(id) + " ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else if (getStatus() == ActionStatus::ERROR)
    {
        msg.append("Error: ");
        msg.append(getErrorMsg());
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
}



// ------------------ Close

Close::Close(int id):tableId(id) {};

void Close::act(Restaurant &restaurant) {
    Table* tableToClose = restaurant.getTable(tableId);
    if(tableToClose != nullptr && tableToClose->isOpen()){
        std::string stat = "Table " + std::to_string(tableId) + " was closed.";
        stat.append("Bill: " + std::to_string(tableToClose->getBill()));
        std::cout << stat << std::endl;
        tableToClose->closeTable();
    }
    else{
        error("Table does not exist or is not open");
        std::cout<< getErrorMsg() << std::endl;
    }
};

std::string Close::toString() const{
    std::string msg("close " + std::to_string(tableId) + " ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else if (getStatus() == ActionStatus::ERROR)
    {
        msg.append("Error: ");
        msg.append(getErrorMsg());
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ CloseAll

CloseAll::CloseAll() {};

void CloseAll::act(Restaurant &restaurant) {
    int restCapacity = restaurant.getNumOfTables();
    if(!restCapacity > 0)
    {
        return;
    }

    for (int i = 0; i < restCapacity; ++i) {
        Table* currTable = restaurant.getTable(i);

        if (currTable->isOpen())
        {
            std::string stat = "Table " + std::to_string(i) + " was closed.";
            stat.append("Bill: " + std::to_string(currTable->getBill()));
            std::cout << stat << std::endl;
            currTable->closeTable();
        }
    }
};

std::string CloseAll::toString() const
{
    std::string msg("closeall ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ PrintMenu

PrintMenu::PrintMenu() {};

void PrintMenu::act(Restaurant &restaurant) {
    std::vector<Dish> menu = restaurant.getMenu();
    for (int i = 0; i < menu.size(); ++i) {
        std::cout  << menu.at(i).getName() << " " << menu.at(i).getType() << " " << menu.at(i).getPrice() << std::endl;
    }
};

std::string PrintMenu::toString() const {
    std::string msg("menu " );
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ PrintTableStatus

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

std::string PrintTableStatus::toString() const
{
    std::string msg("status " + std::to_string(tableId) + " ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ PrintActionsLog

PrintActionsLog::PrintActionsLog() {};

void PrintActionsLog::act(Restaurant &restaurant) {
    std::vector<BaseAction*> actsLog = restaurant.getActionsLog();
    for (int i = 0; i < actsLog.size(); ++i) {
        std::cout << actsLog.at(i)->toString() << std::endl;
    }
};

std::string PrintActionsLog::toString() const
{
    std::string msg("log " );
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ BackupRestaurant

BackupRestaurant::BackupRestaurant() {};

void BackupRestaurant::act(Restaurant &restaurant)
{

};

std::string BackupRestaurant::toString() const
{
    std::string msg("backup ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};



// ------------------ RestoreResturant

RestoreResturant::RestoreResturant(){};

void RestoreResturant::act(Restaurant &restaurant)
{

};

std::string RestoreResturant::toString() const
{
    std::string msg("restore ");
    if (getStatus() == ActionStatus::COMPLETED)
    {
        msg.append("Completed");
    }
    else if (getStatus() == ActionStatus::ERROR)
    {
        msg.append("Error: ");
        msg.append(getErrorMsg());
    }
    else
    {
        msg.append("Pending");
    }
    return msg;
};