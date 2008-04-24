// Dev_unit_Data.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <iostream>
#include "stdafx.h"
#include "Data.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	void* pointer;
	Data* data;
	Data* data2;
	cout<<"Data dev unit"<<endl;

	try{
		data = new Data(500,500);
	}catch(Default_Exceptionhandler* exception){
		cout<<exception->toString();
	}
	data->random_fill();

	try{
		data2 = new Data(data);
	}catch(Default_Exceptionhandler* exception){
		cout<<exception->toString();
	}
	
	data->inttocustomint();
	
	cout<<" Größter Wert = "<<data->maximumValue_int<<endl;


	data->custominttoint();
	if(data->compare(data2)){
		cout<<"Equal"<<endl;
	}else{
		cout<<"Not equal"<<endl;
	}
	return 0;
}

