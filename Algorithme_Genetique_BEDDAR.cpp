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



    if ((sqrt(sommetotal1) / sommetotal) > theData.risque1 && (sqrt(sommetotal2) / sommetotal) > theData.risque2 && (sqrt(sommetotal3) / sommetotal) > theData.risque3  );{
	     return false;
	}
	
	return true;
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
	
	lesDonnees.risque1 = rand();
	lesDonnees.risque2 = rand();
	lesDonnees.risque3 = rand();

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
    double **m;
	int n = nbtype1 + nbtype2 + nbtype3;
	 m = new double*[ n ];
	  for (int i=0; i < n; i++){
	    m[i] = new double[ n ];
	  }
	lesDonnees.matricecovariance =  m;
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
	/*Generer la matrice des noeuds parents aleateoirement*/
	/*La taille de la population K*/
	int k=3;
    double population[k][n]; 
    Solution X0;
	
	for (int i = 0; i < k; i++) {
		int s=0;
		for(int j=0;j<nbtype1;j++)
	{
		X0.variabletype1.push_back(rand());
		s=s+ X0.variabletype1[j];	
	 }
	 for(int j=0;j<nbtype2;j++)
	{
		X0.variabletype2.push_back(rand());
		s=s+ X0.variabletype2[j];
	 } 
	 for(int j=0;j<nbtype3;j++)
	{
		X0.variabletype3.push_back(rand());
		s=s+ X0.variabletype3[j];	
	 }
	 /*la dévision par la somme s avoir la somme des valeurs d'un noeuds egal à 1*/
	   for(int j=0;j<nbtype1;j++)
	{
	    X0.variabletype1[j]=X0.variabletype1[j]/s;
		population[i][j] = X0.variabletype1[j];
	 }
	 for(int j=nbtype1;j<nbtype1+nbtype2;j++)
	{
		population[i][j] = (X0.variabletype2[j-nbtype1]/s);
	 } 
	 for(int j=nbtype1+nbtype2;j<nbtype1+nbtype2+nbtype3;j++)
	{
		population[i][j] = (X0.variabletype3[j-nbtype1-nbtype2]/s);
			 }

	}
	/***********************Affichage de la matrice population****************/
     cout<<"Affichage de la population (les parents) sous forme d'une matrice"<<endl;
		for (int i = 0 ; i < k; i++) {
		 cout << endl;
			for (int j = 0 ; j < n ; j++) {
               cout <<population[i][j]<<" " ;
                                       }
	                                   }
	cout << endl;
	cout<<"la taille de la matrice est "<<k<<" * "<<n<<endl;
    cout<<"***************"<<endl;

    /*calculer la somme des carrés des elements de la matrice dse la population*/
    int som=0;
    int proba1;
    int proba2;
    int f;
    double interm;
    for(int i=0;i<k;i++){
    	for (int j=0;j<n;j++){
    		som=som + population[i][j]*population[i][j];
		}
	}
	cout<<"la somme de la matrice:"<<som<<endl;
	int nbr_iter=0;
	while(nbr_iter<16){
		/* Ordonner la population selon une probabilité qui diminue selon la fonction objectif  F(X)*/
		for(int i=0;i<k-1;i++){
		    proba1=0;
		    for(int j=0;j<n;j++){
			   proba1+=(population[i][j]*population[i][j]);
			}
	    	for(int l=i+1;l<k;l++){
			  proba2=0;
		      for(int j=0;j<n;j++){
		         proba2+=(population[l][j]*population[l][j]);
			}
			if((proba2)<(proba1)){
				for(int j=0;j<n;j++){
				interm=population[i][j];
				population[i][j]=population[l][j];
				population[l][j]=interm;
				}
				}
				}	
		}
	/*Croisement des noeuds aléateoirement pour générer des enfant selon le type d'actif choisis (f=1,2et 3)*/
    	for(int i=0;i<k-1;i=+2){
	       f=rand()%3+1;
	         if(f==1){
		        for(int j=0;j<nbtype1;j++){
			     	interm=population[i][j];
			    	population[i][j]=population[i+1][j];
				    population[i+1][j]=interm;
			  }
	       }
	       else if(f==2){
		        for(int j=nbtype1;j<nbtype1+nbtype2;j++){
			     	interm=population[i][j];
			    	population[i][j]=population[i+1][j];
				    population[i+1][j]=interm;
			  }
	       }
	       else{
		        for(int j=nbtype1+nbtype2;j<nbtype1+nbtype2+nbtype3;j++){
			     	interm=population[i][j];
			    	population[i][j]=population[i+1][j];
				    population[i+1][j]=interm;
			  }
	       }
	}
	
       nbr_iter++;	
	}
	/*ordonner pour la dernière fois la population selon une probabilité qui diminue la fonction objectif*/
		for(int i=0;i<k-1;i++){
		    proba1=0;
		    for(int j=0;j<n;j++){
			   proba1+=(population[i][j]*population[i][j]);
			}
	    	for(int l=i+1;l<k;l++){
			  proba2=0;
		      for(int j=0;j<n;j++){
		         proba2+=(population[l][j]*population[l][j]);
			}
			if((proba2)<(proba1)){
				for(int j=0;j<n;j++){
				interm=population[i][j];
				population[i][j]=population[l][j];
				population[l][j]=interm;
				}
				}
				}	
		}
		 cout<<"*****Affichage de la solution finale*******"<<endl;
		 cout<<"Affichage de la population (les noeuds finales) sous forme d'une matrice"<<endl;
	
	for (int i = 0 ; i < n; i++) {
		 cout << endl;
		 for (int j = 0 ; j < n ; j++) {
            cout <<population[i][j]<<" " ;

                                       }
	                                   }
	cout << endl;
    cout<<"***************"<<endl;
			Solution Sol;
			for(int j=0;j<nbtype1;j++){
				Sol.variabletype1.push_back(population[0][j]);
			}
			for(int j=0;j<nbtype2;j++){
				Sol.variabletype2.push_back(population[0][j+nbtype1]);
			}
			for(int j=0;j<nbtype3;j++){
				Sol.variabletype3.push_back(population[0][j+nbtype1+nbtype2]);
			}
			double x=0;
				for (int i = 0; i < nbtype1; i++) {
	x = x + (Sol.variabletype1[i] * Sol.variabletype1[i]);
	}
	for (int i = 0; i < nbtype2; i++) {
		x =x+ (Sol.variabletype2[i] * Sol.variabletype2[i]);
	}
	for (int i = 0; i < nbtype3; i++) {

	x = x + (Sol.variabletype3[i] * Sol.variabletype3[i]);
	}
		
			cout << "Valeur de la solution finale: " <<Sol.Eval(lesDonnees)<< endl;
			Sol.Print_Solution();
			if(Sol.Realisable(lesDonnees) == false)
              cout<<"*****La solutuion finale est realisable: false******"<<endl;
            else
               cout<<"*****La solutuion finale est realisable: True******"<< endl ;


		return 0 ;
	}

