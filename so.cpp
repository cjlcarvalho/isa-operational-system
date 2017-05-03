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

int load_memory(map <string, string>& memory){
	char v[2];
	// ULTIMO CHAR ESTÁ COM LIXO
	for(int i = 0; i<10, i++){
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

	for(int i = 'A'; j < 'G'; j++){
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

int run_process(ifstream& file, vector<string>& reg, map <string, string>& mem){
	string line, end, val;
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
	return 1;
}

int main(){
	vector<string> registers;
	map <string, string> memory;
  load_registers(registers);
  load_memory(memory);
	ifstream post ("post.txt");
	run_process(post, registers, memory);
	ifstream bios ("bios.txt");
	run_process(bios, registers, memory);

	// ITERANDO PELO MAP
	
	for(map <string, string>::iterator it = memory.begin(); it != memory.end(); ++it)
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
	// END
	
	// REDE, IMPRESSORA, SCANNER, MULTIMIDIA
	  // THREADS PARA CADA UM
	// END
	
	// INDICAR SE O SO ESTÁ COM TODOS OS COMPONENTES PREPARADOS
	  // ACEITAR COMANDOS ATÉ O HALT
	// END

	return 1;
}

