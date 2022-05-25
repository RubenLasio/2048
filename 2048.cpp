#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int n=4;

void inizialization(int campo[n][n]){
	for(int k=0; k<n; k++)
		for(int j=0; j<n; j++)
			campo[k][j]=-1;
}

void riordina(int possibility[n]){
	for(int k=0; k<n; k++)
		for(int j=k+1; j<n; j++){
			if(possibility[k]>possibility[j]){
				int temp=possibility[k];
				possibility[k]=possibility[j];
				possibility[j]=temp;
			}
		}
}

void show(int campo[n][n]){
	cout<<endl<<endl;
	cout<<"\t\t+---------------+---------------+---------------+---------------+\n";
	for(int k=0; k<n; k++){
		cout<<"\t\t|\t";
		for(int j=0; j<n; j++){
			if(campo[k][j]!=-1)
				cout<<campo[k][j]<<"\t|\t";
			else
				cout<<"\t|\t";
		}
		cout<<"\n\t\t+---------------+---------------+---------------+---------------+\n";
	}
}

int genera(int campo[n][n], int empty){
	int possibility[n];//conterrà tutte le celle dove si può inserire un numero;
					   //[n] perchè il massimo di celle è 16 ovvero tutto (solo a inizio game);
	int conta=0;
	for(int j=0; j<n; j++){
		for(int k=0; k<n; k++){
			if(campo[j][k]==(-1)){
				possibility[conta]=k*j+n;//  numero cella disponibile;
				conta++;
			}
		}
	}
	//conta ha i numeri di celle disponibili trovate;   ora bisogna mettere in ordine crescente possibility[n];
	riordina(possibility);
	bool esiste = true;
	int random;
	while(esiste){
		random=rand()%(possibility[conta-1]-possibility[0]+1)+possibility[0];
		for(int k=0; k<conta; k++){
			if(random==possibility[k])
				esiste=false;
		}
		if(esiste)
			random=rand()%(possibility[conta-1]-possibility[0]+1)+possibility[0];
	}
	
	int col, row;
	switch(random){
		case 0: col=0; row=0; break;
		case 1: row=0; col=1; break;
		case 2: row=0; col=2; break;
		case 3: row=0; col=3; break;
		case 4: row=1; col=0; break;
		case 5: row=1; col=1; break;
		case 6: row=1; col=2; break;
		case 7: row=1; col=3; break;
		case 8: row=2; col=0; break;
		case 9: row=2; col=1; break;
		case 10: row=2; col=2; break;
		case 11: row=2; col=3; break;
		case 12: row=3; col=0; break;
		case 13: row=3; col=1; break;
		case 14: row=3; col=2; break;
		case 15: row=3; col=3;
	}
	campo[row][col]=2;
	empty--;
}

bool check(int campo[n][n], char &input){
	if(input=='s'){
		for(int k=0; k<n; k++)
			if(campo[n-1][k]==-1)
				return true;
	}
	else if(input=='w'){
		for(int k=0; k<n; k++)
			if(campo[0][k]==-1)
				return true;
	}
	else if(input=='a'){
		for(int k=0; k<n; k++)
			if(campo[k][0]==-1)
				return true;
	}
	else if(input=='d'){
		for(int k=0; k<n; k++)
			if(campo[k][n-1]==-1)
				return true;
	}
}

int play(int campo[n][n]){
	cout<<endl<<"\t\tInserire (s=giu', a=sinistra, w=su, d=destra) come direzione:\t";
	char input;
	cin>>input;
	while(input!='a'&&input!='w'&&input!='s'&&input!='d'){
		system("cls");
		show(campo);
		cout<<endl<<"\t\tInserire (s=giu', a=sinistra, w=su, d=destra) come direzione:\t";
		cin>>input;
	}
	if(check(campo,input)){//è possibile fare il movimento
		if(input=='a'){
			for(int k=0; k<n; k++)
				if(campo[k][0]==-1){
					campo[k][0]=campo[k][1];
					campo[k][1]=campo[k][2];
					campo[k][2]=campo[k][3];
					campo[k][3]=-1;
				}
		}
		else if(input=='d'){
			for(int k=0; k<n; k++)
				if(campo[k][3]==-1){
					campo[k][3]=campo[k][2];
					campo[k][2]=campo[k][1];
					campo[k][1]=campo[k][0];
					campo[k][0]=-1;
				}
		}
		else if(input=='w'){
			for(int k=0; k<n; k++)
				if(campo[0][k]==-1){
					campo[0][k]=campo[1][k];
					campo[1][k]=campo[2][k];
					campo[2][k]=campo[3][k];
					campo[3][k]=-1;
				}
		}
		else{
			for(int k=0; k<n; k++)
				if(campo[0][k]=-1){
					campo[3][k]=campo[2][k];
					campo[2][k]=campo[1][k];
					campo[1][k]=campo[0][k];
					campo[0][k]=-1;
				}
		}
	}
}

void prova(int campo[n][n]){
	for(int k=0; k<n; k++)
		for(int j=0; j<n; j++){
			campo[k][j]=1;
		}
}

int main(){
	srand(time(0));
	int campo[n][n];
	int empty=n*n;
	
	inizialization(campo);
	//prova(campo);
	//show(campo);
	genera(campo,empty);
	while(true){
		show(campo);
		play(campo);
		genera(campo,empty);
		system("cls");
	}
}
