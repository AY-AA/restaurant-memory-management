#ifndef RESTAURANT_H_
#define RESTAURANT_H_
#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();
    Restaurant(const std::string &configFilePath);
    Restaurant(const Restaurant& restaurant);
    Restaurant & operator = (const Restaurant & restaurant);
    Restaurant( Restaurant&& restaurant);
    Restaurant & operator= ( Restaurant && restaurant);
    ~Restaurant();
    void start();
    void copy(const Restaurant& restaurant);
    int getNumOfTables() const;
    Table* getTable(int ind);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    void openTable(std::string id , std::vector<std::string> data);
    std::vector<Dish>& getMenu();
//	bool backup;
    bool isrestore = false;
private:
    bool open = false;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    int cus_id = 0;
};

#endif