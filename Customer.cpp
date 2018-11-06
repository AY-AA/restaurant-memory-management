#include <iostream>
#include <vector>
#include "Dish.cpp"
#include "Customer.h"


Customer::Customer(std::string c_name, int c_id) : id(c_id), name (c_name)
{


};


std::string Customer::getName() const
{

};
int Customer::getId() const
{

};


class VegetarianCostumer: public Customer
{

};



class CheapCostumer: public Customer
{

};



class SpicyCostumer: public Customer
{


};


class AlcoholicCostumer: public Customer
{


};