//Brendon Uzoigwe
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
//ideas for move up: shift helper function,

DLL::DLL(){
	first = nullptr;
    last = nullptr;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string t, int p, int h, int m){
    DNode *newNode;
    newNode = new DNode(t, p, h, m);
    first = newNode;
    last = newNode;
    numTasks = 1;
    tothrs = h;
    totmin = m;
}

DLL::~DLL(){
	DNode* temp = first;
    while(temp!= nullptr){
        DNode* next = temp->next;
        delete temp;
        temp = next;
    }
    first = nullptr;
    last = nullptr;
}

void DLL::push(string t, int p, int h, int m) {
    DNode* node = new DNode(t, p,h,m);
    if(first == nullptr){
        first = node;
        last = node;
        addTime(h, m);
        numTasks++;
        return;
    }
    else {
            DNode *temp = last;
            while (temp != nullptr && temp->task->priority <= p) {
                temp = temp->prev;
            }
            if(temp == last) {
                node->prev = last;
                last->next = node;
                last = node;
            }
            else if(temp == nullptr){
                first->prev = node;
                node->next = first;
                first = node;
        } else {
           node->prev = temp;
           node->next = temp->next;
           temp->next->prev = node;
           temp->next = node;
        }
        addTime(h, m);
        numTasks++;
    }
}

Task *DLL::pop() {
    DNode *temp = last;
    Task *x = temp->task;
    if (numTasks == 1) {
        first = nullptr;
        last = nullptr;
    } else {
        last = last->prev;
        last->next = nullptr;
    }
    delete temp;
    numTasks--;
    removeTime(x->hr, x->min);
    return x;
}

int DLL::remove(int tn) {
	DNode *temp = last;
    while(temp != nullptr){
        if(temp->task->tasknum == tn) {
            if(temp == first && temp == last){
                first = nullptr;
                last = nullptr;
            }
            else if (temp == first){
                first = temp->next;
                first->prev = nullptr;
            }
            else if (temp == last) {
                last = temp->prev;
                last->next = nullptr;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
                int num = temp->task->tasknum;
                numTasks --;
                removeTime(temp->task->hr, temp->task->min);
                delete temp;
                return num;
        }
        temp = temp->prev;
    }
    return -1;
}

void DLL::addTime(int h, int m) {
    totmin += m;
    if (totmin >= 60) {
        h += totmin / 60;
        totmin %= 60;
    }
    tothrs += h;
}

void DLL::removeTime(int h, int m) {
	tothrs -= h;
    if(m>totmin){
        tothrs -= 1;
        totmin += 60;
    }
    totmin -= m;
}


void DLL::moveUp(int tn) {
    if (first == nullptr || last == nullptr) {
        return;
    }
    DNode* curr = first;
    while (curr != nullptr && curr->task->tasknum != tn) {
        curr = curr->next;
    }
    if (curr == last) {
        last = last->prev;
        last->next = nullptr;
        first->prev = curr;
        curr->next = first;
        curr->prev = nullptr;
        first = curr;
        first->task->priority = first->next->task->priority;
    }
    else {
        DNode* next = curr->next;
        next->prev = curr->prev;
        if (curr->prev != nullptr) {
            curr->prev->next = next;
        }
        else {
            first = next;
        }
        curr->prev = next;
        curr->next = next->next;
        next->next = curr;
        if (curr->next != nullptr) {
            curr->next->prev = curr;
        }
        else {
            last = curr;
        }
        if (curr->task->priority != curr->prev->task->priority) {
            curr->task->priority = curr->prev->task->priority;
        }
    }
}

void DLL::moveDown(int tn) {
    if (first == nullptr || last == nullptr) {
        return;
    }
    DNode* curr = first;
    while (curr != nullptr && curr->task->tasknum != tn) {
        curr = curr->next;
    }
    if (curr == first) {
        first = first->next;
        first->prev = nullptr;
        last->next = curr;
        curr->prev = last;
        curr->next = nullptr;
        last = curr;
        last->task->priority = last->prev->task->priority;
    }
    else {
        DNode* prev = curr->prev;
        prev->next = curr->next;
        if (curr->next != nullptr) {
            curr->next->prev = prev;
        }
        else {
            last = prev;
        }
        curr->next = prev;
        curr->prev = prev->prev;
        prev->prev = curr;
        if (curr->prev != nullptr) {
            curr->prev->next = curr;
        }
        else {
            first = curr;
        }
    }
}

void DLL::changePriority(int tn, int newp) {
    DNode *temp = first;
    if (numTasks == 0) {
        return;
    }
    else if (numTasks == 1 && first->task->tasknum == tn) {
        first->task->priority = newp;
        return;
    }
    while (temp != nullptr) {
        if (temp->task->tasknum == tn) {
            if (newp == 1) {
                while (temp != last) {
                    moveUp(tn);
                    temp->task->priority = newp;
                }
            }
            else if(newp == 2) {
                if (temp->task->priority == 3) {
                    while (temp->task->priority > 2){
                        moveUp(tn);
                    }
                    temp->task->priority = newp;
                }
                else if (temp->task->priority == 1){
                    while(temp->task->priority < 3){
                        moveUp(tn);
                    }
                    temp->task->priority = newp;
                }
                }
            else if(newp == 3){
                while(temp!=first) {
                    moveDown(tn);
                }
                    temp->task->priority = newp;
            }
        }
        temp = temp->next;
    }
}

void DLL::listDuration(int *th, int *tm,int tp) {
    DNode *temp = first;
    while (temp != nullptr) {
        if (temp->task->priority == tp) {
            *th += temp->task->hr;
            *tm += temp->task->min;
        }
        temp = temp->next;
    }
    while (*tm > 59) {
        *tm -= 60;
        *th += 1;
    }

}

void DLL::printList() {
	DNode* temp = last;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while(temp != nullptr){
        temp->task->printTask();
        temp = temp->prev;
    }
    cout<<endl;
}

void DLL::printList(int p) {
    int h = 0;
    int m = 0;
    listDuration(&h, &m, p);
    cout << p <<": Total Time Required: "<< h << ":"<< m <<endl;
    DNode* temp = last;
    while(temp != nullptr){
        if(temp->task->priority == p){
            temp->task->printTask();
        }
        temp = temp->prev;
    }
    cout<<endl;
}

