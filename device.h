//
//  device.hpp
//  opsys
//
//  Created by Chasmandeep Bring on 5/14/16.
//  Copyright © 2016 ChasmandeepB. All rights reserved.
//

#ifndef device_hpp
#define device_hpp

using namespace std;

#include <stdio.h>

class device{
private:
    int devicenum;
    queue<processControlBlock*> devicequeue;
    string name;
    string type;
    
public:
    device(); //constructor
    device(int, string, string);
    void addToDeviceQueue(processControlBlock*);
    string getName(){return this->name;}
    processControlBlock* removeFromDevice();
    void print();
    bool queueIsEmpty();
};


device::device(){
    devicenum = 0;
    name = "";
    type = "";
}

device::device(int number, string type, string name){
    this->devicenum = number;
    this->type = type;
    this->name = name;
}

void device::addToDeviceQueue(processControlBlock *pcb ){
    this->devicequeue.push(pcb);
    cout << "process with ID: " << pcb->getpid() << " added to this queue." << endl;
}

processControlBlock* device::removeFromDevice(){
    processControlBlock *pcb = this->devicequeue.front();
    this->devicequeue.pop();
    return pcb;
}

void device::print(){
    cout << "Device name: " << this->name << endl;
    cout << "Device queue:\n" << endl;
    cout << "PID\t name\t size\t" << endl;
    for(int i = 0; i < this->devicequeue.size(); i++){
        cout << devicequeue.front()->getpid() << "\t" << devicequeue.front()->getName() << "\t" << devicequeue.front()->getSize() << endl;
    }
}

bool device::queueIsEmpty(){
    if(this->devicequeue.empty()){
        return true;
    }
    else return false;
}

#endif /* device_hpp */
