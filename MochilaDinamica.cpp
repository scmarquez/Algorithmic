//Sergio Carrasco Márquez
//Mochila programación dinámica

#include <iostream>
#include <vector>
using namespace std;


class objetos{
	private:
		double peso;
		string name;
		double beneficio;
		double BP;
	public:
		objetos(string nombre, int p, int b){
			peso = p;
			name = nombre;
			beneficio = b;
			BP = b/p;
		}
		objetos(){}
		string getName(){
			return name;
		}
		int getPeso(){
			return peso;
		}
		int getBeneficio(){
			return beneficio;
		}
		double getBP(){
			return beneficio/peso;
		}
};

class Mochila{
	private:
		int capacidad;
		int ocupado;
		vector<objetos> Items;
		vector<int> pesos;
		int nObjetos;
	public: 
		Mochila(int c){
			capacidad = c;
			ocupado = 0;
			nObjetos = 0;
		}
		bool ObjetoCabe(objetos o){
			return(o.getPeso() <= (capacidad - ocupado));
		}
		int getDisponible(){
			return capacidad-ocupado;
		}
		int getCapacidad(){
			return capacidad;
		}
		bool AniadeObjeto(objetos o){
			//Añadir el objeto o la proporción que se pueda añadir de este
			if(getDisponible() > 0){
				Items.push_back(o);
				if(o.getPeso() > getDisponible()){
					//Solo se añaden los kilos que entren en la mochila
					pesos.push_back(getDisponible());
				}
				else{
					pesos.push_back(o.getPeso());
				}
				nObjetos++;
				ocupado += pesos.back();
			}
			
		}

		double BeneficioMochila(){
			double b = 0;
			for(int i = 0; i < nObjetos;i++){
				b+=Items[i].getBP() * pesos[i];
			}
			return b;
		}
		void MestraBeneficios(){
			for(int i = 0; i < nObjetos; i++){
				double b = Items[i].getBP();
				cout << b << endl;
			}
		}
};
int max(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}
void LlenaMochilaDinamica(Mochila &m, objetos *obj, int nItems){
	//Tabla que contendrá las soluciones
	int capacidad = m.getCapacidad();
	int matrix [nItems + 1][capacidad + 1];
	for(int i = 0; i <= nItems; i++){
		for(int j = 0; j <= capacidad; j++){
			matrix[i][j] = 0;
		}
	}

	//cout << "El primer objeto: " << obj[0].getPeso();
	for(int i = 1; i <= capacidad; i++){
		for(int j = 1; j <= nItems; j++){
			if(i - obj[j-1].getPeso() >= 0){
				//cout << "ENtra en el if\n";
				//cout << "Terminos de los maximos:\n";
				//cout << matrix[j-1][i] << endl;
				//cout << matrix[j-1][i-obj[j-1].getPeso()] + obj[j-1].getBeneficio();
				matrix[j][i] = max(matrix[j-1][i],matrix[j-1][i-obj[j-1].getPeso()] + obj[j-1].getBeneficio());
			}
			else{
				matrix[j][i] = matrix[j-1][i];
			}
			
		}
	}
	//Imprime la matriz
	for(int i = 0; i <= nItems; i++){
		for(int j = 0; j <= capacidad;j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	//Explora la tabla en busca de la solución
	bool solucion[nItems];
	int f = nItems;
	int c = capacidad;
	for(int i = 0; i < 5; i++){
		if(matrix[f][c] == matrix[f-1][c]){
			//El objeto no se ha usado
			solucion[nItems-1-i] = false;
		}
		else{
			solucion[nItems-1-i] = true;
			c = c-obj[nItems-1-i].getPeso();
		}
		f--;
	}
	//Rellenar mochila con los objetos seleccionados
	for(int i = 0; i < nItems; i++){
		if(solucion[i]){
			//Si el objeto entra en la solución se carga en la mochila
			m.AniadeObjeto(obj[i]);
			cout << "Aniadido el objeto " << i << endl; 
		}
	}
}
int main(){
	objetos* O = new objetos[5];
	/*
	for(int i = 0; i < 5; i++){
		objetos o("obj",i+1,i+2);
		O[i] = o;
	}
	*/
	objetos o1("obj",5,1);
	O[0] = o1;
	objetos o2("obj",5,3);
	O[3] = o2;
	objetos o3("obj",4,18);
	O[2] = o3;
	objetos o4("obj",4,2);
	O[1] = o4;
	objetos o5("obj",1,28);
	O[4] = o5;
	Mochila m(11);
	LlenaMochilaDinamica(m,O,5);
	cout << "El beneficio obtenido es: " << m.BeneficioMochila();
	//m.MestraBeneficios();
	
}