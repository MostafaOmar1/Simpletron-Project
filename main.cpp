#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

void runSimpletron();
void displayMemPortion(const int* a); 
int formInstruction(const int instruct, const int);
void output (int accum, int currentLocation, int OpCode, int memToapplay);
void displayInterfaceInstructions();
void enterInstruction(int currentLocation, int instruction, int mem[]);

void displayMem(const int mem[], const size_t SIZE);
int convertToInteger(const string& hexa);


int main() {
    runSimpletron();
   
    
    return 0;
    }
    
void runSimpletron() {
//input / output operation
    const int read{10};
    const int write{11};
// load & store operations    
    const int load{20};
    const int store{21};

// arithmetic operations
    const int add{30};
    const int subtract{31};
    const int divide{32};
    const int multiply{33};
    const int mod{34};
    const int exponentiatiion{35};
// transfer of control
    const int branch{40};
    const int branchneg{41};
    const int branchzero{42};
    const int halt{43};

    
    int instruction{0};
    size_t currentLocation{0};
    
    const size_t SIZE{100};
    int mem[SIZE]{};
    int accum{0};
    int OpCode{0};
    int memToapplay{0};

    displayInterfaceInstructions();
    enterInstruction(currentLocation, instruction, mem);
    bool loopCondition{true};

    while (loopCondition) {
        output(accum, currentLocation, OpCode, memToapplay);
        displayMem(mem, SIZE);

        instruction = mem[currentLocation];
        
        OpCode = instruction / 100;
        memToapplay = instruction % 100;
        
        if (OpCode > 0) {
            mem[currentLocation] = OpCode * 100 + memToapplay;
            
            if (OpCode == read) {
                int input{0};
                cout << "Enter value to store in " << memToapplay << ": ";
                cin >> input;
                mem[memToapplay] = input;
            }
            
            else if (OpCode == write) {
                cout << "The value is: " << mem[memToapplay] << endl;
            }
            
            else if(OpCode == load) {
                if (mem[memToapplay] > -9999 && mem[memToapplay] < 9999) {
                    accum = mem[memToapplay];
                }
                else {
                    cout << "***Accumulator overflow happens***"  << endl;
                    loopCondition = false;
                }
                //cout << "Loaded to accumlator" << endl;
            }
            
            else if (OpCode == store) {
                mem[memToapplay] = accum;
                //cout << "stored from accumlator" << endl;
            }
            
            else if (OpCode == add) {
                int op1{mem[memToapplay] + accum};
                if (op1 > -9999 && op1 < 9999) {
                    accum += mem[memToapplay];
                }
                else {
                    cout << "***Accumulator overflow happens***"  << endl;
                    loopCondition = false;
                }                
                //cout << "Added to accumlator" << endl;
            }
            
            else if (OpCode == subtract) {
                int op1{accum - mem[memToapplay]};
                if (op1 > -9999 && op1 < 9999) {
                    accum -= mem[memToapplay];
                }
                else {
                    cout << "***Accumulator overflow happens***"  << endl;
                    loopCondition = false;
                }                
            }
            
            else if (OpCode == divide) {
                if (mem[memToapplay] != 0) {
                    accum = mem[memToapplay] / accum;
                }
                else {
                    cout << "*** Attempt to divide by zero ***" << endl;
                    cout << "*** Simpletron execution abnormally terminated ***" << endl;
                    loopCondition = false;
                }
            }
            
            else if (OpCode == multiply) {
                int op1{accum * mem[memToapplay]};
                if (op1 > -9999 && op1 < 9999) {
                     accum *= mem[memToapplay];
                }
                else {
                    cout << "***Accumulator overflow happens***"  << endl;
                    loopCondition = false;
                }                        
            }
            
            else if (OpCode == mod) {
                accum = mem[memToapplay] % accum;
            }
            
            else if (OpCode == exponentiatiion) {
                accum = pow(accum, mem[memToapplay]);
            }
            
            else if (OpCode == branch) {
                currentLocation = memToapplay - 1;
                //cout << "branch to " << memToapplay << endl;
            }
            
            else if (OpCode == branchneg) {
                if (accum < 0) {
                    currentLocation = memToapplay - 1 ;
                }
            }
            else if (OpCode == branchzero) {
                if (accum == 0) {
                    currentLocation = memToapplay - 1;
                }
            }
            else if (OpCode == halt) {
                    currentLocation = 0;
                    loopCondition = false;
            }
            else {
                cout << "***Invalid Code Operation****" << endl;
            }
        }
        else {
            mem[memToapplay] = instruction;
            if (instruction == -9999) {
                loopCondition = false;
            }
        }
        
        currentLocation++;
        
   //displayMemPortion(mem);
    }
}    
void displayMemPortion(const int* a) {
    for (size_t i{0}; i < 10; i++) {
        cout << setw(5) << a[i];
    }
    cout << endl;
}

int formInstruction(const int instruct, const int pos) {
    return ((instruct * 100) + pos);
}

void output (int accum, int currentLocation, int OpCode, int memToapplay) {
        cout << "REGISTERS:" << endl;
        cout << "accumulator:         " << setw(5) << setfill('0') << internal << accum << endl;
        cout << noshowpos;
        cout << "instructionCounter:     " << setw(2) << setfill('0')  << internal << currentLocation << endl;
        cout << showpos;
        cout << "instructionRegister: " << setw(5) << setfill('0') << internal << accum << endl;
        cout << noshowpos;
        cout << "operationCode:          " << setw(2) << setfill('0') << internal<< OpCode << endl;
        cout << "operand:                " << setw(2) << setfill('0') << internal << memToapplay << endl;
}

void displayInterfaceInstructions() {
cout << "    *** Welcome to Simpletron! ***" << endl;
cout << "*** Please enter your program one instruction ***" << endl;
cout << "*** (or data word) at a time. I will type the ***" << endl;
cout << "*** location number and a question mark (?). ***" << endl;
cout << "*** You then type the word for that location. ***" << endl;
cout << "*** Type the sentinel -99999 to stop entering ***" << endl;
cout << "*** your program. ***" << endl;
}

void enterInstruction(int currentLocation, int instruction, int mem[]) {
    if (currentLocation >= 100) {
        return;
    }
    
    while (instruction != -9999) {
            cout << noshowpos;
            cout << setw(2) << setfill('0') << internal << currentLocation << " ? ";
            if (instruction > -9999 && instruction <= 9999) {
                cin >> instruction;
                mem[currentLocation] = instruction;
                currentLocation++;
            }
            else {
                cout << "Invalid Instuction! please, re-enter the instruction" << endl;  
                instruction = 0;
            }
    }
    
    cout << "*** Program loading completed ***" << endl;
    cout << "*** Program execution begins ***" << endl;    
}

void displayMem(const int mem[], const size_t SIZE) {
    cout << "--------------------------------------------------------------" << endl;
    cout << setfill(' ');
    cout << "  " << setw(6) << 0 << setw(6) << 1 << setw(6) << 2 << setw(6) << 3 <<setw(6)
    << 4 << setw(6) << 5 << setw(6) << 6 << setw(6) << 7 << setw(6) << 8 << setw(6) << 9 << endl;
    
    unsigned int column{0};
    cout << setw(2) << column << " ";
    for (size_t i{0}; i < SIZE; i++) {
        cout << showpos;
        cout << setw(5) << setfill('0') << internal << mem[i] << " ";
        
        if ((i + 1)% 10 == 0 && column != 90) {
            cout << endl;
            column += 10;
            cout << setw(2) << column << " "; 
        }
    }
    cout << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << setfill(' ') << noshowpos;
}

/*int convertToInteger(const string& hexa) {
    static long long postionalVals[4]{}; 
    int exponent{3};
    int accumulator{0};
    
    for (int j{0}; j < hexa.length(); j++) {
    for (int i{3}; i >= 0 ; i--) {
        postionalVals[i] = pow(16, exponent);
        exponent--;
        
     }
    }
    return 1;
        
}*/