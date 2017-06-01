/*
 * SingletonPattern.h
 *      Author: Burak Sonmez , Oğuzhan Sarıtaş
 */

#ifndef SINGLETONPATTERN_H_
#define SINGLETONPATTERN_H_

#include<iostream>
#include <time.h>
#include "TemplatePattern.h"

using namespace std;

class ProcessManager;//Declaration

// SINGLETON PATTERN
class ThreadPool{

	private:
		LightThreadFactory* LightThreadFac;
		HeavyThreadFactory* HeavyThreadFac;

		static ThreadPool* Unique_Pool;

		ProcessManager* AttachedCPU;

		ThreadPool(ProcessManager* CPU){


			cout<<"Thread Pool created!"<<endl;

			this->AttachedCPU=CPU; // Bind CPU

			this->LightThreadFac = new LightThreadFactory(); //factory instance
			this->HeavyThreadFac = new HeavyThreadFactory(); //factory instance

			this->Table = new ThreadTable(); // new thread table
			this->NewCreateThreadToTable(4);	 //size of parameter from table
		}
	public:
		ThreadTable* Table;
		ThreadTable* getTable(){
			return this->Table;
		}
		static ThreadPool* NewPool(ProcessManager* CPU){

			if(Unique_Pool == NULL){
				Unique_Pool = new ThreadPool(CPU);
				return ThreadPool::Unique_Pool;
			}
			else{
				cout<<"Pool Created!"<<endl;
				return ThreadPool::Unique_Pool;
			}
		}

	// MANAGE LINKED LIST
		void NewCreateThreadToTable(int Size){

			srand(time(NULL));
			for(int u=0;u<Size;u++){
				if(rand()%2 == 0) // LightThreadFac or HeavyThreadFac Random

					this->Table->newThread(HeavyThreadFac->CreateNewThread());
				else
					this->Table->newThread(LightThreadFac->CreateNewThread());
			}
			cout<<"CPU add thread to the table and list:"<<endl;

			this->Table->showTreads(this->Table);

		}


		//Simulate

		void AllocateMemory(int Size){
			cout<<"Memory Allocated!"<<endl;
		}
		void CreateTable(int Size,int Priority){
			cout<<"Enter the table!"<<endl; // Simulate
		}
		void
		OrganizeOrder(int Priority){
			cout<<"Priority Allocated!"<<endl; //Simulate
		}


};


ThreadPool* ThreadPool::Unique_Pool = NULL;



#endif // SINGLETONPATTERN_H_
