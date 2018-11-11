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
        for (auto dish : menu) {
            if (dish.getType() == DishType::BVG && (bvgPrice < dish.getPrice() || dishID == -1))
            {
                bvgPrice = dish.getPrice();
                dishID = dish.getId();
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
    ans.append(getName() + "," + "veg");
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
    for (auto dish : menu) {
        if (price > dish.getPrice() || cheapestID == -1)
        {
            price = dish.getPrice();
            cheapestID = dish.getId();
        }
    }
    ans.push_back(cheapestID);
    _ordered = false;
    return ans;
};

std::string CheapCustomer::toString() const
{
    std::string ans;
    ans.append(getName() + "," + "chp");
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
        for (auto dish: menu) {
            if (dish.getType() == DishType::SPC && (price < dish.getPrice() || orderID == -1))
            {
                price = dish.getPrice();
                orderID = dish.getId();
            }

        }
        _ordered = true;
    }

    //orders beverage
    else
    {
        for (auto dish : menu) {
            if (dish.getType() == DishType::BVG && (price > dish.getPrice() || orderID == -1))
            {
                orderID= dish.getId();
                price= dish.getPrice();
            }


        }
    }
    ans.push_back(orderID);
    return ans;
};

std::string SpicyCustomer::toString() const
{
    std::string ans;
    ans.append(getName() + "," + "spc");
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
        for (auto dish : menu) {
            if (dish.getType() == DishType::ALC && (orderPrice > dish.getPrice() || orderID == -1))
            {
                orderID = dish.getId();
                orderPrice = dish.getPrice();
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
    ans.append(getName() + "," + "alc");
    return ans;
};

int AlchoholicCustomer::findNextAlcoholicIndex(const std::vector<Dish> &menu)
{
    int index = -1;
    int nextPrice = _alcPrice;
    bool found = false;
    for (auto dish : menu)
    {
        int currID = dish.getId();
        int currPrice = dish.getPrice();
        if (dish.getType() == DishType::ALC)
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


