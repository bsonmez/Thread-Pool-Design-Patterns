/*
 * FactoryPattern.h
 * Author      : Burak Sonmez, Oğuzhan Sarıtaş
 */

#ifndef FACTORYPATTERN_H_
#define FACTORYPATTERN_H_

#include<iostream>

using namespace std;
/*
 * ++++ Factory Pattern CHECKED ++++
 */


//Factory Pattern STARTS

//Abstract
class Threads{
public:
		Threads* Next; // next tread
		virtual int getSize() =0; //to get private size data
		virtual void setState() =0; // to change state of the tread
		virtual bool getState() =0; // to get state of the tread
		virtual void run() = 0;// runs
		virtual void stop() = 0; // stops
		virtual ~Threads(){
			cout<<"Threads has been deleted!"<<endl;
		};
	protected:
		int _order;  //its priority
		bool _state; //Busy or avaible =  IDLE:0 , BUSY:1;
		int _size;   //Tread size
};

//Concrete 1 ( Light Tread )
class LThread:public Threads{
	public:
		LThread(){
			cout<<"A LThread is Created"<<endl;
			this->Next=NULL;
			this->_size = 256; //256 MB
			this->_order= 1;
			this->_state = 0;
		}
		~LThread(){
			cout<<"Light Thread has been deleted"<<endl;
		}
		int getSize(){
			return this->_size;
		}
		void setState(){
			this->_state = (this->getState()+1) % 2;// swaps busy to avaible or vice verse
		}
		bool getState(){
			return this->_state;
		}
		void run(){
			cout<<"Light Thread's running"<<endl;
			this->_state = 1;
		}
		void stop(){
			cout<<"Light Thread is exiting."<<endl;
			this->_state = 0;
		}
};

//Concrete 2 ( Heavy Tread )
class HThread:public Threads{
	public:
		HThread(){
			cout<<"A HThread is Created!"<<endl;
			this->Next=NULL;
			this->_size = 512; //512 MB
			this->_order= 5;
			this->_state = 0;
		}
		~HThread(){
			cout<<"Light Thread has been deleted"<<endl;
		}
		void run(){
			cout<<"Heavy Thread's running"<<endl;
			this->_state = 1;
		}
		void stop(){
			cout<<"Heavy Thread is exiting."<<endl;
			this->_state = 0;
		}
		int getSize(){
			return this->_size;
		}
		void setState(){
			this->_state = (this->getState()+1) % 2; // swaps busy to avaible or vice verse
		}
		bool getState(){
			return this->_state;
		}
};


//Abstract Factory
class ThreadFactory{
	protected:
		virtual Threads* CreateNewThread() = 0;
		~ThreadFactory(){
			cout<<"Thread Factory is deleted."<<endl;
		}
};

//Concrete 1
class HeavyThreadFactory:public ThreadFactory{
	public:
		HeavyThreadFactory(){
			cout<<"Heavy Thread Factory is created."<<endl;
		}
		virtual ~HeavyThreadFactory(){
			cout<<"Heavy Thread Factory is deleted."<<endl;
		}
		Threads* CreateNewThread(){ // Pure virtual method comes from base class and creates Heavy Tread
			return new HThread();
		}
};

//Concrete 2
class LightThreadFactory:public ThreadFactory{
	public:
		LightThreadFactory(){
			cout<<"Light Thread Factory is created."<<endl;
		}
		virtual ~LightThreadFactory(){
			cout<<"Light Thread Factory is deleted."<<endl;
		}
		Threads* CreateNewThread(){ // Pure virtual method comes from base class and creates Light Tread
			return new LThread();
		}
};


//Factory Pattern ENDS

#endif // FACTORYPATTERN_H_
