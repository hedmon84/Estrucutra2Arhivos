#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
int opc;


struct transacciones {
	int cuenta;
	int transa;
	double monto_transac;
};

struct cliente {
	int Ncuenta;
	char nombre[20];
	double saldo;

	//32 bits
};

void agregar_Cliente() {
	ofstream binaryfile("cuenta.dat", ios::app | ios::out | ios::binary);

	if (!binaryfile) {
		cout << "Error al abrir archivo" << endl;
	}

	cliente nuevo;
	cout << endl << "*** I N G R E S O  D E  C U E N T A S  ***\n";
	cout << "Ingrese codigo:" << endl;
	cin >> nuevo.Ncuenta;
	cout << "Ingrese nombre:" << endl;
	cin >> nuevo.nombre;

	nuevo.saldo = 0;

	binaryfile.seekp(0, ios::end);
	binaryfile.write(reinterpret_cast<const char*>(&nuevo), sizeof(cliente));
	binaryfile.close();
}



void consultarCliente() {
	ifstream empleadoIn("cuenta.dat", ios::in | ios::binary);
	if (!empleadoIn) {
		cout << "Error al intentar abrir el archivo Empleados.dat" << endl;
		return;
	}

	cliente temporal;
	cout << endl << "*** C O N S U L T A R  D E  C L I E N T E S ***\n";
	empleadoIn.seekg(0, ios::beg);
	empleadoIn.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));
	while (!empleadoIn.eof()) {
		cout << "Cliente { codigo:" << temporal.Ncuenta << ", Nombre:" << temporal.nombre << ", Saldo: " << temporal.saldo << "}\n";
		empleadoIn.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));
	}
	empleadoIn.close();


}


void agregarDeposito() {
	ofstream transfile("transacciones.dat", ios::app | ios::out | ios::binary);

	if (!transfile) {
		cout << "Error al abrir archivo" << endl;
	}

	transacciones nuevo;
	cout << endl << "*** D E P O S I T O  ***\n";

	cout << "Ingrese numero de cuenta:" << endl;
	cin >> nuevo.cuenta;
	cout << "Ingrese tipo de transacciones:" << endl;
	cin >> nuevo.transa;
	cout << "Ingrese monto de transacciones:" << endl;
	cin >> nuevo.monto_transac;


	transfile.seekp(0, ios::end);
	transfile.write(reinterpret_cast<const char*>(&nuevo), sizeof(transacciones));
	transfile.close();

	cliente temporal;
	ifstream lecturaA("cuenta.dat", ios::in | ios::binary);
	lecturaA.seekg(0, ios::beg);

	lecturaA.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));

	while (!lecturaA.eof()) {
		if (temporal.Ncuenta == nuevo.cuenta) {
			ofstream escrituraA("cuenta.dat", ios::out | ios::binary);

			temporal.saldo = temporal.saldo + nuevo.monto_transac;

			escrituraA.write((char*)&temporal, sizeof(cliente));
		}
		lecturaA.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));
	}

	return;
}


void agregarRetiro() {
	ofstream transfile("transacciones.dat", ios::app | ios::out | ios::binary);

	if (!transfile) {
		cout << "Error al abrir archivo" << endl;
	}

	transacciones nuevo;
	cout << endl << "*** R E T I R O ***\n";

	cout << "Ingrese numero de cuenta:" << endl;
	cin >> nuevo.cuenta;
	cout << "Ingrese tipo de transacciones:" << endl;
	cin >> nuevo.transa;
	cout << "Ingrese monto de transacciones:" << endl;
	cin >> nuevo.monto_transac;


	transfile.seekp(0, ios::end);
	transfile.write(reinterpret_cast<const char*>(&nuevo), sizeof(transacciones));
	transfile.close();

	cliente temporal;
	ifstream lecturaA("cuenta.dat", ios::in | ios::binary);
	lecturaA.seekg(0, ios::beg);

	lecturaA.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));

	while (!lecturaA.eof()) {
		if (temporal.Ncuenta == nuevo.cuenta) {
			ofstream escrituraA("MaestroCuentas.dat", ios::out | ios::binary);

			temporal.saldo = temporal.saldo - nuevo.monto_transac;

			escrituraA.write((char*)&temporal, sizeof(cliente));
		}
		lecturaA.read(reinterpret_cast<char *>(&temporal), sizeof(cliente));
	}

	return;


}

void consultarHisto() {
	ifstream empleadoIn("transacciones.dat", ios::in | ios::binary);

	if (!empleadoIn) {
		cout << "Error al intentar abrir el archivo Empleados.dat" << endl;
		return;
	}

	transacciones temporal;
	cout << endl << "*** C O N S U L T A  D E  T R A N S A C C I O N E S ***\n";
	empleadoIn.seekg(0, ios::beg);
	empleadoIn.read(reinterpret_cast<char *>(&temporal), sizeof(transacciones));
	while (!empleadoIn.eof()) {
		cout << " { # Cuenta:" << temporal.cuenta << ", Tipo de Transaccion:" << temporal.transa << ", Monto: " << temporal.monto_transac << "}\n";
		empleadoIn.read(reinterpret_cast<char *>(&temporal), sizeof(transacciones));
	}
	cout << endl;

	empleadoIn.close();

}


int main() {
	do {
		cout << " B A N C O   N A C I O N A L " << endl;
		cout << "1. Ingresar Cuenta" << endl;
		cout << "2. Depositos" << endl;
		cout << "3. Retiros" << endl;
		cout << "4. Consultar Historial" << endl;
		cout << "0. Salir" << endl;
		cout << "Ingrese una opcion:" << endl;

		cin >> opc;
		switch (opc) {
		case 1:
			agregar_Cliente();
			break;
		case 2:
			agregarDeposito();
			break;
		case 3:
			agregarRetiro();
			break;
		case 4:
		      consultarCliente();
			consultarHisto();
			break;
		default:
			break;
		}
	} while (opc != 0);
	return 0;
}