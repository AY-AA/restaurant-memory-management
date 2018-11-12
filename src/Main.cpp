#include <iostream>
#include "../include/Restaurant.h"
#include "../include/Customer.h"
#include "../include/Table.h"
#include "../include/Dish.h"
#include <vector>

using namespace std;

Restaurant* backup = nullptr;


int main(int argc, char** argv){


    if(argc!=2){
        std::cout << "usage: rest <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Restaurant rest(configurationFile);
    rest.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
}
//
//    string configurationFile = "../config.txt";
//    Restaurant rest(configurationFile);
//    rest.start();
//
//    if(backup!=nullptr){
//        delete backup;
//        backup = nullptr;
//    }
//    return 0;


}








