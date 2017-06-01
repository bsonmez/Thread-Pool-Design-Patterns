/*
 * ObserverPattern.h
 * Author      : Burak Sonmez, Oğuzhan Sarıtaş
 */

#ifndef OBSERVERPATTERN_H_
#define OBSERVERPATTERN_H_

using namespace std;
/*
 * ++++ Observer Pattern CHECKED ++++
 */

//Observer Pattern STARTS

// Observer
class ObserverMemory{
	protected:
		virtual void Release(int MB) = 0;   // Releases empty space
		virtual void Update(int MB) = 0; 	//Observer function to notify when updated
		virtual void Allocate(int MB) = 0; 	//Assing on the ram
		virtual int getSize() = 0;			//Gets free space
		virtual ~ObserverMemory(){};
};

// Concrete Observer
class MainMemory:public ObserverMemory{
	private:
		int _memory; // Spesific memory
		int _size; 	 //the size of the memory

	public:
		MainMemory(){
			this->_size = 1024; //Sizing the memory GB
			this->_memory = rand() % 1000; //Creates uniqe id and assigns it into memory
			cout<<"Main Memory is created!"<<endl;
		}
		~MainMemory(){
			cout<<"Main Memory is deleted!"<<endl;
		}
		int getMemory(){ //Gets the memory's unique ID
				return this->_memory;
		}
		int getSize(){ // Gets the size
			return this->_size;
		}
		void Update(int MB){ //Allocates the memory if its size smaller than the RAM and bigger than zero
			if(MB > 0 && this->_size > MB){
				this->Allocate(MB);
			}
			else if(MB < 0){ // If its not Releases
				this->Release(MB);
			}
			else{ // Other all conditions , the user will be notified as no memory
				cout<<"Out Of Memory!";
			}
		}
		void Allocate(int MB){ //Allocates the ram amount in the parameter from size
			this->_size += MB;
		}
		void Release(int MB){  //Deallocates the ram amount in the parameter from size
			this->_size -= MB;
		}
};

// Subject
class AbstractMemoryManager{
	protected:
	// Orginal Observer Subject Class
		virtual void Notify(int MB,int ID) = 0;
		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual ~AbstractMemoryManager(){};

};

// Concrete Subject
class MemoryManager:public AbstractMemoryManager{
	private:
		int _memorySockets;				 //avaible socket in the motherboard to plug in rams
		int _totalMemory;   			// total memory(ram) on the motherborad
		MainMemory* _memorySlot[3];		// Avaible size of slots

	public:
		MemoryManager(){
			this->_memorySlot[0] = new MainMemory(); 		  // Creates and assigns first slot onto Memory
			this->_totalMemory = _memorySlot[0]->getSize();  //Adds the first memory's memory on total memory
			this->_memorySockets=1; 						 //Since there is a memory on the board , variable assigned as 1
			cout<<"Memory Manager is created!"<<endl;
		}
		~MemoryManager(){
			cout<<"Memory Manager deleted!"<<endl;
		}
		int getTotalMemory(){
			int counter = 0;
			for(int RAM = 0; RAM < this->_memorySockets ; RAM++){
				counter += this->_memorySlot[RAM]->getSize();
			}
			return counter;
		}
		void Attach(){ // to add new memory on the motherboard
				if(this->_memorySockets < 4){ // checks if there any free space to add memory
					this->_memorySlot[this->_memorySockets] = new MainMemory(); // assigns the memory on the socket
					this->_memorySockets++; // increases the sockets
				}
				else
					cout<<"There is no more avaible Memory Socket.Remove one to add new!"<<endl;
		}
		void Detach(){ // to remove memory on the motherboard
			if(_memorySockets > 0){ // Checks if there is memory on
				delete _memorySlot[_memorySockets-1]; //removes the last one
				_memorySockets--; //decrease the avaible socket size
			}
			cout <<"No RAM FOUND!"<<endl;
		}
		void Notify(int MB,int ID){
			for ( int i = 0 ; i < this->_memorySockets ; i++){
				if(_memorySlot[i]->getMemory() == ID){
					_memorySlot[i]->Update(MB);
					return;
				}
			}
			cout<<"Notification error!"<<endl;
		}
};

//Observer Pattern ENDS

#endif // OBSERVERPATTERN_H_
