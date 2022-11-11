#include<iostream>
#include"list.hpp"

int main(){

    MyList<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    MyList<int> listy=array;
    for(auto it=listy.begin();it!=listy.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<"Size ="<<listy.size()<<std::endl;
    std::cout<<std::endl;

    listy.push_back(4);
    listy.push_back(5);
    listy.push_back(6);
    listy.push_back(7);
    listy.push_back(8);
    listy.erase(listy.begin());
    listy.erase(listy.end());
    for(auto it=listy.begin();it!=listy.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<"Size ="<<listy.size()<<std::endl;
    std::cout<<std::endl;

    listy.push_back(36);
    listy.push_back(6);
    listy.push_back(3);
   std::cout<<*(listy.begin()+1)<<std::endl;
    listy.insert(listy.begin()+4,0);
    //std::cout<<*(listy.end()-2)<<std::endl;
    listy.erase(listy.begin()+1,listy.begin()+3);
   for(auto it=listy.begin();it!=listy.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<"Size ="<<listy.size()<<std::endl;
    return 0;
}