//Práctica Algorítmica
//Sergio Carrasco Márquez

#include <iostream>
#include <fstream>
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
		void MuestraBeneficios(){
			for(int i = 0; i < nObjetos; i++){
				double b = Items[i].getBP();
				cout << b << endl;
			}
		}
		bool Llena(){
			return capacidad == ocupado;
		}
};

void QuickSort(objetos* &v, int tamanio){
	
	//Seleccionar pibote, en este caso será el elemento central
	/*Como cada vez el vector se acercará más a una solución ordenada elegir como pibote el elemento central es una buena opción,
	ya que no consume una cantidad de tiempo relevante*/
	if(tamanio > 1){
		if(tamanio == 2){
			if(v[0].getBP() > v[1].getBP()){
				objetos swap = v[0];
				v[0] = v[1];
				v[1] = swap;
			}
		}
		else{
			objetos pibote = v[tamanio/2];
			int indice = tamanio/2;
			int lastSuperior = 0;
			//Intercambia el primero con el medio
			v[indice] = v[0];
			v[0] = pibote;
			for(int i = 1; i < tamanio; i++){
				if(v[i].getBP() > pibote.getBP() && lastSuperior == 0){
					lastSuperior = i;
				}
				if((v[i].getBP() < pibote.getBP()) && lastSuperior != 0){
					objetos swap = v[i];
					v[i] = v[lastSuperior];
					v[lastSuperior] = swap;
					lastSuperior++;
				}
			}
			v[0] = v[lastSuperior-1];
			v[lastSuperior-1] = pibote;
			//LLama recursivamente
			objetos* v1 = v;
			objetos* v2 = v + lastSuperior;
			QuickSort(v1,lastSuperior-1);
			QuickSort(v2,tamanio- lastSuperior);
			
		}
		
	}
}

void LlenaMochilaGreedy(bool ObjetoCompleto, Mochila &m, objetos *obj, int nItems){
	//El algoritmo greedy busca el objeto con mayor beneficio
	
	//Algoritmo quick sort
	QuickSort(obj,nItems);
	//Una vez ordenados se escogen los objetos por orden de beneficio/peso
	int i = nItems-1;
	while(!m.Llena() && i >= 0){
		if(m.ObjetoCabe(obj[i])){
			m.AniadeObjeto(obj[i]);
		}
		i--;
	}
	//Si se pueden cargar objetos incompletos cargamos la mochila con dichos objetos
	if(!ObjetoCompleto){
		if(m.getDisponible() > 0){
			m.AniadeObjeto(obj[i]);
		}
	}
}

int main(){
	//Crear objetos de prueba
	objetos* O = new objetos[5];
	for(int i = 0; i < 5; i++){
		objetos o("obj",i+15,i+7);
		O[i] = o;
	}
	//Mostrar los objetos y su B/P
	for(int i = 0; i < 5; i++){
		cout << "objeto numero: " << i+1 <<" Peso: " <<O[i].getPeso() << " Beneficio: " << O[i].getBeneficio() << " " << O[i].getBP()<< endl;
	}
	cout << "El peso de la mochila es 6\n";
	Mochila m(6);
	LlenaMochilaGreedy(true,m,O,5);
	cout << "El beneficio obtenido es: " << m.BeneficioMochila();
}