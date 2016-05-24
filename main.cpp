//
//  main.cpp
//  opsys
//
//  Created by Chasmandeep Bring on 5/14/16.
//  Copyright © 2016 ChasmandeepB. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include "processControlBlock.h"
#include "device.h"
#include "cpu.h"

using namespace std;

void setPrinters(vector<device> &printers){
    int num_of_printers;
    
    string type;
    cout << "Number of printers?" << endl;
    cin >> num_of_printers;
    
    for (int i = 0; i < num_of_printers; i++) {
        stringstream sname;
        string name;
        
        sname << "p" << i+1;
        name = sname.str();
        type = "printer";
        device new_device(i, type, name);
        printers.push_back(new_device);
    }
}

void setDisks(vector<device> &disks){
    int num_of_disks;
    
    string type;
    cout << "Number of disks?" << endl;
    cin >> num_of_disks;
    
    for (int i = 0; i < num_of_disks; i++) {
        stringstream sname;
        string name;
        
        sname << "d" << i+1;
        name = sname.str();
        type = "disk";
        device new_device(i, type, name);
        disks.push_back(new_device);
    }
}

void setCPU(CPU &cpu){
    unsigned int mem;
    cout << "How much memory does the system have?" << endl;
    cin >> mem;
    cpu.setMem(mem);
}

int main(int argc, const char * argv[]) {
    
    vector<device> printers;
    vector<device> disks;
    CPU cpu;
    processControlBlock *pcb;
    
    setPrinters(printers);
    setDisks(disks);
    setCPU(cpu);
    
    unsigned int processPriority;
    int pid = 0;
    unsigned int processMemory;
    
    string command;
    
    bool flag = true;
    
    cout << "Enter 0 to quit." << endl;
    while(flag){
        cin >> command;
        if(command[0] == 'A'){
            cout << "Process created. what is it's priority?" << endl;
            cin >> processPriority;
            cout << "How much memory does this Process use?" << endl;
            cin >> processMemory;
            if(cpu.getFreeMem() < processMemory){
                cerr << "Not enough mem." << endl;
                }
            else{
                pid++;
                pcb = new processControlBlock(pid, processMemory, processPriority);
                cpu.add(pcb);
            }
        }
    
    
        else if(command[0] == 't'){
            cout << "Terminating process." << endl;
            pcb = cpu.getProcess();
            pcb->clear();
            cpu.add(pcb);
        }
        
        else if(command[0] == '0'){
            cout << "Shutting down." << endl;
            return 0;
        }
        
        else if(command[0] == 'p'){
            cout << printers.size() << endl;
            for(int i = 0; i < printers.size(); i++){
                if (printers.at(i).getName()[1] == (command[1])) {
                    cout << "Adding current process to " << printers.at(i).getName() << "'s device queue." << endl;
                    processControlBlock *pcb = cpu.getProcess();
                    cout << "Process name?" << endl;
                    string name;
                    cin >> name;
                    cout << "Size?" << endl;
                    int size;
                    cin >> size;
                    cout << "Adding current process to " << disks.at(i).getName() << "'s device queue." << endl;
                    pcb->setName(name);
                    pcb->setSize(size);
                    printers.at(i).addToDeviceQueue(pcb);
                }
            }
            
        }
        
        else if(command[0] == 'd'){
            cout << disks.size() << endl;
            for(int i = 0; i < disks.size(); i++){
                if(disks.at(i).getName()[1] == (command[1])){
                    cout << "Process name?" << endl;
                    string name;
                    cin >> name;
                    cout << "Size?" << endl;
                    int size;
                    cin >> size;
                    cout << "Adding current process to " << disks.at(i).getName() << "'s device queue." << endl;
                    processControlBlock *pcb = cpu.getProcess();
                    pcb->setName(name);
                    pcb->setSize(size);
                    disks.at(i).addToDeviceQueue(pcb);
                }
            }
        }
        
        else if(command[0] == 'P'){
            cout << printers.size() << endl;
            for(int i = 0; i < printers.size(); i++){
                if (printers.at(i).getName()[1] == (command[1])) {
                    cout << "got P1" << endl;
                    processControlBlock *pcb = printers.at(i).removeFromDevice();
                    cpu.add(pcb);
                }
            }
        }
        
        else if(command[0] == 'D'){
            cout << disks.size() << endl;
            for(int i = 0; i < disks.size(); i++){
                if(printers.at(i).getName()[1] == (command[1])){
                    cout << "GOT D BLOCK" << endl;
                    processControlBlock *pcb = disks.at(i).removeFromDevice();
                    pcb->clear();
                    cpu.add(pcb);
                }
            }
        }
        
        else if(command[0] == 'S'){
            
            
            cout << "Snapshot, waiting for input." << endl;
            string comm;
            cin >> comm;
            if(comm[0] == 'r'){
                
                if(cpu.CPUIsFree()){
                    cerr<< "No processes to show" << endl;
                }

                //show pids of processes in readyqueue
                else
                    cout << cpu << endl;
                    command[0] = '4';
            }
            else if(comm[0] == 'i'){
                
                
                cout << "Printer info: " << endl;
                for(int i = 0; i < printers.size(); i++){
                    cout << "Printer name:" << "p" << i << endl;
                    if(!printers.at(i).queueIsEmpty()){
                        printers.at(i).print();
                    }
                    else cout << "Empty" << endl;
                }
                
                for(int i = 0; i < disks.size(); i++){
                    cout << "Disk name:" << "d" << i << endl;
                    
                    if(!disks.at(i).queueIsEmpty()){
                        disks.at(i).print();
                    }
                    else
                        cout << "Empty" << endl;
                    
                }
            }
            else if (comm[0] == 'm'){
            
            }
            else {
                ;
            }
        }
        
        
        else{
            cout << "Incorrect input, try again." << endl;
        }
        
        
    }
    
    
    return 0;
}



