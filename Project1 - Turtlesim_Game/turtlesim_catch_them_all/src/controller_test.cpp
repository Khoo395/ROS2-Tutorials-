#include <random>
#include <iostream>


int main(){
std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 5);
    for(int i = 0;i<5;i++){
    std::cout << dist(mt)<< std::endl;
    }
}