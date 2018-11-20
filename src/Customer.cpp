#include "../include/Customer.h"
#include <vector>
#include <string>
using namespace std;


Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id){}

Customer::Customer(const Customer &_customer):name(_customer.name),id(_customer.id) {}

Customer::~Customer() = default;


int Customer::getId() const
{
    return id;
}
std::string Customer::getName() const
{
    return name;
}



VegetarianCustomer::VegetarianCustomer(std::string name, int id): Customer(name,id){}

VegetarianCustomer::~VegetarianCustomer() = default;

VegetarianCustomer::VegetarianCustomer(const VegetarianCustomer &_customer ): Customer(_customer.getName(),_customer.getId())
{

}


std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu)
{
    std::vector <int> v;
    int a,b;
    a = f_smallest_id(menu);
    b = f_expensive_bvg(menu);
    v.push_back(a);
    v.push_back(b);
    return v;
}
int VegetarianCustomer::f_smallest_id(const std::vector<Dish> &menu)
{
    int a=-1;
    for(unsigned int i=0 ; i<menu.size(); i++)
    {
        if((menu[i].getType()) == 0) {
            if (a == -1) {
                a = menu[i].getId();
            } else {
                if (menu[i].getId() < a) {
                    a = menu[i].getId();
                }
            }
        }
    }
    return a;
}

int VegetarianCustomer::f_expensive_bvg(const std::vector<Dish> &menu)
{
    int a = -1;
    int b = -1;
    for(unsigned int i=0 ; i < menu.size(); i++)
    {
        if(menu[i].getType() == 2 )
        {
            if(menu[i].getPrice() > a)
            {
                a = menu[i].getPrice();
                b = menu[i].getId();
            }
            if(menu[i].getPrice() == a)
            {
                if(menu[i].getId() < b)
                    b = menu[i].getId();
            }
        }
    }
    return b;
}
std::string VegetarianCustomer::toString() const
{
    return this->getName() +',' + "veg";
}

VegetarianCustomer* VegetarianCustomer:: clone () const
{
    VegetarianCustomer *copyCust=new VegetarianCustomer(this->getName(),this->getId());
    return copyCust;
}

CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}

CheapCustomer::~CheapCustomer() = default;

CheapCustomer::CheapCustomer(const CheapCustomer &_customer): Customer(_customer.getName(),_customer.getId())
{
    ord = _customer.ord;
}

std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu)
{
    std::vector <int> v;
    int a;
    if(ord == 0)
    {
        ord=1;
        a = f_cheapest_dish(menu);
        v.push_back(a);
    }
    else
    {
        a = -1;
        v.push_back(a);
    }

    return v;
}
int CheapCustomer::f_cheapest_dish(const std::vector<Dish> &menu)
{
    int a = menu[0].getPrice();
    int b = menu[0].getId();
    for(unsigned int i=0 ; i < menu.size(); i++)
    {
        if(menu[i].getPrice() < a)
        {
            a = menu[i].getPrice();
            b = menu[i].getId();
        }
        if(menu[i].getPrice() == a)
        {
            if(menu[i].getId() < b)
                b = menu[i].getId();
        }

    }
    return b;
}
std::string CheapCustomer::toString() const
{
    return this->getName() +',' + "chp" ;
}

CheapCustomer* CheapCustomer:: clone() const
{
    CheapCustomer *copyCust=new CheapCustomer(this->getName(),this->getId());
    copyCust->ord = this->ord;
    return copyCust;

}

SpicyCustomer::SpicyCustomer(std::string name, int id): Customer(name,id){}

SpicyCustomer::~SpicyCustomer() = default;

SpicyCustomer::SpicyCustomer(const SpicyCustomer &_customer ): Customer(_customer.getName(),_customer.getId())
{
    ord = _customer.ord;
}

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu)
{
    std::vector <int> v;
    int a;
    if(ord == 0)
    {
        a = f_expensive_spc(menu);
        v.push_back(a);
        if(a != -1)
            ord = 1;
    }
    else
    {
        a = f_cheapest_bvg(menu);
        v.push_back(a);
    }
    return v;
}
int SpicyCustomer::f_expensive_spc(const std::vector<Dish> &menu)
{
    int a = -1;
    int b = -1;
    for(unsigned int i=0 ; i < menu.size(); i++)
    {
        if(menu[i].getType() == 1 )
        {
            if(menu[i].getPrice() > a)
            {
                a = menu[i].getPrice();
                b = menu[i].getId();
            }
            if(menu[i].getPrice() == a)
            {
                if(menu[i].getId() < b)
                    b = menu[i].getId();
            }
        }
    }
    return b;
}
int SpicyCustomer::f_cheapest_bvg(const std::vector<Dish> &menu)
{
    int a = -1;
    int b = -1;
    for(unsigned int i=0 ; i < menu.size(); i++)
    {
        if(menu[i].getType() == 2 )
        {
            if(a == -1)
            {
                a = menu[i].getPrice();
                b = menu[i].getId();
            }
            else
            {
                if(menu[i].getPrice() < a)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                if(menu[i].getPrice() == a)
                {
                    if(menu[i].getId() < b)
                        b = menu[i].getId();
                }
            }
        }
    }
    return b;
}


std::string SpicyCustomer::toString() const
{
    return this->getName() +',' + "spc" ;
}

SpicyCustomer*  SpicyCustomer:: clone() const
{
    SpicyCustomer *copyCust=new SpicyCustomer(this->getName(),this->getId());
    // add copy of ord
    return copyCust;

}

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id): Customer(name,id){}

AlchoholicCustomer::~AlchoholicCustomer() = default;

AlchoholicCustomer::AlchoholicCustomer(const AlchoholicCustomer &_customer): Customer(_customer.getName(),_customer.getId())
{
    lst_order_id = _customer.lst_order_id;
    lst_order_price = _customer.lst_order_price;
}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu)
{
    std::vector <int> v;
    int b;
    b = f_cheapest_alc(menu);
    v.push_back(b);
    return v;
}
int AlchoholicCustomer::f_cheapest_alc(const std::vector<Dish> &menu)
{
    int a = -1,b = -1;

    if (lst_order_id == -1)
    {
        for (unsigned int i = 0; i < menu.size(); i++)
        {
            if (menu[i].getType() == 3 )
            {
                if (menu[i].getPrice() < a || a== -1) {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                else
                if (menu[i].getPrice() == a) {
                    if (menu[i].getId() < b)
                        b = menu[i].getId();
                }
            }
        }
    }
    else
    {

        for (unsigned int i = 0; i < menu.size(); i++)
        {
            if (menu[i].getType() == 3 )
            {
                if(menu[i].getPrice() > lst_order_price && a == -1)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                if(menu[i].getPrice() > lst_order_price && menu[i].getPrice() < a)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                if(menu[i].getPrice() == a && menu[i].getId() < b && menu[i].getId() > lst_order_id)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                if(menu[i].getPrice() ==  lst_order_price && menu[i].getId() > lst_order_id && b == -1)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }
                if(menu[i].getPrice() ==  lst_order_price && menu[i].getId() > lst_order_id && menu[i].getId() < b)
                {
                    a = menu[i].getPrice();
                    b = menu[i].getId();
                }

            }
        }

    }
    lst_order_id = b;
    lst_order_price = a;
    return b;
}
std::string AlchoholicCustomer::toString() const
{
    return this->getName() +',' + "alc" ;
}

AlchoholicCustomer*  AlchoholicCustomer:: clone() const
{
    AlchoholicCustomer *copyCust=new AlchoholicCustomer(this->getName(),this->getId() );
    return copyCust;

}