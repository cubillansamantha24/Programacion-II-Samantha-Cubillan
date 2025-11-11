#include <iostream>
#include <fstream>
using namespace std;
struct Persona{
	char nombre[5][20];
	int id;
};
int main(){
	
	int cantidadp = 5;
	ofstream archivo("personas_multi.bin", ios:: binary);
	archivo.write(reinterpret_cast<char*>(&cantidadp), sizeof(int));
	archivo.close();
	
	
	Persona p[5];
	for(int i=0;i<5;i++){
		cout<<"Ingrese el nombre: ";
		cin>>(p[i].nombre);
		p[i].id=id;
		id++;
		
		
	}
	fstream archivop("personas_multi.bin", ios:: binary | ios::app);
	archivop.write(reinterpret_cast<char*>(p), 5 * sizeof(Persona));
	archivop.close();
	ifstream archivol1("personas_multi.bin", ios::binary);
	archivol1.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
	archivol1.close();
	cout<<"La cantidad de personas es: "<< cantidadp<< endl;
	

	
	ifstream archivol2("personas_multi.bin",ios::binary);
	archivol2.read(reinterpret_cast<char*>(p), cantidadp * sizeof(Persona) );
	archivol2.close();
	Persona personasleidad[cantidadp];
	for(int i=0; i<cantidadp; i++){
		cout<<personasleidad[i].nombre<<endl;
		cout<<personasleidad[i].id<<endl;
		
		
	}
	
}