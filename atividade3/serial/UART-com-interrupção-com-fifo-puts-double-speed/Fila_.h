
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
#define	FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "new.h"



template <typename T> class Fila {
public:
    // cria uma fila com capacidade "N"
    Fila();

    // cria uma fila que é cópia de outra fila
    Fila(const Fila& orig);

    // destrutor da fila
    ~Fila();

    Fila& operator=( const Fila& outra ); // OPERADOR DE ATRIBUIÇÃO
    Fila operator+(const Fila& outra);
    bool operator==(const Fila<T>& outra);

    // inverte a ordem da fila
    void inverte();

    // enfileira "algo" no fim da fila
    void enfileira(const T & algo);

    // desenfileira um dado do início da fila
    T desenfileira();

    // retorna uma referência ao dado que está no início
    // da fila, sem removê-lo da fila
    T & frente() const;

    bool vazia() const {return itens == 0; }
    unsigned int tamanho() const { return itens;}
    bool cheia() const { return itens == capacidade;}
private:
    int capacidade;
    int itens, inicio, fim;

    // a área de armazenamento da fila
    T* buffer;

    // aumenta a capacidade da fila em 1
    void aumentaCapacidade();

};

// Abaixo seguem os esqueletos das implementações dos métodos da Fila

template <typename T> Fila<T>::Fila() {
    // inicia os atributos da fila: inicialmente
    // ela está vazia
    capacidade = 1;
    inicio = 0;
    fim = 0;
    itens = 0;

    // aloca memória para guardar "capacidade" dados do tipo "T"
    buffer = new T[(capacidade)*sizeof(T)];
}

template <typename T> Fila<T>::Fila(const Fila& outra) {
  // primeiro devem-se atribuir valores aos atributos desta Fila
  // para que ela pareça vazia
    capacidade = outra.capacidade;
    inicio = 0;
    fim = 0;
    itens = 0;
  // em seguida, basta atribuir a "outra" Fila a este objeto
  // Note o uso do ponteiro predefinido "this", que sempre aponta o objeto que recebe a operação
  // dentro de um método de sua classe
  *this = outra;
}

template <typename T> Fila<T>::~Fila() {
}

template <typename T> Fila<T>& Fila<T>::operator=( const Fila& outra ) {
  // copiar os valores de atributos de "outra"
    capacidade = outra.capacidade;
    inicio = outra.inicio;
    fim = outra.fim;
    itens = outra.itens;
  // alocar memória para "buffer"
    buffer = new T[sizeof(T)*capacidade];
  // copiar conteúdo da "buffer" da "outra" fila
    for(int i = 0; i<capacidade; i++){
        (buffer[i]) = (outra.buffer[i]);
     }

  // retorna uma referência ao próprio objeto
  return *this;
}


template <typename T> Fila<T> Fila<T>::operator+(const Fila& outra){
    int tamanhoFilaOutra = outra.tamanho();

    for(int i =0 ; i<tamanhoFilaOutra; i++){
        enfileira(outra.buffer[i]);
    }

    return *this;
}

template <typename T> bool Fila<T>::operator==(const Fila<T>& outra){
    if(tamanho()!=outra.tamanho()){
        return 0;
    }

    for(int i = 0; i<tamanho(); i++){
        if(buffer[i]!=outra.buffer[i]){
            return 0;
        }
    }
    return 1;
}

template <typename T> void Fila<T>::enfileira(const T& algo) {
    if(cheia()){
        aumentaCapacidade();
    }

    buffer[fim] = algo;
    if(fim==capacidade){
        fim=0;
    } else {
        fim++;
    }
    itens++;
    //cout<< "Inicio " << inicio << " fim " << fim << " itens " << itens << " Numero " << algo << endl;

}

template <typename T> T Fila<T>::desenfileira() {
    if (!vazia ()){
         T temp = buffer[inicio]; //lê o buffer na posição início e salva o valor na variável temp.
         //cout << "Desenfileirou " << temp << " da posição: " << inicio << endl;
         if (inicio==capacidade){
             inicio = 0;
         }
         else {
             inicio++;
         }
         itens--;
         return temp;
    }

}




template <typename T> T & Fila<T>::frente() const {
    if(!vazia ()){
        return buffer[inicio];
    }
    else {
        throw -1;
    }
}


template <typename T> void Fila<T>::inverte() {
    int tamanhoFila = tamanho();
    T valoresTemp[tamanhoFila];

    for(int i=0; i<tamanhoFila; i++){
        valoresTemp[i] = desenfileira();
    }

    for(int i=tamanhoFila-1; i>=0; i--){
        enfileira(valoresTemp[i]);
    }
}

template <typename T> void Fila<T>::aumentaCapacidade() {
    //cria um novo buffer temporario com capacidade+1
	T* bufferTemp = new T[(capacidade+1)*sizeof(T)];


    // copia os valores de um buffer para o outro
    for(int i=0; i<capacidade; i++){
        bufferTemp[i] = buffer[i];
    }

    // limpa o buffer antigo da memoria
    delete [] buffer;

    //aponta buffer para os novos dados
    buffer = bufferTemp;
    capacidade++;
}


#endif	/* FILA_H */



