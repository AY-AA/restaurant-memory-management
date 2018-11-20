#include "../include/Restaurant.h"
#include "../include/Customer.h"
#include "../include/Table.h"
#include "../include/Dish.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
#include <string>
extern Restaurant* backup;
using namespace std;


Restaurant::Restaurant(const std::string &configFilePath)
{
    vector<string> a;
    string part_of_string,line,d_name;
    int counter = 0,c = 0, counter2 = 0,d_price,d_counter=0;
    DishType d_type;
    ifstream myfile ('"' + configFilePath+ '"');
    myfile.open (configFilePath);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            a.push_back(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file";
    for(unsigned int i = 0; i < a.size(); i ++)
    {
        if((a[i])[0] == ' ')
        {

        }
        else
        {
            if((a[i])[0] == '#')
            {
                counter++;
            }
            if(counter == 2 && isdigit((a[i])[0]))
            {
                for(unsigned int j = 0; j < a[i].size(); j++)
                {
                    if((a[i])[j] == ',')
                    {
                        c = stoi(part_of_string);
                        part_of_string = "";
                        Table* t = new Table(c);
                        tables.push_back(t);
                    }
                    else
                    {
                        part_of_string += (a[i])[j];
                    }
                }
                c = stoi(part_of_string);
                part_of_string = "";
                Table* t = new Table(c);
                tables.push_back(t);
                c = 0;
            }
            if(counter == 3 && isalpha((a[i])[0]))
            {
                for(unsigned int j = 0; j < a[i].size(); j++)
                {
                    if((a[i])[j] == ',')
                    {
                        counter2++;
                    }
                    else
                    {
                        part_of_string += (a[i])[j];
                    }
                    if( counter2 == 1 && (a[i])[j] == ',')
                    {
                        d_name = part_of_string;
                        part_of_string = "";
                    }
                    if( counter2 == 2 && (a[i])[j] == ',')
                    {
                        if(part_of_string == "VEG")
                        {
                            d_type = DishType (0);
                            part_of_string = "";
                        }
                        if(part_of_string == "SPC")
                        {
                            d_type = DishType (1);
                            part_of_string = "";
                        }
                        if(part_of_string == "BVG")
                        {
                            d_type = DishType (2);
                            part_of_string = "";
                        }
                        if(part_of_string == "ALC")
                        {
                            d_type = DishType (3);
                            part_of_string = "";
                        }
                    }
                }
                d_price = stoi(part_of_string);
                part_of_string = "";
                Dish dish(d_counter,d_name,d_price,d_type);
                menu.push_back(dish);
                counter2 = 0;
                d_counter++;
            }
        }
    }

}
Restaurant::Restaurant(const Restaurant& restaurant)
{
    cus_id = restaurant.cus_id;
    open = restaurant.open;
    for (unsigned int i = 0; i < restaurant.tables.size(); i++)
    {
        tables.push_back(new Table(*restaurant.tables[i]));
    }
    for (unsigned int i = 0; i < restaurant.menu.size(); i++)
    {
        menu.push_back(restaurant.menu[i]);
    }
    for (unsigned int i = 0; i < restaurant.actionsLog.size(); i++)
    {
        actionsLog.push_back(restaurant.actionsLog[i]->clone());
    }
}
void Restaurant::copy(const Restaurant& restaurant)
{
    this->cus_id = restaurant.cus_id;
    this->open = restaurant.open;
    for (unsigned int i = 0; i < restaurant.tables.size(); i++)
    {
        this->tables.push_back(new Table(*restaurant.tables[i]));
    }
    for (unsigned int i = 0; i < restaurant.actionsLog.size(); i++)
    {
        this->actionsLog.push_back(restaurant.actionsLog[i]->clone());
    }
}
Restaurant & Restaurant::operator = (const Restaurant & restaurant)
{

    for (unsigned int i = 0; i < actionsLog.size(); i++)
    {
        delete (this->actionsLog[i]);
    }
    for (unsigned int i = 0; i < tables.size(); i++)
    {
        delete tables[i];
    }
    tables.clear();
    actionsLog.clear();
    this->copy(restaurant);
    return *this;
}
Restaurant::~Restaurant()
{
    for(unsigned int i = 0 ; i <tables.size(); i++)
    {
        delete(tables[i]);
    }
    for(unsigned int i = 0 ; i <actionsLog.size() ; i++)
    {
        delete(actionsLog[i]);
    }
}
Restaurant::Restaurant( Restaurant&& restaurant)
{

    cus_id = restaurant.cus_id;
    open = restaurant.open;
    restaurant.cus_id=0;
    restaurant.open=true;
    for (unsigned int i = 0; i < restaurant.tables.size(); i++)
    {
        tables.push_back(new Table(*restaurant.tables[i]));
        restaurant.tables[i]=nullptr;
    }
    restaurant.tables.clear();
    for (unsigned int i = 0; i < restaurant.menu.size(); i++)
    {
        menu.push_back(restaurant.menu[i]);
    }
    restaurant.menu.clear();
    for (unsigned int i = 0; i < restaurant.actionsLog.size(); i++)
    {
        actionsLog.push_back(restaurant.actionsLog[i]->clone());
        restaurant.actionsLog[i]=nullptr;
    }
    restaurant.actionsLog.clear();
}

Restaurant & Restaurant::operator = ( Restaurant && restaurant)
{
    open = restaurant.open;
    tables = restaurant.tables;
    cus_id = restaurant.cus_id;
    restaurant.open=open;
    restaurant.cus_id=0;

    for(unsigned int i = 0; i < actionsLog.size(); i ++)
    {
        delete ((actionsLog[i]));
    }
    actionsLog.clear();
    for(unsigned int i = 0; i < restaurant.actionsLog.size(); i ++)
    {
        actionsLog.push_back(restaurant.actionsLog[i]->clone());
        restaurant.actionsLog[i]=nullptr;
    }
    restaurant.actionsLog.clear();
    for(unsigned int i = 0; i < tables.size(); i ++)
    {
        delete ((tables[i]));
    }
    tables.clear();
    for (unsigned int i = 0; i < restaurant.tables.size(); i++)
    {
        tables.push_back(new Table(*restaurant.tables[i]));
        restaurant.tables[i]=nullptr;
    }
    restaurant.tables.clear();

    menu.clear();
    for (unsigned int i = 0; i < restaurant.menu.size(); i++)
    {
        menu.push_back(restaurant.menu[i]);
    }
    restaurant.menu.clear();

    return *this;
}


Table* Restaurant::getTable(int ind)
{
    return tables[ind];
}
std::vector<Dish>& Restaurant::getMenu()
{
    return menu;
}
int Restaurant::getNumOfTables() const
{
    return tables.size();
}
const std::vector<BaseAction*>& Restaurant::getActionsLog() const
{
    return actionsLog;
}
void Restaurant::start()
{

    string x,part_data,cus_name,str;
    vector<string> data;
    vector<Customer*> vc;
    open = true;
    cout << "Restaurant is now open!" << endl;
    getline(cin , x);
    while (x.compare("closeall") != 0)
    {
        for(unsigned int i =0 ; i < x.size(); i++)
        {
            if(x[i] == ' ')
            {
                data.push_back(part_data);
                part_data = "";
            }
            else
            if(x[i] == ',')
            {
                data.push_back(part_data);
                part_data = "";
            }
            else
            {
                part_data += x[i];
            }
        }
        data.push_back(part_data);
        part_data = "";
        if(data[0].compare("open") == 0)
        {
            std::vector<Customer*> tmpCus = customersResList(data);
            OpenTable *open_table = new OpenTable(stoi(data[1]),tmpCus);
            open_table->act(*this);
            this->actionsLog.push_back(open_table);
        }
        if(data[0].compare("order") == 0)
        {
            Order* order = new Order(stoi(data[1]));
            order->act(*this);
            this->actionsLog.push_back(order);
        }
        if(data[0].compare("move") == 0)
        {
            MoveCustomer* movecustomer = new MoveCustomer(stoi(data[1]), stoi(data[2]), stoi(data[3]));
            movecustomer->act(*this);
            this->actionsLog.push_back(movecustomer);
        }
        if(data[0].compare("close") == 0)
        {
            Close* close = new Close(stoi(data[1]));
            close->act(*this);
            this->actionsLog.push_back(close);
        }
        if(data[0].compare("menu") == 0 )
        {
            PrintMenu* printmenu = new PrintMenu();
            printmenu->act(*this);
            this->actionsLog.push_back(printmenu);
        }
        if(data[0].compare("status") == 0)
        {
            PrintTableStatus* printtablestatus = new PrintTableStatus(stoi(data[1]));
            printtablestatus->act(*this);
            this->actionsLog.push_back(printtablestatus);
        }
        if(data[0].compare("log") == 0)
        {
            PrintActionsLog* printactionlog = new PrintActionsLog();
            printactionlog->act(*this);
            this->actionsLog.push_back(printactionlog);
        }
        if(data[0].compare("backup") == 0)
        {
            BackupRestaurant* backuprestaurant = new BackupRestaurant();
            backuprestaurant->act(*this);
            this->actionsLog.push_back(backuprestaurant);

        }
        if(data[0].compare("restore") == 0)
        {
            RestoreResturant* restorerestaurant = new RestoreResturant();
            restorerestaurant->act(*this);
            this->actionsLog.push_back(restorerestaurant);
        }

        data.erase(data.begin(),data.begin()+data.size());
        getline(cin , x);

    }
    open = false;
    CloseAll* closeall = new CloseAll();
    closeall->act(*this);
    this->actionsLog.push_back(closeall);
}

vector<Customer*> & Restaurant::customersResList(vector<string> data)
{
    std::vector<Customer*> vc ;
    for(unsigned int i = 2 ; i < data.size() ; i+= 2)
    {
        if(data[i+1].compare("chp") == 0) {
            CheapCustomer *c = new CheapCustomer(data[i], cus_id);
            vc.push_back(c);
            cus_id++;
        }
        if(data[i+1].compare("alc") == 0) {
            AlchoholicCustomer *c = new AlchoholicCustomer(data[i], cus_id);
            vc.push_back(c);
            cus_id++;
        }
        if(data[i+1].compare("veg") == 0) {
            VegetarianCustomer *c = new VegetarianCustomer(data[i], cus_id);
            vc.push_back(c);
            cus_id++;
        }
        if(data[i+1].compare("spc") == 0)
        {
            SpicyCustomer* c = new SpicyCustomer(data[i], cus_id);
            vc.push_back(c);
            cus_id ++;

        }
    }
    return vc;
}