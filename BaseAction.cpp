//
// Created by alex on 11/5/18.
//

#include "Action.h"
#include <vector>
#include "Table.h"
#include "Restaurant.h"


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

