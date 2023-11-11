//Brendon Uzoigwe
/*
 * DNode.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */

#include <cstdlib>
#include <iostream>
#include "DNode.hpp"
using namespace std;

/* write your constructors here! */
DNode::DNode(){
    task = nullptr;
    prev = nullptr;
    next = nullptr;
}

DNode::DNode(string t, int p, int lenhr, int lenmin){
    task = new Task(t, p, lenhr, lenmin );
    prev = nullptr;
    next = nullptr;
}
