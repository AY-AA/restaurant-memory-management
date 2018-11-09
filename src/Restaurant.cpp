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
    start();
}

void Restaurant::start()
{

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