#include <iostream>
#include <vector>
#include "Dish.cpp"
#include "Customer.h"


Customer::Customer(std::string c_name, int c_id) : id(c_id), name (c_name) {};

std::string Customer::getName() const
{
    return name;
};

int Customer::getId() const
{
    return id;
};



// Vegetarian Customer

VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name,id)
{
    _canOrder = true;
};
std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu)   //orders the smallest id and most expensive beverage (non-alcoholic)
{
    std::vector<int> ans;
    int lowestID = -1;
    int bvgPrice = -1;
    for (int i = 0; i < menu.size(); ++i) {
        if (menu.at(i).getType() == DishType::VEG && (lowestID > menu.at(i).getId() || lowestID == -1))
        {
            lowestID = menu.at(i).getId();
        }
        if (menu.at(i).getType() == DishType::VEG && (bvgPrice < menu.at(i).getPrice() || bvgPrice == -1))
        {
            bvgPrice = menu.at(i).getPrice();
        }
    }
    ans.push_back(lowestID);
    ans.push_back(bvgPrice);

    return ans;
};
std::string VegetarianCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "VEG");
    return ans;
};



// Cheap Customer

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name,id)
{
    _ordered = true;
};
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu)    //orders cheapest dish, and once.
{
    std::vector<int> ans;
    if (!_ordered)
        return ans;
    int cheapest = -1;
    for (int i = 0; i < menu.size(); ++i) {
        if (cheapest > menu.at(i).getPrice() || cheapest == -1)
            cheapest = menu.at(i).getId();
    }
    ans.push_back(cheapest);
    _ordered = false;
    return ans;
};
std::string CheapCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "CHP");
    return ans;
}



// Spicy Customer

SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name,id)
{
    _ordered = true;
};
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu)    //orders the most expensive spicy dish, and then cheapest non-alcoholic beverage
{
    std::vector<int> ans;
    int spicy = -1;
    if (_ordered) {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::SPC && (spicy < menu.at(i).getPrice() || spicy == -1))
                spicy = menu.at(i).getId();
        }
        _ordered = false;
    }
    else
    {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::BVG && (spicy > menu.at(i).getPrice() || spicy == -1))
                spicy = menu.at(i).getId();
        }
    }
    ans.push_back(spicy);
    return ans;
};
std::string SpicyCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "SPC");
    return ans;
};



// Alchoholic Customer


AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name,id)
{
    _ordered = true;
};

//TODO : figure out how to implement the repeats of orders

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu)   //orders cheapest alcoholic beverage and then next expensive till there are no more
{

};
std::string AlchoholicCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "ALC");
    return ans;
};



