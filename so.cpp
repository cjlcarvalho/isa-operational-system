#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#define REG_NUMBER 16

using namespace std;

int load_registers(vector<string>& registers){
	for(int i = 0; i<REG_NUMBER; i++)
	    registers.push_back("");
	return 1;
}

int load_memory(map<string, string>& memory){
	string v("  ");
	for(int i = 0; i<10; i++){
		v[0] = i + 48;
		for(int j = 0; j<10; j++){
			v[1] = j + 48;
			memory[v] = "";
		}
		for(int j = 'A'; j < 'G'; j++){
			v[1] = j;
			memory[v] = "";
		}
	}

	for(int i = 'A'; i < 'G'; i++){
        v[0] = i;
        for(int j = 0; j < 10; j++){
            v[1] = j + 48;
            memory[v] = "";
        }
        for(int j = 'A'; j < 'G'; j++){
            v[1] = j;
            memory[v] = "";
        }
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
    file.clear;
    file.seekg(0);
    return 1;
}

int run_process(vector<string>& reg, map<string, string>& mem, string& start, string& end){
    
    // LER MEMÓRIA
    // EXECUTAR INSTRUÇÕES

    return 1;
}

int load_process(ifstream& file, vector<string>& reg, map<string, string>& mem){
	string line, end, val, ini, fim;
    detect_ini_fim(file, ini, fim);
	// LER ARQUIVO E FAZER AS OPERAÇÕES DE ESCRITA NOS REGS E MEMÓRIA
	if(file.is_open()){
		while(getline(file, line)){
			end = line.substr(0, 2);
			val = line.substr(3, 2);
			// AO INVÉS DE ALOCAR VAL AO ENDEREÇO DA MEMÓRIA, TENTE UTILIZAR LOGO AS OPERAÇÕES NA MEMÓRIA E REGISTRADOR
			// ALIÁS, FAÇA O SEGUINTE
			// TENTE COLOCAR TUDO NOS RESPECTIVOS ENDEREÇOS, GUARDAR O ENDEREÇO INICIAL E O FINAL
			// CHAMAR OUTRA FUNÇÃO QUE EXECUTA O QUE ESTÁ NA MEMÓRIA DO INICIO AO FIM
			mem[end] = val;
		}
		file.close();
    }
    run_process(reg, mem, ini, fim);

	return 1;
}

int main(){
	vector<string> registers;
	map<string, string> memory;
    load_registers(registers);
    load_memory(memory);
	ifstream post ("instructions/post.txt");
	load_process(post, registers, memory);
	ifstream bios ("instructions/bios.txt");
	load_process(bios, registers, memory);

	// ITERANDO PELO MAP
	
	for(map<string, string>::iterator it = memory.begin(); it != memory.end(); ++it)
		cout << "Endereço " << it->first << ": " << it->second << endl;

	// CARREGAR PERIFÉRICOS
	  // VIDEO
	  // TECLADO
	  // MOUSE
	  // PLUG AND PLAY
	// END
	
	// CARREGAR SO NA MEMÓRIA
	  // ABRIR UMA THREAD QUE FICA EM LOOP ATÉ O HALT
	// END
	
	// INICIA BASH
	  // SETAR ALGUNS COMANDOS ( TALVEZ UNS 5 )
        // HALT
        // STATUS 
            // REDE
            // IMPRESSORA
        // IMPRIMIR ARQUIVO
        // CRIAR ARQUIVO
        // LISTAR PASTA
      // END
	// END
	
	// REDE, IMPRESSORA, SCANNER, MULTIMIDIA
	  // THREADS PARA CADA UM
	// END
	
	// INDICAR SE O SO ESTÁ COM TODOS OS COMPONENTES PREPARADOS
	  // ACEITAR COMANDOS ATÉ O HALT
	// END

	return 1;
}

