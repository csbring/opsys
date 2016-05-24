//
//  processControlBlock.h
//  opsys
//
//  Created by Chasmandeep Bring on 5/14/16.
//  Copyright © 2016 ChasmandeepB. All rights reserved.
//

#ifndef processControlBlock_h
#define processControlBlock_h

using namespace std;

class processControlBlock{
private:
    //needs memory, priority, process name, PID
    unsigned int memory;
    int PID;
    unsigned int priority;
    string name;
    int size;
    
public:
    processControlBlock();//default constructor
    processControlBlock(int, unsigned int, unsigned int); //overloaded const
    processControlBlock operator=(processControlBlock &); //overloaded consructor
    unsigned int getMem();  //returns memory
    int getpid(){return this->PID;};   //returns pid
    void setName(string name){this->name = name;}
    void setSize(int size){this->size = size;}
    void clear();
    string getName(){return this->name;};
    int getSize(){return this->size;};
};

processControlBlock::processControlBlock(){
    this->memory = 0;
    this->PID = 0;
    this->priority = 0;
    this->name = "";
    this->size = 0;
}

processControlBlock::processControlBlock(int pid, unsigned int mem, unsigned int priority){
    this->PID = pid;
    this->memory = mem;
    this->priority = priority;
}



processControlBlock processControlBlock::operator=(processControlBlock &pcb){
    this-> PID = pcb.PID;
    this-> memory = pcb.memory;
    this-> priority = pcb.priority;
    this-> name = pcb.name;
    return *this;
}

unsigned int processControlBlock::getMem(){
    return this->memory;
}

void processControlBlock::clear(){
    this->memory = 0;
    this->priority = 0;
    this->name = "";
    this->size = 0;
}



#endif /* processControlBlock_h */
