/*
 * TemplatePattern.h
 *      Author: Burak Sönmez, Oğuzhan Sarıtaş
 */

#ifndef TEMPLATEPATTERN_H_
#define TEMPLATEPATTERN_H_

#include<iostream>

#include<vector>
#include "SingletonPattern.h"

using namespace std;

// TEMPLATE PATTERN
class AbstractThreadPool{
	protected:
		virtual void StorageAllocation(int Size) = 0;
		virtual void CreateTable(int Size,int Priority) = 0;
		virtual void OrganizeOrder(int Priority) = 0;
		void CreateThreadTemplate(int order,int Size,AbstractThreadPool* Concrete){
			Concrete->StorageAllocation(Size);
			Concrete->CreateTable(Size,order);
			Concrete->OrganizeOrder(order);
		}
	~AbstractThreadPool(){
		cout<<"AbstractThreadPool class erased"<<endl;
	}

};
#endif // TEMPLATEPATTERN_H_
