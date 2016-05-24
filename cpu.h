//
//  cpu.h
//  opsys
//
//  Created by Chasmandeep Bring on 5/14/16.
//  Copyright © 2016 ChasmandeepB. All rights reserved.
//

#ifndef cpu_h
#define cpu_h
using namespace std;

class CPU{
private:
    queue<processControlBlock*> readyQueue;
    int memorySize;
    processControlBlock *pcbUsingCPU;
    void addToReadyQueue(processControlBlock *);    //adds to readyqueue
public:
    CPU();
    bool CPUIsFree(); //checks if CPU is empty
    void setMem(unsigned int);
    void removeFromCPU();   //removes current process and puts next one in CPU
    void add(processControlBlock*);
    unsigned int getFreeMem(){return this->memorySize;}
    processControlBlock* getProcess();  //returns current process and removes from CPU
    friend ostream &operator<<(ostream &, CPU); //overloaded << prints CPU readyQueue
};

CPU::CPU(){
    this->memorySize = 0;
    this->pcbUsingCPU = NULL;
}

void CPU::addToReadyQueue(processControlBlock *pcb){
    readyQueue.push(pcb);
    this->memorySize-=pcb->getMem();
}

bool CPU::CPUIsFree(){
    if(!pcbUsingCPU){
        return true;
    }
    else return false;
}

void CPU::setMem(unsigned int mem){
    this->memorySize = mem;
}

void CPU::add(processControlBlock* pcb){
    if(CPUIsFree()){
        pcbUsingCPU = pcb;
        if(this->memorySize < pcb->getMem()){
            cerr << "Cannot add, not enough memory. Terminate some processes." << endl;
        }
        else{
            this->memorySize = this->memorySize - pcb->getMem();
        }
        cout <<"Free memory: " << this-> memorySize << endl;
    }
    else{
        addToReadyQueue(pcb);
        cout << "Free memory: " << this-> memorySize << endl;
    }
}

void CPU::removeFromCPU(){
    if(CPUIsFree()){
        cout << "No processes" << endl;
        return;
    }
    else if(!CPUIsFree()){
        processControlBlock *pcb = this->pcbUsingCPU;
        this->memorySize = this->memorySize + pcb->getMem();
        this->pcbUsingCPU = NULL;
        delete pcb;
    }
    if(!this->readyQueue.empty()){
        pcbUsingCPU = readyQueue.front();
        readyQueue.pop();
        cout << "Free memory: " << this->memorySize << endl;
    }
}

processControlBlock* CPU::getProcess(){
    processControlBlock *pcb;
    if(CPUIsFree()){
        cout << "No Processes." << endl;
        return NULL;
    }
    else if(!CPUIsFree()){
        pcb = this->pcbUsingCPU;
        this->memorySize += pcb->getMem();
        pcbUsingCPU = NULL;
        
        if(!readyQueue.empty()){
            this->pcbUsingCPU = this->readyQueue.front();
            this->readyQueue.pop();
        }
    }
    return pcb;

}

ostream &operator<<(ostream &output, CPU cpu){
    output << "Process in CPU PID: " << cpu.pcbUsingCPU->getpid() << endl;
    output << "Ready Queue:\n PID\t" << endl;
    for(int i = 0; i < cpu.readyQueue.size(); i++){
        output << cpu.readyQueue.front()->getpid() << endl;;
        cpu.readyQueue.pop();
    }
    
    return output;
}




#endif /* cpu_h */
