#pragma 'once'
#include<iostream>
#include <algorithm>

template<typename T>
class MyList{
    private:

        class Node{
            public:
                Node* next;
                Node* previous;
                T data;
                Node(T value, Node* before=nullptr,Node* after=nullptr):next{after},previous{before},data{value}{}
        };

        size_t size_;
        Node* first;
        Node* last;

    public:
        MyList(){first=last=nullptr; size_=0;}

        MyList(const MyList& other){Node* temp=other.first; size_=0; while(temp){push_back(temp->data);  temp=temp->next;}}

        MyList& operator =(const MyList& other){delete_list(); auto temp=other.first; while(temp){push_back(temp->data); temp=temp->next;} return *this;}

        MyList(MyList&& other):first{other.first},last{other.last},size_{other.size_}{other.first=nullptr; other.last=nullptr;}

        MyList& operator =(MyList&& other){delete_list(); first=other.first; last=other.last; size_=other.size_; other.first=nullptr; other.last=nullptr; return *this;}
        
        ~MyList(){delete_list();}
        // Methods of class

        void push_back(T value){
            if(empty()){first=last=new Node(value); size_++; return;}
            auto temp=new Node(value);
            last->next=temp;
            temp->previous=last;
            last=temp;
            size_++;
            temp=nullptr;
        }

        void delete_list(){
            if(empty()){return;}
            auto temp=first;
            while(temp){
                first=temp->next;
                delete temp;
                temp=first;
            }
            size_=0;
        }

        bool empty(){ return size_==0;}

        size_t size(){return size_;}

        void pop_back(){
            if(empty()){return;}
            auto temp=last;
            last=last->previous;
            size_--;
            delete temp;
        }

        void pop_front(){
            if(empty()){return;}
            auto temp=first;
            first=first->next;
            size_--;
            delete temp;
        }

        void push_front(T data){
            if(empty()){first=last=new Node(data); size_++; return;}
            auto temp=new Node(data);
            first->previous=temp;
            temp->next=first;
            first=temp;
            temp=nullptr;
            size_++;
        }

        T front(){return first->data;}

        T back(){return last->data;}

        class Iterator{
            private:

                Node* ptr;

            public:

                Iterator(Node* other):ptr{other}{};
                ~Iterator(){ptr=nullptr;}

                T operator*(){return ptr->data;}
                
                Iterator& operator ++(){ptr=ptr->next; return *this;}
                Iterator operator ++(int){auto temp=ptr; ptr=ptr->next; return temp;}
                Iterator& operator --(){  ptr=ptr->previous; return *this;}
                Iterator operator --(int){auto temp=ptr;  ptr=ptr->previous; return temp;}

                Iterator operator+(int value){while(value--){ptr=ptr->next;} return *this;}
                Iterator operator-(int value){while(value--){ ptr=ptr->previous;} return *this;}

                bool operator==(Iterator other){return ptr==other.ptr;}
                bool operator!=(Iterator other){return ptr!=other.ptr;}

                Node* give_node(){return ptr;}
        };

        Iterator begin(){return Iterator{first};}
        Iterator end(){return Iterator{last->next};}

        Iterator erase(Iterator position){
            if(empty()){return end();}
            if(position==begin()){pop_front(); return begin();}
            if(position==end()){pop_back(); return end();}
            auto behind=position.give_node()->previous;
            auto infront=position.give_node()->next;
            behind->next=infront;
            infront->previous=behind;
            size_--;
            delete position.give_node();
            return infront;
        }

        Iterator erase(Iterator from, Iterator to){
        if(empty()){return end();}
        auto tempF=from.give_node()->previous;
        auto tempT=to.give_node();
        tempF->next=tempT;
        tempT->previous=tempF;

        auto remove=from;
        while(remove!=to){
            from++;
            delete remove.give_node();
            remove=from;
            size_--;
        }

        return tempT;
        }

        void insert(Iterator position, T value){
            auto location=position.give_node();
            auto temp=new Node(value);
            temp->previous=location->previous;
            location->previous->next=temp;
            temp->next=location;
            location->previous=temp;
            size_++;
            temp=nullptr;

        }

};