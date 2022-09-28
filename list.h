// =================================================================
//
// File: list.h
// Author: Sven Chavez Garcia
// Date: 
// 
// =================================================================
#ifndef LIST_H
#define LIST_H

#include <string>

#include <sstream>
#include "exception.h"
#include "header.h"
#include <iostream>

template <class T> class List;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {
}

// =================================================================
// Definition of the List class
// =================================================================
template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;
#pragma region a
public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;
#pragma endregion a
};


// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
List<T>::List() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the list.
// =================================================================
template <class T>
List<T>::~List() {
	clear();
}

// =================================================================
// Returns if the list is empty or not
//
// @returns true if the list is empty, false otherwise.
// =================================================================
template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the list.
//
// @returns size, the number of items in the list.
// =================================================================
template <class T>
uint List<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the list.
//
// @returns true if val is in the list, false otherwise
// =================================================================
template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the list.
// =================================================================
template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the list.
//
// @returns a string containing all the elements of the list.
// =================================================================
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the list.
//
// @returns the object T at the beginning of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the list.
//
// @returns the object T at the end of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the element that is in the position indicated by index.
//
// @returns the element in index
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::get(uint index) const { 
	Node<T> *p; // creamos un apuntador de tipo nodo para obtener el valor
	p = head; // lo igualamos a head para que sea el primer elemento en la lista [0]

	if(index == 0){ 
		return head->value; // si el valor que estan buscando es el primero se devuelve el valor [0]
	}

	if ((index < 0) || (index >= size)) throw IndexOutOfBounds(); // en caso de que el index sea menor a 0 o mayor al tamaño se marca error

	for (int i = 0; i < index; i++)
	{
		p = p->next; // recorremos la lista una vez para poder encontrar el valor del index O(n)
	}

	return p->value; //retornamos el valor 
}

// =================================================================
// Add an item to the beginning of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = NULL;
	p->next = q;
	size++;
}

// =================================================================
// Add an element in index (0 <= index <= size). The element that
// was in that position is shifted to the right.
//
// @throws IndexOutOfBounds, if index > size.
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	if (index < 0 || index > size){
		throw IndexOutOfBounds(); // checamos que el index este dentro del rango
	}

	if(index == 0) {
		push_front(val); // en caso de que lo quieran en la primera posicion se regresa el pushfront
		return;
	};
	Node<T> *aux, *nuevo; //creamos un nodo auxiliar y el nuevo a insertar
	int cont = 1; // inicializamos el contador en 1 
	if (empty()) { 
		push_front(val); // si la lista esta vacia aplicamos pushfront
		return;
	}
	aux = head; //  igualamos el auxiliar al head
	while (cont < index) 
	{
		aux = aux->next; // recorremos la lista hasta llega a la posicion desada O(n)
		cont++; // aumentamos el contador 
	};
	nuevo = new Node<T>(val); // asignamos un nuevo nodo a la memoria dinamica
	nuevo->next = aux->next; // igualamos los apuntadores para hacer el cambio
	aux->next = nuevo; // y modificamos el apuntador anterior al nuevo nodo
	size++; //aumentamos el tamnio 
	return;
	
}

// =================================================================
// Delete the item at the beginning of the list.
//
// @returns the element that was at the beginning of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_front() {
	T val;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;
	return val;
}

// =================================================================
// Delete the item at the end of the list.
//
// @returns the element that was at the end of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}

	q->next = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the element found in index (0 <= index <size).
//
// @returns the element that was in index.
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::remove_at(uint index) {
	T val; // el valor a regresar
	if (empty()){
		throw NoSuchElement(); // si no hay nada en la lista regresar error
	}
	if (index < 0 || index > size){
		throw IndexOutOfBounds(); // si hay algo fuera de rango mandar error 
	}
	if (index == 0){
		return pop_front(); // si es el de hasta adelante entonces usar popfront
	}
	Node<T> *p, *q; //creamos un auxiliares para quitar un nodo
	int cont = 0; //contador
	p = head; // igualamos a head
	q = NULL; // igualamos a null que va a recorrer la lista
	while (cont < index)
	{
		q = p; // igualamos a p
		p = p->next; // movemos p a la siguiente posicion
		cont++; // aumentamos el contador O(n)
	};
	val = p->value; // el valor a regresar para saber cual quitamos 
	q->next = p->next;// igualamos el apuntador q al p para eliminar el nodo de en medio 
	delete p; // eliminamos el espacio en memoria 
	size--; // reducimos el tamanio
	return val; //regresamos el valor quitado 
}

// =================================================================
// Returns the position of an item in the list.
//
// @returns the position of an item in the list, -1 otherwise.
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
long int List<T>::indexOf(T val) const {
	if (contains(val) == false){ 
		return -1; // verificamos si el valor existe en la lista si no regresamos -1
	}
	int cont = 0;
	Node<T> *p; // creamos un nodo para regresar el index
	p = head; // igualamos al head de la lista

	while (true)
	{
		if (p->value == val){
			return cont; // si se encuentra el valor se detiene el contador y se regresa la posicio
			break; // se rompe el ciclo 
		}
		p = p->next; // de lo contrario se recorre la lista O(n)
		cont++; // se aumenta el contador
	}

}

#endif /* LIST_H */
