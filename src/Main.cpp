#include "../include/Restaurant.h"
#include <iostream>

using namespace std;

Restaurant* backup = nullptr;

int main(int argc, char** argv){

//    std::string a = "asd";
    string configurationFile = "config.txt";
    Restaurant rest(configurationFile);
    rest.start();
    if(backup!=nullptr){
        delete backup;
        backup = nullptr;
    }

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
}