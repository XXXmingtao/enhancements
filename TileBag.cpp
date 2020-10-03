
#include "TileBag.h"

#include <iostream>
#include <fstream>
#include <exception>

Node::Node(Tile tile, Node* next) :
   tile(tile),
   next(next)
{}

TileBag::TileBag() {
   head = nullptr;
}

TileBag::TileBag(TileBag& other) {
   head = nullptr;
   for(int i=0;i!=other.size();++i){
      addBack(other.get(i));
   }
}

TileBag::~TileBag() {
   clear();
}

int TileBag::size() {
   int count = 0;
   Node* current = head;
   while(current!=nullptr){
      ++count;
      current = current->next;
   }
   return count;
}

Tile TileBag::get(int index) {
   int count = 0;
   Node* current = head;
   Tile returnValue = NO_TILE;
   if(index>=0&&index<size()){
      while(count<index){
         ++count;
         current = current->next;
      }
      returnValue = current->tile;
   } else {
      throw std::out_of_range("Linked List get - index out of range");
   }
   return returnValue;
}

void TileBag::addFront(Tile tile) {
   Node* node = new Node(tile, head);
   head = node;
}

void TileBag::addBack(Tile tile) {
   Node* toAdd = new Node(tile, nullptr);
   if(head == nullptr){
      head = toAdd;
   } else {
      Node* current = head;
      while(current->next!=nullptr){
         current = current->next;
      }
      current->next = toAdd;
   }
}

void TileBag::removeBack() {
   Node* current = head;
   Node* previous = current;
   while(current->next!=nullptr){
      previous = current;
      current = current->next;
   }
   delete current;
   previous->next = nullptr;
}

void TileBag::removeFront() {
   if(head!=nullptr){
      Node* current = head;
      head = head->next;
      delete current;
   }
}

void TileBag::clear() {
   while(head!=nullptr){
      removeFront();
   }
}

