/*
 * IteratorPattern.h
 * Author      : Burak Sonmez, Oğuzhan Sarıtaş
 */

#ifndef ITERATORPATTERN_H_
#define ITERATORPATTERN_H_


#include<iostream>

#include "FactoryPattern.h"

using namespace std;
/*
 * ++++ Iterator Pattern CHECKED ++++
 */


//Iterator Pattern STARTS

//Abstract Iterator
class Iterator{
	protected:
	//Abstract Iterator implemented as usual
		virtual Threads* First() = 0;
		virtual Threads* Next() = 0;
		virtual bool IsDone(int required) = 0;
		virtual Threads* CurrentThread(Threads* Current) = 0;
		virtual ~Iterator(){};
};

//Abstract Aggregate
class AggregateIterator{
	protected:
	//Abstract Aggregate implemented as usual
		virtual Threads* checkThread(int Size) = 0;
		virtual void newThread(Threads* addTread) = 0;
		virtual ~AggregateIterator(){};
};

//Concrete Iterator
class ThreadTableIterator:public Iterator{
	public:
		ThreadTableIterator(){
			cout<<"ThreadTableIterator created!"<<endl;
		}
		~ThreadTableIterator(){
			cout<<"ThreadTableIterator deleted!"<<endl;
		}
		Threads* First(){
			return NULL;
		}
		Threads* Next(){
			return NULL;
		}
		bool IsDone(int check){
			return false;
		}
		Threads* CurrentThread(Threads* Current){
			return Current;
		}
};

/*Concrete Aggregate*/
class ThreadTable:public AggregateIterator{
	private:
		Threads* First; // The First thread
		ThreadTableIterator* _tti; //Thread Table's iterator
	public:
		ThreadTable(){
			cout<<"Thread Table is Created!"<<endl;
			this->First = NULL; // Initinals null for the first
			this->_tti = new ThreadTableIterator();  // creates new table
		}
		~ThreadTable(){
			cout<<"Thread Table is deleted!"<<endl;
		}
		Threads* getFirst(){
			return this->First;
		}
		 Threads* checkThread(int Size){ // Finds an avaible thread and assign is as many as size
			for(Threads* _check = this->First; _check != NULL ; _check=_check->Next){
				if(_check->getState() == 0 && _check->getSize() == Size)
					return _check;
				else
					continue;
			}
		return NULL;
		}
		void newThread(Threads* addTread){ //adds new threads
			if(First == NULL){ // If there is no assing(add) as first in the stack
				this->First = addTread;
			}else{ //If there is First then add next.FILO(first in last out)
				addTread->Next = this->First;
				this->First = addTread;
			}
		}
		void showTreads(ThreadTable* _row){ // to show all treads assigned
			if(_row->First!=NULL){
					for(Threads* First = _row->First ; First != NULL ; First=First->Next)
						cout<<_row<<" = "<<First->getSize()<<"MB"<<endl;
					}
			else
				cout<<"Table is empty"<<endl;
		}
};

//Iterator Pattern ENDS

#endif // ITERATORPATTERN_H_
