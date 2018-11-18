/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Fila.h
 * Author: schaiana
 *
 * Created on 8 de Abril de 2016, 11:05
 */

#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T, int capacidade> class Fila {
public:

	Fila() {
		limpa_fila();
	}

	~Fila() {};

	void enfileira(const T & obj) {

	  if ( itens == capacidade ) return;

	  buffer[fim] = obj;
	  itens++;
	  fim++;

	  if (fim == capacidade ) fim = 0;

	}

	T desenfileira() {

	  T temp = buffer[inicio];
	  inicio++;
	  itens--;

	  if ( inicio == capacidade ) inicio = 0;

	  return temp;
	}

	void limpa_fila() {

		inicio =0;
		fim = 0;
		itens = 0;

		memset((void*) buffer, 0, capacidade * sizeof(T));
	}



    void inverte() {
        int tamanhoFila = tamanho();
        T valoresTemp[tamanhoFila];

        for(int i=0; i<tamanhoFila; i++){
            valoresTemp[i] = desenfileira();
        }

        for(int i=tamanhoFila-1; i>=0; i--){
            enfileira(valoresTemp[i]);
        }
    }

    T & frente() const {
        if(!vazia ()){
            return buffer[inicio];
        }
        else {
            throw -1;
        }
    }

    	bool vazia() const {
    		return itens == 0;
    	}
    	bool cheia() const {
    		return itens == capacidade;
    	}
    	int tamanho() const {
    		return itens;
    	}


    private:
        int itens, inicio, fim;
        T buffer[capacidade];
};

#endif /* FILA_H_ */
