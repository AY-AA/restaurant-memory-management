#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"
using namespace std;
class Customer
{
public:
    Customer(std::string c_name, int c_id);
    Customer(const Customer &_customer);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    virtual Customer* clone() const = 0;
    virtual ~Customer() = 0;

    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;

};


class VegetarianCustomer : public Customer {
public:
    VegetarianCustomer(std::string name, int id);
    VegetarianCustomer(const VegetarianCustomer &_customer);
    virtual ~ VegetarianCustomer();
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int f_smallest_id(const std::vector<Dish> &menu);
    int f_expensive_bvg(const std::vector<Dish> &menu);
    VegetarianCustomer* clone () const;

private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    CheapCustomer(const CheapCustomer &_customer);
    virtual ~ CheapCustomer();
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int f_cheapest_dish(const std::vector<Dish> &menu);
    CheapCustomer* clone() const;

private:
    int ord = 0;
};


class SpicyCustomer : public Customer {
public:
    SpicyCustomer(std::string name, int id);
    SpicyCustomer(const SpicyCustomer &_customer );
    virtual ~ SpicyCustomer();
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int f_expensive_spc(const std::vector<Dish> &menu);
    int f_cheapest_bvg(const std::vector<Dish> &menu);
    SpicyCustomer* clone() const;

private:
    int ord = 0;
};


class AlchoholicCustomer : public Customer {
public:
    AlchoholicCustomer(std::string name, int id);
    AlchoholicCustomer(const AlchoholicCustomer &_customer);
    virtual ~ AlchoholicCustomer();
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int f_cheapest_alc(const std::vector<Dish> &menu);
    AlchoholicCustomer* clone() const;

private:
    int lst_order_id = -1;
    int lst_order_price = -1;

};



#endif