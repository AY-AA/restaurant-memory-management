#include <iostream>
#include <vector>
#include "../include/Dish.h"
#include "../include/Customer.h"



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
    _ordered = false;
};

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu)   //orders the smallest id and most expensive beverage (non-alcoholic)
{
    std::vector<int> ans;
    int dishID = -1;
    int bvgPrice = -1;

    // finding dish
    if (!_ordered) {
        for (int i = 0; !_ordered && i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::VEG && (dishID > menu.at(i).getId() || dishID == -1)) {
                dishID = menu.at(i).getId();
            }
        }
        if (dishID != -1)
        {
            ans.push_back(dishID);
            _ordered = true;
        }
    }

    // finding beverage
    else {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::VEG && (bvgPrice < menu.at(i).getPrice() || dishID == -1))
            {
                bvgPrice = menu.at(i).getPrice();
                dishID = menu.at(i).getId();
            }
        }
        if (bvgPrice != -1)
            ans.push_back(dishID);
    }
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
    _ordered = false;
};

std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu)    //orders cheapest dish, only once.
{
    std::vector<int> ans;
    if (_ordered)
        return ans;
    int cheapestID = -1;
    int price = -1;
    for (int i = 0; i < menu.size(); ++i) {
        if (price > menu.at(i).getPrice() || cheapestID == -1)
        {
            price = menu.at(i).getPrice();
            cheapestID = menu.at(i).getId();
        }
    }
    ans.push_back(cheapestID);
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
    _ordered = false;
};

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu)    //orders the most expensive spicy dish, and then cheapest non-alcoholic beverage
{
    std::vector<int> ans;
    int orderID = -1;
    int price = -1;

    //orders dish
    if (!_ordered) {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::SPC && (price < menu.at(i).getPrice() || orderID == -1))
            {
                price = menu.at(i).getPrice();
                orderID = menu.at(i).getId();
            }

        }
        _ordered = true;
    }

    //orders beverage
    else
    {
        for (int i = 0; i < menu.size(); ++i) {
            if (menu.at(i).getType() == DishType::BVG && (price > menu.at(i).getPrice() || orderID == -1))
            {
                int orderID = menu.at(i).getId();
                int price = menu.at(i).getPrice();
            }


        }
    }
    ans.push_back(orderID);
    return ans;
};

std::string SpicyCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "SPC");
    return ans;
};




// Alcoholic Customer


AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name,id)
{
    _ordered = true;
    _canOrder = true;
    _alcPrice = -1;
};

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu)   //orders cheapest alcoholic beverage and then next expensive till there are no more
{
    std::vector<int> ans;
    int orderID = -1;
    int orderPrice = -1;
    //orders dish
    if (!_ordered) {
        for (int i = 0; i < menu.size(); ++i) {
            Dish currDish = menu.at(i);
            if (currDish.getType() == DishType::ALC && (orderPrice > currDish.getPrice() || orderID == -1))
            {
                orderID = currDish.getId();
                orderPrice = currDish.getPrice();
            }
        }
        _ordered = true;
        ans.push_back(orderID);
    }

        //orders beverage
    else if (_canOrder)
    {
        orderID = findNextAlcoholicIndex(menu);
        if (orderID == -1)
            _canOrder = false;
        ans.push_back(orderID);
    }
    return ans;
};

std::string AlchoholicCustomer::toString() const
{
    std::string ans;
    ans.append(std::to_string(this->getId()) + " " + this->getName() + "," + "ALC");
    return ans;
};

int AlchoholicCustomer::findNextAlcoholicIndex(const std::vector<Dish> &menu)
{
    int index = -1;
    int nextPrice = _alcPrice;
    bool found = false;
    for (int i = 0; i < menu.size(); ++i)
    {
        int currID = menu.at(i).getId();
        int currPrice = menu.at(i).getPrice();
        if (menu.at(i).getType() == DishType::ALC)
        {
            if (!found && nextPrice < currPrice)
            {
                index = currID;
                nextPrice = currPrice;
                found = true;
            }
            else if (found && nextPrice > currPrice && currPrice > _alcPrice)
            {
                index = currID;
                nextPrice = currPrice;
            }
        }
    }
    _alcPrice = nextPrice;
    return index;
};


