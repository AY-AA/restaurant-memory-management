#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/Restaurant.h"
#include "../include/Table.h"


Restaurant::Restaurant() {};

Restaurant::Restaurant(const std::string &configFilePath)
{
    readFile(configFilePath);
}

void Restaurant::start() {
    std::string userChoice;
    std::cout << "Restaurant is now open!";
    int nextId = 0;
    do {
        std::cin >> userChoice;
        std::string firstWord = userChoice.substr(0, userChoice.find(" "));
        if (firstWord == "open") {
            std::vector<std::string> tableInstructions = parseInput(userChoice);
            //std::vector<std::string> customersToAdd;
            int tableId = std::stoi(tableInstructions.at(1));
            Table* tableToOpen = tables.at(tableId);
            tableToOpen->openTable();
            std::string name;
            std::string type;
            for (int i = 2; i < tableInstructions.size() - 1; i++) {
                name = tableInstructions.at(i);
                type = tableInstructions.at(i + 1);
                if(type == "veg"){
                    Customer* toAdd = new VegetarianCustomer(name,nextId);
                    tableToOpen->addCustomer(toAdd);
                    nextId++;
                }
                else if(type == "spc"){
                    Customer* toAdd = new SpicyCustomer(name,nextId);
                    tableToOpen->addCustomer(toAdd);
                    nextId++;
                }
                else if(type == "chp"){
                    Customer* toAdd = new CheapCustomer(name,nextId);
                    tableToOpen->addCustomer(toAdd);
                    nextId++;
                }
                else{ //alc
                    Customer* toAdd = new AlchoholicCustomer(name,nextId);
                    tableToOpen->addCustomer(toAdd);
                    nextId++;
                }
            }

        } else if (firstWord == "order") {

        } else if (firstWord == "move") {

        } else if (firstWord == "close") {

        } else if (firstWord == "menu") {

        } else if (firstWord == "status") {

        } else if (firstWord == "log") {

        } else if (firstWord == "backup") {

        } else if (firstWord == "restore") {

        } else {//closeall

        }
        std::cin >> userChoice;
        firstWord = userChoice.substr(0, userChoice.find(" "));
    } while (userChoice != "closeall");

    const std::vector<std::string>& Restaurant::parseInput(std::string &str) {
        std::vector<std::string> v;
        int i = 0;
        while(i < userChoice.length()) {
            if(str.at(i) == *" "){
                std::string sub = str.substr(0,userChoice.find(" "));
                v.push_back(sub);
                str.erase(0,str.find(" ") + 1);
                i = 0;
            }
            i++;
        }
        v.push_back(userChoice);
        return v;
    };

int Restaurant::getNumOfTables() const
{

};

Table* Restaurant::getTable(int ind){


};

const std::vector<BaseAction*> & Restaurant::getActionsLog() const
{

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
    }

    return caseNumber;
};

DishType Restaurant::parseDishType (const std::string& dish)
{
    if (dish.compare("VEG") == 0)
        return DishType::VEG;
    if (dish.compare("SPC") == 0)
        return DishType::SPC;
    if (dish.compare("BVG") == 0)
        return DishType::BVG;
    if (dish.compare("ALC") == 0)
        return DishType::ALC;
};

void Restaurant::insertNewDish(const std::string& currLine)
{
    int dishId = menu.size();
    std::string dishName;
    int dishPrice;
    DishType dishType;

    int currDetail = 1;
    int lastIndex = -1;

    for (int i = 0; i < currLine.size() && currDetail != 3; ++i)
    {
        if (currLine.at(i) != ',')
            continue;
        if (currDetail == 1)
        {
            dishName = currLine.substr(0,i);
            lastIndex = i;
            currDetail++;
        }
        else if (currDetail == 2)
        {
            dishType = parseDishType(currLine.substr(lastIndex+1,3));

            std::string::size_type sz;
            dishPrice = std::stoi (currLine.substr(i+1),&sz);

        }

    }

    menu.push_back(Dish(dishId,dishName,dishPrice,dishType));
};