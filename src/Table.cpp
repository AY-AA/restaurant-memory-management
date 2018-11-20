#include <vector>
#include "../include/Customer.h"
#include "../include/Dish.h"
#include "../include/Table.h"
using namespace std;

Table::Table(int t_capacity):capacity(t_capacity), open(false) {}

int Table::getCapacity() const
{

    return capacity;
}

Table::Table(const Table &table)
{
    capacity = table.capacity;
    open = table.open;
    num_of_orders = table.num_of_orders;
    for(unsigned int i = 0 ; i < table.customersList.size() ; i ++)
    {
        customersList.push_back(table.customersList[i]->clone());
    }
    for (unsigned int i = 0; i < table.orderList.size(); i++)
    {
        orderList.emplace_back(table.orderList[i].first , table.orderList[i].second);
    }
}

Table::~Table()
{
    for(unsigned int i = 0 ; i < customersList.size(); i ++)
    {
        delete(customersList[i]);
    }
    customersList.clear();
    orderList.clear();
}
void Table::closetable2()
{
    for (unsigned int i = 0;i < customersList.size() ; i++)
        delete(customersList[i]);
    this->orderList.clear();
    this->customersList.clear();
    this->open = false;
    this->num_of_orders = 0;
}

Table & Table::operator = (const Table & tbl)
{

    capacity = tbl.capacity;
    open = tbl.open;
    num_of_orders = tbl.num_of_orders;

    for(unsigned int i = 0 ; i < customersList.size() ; i ++)
    {
        delete (this->customersList[i]);

    }
    customersList.clear();
    this->getOrders().clear();

    for(unsigned int i = 0 ; i < tbl.customersList.size(); i ++)
        customersList.push_back(tbl.customersList[i]->clone());

    for(unsigned int i = 0 ; i < tbl.orderList.size(); i ++)
        orderList.emplace_back(tbl.orderList[i].first , tbl.orderList[i].second);
    return *this;
}

void Table::addCustomer(Customer* customer)
{
    if (((int)(customersList).size()) < this->capacity)
        (customersList).push_back(customer);
}

void Table::removeCustomer(int id){
    for(unsigned int i=0;i<((customersList).size());i++)
    {
        if (customersList[i]->getId() == id)
            customersList.erase(customersList.begin() + i);

    }
    //maybe we need to do here destructor for customer
}
Customer* Table:: getCustomer(int id)
{

    for(unsigned int i = 0 ; i < ((customersList).size()) ; i++) {
        if (customersList[i]->getId() == id)
            return customersList[i];
    }

    return nullptr;
}
std::vector<Customer*>& Table:: getCustomers()
{
    return customersList;

}
// get refrence of menu
//           return 0orderpair (id customer, dish)

void Table::order(const std::vector<Dish> &menu)
{
    for(unsigned int i = 0; i < customersList.size(); i ++)
    {
        vector<int> a = (getCustomers()[i]->order(menu));
        if(a.size() == 2)
        {
            orderList.emplace_back(customersList[i]->getId(), menu[(a)[0]]);
            if (isdigit(a[1]) == 0)
                orderList.emplace_back(customersList[i]->getId(), menu[(a)[1]]);
        } else
        if(a[0] >=0)
        {
            orderList.emplace_back(customersList[i]->getId(), menu[(a)[0]]);
        }
    }
}
std::vector<OrderPair>& Table::getOrders()
{
    return orderList;
}
void Table::openTable()
{
    open = true;
}
void Table::closeTable()
{
    open = false;
}
int Table::getBill()
{
    int sum=0;
    for(unsigned int i = 0; i < ((orderList).size()); i ++)
        sum+= orderList[i].second.getPrice();
    return sum;
}
bool Table::isOpen()
{
    if(open == true)
        return true;
    return false;
}