#include <iostream>
#include<conio.h>
#include<iomanip>
#include<stdlib.h> 
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<windows.h>
using namespace std;
class book
{
	char bno[6];//n0 de libro
	char bname[50];//nombre de libro
	char aname[20];//autor
	public:
	void createbook()
	{
		cout<<"\nIngresar Nuevo Libro...\n";
		cout<<"\nIngresar Número de Libro: ";
		cin>>bno;
		cout<<"\nIngresar Nombre del Libro: ";
		cin>>bname;
		cout<<"\nIngresar Nombre del Autor: ";
		cin>>aname;
		cout<<"\n\n\nLibro creado!..";
	}
	void showbook()
	{
		cout<<"\nNumero de Libro: "<<bno;
		cout<<"\nNombre del Libro: ";
		puts(bname);
		cout<<"\nNombre del Autor: ";
		puts(aname);
	}
	void modifybook()
	{
		cout<<"\nNumero de libro: "<<bno;
		cout<<"\nModificar nombre del libro: ";
		cin>>bname;
		cout<<"\nModificar autor del libro: ";
		cin>>(aname);
		gets(aname);
		
	}
	
	char* retbno()
	{
		return bno;
	
	}
	void report()
	{
		cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
};

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
	public:
	void createstudent()
	{
		cout<<"\nIngresar nuevo estudiante...\n";
		cout<<"\nIngresar el N° de admision: ";
		cin>>admno;
		cout<<"Ingresar el nombre del estudiante: ";
		cin>>name;
		token=0;
		stbno[0]='\0';
		cout<<"\n\nRegistro de Estudiante creado...";
	}
	void showstudent()
	{
		cout<<"\nNumero de admision : "<<admno;
		cout<<"\nNombre de estudiante : ";
		puts(name);
		cout<<"\nNo de libros prestados : "<<token;
		if(token==1)
		{
			cout<<"\nNumero de libro "<<stbno;
		}
	}
	void modifystudent()
	{
		cout<<"\nNumero de Admision. "<<admno;
		cout<<"\nModificar nombre de estudiante: ";
		cin>>(name);
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token=1;
	}
	void resettoken()
	{ 
	token=0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}
	void report()
	{
		cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl ;
	}
};
fstream fp,fp1;
book bk;
student st;
void writebook()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do{
		bk.createbook();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDesea agregar mas registros...(s/n?) ";
		cin>>ch;
	}while(ch=='s'||ch=='S');
	fp.close();
}

void writestudent()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do{
		
		st.createstudent();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\nDesea agregar mas registros...(s/n?) ";
		cin>>ch;
	}while(ch=='s'||ch=='S');
	fp.close();
}
 void displayspb(char n[])
 {
	 cout<<"\nDetalles del libro\n";
	 int flag=0;
	 fp.open("book.dat",ios::in);
	 while(fp.read((char *)&bk,sizeof(book)))
	 {
		 if(strcmpi(bk.retbno(),n)==0)
		 {
			  bk.showbook();
			  flag=1;
		 }
	 }
	 fp.close();
	 if(flag==0)
	 {
		 cout<<"\n\nEl libro no existe";
	 }
	 getch();
}
 void displaysps(char n[])
 {
	 cout<<"\nDetalles del estudiante\n";
	 int flag=0;
	 fp.open("student.dat", ios::in);
	 while(fp.read((char *)&st,sizeof(student)))
	 {
		 if(strcmpi(st.retadmno(),n)==0)
		 {
			  st.showstudent();
			  flag=1;
		 }
	 }
	 fp.close();
	 if(flag==0)
	 {
		 cout<<"\n\nEl estudiante no existe";   		 
	 }
	 getch();
}
void modifybook()
{
	char n[6];
	int found=0;
	cout<<"\n\nMODIFICAR LIBRO REGISTRADO...";
	cout<<"\n\nIngresar numero de libro. ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			cout<<"\nIngresar nuevos detlles del libro";
			bk.modifybook();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char *)&bk,sizeof(book));
			cout<<"\n\nRegistro actualizado!";
			found=1;
		}
			
	}
	fp.close();
	if(found==0)
	{
		cout<<"\n\nRegistro no encontrado";
		
	}
	getch();
}
 void modifystudent()
{
	char n[6];
	int found=0;
	cout<<"\n\nMODIFICAR REGISTRO DE ESTUDIANTE...";
	cout<<"\n\nIngresar numero de admision. ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			cout<<"\nIngresar nuevos detalles del estudiante: ";
			st.modifystudent();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char *)&st,sizeof(student)); 
			cout<<"\n\nRegistro actualizado";
			found=1;
		}
			
	}
	fp.close();
	if(found==0)
	{
		cout<<"\n\nRegistro no encontrado";
		
	}
	getch();
}
 
 void deletestudent()
 {
	 char n[6];
	 int flag=0;
	 cout<<"\n\n\n\tBORRAR ESTUDIANTE...";
	 cout<<"\n\nIngresar el numero de admision : ";
	 cin>>n;
	 fp.open("student.dat",ios::in|ios::out);
	 fstream fp2;
	 fp2.open("temp.dat",ios::out);
	 fp.seekg(0,ios::beg);
	 while(fp.read((char*)&st,sizeof(student)))
	 {
		 if(strcmpi(st.retadmno(),n)!=0)
		 {
			 fp2.write((char*)&st,sizeof(student));
		 }
		 else{
			 flag=1;//student found
		 }
	 } 
	 fp2.close();
	 fp.close();
	 remove("student.dat");
	 rename("temp.dat","student.dat");//data after deletion moved to temp
	 if(flag==1)
	 {
		 cout<<"\n\n\tRegistro eliminado..";
	 }
	 else
	 {
		cout<<"\n\nRegistro no encontrado"; 
	 }
	 getch();
 }
  void deletebook()
 {
	 char n[6];
	 int flag=0;
	 cout<<"\n\n\n\tBORRAR LIBRO...";
	 cout<<"\n\nIngresar numero de libro : ";
	 cin>>n;
	 fp.open("book.dat",ios::in|ios::out);
	 fstream fp2;
	 fp2.open("Temp.dat",ios::out);
	 fp.seekg(0,ios::beg);
	 while(fp.read((char*)&bk,sizeof(book)))
	 {
		 if(strcmpi(bk.retbno(),n)!=0)
		 {
			 fp2.write((char*)&st,sizeof(book));
		 }
		 else{
			 flag=1;
		 }
	 } 
	 fp2.close();
	 fp.close();
	 remove("book.dat");
	 rename("Temp.dat","book.dat");
	 if(flag==1)
	 {
		 cout<<"\n\n\tRegistro eliminado... ";
	 }
	 else
	 {
		cout<<"\n\nRegistro no encontrado"; 
	 }
	 getch();
 }
 void displayalls()
 {
	 fp.open("student.dat",ios::in);
	 if(!fp)
	 {
		 cout<<"El archivo no se pudo abrir";
		 getch();
		 return;
	 }
	 cout<<"\n\n\t\tLista de estudiantes\n\n";
	 cout<<"==================================================================\n";
	 cout<<"\tN° de admision"<<setw(10)<<"Nombre"<<setw(20)<<"Libro asignado\n";
	 cout<<"==================================================================\n";
	 while(fp.read((char*)&st,sizeof(student)))
	 {
		 st.report();
	 }
	 fp.close();
	 getch();
 }
  void displayallb()
 {
	 fp.open("book.dat",ios::in);
	 if(!fp)
	 {
		 cout<<"El archivo no se pudo abrir";
		 getch();
		 return;
	 }
	 cout<<"\n\n\t\tLista de libros\n\n";
	 cout<<"==================================================================\n";
	 cout<<"\tN° de libro"<<setw(20)<<"Nombre: "<<setw(25)<<"Autor:\n";
	 cout<<"==================================================================\n";
	 while(fp.read((char*)&bk,sizeof(book)))
	 {
		 bk.report();
	 }
	 fp.close();
	 getch();
 }
 void bookissue()
 {
	 char sn[6],bn[6];
	 int found=0,flag=0;
	 cout<<"\n\nLIBRO ASIGNADO...";
	 cout<<"\n\n\tIngresar numero de admision: ";
	 cin>>sn;
	 fp.open("student.dat",ios::in|ios::out);
	 fp1.open("book.dat",ios::in|ios::out);
	 while(fp.read((char*)&st,sizeof(student))&& found==0)
	 {
		 if(strcmpi(st.retadmno(),sn)==0)
		 {
			 found=1;
			 if(st.rettoken()==0)
			 {
				 cout<<"\n\n\tIngresar N° de libro";
			 cin>>bn;
			  while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			  {
				   if(strcmpi(bk.retbno(),bn)==0)
		             {
			          flag=1;
					  st.addtoken();
					  st.getstbno(bk.retbno());
					  int pos=-1*sizeof(st);
					  fp.seekg(pos,ios::cur);
					  fp.write((char*)&st,sizeof(student));
					  cout<<"\n\n\tRegistro de prestamo exitoso\n\n ";
					  cout <<"Tenga en cuenta la fecha de emisión del libro en el reverso de su libro y devuélvalo dentro de los 15 días; de lo contrario, tendra una multa";
					  
					
			  }
		 }
		 if(flag==0)
		 {
			 cout<<"Numero de libro no existente";
		 }
		 
	 } 
	 
	 else
	 {
		 
		 cout<<"Usted no devolvió el ultimo libro";
		 
	 }
	 
		 
 
	 }
 
 }
 if(found==0)
 {
	 cout<<"El registro de estudiante no existe...";
	 
 }
 getch();
 fp.close();
 fp1.close();
 }
 
 void bookdeposit()
 {
	 char sn[6],bn[6];
	 int found=0,flag=0,day,fine;
	 //clrscr();
	 cout<<"\n\nBOOK DEPOSIT...";
	 cout<<"\n\n\tEnter Admission no. Of Student";
	 cin>>sn;
	 fp.open("student.dat",ios::in|ios::out);
	 fp1.open("book.dat",ios::in|ios::out);
	 while(fp.read((char*)&st,sizeof(student))&& found==0)
	 {
		 if(strcmpi(st.retadmno(),sn)==0)//compare admsn no.
		 {
			 found=1;
			 if(st.rettoken()==1)//if book issued
			 {
				 while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			  {
				   if(strcmpi(bk.retbno(),st.retstbno())==0)
		             {
			          flag=1;
					  bk.showbook();
					  cout<<"\n\n Libro depositado en número de días";
					  cin>>day;
					  if(day>15)
					  {
						  fine=(day-15)*1;
						  cout<<"\n\n Fine = "<<fine;
					  }
					  st.resettoken();
					 
					  int pos=-1*sizeof(st);
					  fp.seekg(pos,ios::cur);
					  fp.write((char*)&st,sizeof(student));
					  cout<<"\n\n\tDeposito de libro exitoso";
			  }
		 }
		 if(flag==0)
		 {
			 cout<<"El numero de libro no existe";
		 }
		 
	 } 
	 
	 else
	 {
		 
		 cout<<"Ningun libro prestado";
		 
	 }
	 
		 
 
	 }
 
 }
 if(found==0)
 {
	 cout<<"Registro de estudiante no existe...";
	 
 }
 getch();
 fp.close();
 fp1.close();
 }
 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 
 
void start()
{ //clrscr();
gotoxy(35,11);
cout<<"SISTEMA DE";
gotoxy(35,14);
cout<<"GESTION";
gotoxy(35,17);
cout<<"DE BIBLIOTECA";
getch();
}
void adminmenu()
{
	//clrscr();
	int ch2;
	cout<<"\n\n\n\tMENU DEL ADMINISTRADOR";
	cout<<"\n\n\n\t1.CREAR REGISTRO DE ESTUDIANTE";
	cout<<"\n\n\n\t2.MOSTRAR TODOS LOS REGISTROS DE ESTUDIANTES";
	cout<<"\n\n\n\t3.MOSTRAR REGISTRO ESPECIFICO DE ESTUDIANTE";
	cout<<"\n\n\n\t4.MODIFICAR REGISTRO DE ESTUDIANTE";
	cout<<"\n\n\n\t5.ELIMINAR REGISTRO DE ESTUDIANTE";
	cout<<"\n\n\n\t6.CREAR REGISTRO DE LIBRO";
	cout<<"\n\n\n\t7.MOSTRAR TODOS LOS REGISTROS DE LIBROS";
	cout<<"\n\n\n\t8.MOSTRAR REGISTRO ESPECIFICO DE LIBRO";
	cout<<"\n\n\n\t9.MODIFICAR REGISTRO DE LIBRO";
	cout<<"\n\n\n\t10.ELIMINAR REGISTRO DE LIBRO";
	cout<<"\n\n\n\t11.REGRESAR AL MENU DEL LIBRO";
	cout<<"\n\n\n\tINGRESE SU ELECCION(1-11)";
	cin>>ch2;
	switch(ch2)
	{
		case 1: writestudent();
		break;
		case 2: displayalls();
		break;
		case 3: char num[6];
		//clrscr();
		cout<<"\n\n\t Ingrese No de admision";
		cin>>num;
		displaysps(num);
		break;
		case 4: modifystudent();
		break;
		case 5:deletestudent();
		break;
		case 6:writebook();
		break;
		case 7:displayallb();
		break;
		case 8:
	    {char num[6];
		
		cout<<"\n\n\tIngresar Numero de Libro: ";
		cin>>num;
		displayspb(num);
		break;
		}
		case 9:modifybook();
		break;
		case 10:deletebook();
		break;
		case 11:
		return;
		default:
		cout<<"Opcion invalida"; 
	}
	adminmenu();
} 
int main()

{ 
char ch;
start();
do{
	cout<<"\n\n\n\t MENU PRINCIPAL";
	cout<<"\n\n\n\t1 LIBRO PRESTADO";
	cout<<"\n\n\n\t2 DEPOSITO DE LIBRO";
	cout<<"\n\n\n\t3 MENU DEL ADMINISTRADOR"; 
	cout<<"\n\n\n\t4 SALIR";
	cout<<"\n\n\n\t ELEGIR OPCION(1-4)";  
	ch=getche();
	switch(ch)
	{ case '1': bookissue(); 
	  break;
	  case '2': bookdeposit();
	  break;
	  case '3': 
	  adminmenu();
	  break;
	  case '4': 
	  exit(0); 
	  break;
	  default:
	  cout<<"OPCION INVALIDA"; 
	  
	}         
}while(ch!=4 ); 

}
