//Brendon Uzoigwe
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("/Users/brendonuzoigwe/CLionProjects/DLLTaskManager/ListofTasks.txt");
}

