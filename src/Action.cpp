#include <vector>
#include "../include/Action.h"
#include <string>
#include <iostream>
#include "../include/Customer.h"
#include "../include/Restaurant.h"
#include <utility>
#include <iomanip>
extern Restaurant* backup;
using namespace std;

BaseAction::BaseAction():status(PENDING){}
ActionStatus BaseAction:: getStatus() const
{
    return status;
}
void BaseAction:: setStatus(ActionStatus sts)
{
    status = sts;
}
void BaseAction:: setErrorMsg(string ermsg)
{
    errorMsg = ermsg;
}
BaseAction::BaseAction(const BaseAction & baseaction)
{
    errorMsg = baseaction.errorMsg;
    status = baseaction.status;
}
BaseAction & BaseAction::operator = (const BaseAction & bs)
{
    errorMsg = bs.errorMsg;
    status = bs.status;
    return *this;
}

void BaseAction:: complete()
{
    status = COMPLETED;
}

void BaseAction:: error(std::string _errorMsg)
{
    errorMsg = _errorMsg;
    status = ERROR;
}
std::string BaseAction:: getErrorMsg() const
{
    return ("Error:" + errorMsg );
}
std::string BaseAction:: getErrorMsg2() const
{
    return (errorMsg);
}

OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList) {}

OpenTable::~OpenTable()
{
    for(unsigned int i = 0 ; i <customers.size() ; i++)
    {
        delete(customers[i]);
    }
}

OpenTable::OpenTable(const OpenTable & opentable):BaseAction(opentable), tableId(opentable.tableId), customers()
{
    for(unsigned int i = 0 ; i < opentable.customers.size() ; i ++)
    {
        customers.push_back((opentable.customers[i]->clone()));
    }

}

void OpenTable::act(Restaurant &restaurant)
{
    if (tableId > restaurant.getNumOfTables()||(restaurant.getTable(tableId))->isOpen() == true )
    {
        input = "open " + to_string(tableId) + ' ';
        for(unsigned int i = 0 ; i <customers.size() ; i++)
        {
            input += customers[i]->toString()+' ';
        }
        input+= "Error: Table does not exist or is already open";
        for(unsigned int i = 0; i<customers.size() ; i++)
        {
            delete(customers[i]);
        }
        customers.clear();
        error(" Table does not exist or is already open");
        cout << "Error: Table does not exist or is already open" << endl;
    }
    else
    {
        restaurant.getTable(tableId)->openTable();
        for(unsigned int i = 0 ; i < customers.size() ; i ++)
        {
            restaurant.getTable(tableId)->addCustomer(customers[i]->clone());
        }
        restaurant.getTable(tableId)->openTable();
        complete();
    }
}

std::string OpenTable::toString() const
{
    if(this->getStatus() == 2)
    {
        return input;
    }
    string x = "open " + to_string(tableId) + ' ';
    for (unsigned int i = 0; i < customers.size(); i++) {
        x += customers[i]->toString() + ' ';
    }
    x += this->getErrorMsg();
    if (this->getStatus() == 1)
        x += "Completed";
    return x;
}

OpenTable *OpenTable:: clone () const
{
    vector<Customer*> vc;
    for(unsigned int i = 0 ; i < this->customers.size() ; i ++)
    {
        vc.push_back(this->customers[i]->clone());
    }
    OpenTable *ot = new OpenTable(this->tableId, vc);
    ot->setErrorMsg(this->getErrorMsg2());
    ot->setStatus(this->getStatus());
    return ot;
}
Order::Order (int id):tableId(id){}

Order::Order(const Order & order):BaseAction(order), tableId(order.tableId){}

Order::~Order() {}

void Order::act(Restaurant &restaurant)
{
    std::string nameCustomer,nameDish;
    if (tableId > restaurant.getNumOfTables() || (restaurant.getTable(tableId))->isOpen() == false)
    {
        error("Table does not exist or is already open");
        cout <<  "Table does not exist or is already open" << endl;
    }
    else (restaurant.getTable(tableId))->order(restaurant.getMenu());
    {
        int d;
        d = restaurant.getTable(tableId)->num_of_orders;
        std::vector<OrderPair> &CustomerOrders = ((restaurant.getTable(tableId))->getOrders());
        for (unsigned int i = d; i < CustomerOrders.size(); i++)
        {
            nameCustomer = ((restaurant.getTable(tableId))->getCustomer((CustomerOrders[i]).first))->getName();
            nameDish = ((CustomerOrders[i]).second.getName());
            cout << (nameCustomer + " ordered " + nameDish) << endl;
            restaurant.getTable(tableId)->num_of_orders++;
        }
        complete();
    }
}
std::string Order::toString() const
{
    if (this->getStatus() == 2)
        return "order " + to_string(tableId) + ' ' + "Error: Table does not exist or is already open";
    if (this->getStatus() == 1)
        return "order " + to_string(tableId) + ' ' + "Completed";
    return "";
}

Order *Order:: clone () const
{
    Order *ord = new Order (this->tableId);
    ord->setErrorMsg(this->getErrorMsg2());
    ord->setStatus(this->getStatus());
    return ord;
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTable(src),dstTable(dst),id(customerId){}

MoveCustomer::MoveCustomer(const MoveCustomer & movecustomer):BaseAction(movecustomer), srcTable(movecustomer.srcTable), dstTable(movecustomer.dstTable), id(movecustomer.id) {}

MoveCustomer::~MoveCustomer() {}

void MoveCustomer:: act(Restaurant &restaurant)
{
    int idOfDish;
    vector<OrderPair> vc;
    if(dstTable > restaurant.getNumOfTables() || (int)((restaurant.getTable(dstTable)->getCustomers()).size()) > restaurant.getTable(dstTable)->getCapacity() || restaurant.getTable(dstTable)->isOpen() == false || restaurant.getTable(srcTable)->isOpen() == false)
    {
        this->error("Cannot move customer");
        this->toString();
    }
    else
    {
        restaurant.getTable(dstTable)->addCustomer(restaurant.getTable(srcTable)->getCustomer(id));
        for (unsigned int k = 0; k < restaurant.getTable(srcTable)->getOrders().size(); k++)
            vc.emplace_back(restaurant.getTable(srcTable)->getOrders()[k]);

        for (unsigned int i = 0; i < restaurant.getTable(srcTable)->getOrders().size(); i++)
        {
            idOfDish = restaurant.getTable(srcTable)->getOrders()[i].second.getId();
            if (restaurant.getTable(srcTable)->getOrders()[i].first == id)
            {
                for (unsigned int j = 0; j < restaurant.getMenu().size(); j++)
                {
                    if (restaurant.getMenu()[j].getId() == idOfDish)
                    {
                        restaurant.getTable(dstTable)->getOrders().emplace_back(id, restaurant.getMenu()[j]);//enter order to new table
                        restaurant.getTable(dstTable)->num_of_orders++;
                        restaurant.getTable(srcTable)->num_of_orders--;
                    }
                }
            }
        }
        restaurant.getTable(srcTable)->getOrders().clear();
        for (unsigned int i = 0; i < vc.size(); i++) {
            if (id != vc[i].first)
                restaurant.getTable(srcTable)->getOrders().emplace_back(vc[i].first, vc[i].second);
        }
        restaurant.getTable(srcTable)->removeCustomer(id);
        if (((restaurant.getTable(srcTable))->getCustomers()).size() == 0)//if we can close the old table
        {
            restaurant.getTable(srcTable)->closeTable();
        }
        complete();
    }
}

std::string MoveCustomer::toString() const
{
    if (this->getStatus() == 2)
        return "order " + to_string(dstTable) + ' ' + "Error: Table does not exist or is already open";
    if (this->getStatus() == 1)
        return "move " + to_string(srcTable) + ' ' + to_string(dstTable) + ' ' + to_string(id) + " Completed";
    return "";
}

MoveCustomer *MoveCustomer:: clone () const
{
    MoveCustomer *mvc = new MoveCustomer (this->srcTable, this->dstTable, this->id);
    mvc->setErrorMsg(this->getErrorMsg2());
    mvc->setStatus(this->getStatus());
    return mvc;
}


Close::Close(const Close & close): tableId(close.tableId){}

Close::~Close() {}

Close::Close (int id):tableId(id){}
void Close::act(Restaurant &restaurant)
{
    if (tableId > restaurant.getNumOfTables() || (restaurant.getTable(tableId))->isOpen() == false)
    {
        error("Table does not exist or is already open");
    }
    else
    {
//                if(restaurant.backup != true)
        cout << "Table " + to_string(tableId) +" was closed. Bill " + to_string(restaurant.getTable(tableId)->getBill()) +"NIS" <<endl;
        (restaurant.getTable(tableId))->closetable2();
        complete();
    }
}
std::string Close::toString() const
{
    if (this->getStatus() == 2)
        return "close " + to_string(tableId) + ' ' + "Error: Table does not exist or is already open";
    if (this->getStatus() == 1)
        return "close " + to_string(tableId) + ' ' + "Completed";
    return "";
}

Close *Close:: clone () const
{
    Close *cls = new Close (this->tableId);
    cls->setErrorMsg(this->getErrorMsg2());
    cls->setStatus(this->getStatus());
    return cls;
}

CloseAll::CloseAll (){}

CloseAll::CloseAll(const CloseAll & closeall):BaseAction(closeall){}

CloseAll::~CloseAll() {}

void CloseAll::act(Restaurant &restaurant)
{
    for (int i = 0; i < restaurant.getNumOfTables(); ++i)
    {
        Close close = Close(i);
        close.act(restaurant);
    }
    complete();
}


std::string CloseAll::toString() const
{
    return "closeall";
}

CloseAll *CloseAll:: clone () const
{
    CloseAll *clsa = new CloseAll ();
    clsa->setErrorMsg(this->getErrorMsg2());
    clsa->setStatus(this->getStatus());
    return clsa;
}

PrintMenu::PrintMenu (){}

PrintMenu::PrintMenu(const PrintMenu & printmenu):BaseAction(printmenu){}

PrintMenu::~PrintMenu() {}

void PrintMenu::act(Restaurant &restaurant)
{
    string x;
    int y;
    for(unsigned int i = 0; i < restaurant.getMenu().size() ; i ++)
    {
        x += restaurant.getMenu()[i].getName() + ' ';
        y = restaurant.getMenu()[i].getType();
        if(y == 0)
            x += "VEG ";
        if(y == 1)
            x += "SPC ";
        if(y == 2)
            x += "BVG ";
        if(y == 3)
            x += "ALC ";
        x += to_string(restaurant.getMenu()[i].getPrice());
        cout <<  x <<endl;
        x = "";
    }
    complete();
}
std::string PrintMenu::toString() const
{
    if (this->getStatus() == 1)
        return "menu Completed";
    return "";
}

PrintMenu *PrintMenu:: clone () const
{
    PrintMenu *prtm = new PrintMenu ();
    prtm->setErrorMsg(this->getErrorMsg2());
    prtm->setStatus(this->getStatus());
    return prtm;
}

PrintTableStatus::PrintTableStatus (int id):tableId(id){}

PrintTableStatus::PrintTableStatus(const PrintTableStatus & printtablestatus):BaseAction(printtablestatus), tableId(printtablestatus.tableId){}

PrintTableStatus::~PrintTableStatus() {}

void PrintTableStatus::act(Restaurant &restaurant)
{
    if(restaurant.getTable(tableId)->isOpen() == 0)
        cout << "Table " + to_string(tableId) + ' ' + "status: closed"  << endl;
    else
    {
        if (restaurant.getTable(tableId)->isOpen() == 1)
            cout << "Table " + to_string(tableId) + ' ' + "status: open" << endl;
        cout << "Customers:" << endl;
        for (unsigned int i = 0; i < restaurant.getTable(tableId)->getCustomers().size(); i++) {
            cout << to_string(restaurant.getTable(tableId)->getCustomers()[i]->getId()) + ' ' +
                    (restaurant.getTable(tableId)->getCustomers()[i]->getName()) << endl;
        }
        cout << "Orders:" << endl;
        for (unsigned int j = 0; j < restaurant.getTable(tableId)->getOrders().size(); j++)
        {
            cout << (restaurant.getTable(tableId)->getOrders()[j].second.getName()) + ' ' + to_string(restaurant.getTable(tableId)->getOrders()[j].second.getPrice()) + "NIS " + to_string(restaurant.getTable(tableId)->getOrders()[j].first) << endl;
        }
        cout << "Current Bill: " + to_string(restaurant.getTable(tableId)->getBill()) + "NIS" << endl;

    }
    complete();

}
std::string PrintTableStatus::toString() const
{
    if (this->getStatus() == 1)
        return "status " + to_string(tableId) + ' ' + "Completed";
    return "";
}
PrintTableStatus *PrintTableStatus:: clone () const
{
    PrintTableStatus *prts = new PrintTableStatus(this->tableId);
    prts->setErrorMsg(this->getErrorMsg2());
    prts->setStatus(this->getStatus());
    return prts;
}
PrintActionsLog::PrintActionsLog (){}

PrintActionsLog::PrintActionsLog(const PrintActionsLog & printactionlog):BaseAction(printactionlog){}

PrintActionsLog::~PrintActionsLog() {}

void PrintActionsLog::act(Restaurant &restaurant)
{
    for(unsigned int i = 0; i < restaurant.getActionsLog().size() ; i ++)
        cout << restaurant.getActionsLog()[i]->toString() <<endl;
    complete();
}
std::string PrintActionsLog::toString() const
{
    if (this->getStatus() == 1)
        return "log Completed";
    return "";
}
PrintActionsLog *PrintActionsLog:: clone () const
{
    PrintActionsLog *actl = new PrintActionsLog();
    actl->setErrorMsg(this->getErrorMsg2());
    actl->setStatus(this->getStatus());
    return actl;
}


BackupRestaurant::BackupRestaurant (){}

BackupRestaurant::~BackupRestaurant(){}

void BackupRestaurant::act(Restaurant &restaurant)
{
    if (backup == nullptr)
    {
        backup = new Restaurant(restaurant);
    }
    *backup = restaurant;

    complete();
}
std::string BackupRestaurant::toString() const
{
    if (this->getStatus() == 1)
        return "Backup Completed";
    return "";
}
BackupRestaurant *BackupRestaurant:: clone () const
{
    BackupRestaurant *bcp = new BackupRestaurant();
    bcp->setErrorMsg(this->getErrorMsg2());
    bcp->setStatus(this->getStatus());
    return bcp;
}
RestoreResturant::RestoreResturant (){}

RestoreResturant::~RestoreResturant(){}

void RestoreResturant::act(Restaurant &restaurant)
{
    if( backup == nullptr)
    {
        error("No backup available");
    }
    else
    {
        restaurant = *backup;
        restaurant.isrestore = true;
        complete();
    }
}
std::string RestoreResturant::toString() const
{
    if (this->getStatus() == 1)
        return "Restore Completed";
    return "";
}
RestoreResturant *RestoreResturant:: clone () const
{
    RestoreResturant *rst = new RestoreResturant();
    rst->setErrorMsg(this->getErrorMsg2());
    rst->setStatus(this->getStatus());
    return rst;
}








