#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;



class Nave{
	private:
		int num=3;
		int posizione[3];
		int colpi[25];
	
	public:
		Nave(){
		srand(time(NULL));
		azzera(colpi, 25);
		};
		
		void azzera(int vet[], int max){
			for(int x=0;x<max;x++){
				vet[x]=0;
			}
		} 
		
		
		int colpo(){
			int colpo=0;
			bool flag=false;
			do{
				flag=false;
				colpo=rand()%25+1;			
				for(int x=0;x<25;x++){
					if(colpo==colpi[x])
						flag=true;
				}
			}while(flag==true);
			
			flag=false;
			
			for(int x=0;x<25;x++){
				if(colpi[x]==0&&flag==false){
					colpi[x]=colpo;
					flag=true;
				}
				
			}
			
			return colpo;
		};

		void colpo(int num){
			bool flag=false;
			for(int x=0;x<=25;x++){
				if(colpi[x]==0&&flag==false){
					colpi[x]=num;
					flag=true;
				}
			}	
		};
			
		void setNum(){
			num--;	
		};
		
		void setPosizione(int x, int num){
			posizione[x]=num;
		};
		
		
		int getNum(){
			return num;
		};
		
		int getPosizione(int x){
			int num=posizione[x];
			return num;
		}
		
		int getColpi(int x){
			return colpi[x];
		};
		
		void takedown(int val){
			for(int x=0;x<3;x++)
				if(posizione[x]==val)
					posizione[x]=-1;	
		};
		
};


Nave naviuser;
Nave navipc;

void debug(){
	for(int x=0;x<25;x++){
		cout<<navipc.getColpi(x)<<" ";
	}
}

void clear(){
	system("cls");
}

void caricamento(){
	int vet[5];
	system("cls");
	
	cout<<"Caricamento in corso..."<<endl<<"_________________________"<<endl;
	
	for(int x=0;x<5;x++){
		vet[x]=rand()%9+1;
	}
	
	Sleep(1000);
	
	for(int x=0;x<5;x++){
		for(int y=0;y<=vet[x];y++)
			Sleep(250);
		cout<<"_____";
	}
	
	Sleep(2000);
	system("cls");
}

bool posizione(int ver){
	for(int x=0;x<3;x++){
		if(ver==naviuser.getPosizione(x))
			return true;
	}
	return false;
}

bool posizione(int val, int stat){
	for(int x=0;x<3;x++){
		if(val==navipc.getPosizione(x))
			return true;
	}
	return false;
}
	 
void outputnavi(){
	for(int x=1;x<=25;x++){
		bool flag=false;
		for(int y=0;y<25;y++){
			if(x==naviuser.getColpi(y))
				flag=true;
		}
		
		if(posizione(x)==false&&flag==true)
			cout<<" @";
			else{
				if(posizione(x)==true)
					cout<<" O";
					else
						cout<<" #";
			}
		
		if(x%5==0)
			cout<<endl;
		
	}
	
	cout<<"Navi alleate rimanenti: "<<naviuser.getNum()<<"\nNavi nemiche: "<<navipc.getNum()<<"\n\n"<<endl;
}

void outputnavicpu(){
	for(int x=1;x<=25;x++){
		if (posizione(x,1)==true)
			cout<<" O";
			else
				cout<<" #";
		
		if(x%5==0)
			cout<<endl;
	}
	cout<<endl;
}

void navicpu(){
	for(int x=0;x<3;x++){
		int num=rand()%25+1;
		navipc.setPosizione(x,num);
	}
}

void naviutente(){
	for(int x=0;x<3;x++){
	cout<<"Posiziona le navi:"<<endl;
		int num;
		do{
			outputnavi();
			cout<<"\n\n"<<x+1<<" nave:\n"<<">> ";
			cin>>num;
			if(num<=0||num>25){
				cout<<"\nPuoi inserire solo valori da 1 a 25\n";
				Sleep(2000);
			}
			clear();
		}while(num<=0||num>25);
		naviuser.setPosizione(x,num);
	}
	outputnavi();
	Sleep(1500);
}

bool verifica(int colpo, int flag){
	if (flag==1){
		for(int x=0;x<3;x++){
			if (colpo==navipc.getPosizione(x))
				return true;
	}
	return false;
	}
	else{
		for(int x=0;x<3;x++){
			if (colpo==naviuser.getPosizione(x))
				return true;
		}
	return false;
	}
	
}

bool ridondanza(int val){
	for(int x=0;x<25;x++){
		if(val==naviuser.getColpi(x))
			return true;
	}
	return false;
}

bool vicinanza(int col, int flag){
	if (flag==1){
		for(int x=0;x<3;x++){
			if(col==(navipc.getPosizione(x))-1||col==(navipc.getPosizione(x))+1)
				return true;
				else
					return false;
		}
	}else{
		for(int x=0;x<3;x++){
			if(col==(naviuser.getPosizione(x))-1||col==(naviuser.getPosizione(x))+1)
				return true;
				else
					return false;
		}
	}
}

int main(){
	int colpopc;
	string risposta;
	cout<<"BENVENUTO NEL GIOCO DI GUERRA NAVALE!!"<<endl;
	cin.ignore();
	cout<<"E' il momento di iniziare :-)";
	Sleep(1000);
	clear();
	naviutente();
	caricamento();
	navicpu();
	clear();
	
	do{
		outputnavi();
		int col;
		do{
		cout<<"GUERRA NAVALE\n"<<"Scegli dove colpire:\n"<<">> ";
			cin>>col;
			if(ridondanza(col)==true){
				cout<<"Non puoi colpire due volte lo stesso punto"<<endl;
				Sleep(2000);
				clear();
				outputnavi();
			}
			if(col>=25||col<0){
				cout<<"Puoi inserire solo valori compresi tra 1 e 25"<<endl;
				Sleep(2000);
				clear();
				outputnavi();
			}
		}while(col>=25||col<0||ridondanza(col)==true);
		naviuser.colpo(col);
		
		if(verifica(col,1)==true){
			cout<<"Complimenti hai colpito una nave nemica!"<<endl;
			navipc.setNum();
			navipc.takedown(col);
		}
			else{
				if(vicinanza(col,1)==true)
					cout<<"Per poco non hai colpito una nave nemica!!"<<endl;
					else
						cout<<"Colpo a vuoto!"<<endl;
			} 
		
		cout<<"\nOra e' il turno dell'avversario"<<endl;
		Sleep(1000);
		colpopc=navipc.colpo();
		if(verifica(colpopc,2)==true){
			cout<<">>Dannazione! Il nemico ha colpito una nave alleata in posizione:\t"<<colpopc<<endl;
			naviuser.setNum();
			naviuser.takedown(colpopc);
		}
		else{
			if(vicinanza(colpopc,2)==true)
				cout<<">>Per poco il nemico non ha colpito la nostra nave!!"<<endl;
				else
					cout<<">>Il colpo nemico e' andato a vuoto!!"<<endl;
		}
		Sleep(3000);
		clear();
	}while(navipc.getNum()!=0&&naviuser.getNum()!=0);
	
	if(navipc.getNum()==0)
		cout<<"Complimenti hai vinto, ottimo lavoro!"<<endl;
		else{
			cout<<"Mi dispiace hai perso!\n\nLa posizione delle navi nemiche era:\n\n";
			outputnavicpu();
		}
	
	system("pause");
	
}
