#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/Restaurant.h"
#include "../include/Table.h"

Restaurant::Restaurant() = default;

Restaurant::Restaurant(const std::string &configFilePath)
{
    readFile(configFilePath);
};

void Restaurant::start()
{
    std::string userChoice;
    std::cout << "Restaurant is now open!";

    int nextId = 0;
    do{
        std::string userChoice;
        std::getline(std::cin, userChoice);
//        std::cin >> userChoice;
        std::string firstWord = userChoice.substr(0, userChoice.find(' '));
        std::vector<std::string> tableInstructions = parseInput(userChoice);

        if (firstWord == "open") {
            std::vector<Customer *> customersToAdd;
            int tableId = std::stoi(tableInstructions.at(1));
            std::string name;
            std::string type;
            for (int i = 2; i < tableInstructions.size() - 1; i++) {
                name = tableInstructions.at(i);
                type = tableInstructions.at(i + 1);
                if (type == "veg") {
                    Customer *toAdd = new VegetarianCustomer(name, nextId);
                    customersToAdd.push_back(toAdd);
                    nextId++;
                } else if (type == "spc") {
                    Customer *toAdd = new SpicyCustomer(name, nextId);
                    customersToAdd.push_back(toAdd);
                    nextId++;
                } else if (type == "chp") {
                    Customer *toAdd = new CheapCustomer(name, nextId);
                    customersToAdd.push_back(toAdd);
                    nextId++;
                } else { //alc
                    Customer *toAdd = new AlchoholicCustomer(name, nextId);
                    customersToAdd.push_back(toAdd);
                    nextId++;
                }
            }
            OpenTable* op = new OpenTable(tableId, customersToAdd);
            op->act(*this);
            actionsLog.push_back(op);
            delete(op);
        }
        else if(firstWord == "order"){
            std::string::size_type sz;
            int orderTable = std::stoi (tableInstructions.at(1),&sz);
            Order* order = new Order(orderTable);
            actionsLog.push_back(order);
        }
        else if(firstWord == "order"){
            std::string::size_type sz;
            int orderTable = std::stoi (tableInstructions.at(1),&sz);
            Order* order = new Order(orderTable);
            order->act(*this);
            actionsLog.push_back(order);
        }
        else if(firstWord == "move"){
            std::string::size_type sz;
            int srcTable = std::stoi (tableInstructions.at(1),&sz);
            int destTable = std::stoi (tableInstructions.at(2),&sz);
            int customerId = std::stoi (tableInstructions.at(3),&sz);

            MoveCustomer* move = new MoveCustomer(srcTable,destTable,customerId);
            move->act(*this);
            actionsLog.push_back(move);

        }
        else if(firstWord == "close"){
            std::string::size_type sz;
            int table = std::stoi (tableInstructions.at(1),&sz);
            Close* close = new Close(table);
            close->act(*this);
            actionsLog.push_back(close);
        }
        else if(firstWord == "closeall"){
            CloseAll *closeall = new CloseAll();
            closeall->act(*this);
            actionsLog.push_back(closeall);
        }
        else if(firstWord == "menu"){
            PrintMenu *menu = new PrintMenu();
            menu->act(*this);
            actionsLog.push_back(menu);
        }
        else if(firstWord == "status"){
            std::string::size_type sz;
            int table = std::stoi (tableInstructions.at(1),&sz);
            PrintTableStatus* status = new PrintTableStatus(table);
            status->act(*this);
            actionsLog.push_back(status);
        }
        else if(firstWord == "log"){
            PrintActionsLog* log = new PrintActionsLog();
            log->act(*this);
            actionsLog.push_back(log);
        }
        else if(firstWord == "backup"){

        }
        else if(firstWord == "restore"){
//            RestoreResturant * restore = new RestoreResturant();
//            restore->act();
        }
        else { // bad input
            std::cout << "bad input" << std::endl;
        }
        std::cin >> userChoice;
        firstWord = userChoice.substr(0, userChoice.find(" "));
    }
    while(userChoice != "closeall");
};

const std::vector<std::string>& Restaurant::parseInput(std::string &str) {
    std::vector<std::string> v;
    int i = 0;
    while(i < str.length()) {
        if(str.at(i) == ' '){
            std::string sub = str.substr(0, i);
            v.push_back(sub);
            str.erase(0,i + 1);
            i = 0;
        }
        i++;
    }
    v.push_back(str);
    return v;
};

int Restaurant::getNumOfTables() const
{
    return tables.size();
};

Table* Restaurant::getTable(int ind){
    if (ind > tables.size())
        return nullptr;
    return tables.at(ind);
};

const std::vector<BaseAction*> & Restaurant::getActionsLog() const
{
    return actionsLog;
};

std::vector<Dish>& Restaurant::getMenu()
{
    return menu;
};

void Restaurant::readFile(const std::string &configFilePath)
{
    std::ifstream infile(configFilePath);

    if (!infile.is_open())
        return;

    std::string currLine;
    int caseNumber = 1;

    while(std::getline(infile,currLine))
    {
        caseNumber = parseLine(currLine,caseNumber);
    }
    infile.close();

};

int Restaurant::parseLine(const std::string &currLine, int caseNumber)
{
    if (currLine.at(0) == '#')
    {
        return caseNumber;
    }
    //next line parsing
    switch (caseNumber)
    {
        case 1:     // number of tables
        {
            std::string::size_type sz;
            int size = std::stoi (currLine,&sz);
            tables.reserve(size);
            caseNumber++;

            break;
        }
        case 2:     // tables capacity
        {
            std::stringstream ss(currLine);
            int i;
            while (ss >> i)
            {
                tables.push_back(new Table(i));
                if (ss.peek() == ',')
                    ss.ignore();
            }
            caseNumber++;

            break;
        }
        case 3:     // dishes
        {
            insertNewDish(currLine);

            break;
        }
        default: return caseNumber;
    }

    return caseNumber;
};

DishType Restaurant::parseDishType (const std::string& dish)
{
    if (dish == "VEG")
        return DishType::VEG;
    if (dish == "SPC")
        return DishType::SPC;
    if (dish == "BVG")
        return DishType::BVG;
    if (dish =="ALC")
        return DishType::ALC;
};

void Restaurant::insertNewDish(const std::string& currLine)
{
    std::string dishName;
    int dishPrice = -1;
    DishType dishType;

    int currDetail = 1;
    int lastIndex = -1;

    for (int i = 0; i < currLine.size() && currDetail != 3; ++i)
    {
        if (currLine.at(i) != ',')
            continue;
        if (currDetail == 1)    //dish name found
        {
            dishName = currLine.substr(0,i);
            lastIndex = i;
            currDetail++;
        }
        else if (currDetail == 2)   //dish type and price found
        {
            dishType = parseDishType(currLine.substr(lastIndex+1,3));
            std::string::size_type sz;
            dishPrice = std::stoi (currLine.substr(i+1),&sz);
        }

    }
    if (dishPrice != -1)
        menu.push_back(Dish(menu.size(),dishName,dishPrice,dishType));
};


Restaurant::~Restaurant()
{
    for (auto table : tables) {
        delete table;
    }
};