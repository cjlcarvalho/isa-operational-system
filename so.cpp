#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

int bin_to_int(string bin){
    char a = bin[0];
    char b = bin[1];
    int a1, b1;
    if(a >= '0' && a <= '9')
        a1 = a - 48;
    else if(a >= 'A' && a <= 'F')
        a1 = a - 55;
    if(b >= '0' && b <= '9')
        b1 = b - 48;
    else if(b >= 'A' && b <= 'F')
        b1 = b - 55;
    a = a << 4;
    return a + b;
}

string int_to_bin(int a){
    int r = a % 16;
    char r1, a1;
    string result;
    if(a > 15)
        a -= 15;
    else
        a -= (a % 16);
    a = a >> 4;
    r1 = (r < 10) ? (r + 48) : (r + 55);
    a1 = (a < 10) ? (a + 48) : (a + 55);
    result.push_back(a1);
    result.push_back(r1);
    return result;
}

void load_mem(map<string, string>& registers, map<string,string>& memory, string inst1, string inst2, auto& PC){
    registers[inst1.substr(1, 1)] = memory[inst2];
    ++PC;
}

void load_bits(map<string, string>& registers, string inst1, string inst2, auto& PC){
    registers[inst1.substr(1, 1)] = inst2;
    ++PC;
}

void store(map<string, string>& registers, map<string, string>& memory, string inst1, string inst2, auto& PC){
    memory[inst2] = registers[inst1.substr(1, 1)];
    ++PC;
}

void move(map<string, string>& registers, string inst1, auto& PC){
    registers[inst1.substr(1, 1)] = registers[inst1.substr(1, 1)];
    ++PC;
}

void add_comp_two(map<string, string>& registers, string inst1, string inst2, auto& PC){
    int a = bin_to_int(registers[inst2.substr(0, 1)]);
    int b = bin_to_int(registers[inst2.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(a + b);
    ++PC;
}

void add(map<string, string>& registers, string inst1, string inst2, auto& PC){
    float a = bin_to_int(registers[inst2.substr(0, 1)]);
    float b = bin_to_int(registers[inst2.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(a + b);
    ++PC;
}

void orr(map<string, string>& registers, string inst1, string inst2, auto& PC){
    int a = bin_to_int(registers[inst2.substr(0, 1)]);
    int b = bin_to_int(registers[inst2.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(a | b);
    ++PC;
}

void andd(map<string, string>& registers, string inst1, string inst2, auto& PC){
    int a = bin_to_int(registers[inst2.substr(0, 1)]);
    int b = bin_to_int(registers[inst2.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(a & b);
    ++PC;
}

void xorr(map<string, string>& registers, string inst1, string inst2, auto& PC){
    int a = bin_to_int(registers[inst2.substr(0, 1)]);
    int b = bin_to_int(registers[inst2.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(a ^ b);
    ++PC;
}

int rotl(int v, int shift) {
    int s =  (shift >= 0) ? (shift % 32) : -((-shift)%32);
    return (v<<s) | (v>>(32-s));
}

void rotate(map<string, string>& registers, string inst1, string inst2, auto& PC){
    int shift = bin_to_int(inst2.substr(1, 1));
    int r = bin_to_int(registers[inst1.substr(1, 1)]);
    registers[inst1.substr(1, 1)] = int_to_bin(rotl(r, shift));
    ++PC;
}

void jump(map<string, string>& registers, map<string, string>& mem, string inst1, string inst2, auto& PC){
    if(registers[0] == registers[inst1.substr(1, 1)]){
        PC = mem.find(inst2);
        --PC;
    }
}

bool halt(){
    return true;
}

int load_registers(map<string, string>& registers){
    registers["0"] = "";
    registers["1"] = "";
    registers["2"] = "";
    registers["3"] = "";
    registers["4"] = "";
    registers["5"] = "";
    registers["6"] = "";
    registers["7"] = "";
    registers["8"] = "";
    registers["9"] = "";
    registers["A"] = "";
    registers["B"] = "";
    registers["C"] = "";
    registers["D"] = "";
    registers["E"] = "";
    registers["F"] = "";
    return 1;
}

int load_memory(map<string, string>& memory){
    string v("  ");
    for(int i = '0'; i < 'G'; i++){
        v[0] = i;
        for(int j = '0'; j < 'G'; j++){
            v[1] = j;
            memory[v] = "";
            if(j == '9')
                j = 'A' - 1;
        }
        if(i == '9')
            i = 'A' - 1;
    }
    return 1;
}

int detect_ini_fim(ifstream& file, string& inicio, string& fim){
    string line;
    if(file.is_open()){
        getline(file, line);
        inicio = line.substr(0, 2);
        while(getline(file, line)){}
        fim = line.substr(0, 2);
    }
    file.clear();
    file.seekg(0);
    return 1;
}

int run_process(map<string, string>& reg, map<string, string>& mem, string& start, string& end){
    bool ht;
    auto PC = mem.find(start);
    while(PC != mem.find(end)){
        ht = false;
        switch(PC->second[0]){
            case '1': load_mem(reg, mem, PC->second, next(PC, 1)->second, PC); break;
            case '2': load_bits(reg, PC->second, next(PC, 1)->second, PC); break;
            case '3': store(reg, mem, PC->second, next(PC, 1)->second, PC); break;
            case '4': move(reg, next(PC, 1)->second, PC); break;
            case '5': add_comp_two(reg, PC->second, next(PC, 1)->second, PC); break;
            case '6': add(reg, PC->second, next(PC, 1)->second, PC); break;
            case '7': orr(reg, PC->second, next(PC, 1)->second, PC); break;
            case '8': andd(reg, PC->second, next(PC, 1)->second, PC); break;
            case '9': xorr(reg, PC->second, next(PC, 1)->second, PC); break;
            case 'A': rotate(reg, PC->second, next(PC, 1)->second, PC); break;
            case 'B': jump(reg, mem, PC->second, next(PC, 1)->second, PC); break;
            case 'C': ht = halt(); break; 
        }
        if(ht)
            break;
        ++PC;
    }

    return 1;
}

int start_bash(thread& rede, thread& scanner, thread& multimidia){
    string op, file_name, content;
    cout << "BASH STARTING ";
    for(int i = 0; i<3; i++){
        cout << ".";
        sleep(1);
    }
    cout << endl;
    cout << "ISA OPERATIONAL SYSTEM" << endl;
    map<string, string> files;
    while(true){
        cout << "C:\\ "; 
        cin >> op;
        if(!op.compare("HALT")){
            break;
        }
        else if(!op.compare("REDE")){
            if(rede.joinable())
                cout << "REDE DISPONÍVEL" << endl;
            else
                cout << "REDE INDISPONÍVEL" << endl;
        }
        else if(!op.compare("IMPRESSORA")){
            if(scanner.joinable())
                cout << "IMPRESSORA DISPONÍVEL" << endl;
            else
                cout << "IMPRESSORA INDISPONÍVEL" << endl;
        }
        else if(!op.compare("MULTIMIDIA")){
            if(multimidia.joinable())
                cout << "MULTIMIDIA DISPONÍVEL" << endl;
            else
                cout << "MULTIMIDIA INDISPONÍVEL" << endl;
        }
        else if(!op.compare("PRINT")){
            cout << "FILE: " << endl;
            cin >> file_name;
            if(files.find(file_name) != files.end())
                cout << "CONTENT: " << files.find(file_name)->second << endl;
            else
                cout << "THIS FILE DOES NOT EXIST" << endl;
        }
        else if(!op.compare("NEW")){
            cout << "NEW FILE: " << endl;
            cin >> file_name;
            cout << "CONTENT: ";
            cin >> content;
            files[file_name] = content;
        }
        else if(!op.compare("LIST")){
            cout << "LIST OF FILES" << endl;
            for(auto it = files.begin(); it != files.end(); ++it)
                cout << it->first << endl;
        }
        else if(!op.compare("HELP")){
            cout << "COMMANDS: " << endl;
            cout << "REDE" << endl;
            cout << "IMPRESSORA" << endl;
            cout << "MULTIMIDIA" << endl;
            cout << "PRINT" << endl;
            cout << "NEW" << endl;
            cout << "LIST" << endl;
            cout << "HALT" << endl;
            cout << "CLEAR" << endl;
        }
        else if(!op.compare("CLEAR")){
            #if __WIN32__
                system("cls");
            #else
                system("clear");
            #endif
        }
        else
            cout << "UNKNOWN OPERATION" << endl;
    }
    return 1;
}

int load_process(ifstream& file, map<string, string> reg, map<string, string> mem){
    string line, end, val, ini, fim;
    detect_ini_fim(file, ini, fim);
    if(file.is_open()){
        while(getline(file, line)){
            end = line.substr(0, 2);
            val = line.substr(3, 2);
            mem[end] = val;
        }
        file.close();
    }
    run_process(reg, mem, ini, fim);
    return 1;
}

int main(){
    map<string, string> registers;
    map<string, string> memory;
    load_registers(registers);
    load_memory(memory);
    ifstream post ("instructions/post.txt");
    load_process(post, registers, memory);
    ifstream bios ("instructions/bios.txt");
    load_process(bios, registers, memory);

    ifstream video("instructions/video.txt");
    ifstream teclado("instructions/teclado.txt");
    ifstream mouse("instructions/mouse.txt");
    ifstream pnp("instructions/pnp.txt");

    thread t1(load_process, ref(video), registers, memory);
    thread t2(load_process, ref(teclado), registers, memory);
    thread t3(load_process, ref(mouse), registers, memory);
    thread t4(load_process, ref(pnp), registers, memory);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ifstream sistema("instructions/sistema.txt");
    thread so(load_process, ref(sistema), registers, memory);

    ifstream rede("instructions/rede.txt");
    ifstream scanner("instructions/scanner.txt");
    ifstream multimidia("instructions/multimidia.txt");
    
    thread redes(load_process, ref(rede), registers, memory);
    thread scanners(load_process, ref(scanner), registers, memory);
    thread multimidias(load_process, ref(multimidia), registers, memory);
    start_bash(redes, scanners, multimidias);

    redes.join();
    scanners.join();
    multimidias.join();
    so.join();

    return 0;
}