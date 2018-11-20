#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"


enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

//Forward declaration
class Restaurant;

class BaseAction{
public:
    BaseAction();
    BaseAction(const BaseAction & baseaction);
    virtual ~ BaseAction() = default;
    BaseAction & operator = (const BaseAction & bs);
    ActionStatus getStatus() const;
    void setStatus(ActionStatus sts) ;
    void setErrorMsg(string ermsg) ;
    virtual void act(Restaurant& restaurant) = 0;
    virtual std::string toString() const = 0;
    virtual BaseAction* clone() const = 0;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
    std::string getErrorMsg2() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTable : public BaseAction {
public:
    OpenTable(int id, std::vector<Customer *> &customersList);
    OpenTable(const OpenTable & opentable);
    virtual ~OpenTable() ;
    OpenTable & operator = (const OpenTable & op);
    void act(Restaurant &restaurant);
    std::string toString() const;
    OpenTable* clone () const;
    string input;
    int typeAction=0;
private:
    const int tableId;
    std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    Order(const Order & order);
    virtual ~Order();
    void act(Restaurant &restaurant);
    std::string toString() const;
    Order* clone () const;

private:
    const int tableId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    MoveCustomer(const MoveCustomer & movecustomer);
    virtual ~MoveCustomer();
    void act(Restaurant &restaurant);
    std::string toString() const;
    MoveCustomer* clone () const;

private:
    const int srcTable;
    const int dstTable;
    const int id;
};

class Close : public BaseAction {
public:
    Close(int id);
    Close(const Close & close);
    virtual ~Close();
    void act(Restaurant &restaurant);
    std::string toString() const;
    Close* clone () const;

private:
    const int tableId;
};

class CloseAll : public BaseAction {
public:
    CloseAll();
    CloseAll(const CloseAll & closeall);
    virtual ~CloseAll();
    void act(Restaurant &restaurant);
    std::string toString() const;
    CloseAll* clone () const;

//	void deletebackup();
private:
};


class PrintMenu : public BaseAction {
public:
    PrintMenu();
    PrintMenu(const PrintMenu & printmenu);
    virtual ~PrintMenu();
    void act(Restaurant &restaurant);
    std::string toString() const;
    PrintMenu* clone () const;


private:
};


class PrintTableStatus : public BaseAction {
public:
    PrintTableStatus(int id);
    PrintTableStatus(const PrintTableStatus & printtablestatus);
    virtual ~PrintTableStatus();
    void act(Restaurant &restaurant);
    std::string toString() const;
    PrintTableStatus* clone () const;


private:
    const int tableId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    PrintActionsLog(const PrintActionsLog & printactionlog);
    virtual ~PrintActionsLog();
    void act(Restaurant &restaurant);
    std::string toString() const;
    PrintActionsLog* clone () const;


private:
};


class BackupRestaurant : public BaseAction {
public:
    BackupRestaurant();
    void act(Restaurant &restaurant);
    virtual ~BackupRestaurant();
    std::string toString() const;
    BackupRestaurant* clone () const;


private:
};


class RestoreResturant : public BaseAction {
public:
    RestoreResturant();
    void act(Restaurant &restaurant);
    virtual ~RestoreResturant();
    std::string toString() const;
    RestoreResturant* clone () const;

};


#endif