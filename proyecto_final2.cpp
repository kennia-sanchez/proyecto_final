#include <stdio.h>
#include <conio.h>
#include <String.h>
#include <fstream>

using namespace std;

struct Nodo{
	char nnom[20], nfam[20], nu_m[20];
	int nclave, np_u, ne_i, ne_a, ns_min, ns_max;
	Nodo *prev, *next;
};

Nodo *actual, *nuevo, *primero, *ultimo;
char falso[2];

char nom[20], fam[20], u_m[20];
int clave, p_u, e_i, e_a, s_min, s_max;

void inserta_final(int pclave, char pnom[20], char pfam[20], char pu_m[20], int pp_u, int pe_i, int pe_a, int ps_min, int ps_max){
	nuevo=new Nodo;
	nuevo->nclave=pclave;
	strcpy(nuevo->nnom,pnom);
	strcpy(nuevo->nfam,pfam);
	strcpy(nuevo->nu_m,pu_m);
	nuevo->np_u=pp_u;
	nuevo->ne_i=pe_i;
	nuevo->ne_a=pe_a;
	nuevo->ns_min=ps_min;
	nuevo->ns_max=ps_max;
	
	nuevo->prev=NULL;
	nuevo->next=NULL;
	
	if(primero==NULL){
		primero=nuevo;
		ultimo=nuevo;
	}
	else{
		ultimo->next=nuevo;
		nuevo->prev=ultimo;
		ultimo=nuevo;
	}
}

void cargar_archivo(char archivo[21]){
	ifstream arch;
	arch.open(archivo,ios::in);
	while(!arch.eof()){
		arch>>clave>>nom>>fam>>u_m>>p_u>>e_i>>e_a>>s_min>>s_max;
		if(!arch.eof()){
			inserta_final(clave,nom,fam,u_m,p_u,e_i,e_a,s_min,s_max);
		}
	}
	arch.close();
}

void descargar_archivo(char archivo[21]){
	if(primero==NULL){
		printf("Error, la lista est%c vac%ca ...\n",160,161);
		getche();
	}
	ofstream arch;
	arch.open(archivo,ios::out);
	actual=primero;
	while(actual!=NULL){
		arch <<actual->nclave <<" " <<actual->nnom <<" " <<actual->nfam <<" " <<actual->nu_m <<" " <<actual->np_u <<" " <<actual->ne_i <<" " <<actual->ne_a <<" " <<actual->ns_min <<" " <<actual->ns_max <<"\n";
		actual=actual->next;
	}
	arch.close();
}

void altas(){
	bool existe;
	do{
		printf("Indica la clave del producto                    : "); scanf("%d", &clave); gets(falso);
		if((clave<1) || (clave>99999)){
			printf("Error, el rango de la clave es de 1 a 99999 ...\n");
			getche();
		}
		existe=false;
		actual=primero;
		while(actual!=NULL){
			if(actual->nclave==clave){
				existe=true;
				printf("Error, la clave del producto se duplica en la base de datos ...\n");
				getche();
			}
			actual=actual->next;
		}
	} while (((clave<1) || (clave>99999)) || (existe==true));
	
		int x;
		do{
			printf("Indica el nombre del producto                 : "); gets(nom);
			x=strlen(nom);
			if((x<1) || (x>20)){
				printf("Error, el nombre del producto debe tener entre 1 y 20 caracteres ...\n");
				getche();
			}
		} while ((x<1) || (x>20));
		
		do{
			printf("Indica la familia del producto                : "); gets(fam);
			x=strlen(fam);
			if((x<1) || (x>20)){
				printf("Error, la familia del producto debe tener entre 1 y 20 caracteres ...\n");
				getche();
			}
		} while ((x<1) || (x>20));
		
		do{
			printf("Indica la unidad de medida del producto       : "); gets(u_m);
			x=strlen(u_m);
			if((x<1) || (x>20)){
				printf("Error, la unidad de medida del producto debe tener entre 1 y 20 caracteres ...\n");
				getche();
			}
		} while ((x<1) || (x>20));
		
		do{
			printf("Indica el precio unitario del producto        : "); scanf("%d", &p_u); gets(falso);
			if((p_u<1) || (p_u>99999)){
				printf("Error, el rango del precio unitario es de 1 a 99999 ...\n");
				getche();
			}
		} while ((p_u<1) || (p_u>99999));
		
		do{
			printf("Indica la existencia inicial del producto     : "); scanf("%d", &e_i); gets(falso);
			if((e_i<1) || (e_i>99999)){
				printf("Error, el rango de la existencia inicial es de 1 a 99999 ...\n");
				getche();
			}
		} while ((e_i<1) || (e_i>99999));
		
		do{
			printf("Indica el stock minimo del producto           : "); scanf("%d", &s_min); gets(falso);
			if((s_min<1) || (s_min>99999)){
				printf("Error, el rango del stock minimo es de 1 a 99999 ...\n");
				getche();
			}
		} while ((s_min<1) || (s_min>99999));
		
		do{
			printf("Indica el stock maximo del producto           : "); scanf("%d", &s_max); gets(falso);
			if((s_max<1) || (s_max>99999)){
				printf("Error, el rango del stock maximo es de 1 a 99999 ...\n");
				getche();
			}
		} while ((s_max<1) || (s_max>99999));

	e_a=e_i;
	inserta_final(clave,nom,fam,u_m,p_u,e_i,e_a,s_min,s_max);
	printf("\nPRODUCTO AGREGADO\n");
	getche();
}

void bajas(){
	bool existe;
	Nodo *auxiliar;
	auxiliar=new Nodo;
	printf("Indica la clave del producto a eliminar               :   ");
	scanf("%d",&clave);
	existe=false;
	actual=primero;
	while(actual!=NULL){
		if(actual->nclave==clave){
			existe=true;
			break;
		}
		actual=actual->next;
	}
	if(!existe){
		printf("Error, la clave del producto no existe ...\n");
		getche();
	}
	else{
		if(primero==ultimo){
			delete(actual);
			primero=NULL;
			ultimo=NULL;
		}
		else{
			if(actual==primero){
				auxiliar=primero->next;
				auxiliar->prev=NULL;
				delete(actual);
				primero=auxiliar;
			}
			else{
				if(actual==ultimo){
					auxiliar=actual->prev;
					auxiliar->next=NULL;
					delete(actual);
					ultimo=auxiliar;
				}
				else{
					auxiliar=actual->prev;
					auxiliar->next=actual->next;
					auxiliar=actual->next;
					auxiliar->prev=actual->prev;
					delete(actual);
				}
			}
		}
	}
	printf("\nPRODUCTO ELIMINADO\n");
	getche();
}

void consulta_clave(){
	bool existe;
	printf("Indica la clave del producto                          : ");
	scanf("%d", &clave); gets(falso);
	existe=false;
	actual=primero;
	while(actual!=NULL){
		if(actual->nclave==clave){
			printf("%d %s %s %s %d %d %d %d %d \n",actual->nclave,actual->nnom,actual->nfam,actual->nu_m,actual->np_u,actual->ne_i,actual->ne_a,actual->ns_min,actual->ns_max);
			existe=true;
			break;
		} 
		actual=actual->next;
	}
	if(!existe){
		printf("Error, la clave del producto no existe ...\n");
	}
	getche();
}

void consulta_familia(){
	bool existe;
	printf("Indica la familia del producto                        : "); gets(fam);
	existe=false;
	actual=primero;
	while(actual!=NULL){
		if(strcmp(fam,actual->nfam)==0){
			printf("%d %s %s %s %d %d %d %d %d\n",actual->nclave,actual->nnom,actual->nfam,actual->nu_m,actual->np_u,actual->ne_i,actual->ne_a,actual->ns_min,actual->ns_max);
			existe=true;
		}
		actual=actual->next;
	}
	if(!existe){
		printf("Error, la clave del producto no existe ...\n");
	}
	getche();
}
 
void lista_primero_ultimo(){
	if(primero==NULL){
		printf("Error, la lista est%c vac%ca ...\n",160,161);
	}
	else{
		actual=primero;
		while(actual!=NULL){
			printf("%d %s %s %s %d %d %d %d %d\n",actual->nclave,actual->nnom,actual->nfam,actual->nu_m,actual->np_u,actual->ne_i,actual->ne_a,actual->ns_min,actual->ns_max);
			actual=actual->next;
		}
	}
}


void menu_archivo_productos(){
	char op;
	while (op!='x'){
		printf("\n\n");
		printf("***** MENU ARCHIVOS DE PRODUCTOS *****\n");	
		printf("a) Alta nuevos productos \n");
		printf("b) Baja productos obsoletos \n");
		printf("c) Consulta productos por clave \n");
		printf("d) Consulta productos por familia \n");
		printf("l) Lista \n");
		printf("x) Terminar \n");
		printf("Indica la opci%cn deseada : ",162);
		scanf("%c",&op); gets(falso);
		
		if(op=='a') altas();
		if(op=='b') bajas();
		if(op=='c') consulta_clave();
		if(op=='d') consulta_familia();
		if(op=='l') lista_primero_ultimo();
		if(op=='x') descargar_archivo("productos.txt");
	}
}

void menu_principal(){
	char op;
	while (op!='x'){
		printf("\n\n\n");
		printf("***** MENU PRINCIPAL *****\n");
		printf("a) Archivo de productos \n");
		printf("b) Entradas/Salidas de productos \n");
		printf("c) Reportes \n");
		printf("x) Terminar \n");
		printf("Indica la opci%cn deseada : ",162);
		scanf("%c",&op); gets(falso);
		
		if(op=='a') menu_archivo_productos();
	}
}

main(){
	ofstream arch;
	arch.open("productos.txt",ios::app);
	arch.close();
	cargar_archivo("productos.txt");
	menu_principal();
	descargar_archivo("productos.txt");
}
