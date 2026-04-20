#include <iostream>
#include <cstdlib>
#include<vector>
#include<math.h>
#include<time.h>

using namespace std;

class Donnees {

public:
	int n;
	double budgetmax1;
	double budgetmax2;
	double budgetmax3;
    
	double risque1;
	double risque2;
	double risque3;
	double *valeur;

	vector<double> bornesup1;
	vector<double> bornesup2;
	vector<double> bornesup3;

	double **matricecovariance;

};

class Solution {

public:

	Solution(); //Constructeur par défaut
	Solution(const Solution& sol); //Constructeur par copie
	~Solution();

	vector<double> variabletype1;
	vector<double> variabletype2;
	vector<double> variabletype3;

	double Eval(const Donnees& theData);
	double getValue(int index);
	bool Realisable(const Donnees& theData);

	Solution Voisinage();
	Solution Voisinage_Ajout();
	void Print_Solution();

	Solution& operator=(const Solution& sol);
};
Solution::Solution() {

}

Solution::Solution(const Solution& sol) {

	variabletype1 = sol.variabletype1;
	variabletype2 = sol.variabletype2;
	variabletype3 = sol.variabletype3;

}
Solution::~Solution() {

}
Solution& Solution::operator=(const Solution& sol) {

	variabletype1 = sol.variabletype1;
	variabletype2 = sol.variabletype2;
	variabletype3 = sol.variabletype3;

	return *this;
}

double Solution::getValue(int index){
	int a = variabletype1.size();
	int b = variabletype2.size();
	int c = variabletype3.size();
	if (index < a)
		return variabletype1[index];
	if (index < a + b)
		return variabletype2[index - a];
	if (index < a + b + c)
		return variabletype3[index - a - b];
	return 0;
}


double Solution::Eval(const Donnees& theData) {

	double valeur_sol = 0;

	int a = variabletype1.size();
	int b = variabletype2.size();
	int c = variabletype3.size();

	for (int i = 0; i < a; i++) {
		valeur_sol = valeur_sol + (variabletype1[i] * variabletype1[i]);
	}
	for (int i = 0; i < b; i++) {
		valeur_sol = valeur_sol + (variabletype2[i] * variabletype2[i]);
	}
	for (int i = 0; i < c; i++) {

		valeur_sol = valeur_sol + (variabletype3[i] * variabletype3[i]);
	}
	return valeur_sol;
}
bool Solution::Realisable(const Donnees& theData) {
	double sommetotale = 0 ;
	double sommetotale1 = 0;
	double sommetotale2 = 0;
	double sommetotale3 = 0;
	int a = variabletype1.size();
	int b = variabletype2.size();
	int c = variabletype3.size();
	for (int i = 0; i < a; i++) {
		sommetotale1 = sommetotale1 + variabletype1[i];
	}

	for (int i = 0; i < b; i++) {
		sommetotale2 = sommetotale2 + variabletype2[i];
	}
	for (int i = 0; i < c; i++) {
		sommetotale3 = sommetotale3 + variabletype3[i];
	}
sommetotale = sommetotale1 + sommetotale2 + sommetotale3;
	if (sommetotale >1 && sommetotale < 0.95){

      return false;
	}

	

	if (sommetotale1 > theData.budgetmax1)
				return false;
	if (sommetotale2 > theData.budgetmax2)
					return false;
	if (sommetotale3 > theData.budgetmax3)
					return false;

	for (int i = 0; i < a; i++) {
			
		if (variabletype1[i] < 0.0 && variabletype1[i] > theData.bornesup1[i])
		return false;
		}

	for (int i = 0; i < b; i++) {
		
		if (variabletype2[i] < 0.0 && variabletype2[i] > theData.bornesup2[i])
				return false;
	}
	for (int i = 0; i < c; i++) {
	
		if (variabletype3[i] < 0.0 && variabletype3[i] > theData.bornesup3[i])
				return false;

	}
	double sommetotal = 0.0;
	double sommetotal1 = 0.0;
	double sommetotal2 = 0.0;
	double sommetotal3 = 0.0;

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			sommetotal1 = sommetotal1 + theData.matricecovariance[i][j]* variabletype1[i] * variabletype1[j];
		}

	}
	for (int i = a; i < a + b; i++) {
		for (int j = a; j < a + b; j++) {
			sommetotal2 = sommetotal2 + theData.matricecovariance[i][j]* variabletype2[i-a] * variabletype2[j-a];
		}
	}
	for (int i = a + b; i < a + b + c; i++) {
		for (int j = a + b; j < a + b + c; j++) {
			sommetotal3 = sommetotal3 + theData.matricecovariance[i][j]* variabletype3[i-a-b] * variabletype3[j-a-b];
		}
	}

	for (int i = 0; i < a + b + c; i++) {
		for (int j = 0; j < a + b + c; j++) {
		    double result_i= getValue(i);
		    double result_j = getValue(j);
			sommetotal = sommetotal + theData.matricecovariance[i][j]*result_i*result_j;
		}
		}



   if ((sqrt(sommetotal1) / sommetotal) > (theData.risque1/100) && (sqrt(sommetotal2) / sommetotal) > (theData.risque2/100) && (sqrt(sommetotal3) / sommetotal) > (theData.risque3/100)  );{
	     return false;
	}
	
	return true;
  }


Solution Solution::Voisinage() {

	//******* choisir un voisinage aleatoirement************


	 Solution temp = *this;
	temp = Voisinage_Ajout();
	return temp;
}
	Solution Solution::Voisinage_Ajout(){
		Solution temp = *this;

	
	int s =0;
	int a = variabletype1.size();
	int b = variabletype2.size();
	int c = variabletype3.size();

	srand(time(NULL));
    int z1=0;
    int z2=1;
    int z3=2;
    int Typ;
    //La première méthode de choisir un voisin 
    for (int i=0;i<a;i++){
    	temp.variabletype1[i]=variabletype1[i];
	}
	for (int i=0;i<b;i++){
    	temp.variabletype2[i]=variabletype2[i];
	}
	for (int i=0;i<c;i++){
    	temp.variabletype3[i]=variabletype3[i];
	}
	Typ=1+rand()%3;
		z1=rand()%a;
		z2=rand()%b;
		z3=rand()%c;
		if (Typ=1){
		temp.variabletype1[z1]=temp.variabletype1[z1]/2;
		temp.variabletype2[z2]=	temp.variabletype2[z2]+temp.variabletype1[z1]/2;
		temp.variabletype3[z3]=	temp.variabletype3[z3]+temp.variabletype1[z1]/2;
	}
		if (Typ=2){
		temp.variabletype2[z2]=temp.variabletype2[z2]/2;
		temp.variabletype1[z1]=	temp.variabletype1[z1]+temp.variabletype2[z2]/2;
		temp.variabletype3[z3]=	temp.variabletype3[z3]+temp.variabletype2[z2]/2;
	}
		if (Typ=3){
		temp.variabletype3[z3]=temp.variabletype3[z3]/2;
		temp.variabletype1[z1]=	temp.variabletype1[z1]+temp.variabletype3[z3]/2;
		temp.variabletype2[z2]=	temp.variabletype2[z2]+temp.variabletype3[z3]/2;
	}
	//La deuxième méthode pour générer un voisin 
	/*for(int i=0;i<a;i++)
	{
		temp.variabletype1[i] = rand();
		s=s+ temp.variabletype1[i];	
	 }
	 for(int i=0;i<b;i++)
	{
		temp.variabletype2[i] = rand();
		s=s+ temp.variabletype2[i];
	 } 
	 for(int i=0;i<c;i++)
	{
		temp.variabletype3[i] = rand();
		s=s+ temp.variabletype3[i];	
	 }
	 /*la dévision par la somme s avoir la somme des valeurs de vecteur egal à 1*/
	   /*for(int i=0;i<a;i++)
	{
		temp.variabletype1[i] = temp.variabletype1[i]/s	;
	 }
	 for(int i=0;i<b;i++)
	{
		temp.variabletype2[i] = temp.variabletype2[i]/s	;
	 } 
	 for(int i=0;i<c;i++)
	{
		temp.variabletype3[i] = temp.variabletype3[i]/s;
			 }
*/

			return temp;

}


void Solution::Print_Solution(){
	int a = variabletype1.size();
	int b = variabletype2.size();
	int c = variabletype3.size();
	for (int i = 0; i < a; i++) {

		cout<<"le Type 1 "<< variabletype1[i] << endl;
			}

			for (int i = 0; i < b; i++) {
				cout<<"le Type 2 "<< variabletype2[i] << endl;
			}
			for (int i = 0; i < c; i++) {

						cout<<"le Type 3 "<< variabletype3[i] << endl;
							}


}



int main() {

	//Données du problème

	/*********************************************************************/
	srand(time(NULL));
	Donnees lesDonnees;

	lesDonnees.budgetmax1 = rand();
	lesDonnees.budgetmax2 = rand();
	lesDonnees.budgetmax3 = rand();
	
	lesDonnees.risque1 = rand()/100;
	lesDonnees.risque2 = rand()/100;
	lesDonnees.risque3 = rand()/100;

	int nbtype1 = 5;
	int nbtype2 = 5;
	int nbtype3 = 5;

	for (int i = 0; i < nbtype1; i++) {
		lesDonnees.bornesup1.push_back(rand());
		
	}
	for (int i = 0; i < nbtype2; i++) {
		lesDonnees.bornesup2.push_back(rand());
		
	}
	for (int i = 0; i < (nbtype3); i++) {
		lesDonnees.bornesup3.push_back(rand());
		
}  

	//Generer la matrice de variance et covariance aleateoirement
    double **t;
	int n = nbtype1 + nbtype2 + nbtype3;
	 t = new double*[ n ];
	  for (int i=0; i < n; i++){
	    t[i] = new double[ n ];
	  }
	lesDonnees.matricecovariance =  t;
	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			if (i == j){
				lesDonnees.matricecovariance[i][j] = 0.1 + (4.0 * rand())
						/ RAND_MAX;}

            else{
			lesDonnees.matricecovariance[i][j] = -10 + (20.0 * rand()) / RAND_MAX;
			lesDonnees.matricecovariance[j][i] = lesDonnees.matricecovariance[i][j];
               }


	    	}
	}
	/***********************Affichage de la matrice de variance covariance****************/
     cout<<"Affichage de la matrice de variance et covariance"<<endl;
	int tail = 0;
	for (int i = 0 ; i < n; i++) {
		 cout << endl;
		 tail++;
	for (int j = 0 ; j < n ; j++) {
               cout <<lesDonnees.matricecovariance[i][j]<<" " ;

                                       }
	                                   }
	cout << endl;
	cout<<"la taille de la matrice est "<<tail<<" * "<<tail<<endl;
    cout<<"***************"<<endl;
	//Initialisation de la solution X0
			Solution X0;
				int s=0;
		for(int i=0;i<nbtype1;i++)
	{
		X0.variabletype1.push_back(rand());
		s=s+ X0.variabletype1[i];	
	 }
	 for(int i=0;i<nbtype2;i++)
	{
		X0.variabletype2.push_back(rand());
		s=s+ X0.variabletype2[i];
	 } 
	 for(int i=0;i<nbtype3;i++)
	{
		X0.variabletype3.push_back(rand());
		s=s+ X0.variabletype3[i];	
	 }
	 /*la dévision par la somme s avoir la somme des valeurs de vecteur egal à 1*/
	   for(int i=0;i<nbtype1;i++)
	{
		X0.variabletype1[i] = X0.variabletype1[i]/s	;
	 }
	 for(int i=0;i<nbtype2;i++)
	{
		X0.variabletype2[i] = X0.variabletype2[i]/s	;
	 } 
	 for(int i=0;i<nbtype3;i++)
	{
		X0.variabletype3[i] = X0.variabletype3[i]/s;
			 }
	cout<<"*******Les donnéées de la solution initiale est:********"<<endl;
	cout<<"*******type1********"<<endl;
	for (int i = 0; i < nbtype1; i++) {
	  cout<<X0.variabletype1[i]<<endl;
				}
	cout<<"*******type2********"<<endl;
	for (int i = 0; i < nbtype1; i++) {
	   cout<<X0.variabletype2[i]<<endl;
							}
	cout<<"*******type3********"<<endl;
		for (int i = 0; i < nbtype1; i++) {
		   cout<<X0.variabletype3[i]<<endl;
							}
	cout<<"*****************"<<endl;
	cout << "Valeur de la solution initiale : " << X0.Eval(lesDonnees) << endl;
           
/*résolution de probleme avec le récuit simulé*/
			//Initialisation de la solution courante à X0
	Solution sol_x = X0;
	Solution best_sol = X0;
	Solution sol_y;
	Solution sol_t;

//********Gestion de le temperature****************

	double T = 16;
	double Tmin = 0.01;
	double mu = 0.99;
	int nb_iter = 0;
	sol_y = sol_x.Voisinage();
		            
				while(nb_iter<1000){
				
			        //Choisir aleatoirement un voisin de X (solution courante). Le voisin doit etre realisable
		        	sol_y = sol_x.Voisinage();
		        	//On verifie si le voisin est meilleur que la solution courante

		        	if(sol_y.Eval(lesDonnees) < sol_x.Eval(lesDonnees)){
		
			         	sol_x = sol_y;

			        	//Si la nouvelle solution est meilleure que la meilleure solution connue, on la conserve
				        if(sol_y.Eval(lesDonnees) < best_sol.Eval(lesDonnees)){					        best_sol = sol_y;
					        cout << "Amelioration de la solution courante: " << best_sol.Eval(lesDonnees) << endl;
            	        	best_sol.Print_Solution();
            	        	if(best_sol.Realisable(lesDonnees) == false)
                             	cout<<"*****La solutuion courante est realisable: false******"<<endl;
                            else
            	                cout<<"*****La solutuion courante est realisable: True******"<< endl ;
				        
				         }

		        	else{	//En cas de non amÃ©lioration, on accepte la solution voisine selon la proba

			        	float eval_x = sol_x.Eval(lesDonnees);
			        	float eval_y = sol_y.Eval(lesDonnees);
			        	cout<< 1.0*rand()/RAND_MAX<<" "<<exp((eval_y-eval_x)/T)<<endl;
  				        if((1.0*rand()/RAND_MAX) < exp((eval_y-eval_x)/T)){				        	sol_x = sol_y;}
		           	}}

		         	T = T*mu;
			        nb_iter++; }
	            
				
			
		  		cout<<"*****************"<<endl;
		  	    cout << "Affichage de la Valeur initiale: " << X0.Eval(lesDonnees) << endl;
                X0.Print_Solution();
		  		cout<<"*****************"<<endl;
                cout<<"*****Affichage de la solution finale*******"<<endl;
		  		cout << "Valeur solution: " << best_sol.Eval(lesDonnees) << endl;
                best_sol.Print_Solution();   
                if(best_sol.Realisable(lesDonnees) == false)
            	cout<<"*****La solutuion finale est realisable: false******"<<endl;
                else
            	cout<<"*****La solutuion finale est realisable: True******"<< endl ;

		return 0 ;
	}

