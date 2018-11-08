#include "Restaurant.h"
#include <iostream>
#include "Table.cpp"
#include "vector"
#include "Dish.h"

using namespace std;

//Restaurant* backup = nullptr;

int main() {
    std::cout << "Hello, World!" << std::endl;


    Customer* alex = new VegetarianCustomer("Alex",5);
    Customer* avishai = new SpicyCustomer("Avishai",13);
    Customer* shaked = new CheapCustomer("Shaked",12);
    Table* t1 = new Table(3);
    t1->addCustomer(alex);
    t1->addCustomer(avishai);
    t1->addCustomer(shaked);
    t1->removeCustomer(13);
    cout<< avishai->getName() <<endl;
    //t1->getCustomers();
//    std::vector<Dish> menu;
//
//    Customer*& y = x;
//
//
//
//    VegetarianCustomer z("ASD",1);
//    VegetarianCustomer &t = z;
//
//
//    menu.push_back(Dish(0,"Fish",50,DishType::VEG));
//
//    std::vector<int> ASD (x->order(menu));

//    std::vector<Dish*> A;
//    for (int i = 0; i < 10; ++i) {
//        A.push_back(new Dish(i,"A",i*10,DishType::VEG));
//    }
//    cout << A.size();
//    for (int i = 0; i < A.size(); ++i) {
//        cout << A.at(i)->getId() << endl;
//    }
//    A.erase(A.begin() + 4);
//    for (int i = 0; i < A.size(); ++i) {
//        cout << A.at(i)->getId() << endl;
//    }
//    cout << A.size();
    return 0;

}







//
//int main(int argc, char** argv){
//    if(argc!=2){
//        std::cout << "usage: rest <config_path>" << std::endl;
//        return 0;
//    }
//    string configurationFile = argv[1];
//    Restaurant rest(configurationFile);
//    rest.start();
//    if(backup!=nullptr){
//        delete backup;
//        backup = nullptr;
//    }
//    return 0;
//}