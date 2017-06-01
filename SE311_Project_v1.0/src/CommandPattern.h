/*
 * CommandPattern.h

 * Author      : Burak Sonmez, Oğuzhan Sarıtaş
 */

#ifndef COMMANDPATTERN_H_
#define COMMANDPATTERN_H_

//The patterns(headers) will be need to use in this header
#include "IteratorPattern.h"
#include "TemplatePattern.h"
#include "ObserverPattern.h"

using namespace std;
/*
 * ++++ Command Pattern CHECKED ++++
 */


//Command Pattern STARTS


//Receiver
class ProcessManager{
	private:
		// Those are the ones should included in Process Manager
		ThreadTable* _threadtable;
		MemoryManager* _memoryManager;
		ThreadPool* _threadPool;

	public:
		ProcessManager(){
			cout<<"Process Manager Created!"<<endl;
			this->_memoryManager = new MemoryManager();  //Creates new memory manager
			this->_threadPool->NewPool(this);			 // Creates new Pool
			this->_threadtable = _threadPool->Table;	 // the created pool assigns the table
		}
		~ProcessManager(){
			cout<<"Process Manager Killed!"<<endl;
		}

		void Operate(int Size){ // Gets Thread's size and checks avaible threads
			Threads* _avaible = this->_threadtable->checkThread(Size); //checks for avabile
			if(_avaible != NULL){
				_memoryManager->Notify(Size,201); // 201 is simulated Memory id
				_avaible->run(); // run
				_avaible->stop(); // stop
				_memoryManager->Notify(-1*Size,601); // 601 is simulated Memory id
			}
			else{
				cout<<"Operation is rejected!"<<endl;
			}
		}
};

//Abstract
class SystemOperation{
	public:
		virtual void Execute(ProcessManager* _cpu) = 0;
		virtual ~SystemOperation(){};
};

//Concrete 1
class HeavyOperation:public SystemOperation{
	public:
		HeavyOperation(){ //Constracter
			cout<<"Heavy operation is created!"<<endl;
		}
		~HeavyOperation(){ //deconstracter
			cout<<"Heavy operation is deleted!"<<endl;
		}
		void Execute(ProcessManager* _cpu){ // To execute Operation in process Manager by using heavy opreation
			_cpu->Operate(512);
		}
};

//Concrete 2
class LightOperation:public SystemOperation{
	public:
		LightOperation(){ //Constracter
			cout<<"Light operation is created!"<<endl;
		}
		~LightOperation(){ //deconstracter
			cout<<"Light operation is deleted!"<<endl;
		}
		void Execute(ProcessManager* _cpu){ // To execute Operation in process Manager by using light opreation
			_cpu->Operate(256);
		}
};

//Invoker
class OperatingSystem{
	private:
		ProcessManager* _cpu;
		LightOperation* Light;
		HeavyOperation* Heavy;
		string _osType;

	public:
		OperatingSystem(string n){
			this->_osType = n; // assigns the type(name) of operating system
			// Creates instances from classes
			this->_cpu = new ProcessManager();
			this->Light = new LightOperation();
			this->Heavy = new HeavyOperation();
		}
		~OperatingSystem(){
			cout<<"Operating System is deleted!"<<endl;
		}
		LightOperation* getLightOperation(){ // get Concrete Command 2
			return this->Light;
		}
		HeavyOperation* getHeavyOperation(){ //get  Concrete Command 1
			return this->Heavy;
		}
		void SystemCall(SystemOperation* Interface){ //Runs System's Interface
					Interface->Execute(this->_cpu);
				}
};

//Client
class User{
	private:
		OperatingSystem* OS; //User's Operation system object
		string _type;
		string _username;
	public:
		User(){
			//cout<<"User Created! Please write your operating system down.EX:'mac'  "<<endl;
			//cin>>_type;
			//cout<< _type <<" is starting please stand by..."<<endl;
			cout << "User created!"<< endl << "Operating System is starting!" <<endl;
			this->OS = new OperatingSystem(_type);

		}
		~User(){
			cout<<"The user has been deleted!"<<endl;
		}
		void loadOperation(string Action){
			if(Action == "Heavy")
				OS->SystemCall(OS->getHeavyOperation()); // Calls 512MB Operation ( Concerete Command )
			else if(Action == "Light")
				OS->SystemCall(OS->getLightOperation()); // Calls 256MB Operation ( Concerete Command )
			else
				cout<<"Should be either Heavy nor Light Operation!";
		}
};

//Command Pattern ENDS


#endif // COMMANDPATTERN_H_
