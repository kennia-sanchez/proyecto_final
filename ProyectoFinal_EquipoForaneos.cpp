/*
Tecnológico de Monterrey 
Estructura de datos
Proyecto final "Inventario"  
Profesor Víctor Mañón
Karol Paola Nava Jiménez A01369164
Kennia Jackeline Sánchez Castillo A00517129
Ismael Vidal López A00826076
*/



#include <stdio.h>
#include <conio.h>
#include <String.h>
#include <fstream>
#include <time.h>

using namespace std;

int cla,pu,ei,ea,sminn,smaxx;
char nom[21], fam[21], udm[21];

int cla_mov, cantidad;
char fecha[11], tipo[2], subtipo[2];

struct Nodo{
	int ncla, npu, nei, nea, nsminn, nsmaxx;
	char nnom[21], nfam[21], nudm[21];
	Nodo *prev, *next;
};

struct NodoM{
	int ncla_mov,ncantidad;
	char nfecha[11], ntipo[2], nsubtipo[2];
	NodoM *prevM, *nextM;
};

Nodo *actual, *nuevo, *anterior, *primero, *ultimo;
NodoM *actualM, *nuevoM, *anteriorM, *primeroM, *ultimoM;
char falso[2];

void insertar_productos(int pcla, char pnom[21], char pfam[21], char pudm[21],int ppu,int pei,int pea, int psminn, int psmaxx){
        
	nuevo=new Nodo;
    nuevo->ncla=cla;
    strcpy(nuevo->nnom,pnom);
    strcpy(nuevo->nfam,pfam);
    strcpy(nuevo->nudm,pudm);
    nuevo->npu=ppu;
    nuevo->nei=pei;
    nuevo->nea=pea;
    nuevo->nsminn=psminn;
    nuevo->nsmaxx=psmaxx;
    nuevo->prev=NULL;
    nuevo->next=NULL;
        
    if (primero==NULL){
        primero=nuevo;
        ultimo=nuevo;
	}
	else{
		ultimo->next=nuevo;
		nuevo->prev=ultimo;
		ultimo=nuevo;
	}
}

void insertar_movimientos(int pcla_mov, char pfecha[11], int pcantidad, char ptipo[2],char psubtipo[2]){
    
	nuevoM=new NodoM;
    nuevoM->ncla_mov=pcla_mov;
    strcpy(nuevoM->nfecha,pfecha);
    nuevoM->ncantidad=pcantidad;
	strcpy(nuevoM->ntipo,ptipo);
	strcpy(nuevoM->nsubtipo,psubtipo);
    nuevoM->prevM=NULL;
    nuevoM->nextM=NULL;
        
    if (primeroM==NULL){
        primeroM=nuevoM;
        ultimoM=nuevoM;
	}
	else{
		ultimoM->nextM=nuevoM;
		nuevoM->prevM=ultimoM;
		ultimoM=nuevoM;
	}
}

int ask_clave(){
	do {
		printf("Indique la clave del producto               : ");scanf("%d",&cla); gets(falso);
	    if ((cla<1) || (cla>99999)){
	        printf("Error, clave fuera de rango entre 1 y 99,999\n");
	        getche();
	        system("cls");
	    }
	} while ((cla<1) || (cla>99999));
	return(cla);
}

bool busca_clave(){
	ask_clave();
	actual=primero;
	anterior=NULL;
	while (actual!=NULL){
		if (actual->ncla==cla){
			return true;
		}
		anterior=actual;
		actual=actual->next;
	}
	return false;
}

void cargar_productos(){
	ifstream arch;
	arch.open("productos.txt",ios::in);
	while(!arch.eof()){
		arch >>cla >>nom >>fam >>udm >>pu >>ei >>ea >>sminn >>smaxx;
		if (!arch.eof()){
			insertar_productos(cla,nom,fam,udm,pu,ei,ea,sminn,smaxx);
		}
	}
	arch.close();
}

void descargar_productos(){
	if (primero==NULL){
		printf("Error, la lista est%c vac%ca...\n",160,161);
		getche();
	}
	ofstream arch;
	arch.open("productos.txt",ios::out);
	actual=primero;
	while (actual!=NULL){
		arch <<actual->ncla <<" " <<actual->nnom <<" " <<actual->nfam <<" " <<actual->nudm <<" " <<actual->npu <<" " <<actual->nei <<" " <<actual->nea <<" " <<actual->nsminn <<" "<<actual->nsmaxx <<"\n";
		actual=actual->next;
	}
	arch.close();
}

void cargar_movimientos(){
	ifstream arch;
	arch.open("movimientos.txt",ios::in);
	while(!arch.eof()){
		arch >>cla_mov >>fecha >>cantidad >>tipo >>subtipo;
		if (!arch.eof()){
			insertar_movimientos(cla_mov,fecha,cantidad,tipo,subtipo);
		}
	}
	arch.close();
}

void descargar_movimientos(){
	if (primero==NULL){
		printf("Error, la lista est%c vac%ca...\n",160,161);
		getche();
	}
	ofstream arch;
	arch.open("movimientos.txt",ios::out);
	actualM=primeroM;
	while (actualM!=NULL){
		arch <<actualM->ncla_mov <<" " <<actualM->nfecha <<" " <<actualM->ncantidad <<" " <<actualM->ntipo <<" " <<actualM->nsubtipo <<"\n";
		actualM=actualM->nextM;
	}
	arch.close();
}

void alta_productos(){
	system("cls");
	if (busca_clave()){
		printf("Error, la clave se duplica en el archivo\n");
        getche();
	}
	else{
		do {
			printf("Indique el nombre del producto              : "); gets(nom);
            if ((strlen(nom)<1) || (strlen(nom)>20)){
                printf("Error, el nombre debe tener entre 1 y 20 caracteres ...\n");
                getche();
            }
		} while ((strlen(nom)<1) || (strlen(nom)>20));
		
		do{
			printf("Indica la familia del producto             : "); gets(fam);
            if ((strlen(fam)<1) || (strlen(fam)>20)){
                printf("Error, la familia debe tener entre 1 y 20 caracteres ...\n");
                getche();
            }
		} while ((strlen(fam)<1) || (strlen(fam)>20));
		
		do{
			printf("Indica la unidad de medida del producto    : "); gets(udm);
            if ((strlen(udm)<1) || (strlen(udm)>20)){
                printf("Error, la unidad de medida debe tener entre 1 y 20 caracteres ...\n");
                getche();
            }
		} while ((strlen(udm)<1) || (strlen(udm)>20));
		
		do{
			printf("Indica el precio unitario por cada producto: ");scanf("%d",&pu);gets(falso);
            if ((pu<1) || (pu>999999)){
                printf("Error, el precio unitario fuera de rango entre 1 y 999,999\n");
                getche();
            }
		} while ((pu<1) || (pu>999999));
		
		do{
			printf("Indica la existencia inicial del producto  : ");scanf("%d",&ei);gets(falso);
            if ((ei<1) || (ei>999999)){
                printf("Error, existencia inicial fuera de rango entre 1 y 999,999\n");
                getche();
            }
		} while ((ei<1) || (ei>999999));
		
		ea=ei;
		
		do{
			printf("Indica el stock m%cnimo                     : ",161);scanf("%d",&sminn);gets(falso); 
            if ((sminn<1) || (sminn>999999)){
                printf("Error, stock m%cnimo fuera de rango entre 1 y 999,999\n",161);
                getche();
            }
		} while ((sminn<1) || (sminn>999999));
		
		do{
			printf("Indica el stock m%cximo                     : ",160);scanf("%d",&smaxx);gets(falso); 
            if ((smaxx<1) || (smaxx>999999)){
                printf("Error, stock m%cximo fuera de rango entre 1 y 999,999\n",160);
                getche();
            }
		} while ((smaxx<1) || (smaxx>999999));
		
		for (int i=0;i<strlen(nom);i++) if (nom[i]==' ') nom[i]='_';
	    for (int i=0;i<strlen(fam);i++) if (fam[i]==' ') fam[i]='_';
        for (int i=0;i<strlen(udm);i++) if (udm[i]==' ') udm[i]='_';
        
        insertar_productos(cla,nom,fam,udm,pu,ei,ea,sminn,smaxx);
		descargar_productos();
		printf("Datos del producto guardados exitosamente");
		getche();
    }
}

void bajas_productos(){
	Nodo *auxiliar;
	NodoM *auxiliarM;
	if (!busca_clave()){
		printf("Error, clave inexistente del producto solicitado\n");
		getche();
   }
	else{
		if (primero==ultimo){
			delete(actual);
			primero=NULL;
			ultimo=NULL;
		}
		else{
			if (actual==primero){
				auxiliar=primero->next;
				auxiliar->prev=NULL;
				delete(actual);
				primero=auxiliar;
			}
			else{
				if (actual==ultimo){
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
		actualM=primeroM;
		while (actualM!=NULL){
			if (actualM->ncla_mov==cla){
				if (primeroM==ultimoM){
					delete(actualM);
					primeroM=NULL;
					ultimoM=NULL;
				}
				else{
					if (actualM==primeroM){
						auxiliarM=primeroM->nextM;
						auxiliarM->prevM=NULL;
						delete(actualM);
						primeroM=auxiliarM;
					}
					else{
						if (actualM==ultimoM){
							auxiliarM=actualM->prevM;
							auxiliarM->nextM=NULL;
							delete(actualM);
							ultimoM=auxiliarM;
						}
						else{
							auxiliarM=actualM->prevM;
							auxiliarM->nextM=actualM->nextM;
							auxiliarM=actualM->nextM;
							auxiliarM->prevM=actualM->prevM;
							delete(actualM);
						}
					}
				}
			}
			actualM=actualM->nextM;
		}
		descargar_productos();
		descargar_movimientos();
		printf("Datos eliminados correctamente");
		getche();
	}
}

void consulta_por_clave(){
	if (busca_clave()){

		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
	    for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]==' ') actual->nfam[i]='_';
        for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]==' ') actual->nudm[i]='_';
        
		printf("Nombre            : %s\n",actual->nnom);
		printf("Familia           : %s\n",actual->nfam);
		printf("Unidad de medida  : %s\n",actual->nudm);
		printf("Precio unitario   : %d\n",actual->npu);
		printf("Existencia inicial: %d\n",actual->nei);
		printf("Existencia actual : %d\n",actual->nea);
		printf("Stock m%cnimo      : %d\n",161,actual->nsminn);
		printf("Stock m%cximo      : %d\n",160,actual->nsmaxx);
		getche();
		
		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
	    for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]==' ') actual->nfam[i]='_';
        for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]==' ') actual->nudm[i]='_';
	}
	else{
		printf("Error, clave inexistente en el archivo de productos\n");
		getche();
	}
}

void consulta_por_familia(){
	char vfam[21];
	bool existe=false;
	printf("Indica la familia del producto             : "); gets(vfam);
	actual=primero;
	while (actual!=NULL){
		if (strcmp(actual->nfam,vfam)==0){
			
			for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]=='_') actual->nnom[i]=' ';
			for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]=='_') actual->nfam[i]=' ';
        	for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]=='_') actual->nudm[i]=' ';
        
			printf("Nombre            : %s\n",actual->nnom);
			printf("Familia           : %s\n",actual->nfam);
			printf("Unidad de medida  : %s\n",actual->nudm);
			printf("Precio unitario   : %d\n",actual->npu);
			printf("Existencia inicial: %d\n",actual->nei);
			printf("Existencia actual : %d\n",actual->nea);
			printf("Stock m%cnimo      : %d\n",161,actual->nsminn);
			printf("Stock m%cximo      : %d\n",160,actual->nsmaxx);
			printf("-----------------------------------------\n");
			getche();
		
			for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
		    for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]==' ') actual->nfam[i]='_';
	        for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]==' ') actual->nudm[i]='_';
			existe=true;
		}
		actual=actual->next;
	}
	if (!existe){
		printf("Error, clave inexistente en el archivo de productos\n");
		getche();
	}
}

void entradas(int entrada){
	if (!busca_clave()){
		printf("Error, clave inexistente en archivo de productos\n");
		getche();
	}
	else{
		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]=='_') actual->nnom[i]=' ';
		printf("Nombre del producto                        : %s\n",actual->nnom);
		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
		
		do{
			printf("Indica la cantidad de movimiento           : "); scanf("%d",&cantidad); gets(falso);
			if ((cantidad<1) || (cantidad>999999)){
				printf("Error, cantidad fuera de rango entre 1 y 999,999\n");
				getche();
			}
		} while ((cantidad<1) || (cantidad>999999));
		time_t tiempo = time(NULL);
		struct tm *tlocal = localtime(&tiempo);
		strftime(fecha,11,"%d/%m/%Y",tlocal);
	
		if (entrada==1){												
			strcpy(tipo,"E");
			strcpy(subtipo,"C");
			
			actual->nea=actual->nea+cantidad;
		}else if(entrada == 2){                                       
			strcpy(tipo,"E");
			strcpy(subtipo,"D");
			
			actual->nea=actual->nea+cantidad;			
		}else if(entrada == 3){                                       
			strcpy(tipo,"S");
			strcpy(subtipo,"V");
			
			actual->nea=actual->nea-cantidad;
		}else if (entrada == 4){									
			strcpy(tipo,"S");
			strcpy(subtipo,"P");
			
			actual->nea=actual->nea-cantidad;		
		}else if(entrada == 5){
			strcpy(tipo,"S"); 										
			strcpy(subtipo,"M");
			
			actual->nea=actual->nea-cantidad;		
		}
		descargar_productos();
		insertar_movimientos(cla,fecha,cantidad,tipo,subtipo);
		descargar_movimientos();
		printf("Datos del movimiento guardados exitosamente\n");
		getche();
	}
}

void lista_productos(int op_ord){
	printf("=======================================================================================================================================\n");
	printf("Clave   Nombre del producto  Familia del producto      Unidad de medida  Precio unitario  Existencia Actual  Stock M%cnimo  Stock M%cximo\n",161,160);
	printf("=======================================================================================================================================\n");

	actual=primero;
	while (actual!=NULL){
		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]=='_') actual->nnom[i]=' ';
		for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]=='_') actual->nfam[i]=' ';
        for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]=='_') actual->nudm[i]=' ';
        if (op_ord==4){
        	if (actual->nea<=actual->nsminn) printf("%5d  %20s  %20s  %20s           %6d             %6d        %6d        %6d\n",actual->ncla,actual->nnom,actual->nfam,actual->nudm,actual->npu,actual->nea,actual->nsminn,actual->nsmaxx);
		}
		else{
			if (op_ord==5){
				if (actual->nea>=actual->nsmaxx) printf("%5d  %20s  %20s  %20s           %6d             %6d        %6d        %6d\n",actual->ncla,actual->nnom,actual->nfam,actual->nudm,actual->npu,actual->nea,actual->nsminn,actual->nsmaxx);
			}
			else{
				printf("%5d  %20s  %20s  %20s           %6d             %6d        %6d        %6d\n",actual->ncla,actual->nnom,actual->nfam,actual->nudm,actual->npu,actual->nea,actual->nsminn,actual->nsmaxx);
			}
		}
		for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
		for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]==' ') actual->nfam[i]='_';
        for (int i=0;i<strlen(actual->nudm);i++) if (actual->nudm[i]==' ') actual->nudm[i]='_';
		actual=actual->next;
	}
	getche();
}

void ordenar_reporte(int op_orden){
	Nodo *auxiliar, *posterior;
	auxiliar=new Nodo;
	posterior=new Nodo;
	actual=primero;
	while(actual!=NULL){
		posterior=actual->next;
		while(posterior!=NULL){
			if (op_orden==1){
				if (actual->ncla>posterior->ncla){
					
					auxiliar->ncla=actual->ncla;
					strcpy(auxiliar->nnom,actual->nnom);
					strcpy(auxiliar->nfam,actual->nfam);
					strcpy(auxiliar->nudm,actual->nudm);
					auxiliar->npu=actual->npu;
					auxiliar->nei=actual->nei;
					auxiliar->nea=actual->nea;
					auxiliar->nsminn=actual->nsminn;
					auxiliar->nsmaxx=actual->nsmaxx;
					
					actual->ncla=posterior->ncla;
					strcpy(actual->nnom,posterior->nnom);
					strcpy(actual->nfam,posterior->nfam);
					strcpy(actual->nudm,posterior->nudm);
					actual->npu=posterior->npu;
					actual->nei=posterior->nei;
					actual->nea=posterior->nea;
					actual->nsminn=posterior->nsminn;
					actual->nsmaxx=posterior->nsmaxx;
	
					posterior->ncla=auxiliar->ncla;
					strcpy(posterior->nnom,auxiliar->nnom);
					strcpy(posterior->nfam,auxiliar->nfam);
					strcpy(posterior->nudm,auxiliar->nudm);
					posterior->npu=auxiliar->npu;
					posterior->nei=auxiliar->nei;
					posterior->nea=auxiliar->nea;
					posterior->nsminn=auxiliar->nsminn;
					posterior->nsmaxx=auxiliar->nsmaxx;
				}
			}
			if (op_orden==2){
				if (strcmp(actual->nnom,posterior->nnom)==1){
					
					auxiliar->ncla=actual->ncla;
					strcpy(auxiliar->nnom,actual->nnom);
					strcpy(auxiliar->nfam,actual->nfam);
					strcpy(auxiliar->nudm,actual->nudm);
					auxiliar->npu=actual->npu;
					auxiliar->nei=actual->nei;
					auxiliar->nea=actual->nea;
					auxiliar->nsminn=actual->nsminn;
					auxiliar->nsmaxx=actual->nsmaxx;
					
					actual->ncla=posterior->ncla;
					strcpy(actual->nnom,posterior->nnom);
					strcpy(actual->nfam,posterior->nfam);
					strcpy(actual->nudm,posterior->nudm);
					actual->npu=posterior->npu;
					actual->nei=posterior->nei;
					actual->nea=posterior->nea;
					actual->nsminn=posterior->nsminn;
					actual->nsmaxx=posterior->nsmaxx;
	
					posterior->ncla=auxiliar->ncla;
					strcpy(posterior->nnom,auxiliar->nnom);
					strcpy(posterior->nfam,auxiliar->nfam);
					strcpy(posterior->nudm,auxiliar->nudm);
					posterior->npu=auxiliar->npu;
					posterior->nei=auxiliar->nei;
					posterior->nea=auxiliar->nea;
					posterior->nsminn=auxiliar->nsminn;
					posterior->nsmaxx=auxiliar->nsmaxx;
				}
			}
			if (op_orden==4){
				if (actual->nea>posterior->nea){
					
					auxiliar->ncla=actual->ncla;
					strcpy(auxiliar->nnom,actual->nnom);
					strcpy(auxiliar->nfam,actual->nfam);
					strcpy(auxiliar->nudm,actual->nudm);
					auxiliar->npu=actual->npu;
					auxiliar->nei=actual->nei;
					auxiliar->nea=actual->nea;
					auxiliar->nsminn=actual->nsminn;
					auxiliar->nsmaxx=actual->nsmaxx;
					
					actual->ncla=posterior->ncla;
					strcpy(actual->nnom,posterior->nnom);
					strcpy(actual->nfam,posterior->nfam);
					strcpy(actual->nudm,posterior->nudm);
					actual->npu=posterior->npu;
					actual->nei=posterior->nei;
					actual->nea=posterior->nea;
					actual->nsminn=posterior->nsminn;
					actual->nsmaxx=posterior->nsmaxx;
	
					posterior->ncla=auxiliar->ncla;
					strcpy(posterior->nnom,auxiliar->nnom);
					strcpy(posterior->nfam,auxiliar->nfam);
					strcpy(posterior->nudm,auxiliar->nudm);
					posterior->npu=auxiliar->npu;
					posterior->nei=auxiliar->nei;
					posterior->nea=auxiliar->nea;
					posterior->nsminn=auxiliar->nsminn;
					posterior->nsmaxx=auxiliar->nsmaxx;
				}
			}
			if (op_orden==5){
				if (actual->nea>posterior->nea){
					
					auxiliar->ncla=actual->ncla;
					strcpy(auxiliar->nnom,actual->nnom);
					strcpy(auxiliar->nfam,actual->nfam);
					strcpy(auxiliar->nudm,actual->nudm);
					auxiliar->npu=actual->npu;
					auxiliar->nei=actual->nei;
					auxiliar->nea=actual->nea;
					auxiliar->nsminn=actual->nsminn;
					auxiliar->nsmaxx=actual->nsmaxx;
					
					actual->ncla=posterior->ncla;
					strcpy(actual->nnom,posterior->nnom);
					strcpy(actual->nfam,posterior->nfam);
					strcpy(actual->nudm,posterior->nudm);
					actual->npu=posterior->npu;
					actual->nei=posterior->nei;
					actual->nea=posterior->nea;
					actual->nsminn=posterior->nsminn;
					actual->nsmaxx=posterior->nsmaxx;
	
					posterior->ncla=auxiliar->ncla;
					strcpy(posterior->nnom,auxiliar->nnom);
					strcpy(posterior->nfam,auxiliar->nfam);
					strcpy(posterior->nudm,auxiliar->nudm);
					posterior->npu=auxiliar->npu;
					posterior->nei=auxiliar->nei;
					posterior->nea=auxiliar->nea;
					posterior->nsminn=auxiliar->nsminn;
					posterior->nsmaxx=auxiliar->nsmaxx;
				}
			}
		posterior=posterior->next;
		}
		actual=actual->next;
	}
	if (op_orden==4) lista_productos(4);
	if (op_orden==5) lista_productos(5);
	if (op_orden==1) lista_productos(1);
	if (op_orden==2) lista_productos(2);
	delete(auxiliar);
	delete(posterior);
}

void lista_movimientos(){
	for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]=='_') actual->nnom[i]=' ';
	for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]=='_') actual->nfam[i]=' ';
			
	printf("\nClave  :  %d\n",actual->ncla);
	printf("Nombre :  %s\n",actual->nnom);
	printf("Familia:  %s\n\n",actual->nfam);
			
	for (int i=0;i<strlen(actual->nnom);i++) if (actual->nnom[i]==' ') actual->nnom[i]='_';
	for (int i=0;i<strlen(actual->nfam);i++) if (actual->nfam[i]==' ') actual->nfam[i]='_';
	
	printf("Fecha       Cantidad  Entrada/Salida  Subtipo\n");
	printf("==============================================\n");
	
	actualM=primeroM;
	while (actualM!=NULL){
		if (actualM->ncla_mov==cla){
			printf("%10s  %6d           %1s           %1s\n",actualM->nfecha,actualM->ncantidad,actualM->ntipo,actualM->nsubtipo);
		}
		actualM=actualM->nextM;
	}
	getche();
}

void ordenar_movimientos(){
	NodoM *auxiliarM, *posteriorM;
	auxiliarM=new NodoM;
	posteriorM=new NodoM;
	if (!busca_clave()){
		printf("Error, clave inexistente del producto solicitado\n");
		getche();
	}
	else{
		actualM=primeroM;
		while (actualM!=NULL){
			posteriorM=actualM->nextM;
			while (posteriorM!=NULL){
				if (strcmp(actualM->nfecha,posteriorM->nfecha)==1){
					
					auxiliarM->ncla_mov=actualM->ncla_mov;
					strcpy(auxiliarM->nfecha,actualM->nfecha);
					auxiliarM->ncantidad=actualM->ncantidad;
					strcpy(auxiliarM->ntipo,actualM->ntipo);
					strcpy(auxiliarM->nsubtipo,actualM->nsubtipo);
					
					actualM->ncla_mov=posteriorM->ncla_mov;
					strcpy(actualM->nfecha,posteriorM->nfecha);
					actualM->ncantidad=posteriorM->ncantidad;
					strcpy(actualM->ntipo,posteriorM->ntipo);
					strcpy(actualM->nsubtipo,posteriorM->nsubtipo);
	
					posteriorM->ncla_mov=auxiliarM->ncla_mov;
					strcpy(posteriorM->nfecha,auxiliarM->nfecha);
					posteriorM->ncantidad=auxiliarM->ncantidad;
					strcpy(posteriorM->ntipo,auxiliarM->ntipo);
					strcpy(posteriorM->nsubtipo,auxiliarM->nsubtipo);
				}
				posteriorM=posteriorM->nextM;
			}
			actualM=actualM->nextM;
		}
		lista_movimientos();
		delete(auxiliarM);
		delete(posteriorM);
	}
}

void menu_productos(){
    char op[2];
    do{
        system("cls");
        printf("**************************************\n");
        printf("***** MENU ARCHIVOS DE PRODUCTOS *****\n");
        printf("**************************************\n");
        printf("a) Alta de productos\n"); 
        printf("b) Baja productos obsoletos\n");
        printf("c) Consulta productos por clave\n");
        printf("d) Consulta productos por familia\n");
        printf("x) Rregresar al men%c principal\n\n",163);
        printf("Indica la opci%cn deseada : ",162); gets(op);
        strcpy(op,strlwr(op));
        
        if ((strcmp(op,"a")!=0) && (strcmp(op,"b")!=0) && (strcmp(op,"c")!=0) && (strcmp(op,"d")!=0) && (strcmp(op,"x")!=0)){
			printf("Error, entrada diferente a las opciones disponibles...\n",162);
			getche();
        }else{
            if (strcmp(op,"a")==0){
            	system("cls");
            	alta_productos();
			}
			if (strcmp(op,"b")==0){
				system("cls");
				bajas_productos();
			}
			if (strcmp(op,"c")==0){
				system("cls");
				consulta_por_clave();
        	}
        	if (strcmp(op,"d")==0){
				system("cls");
				consulta_por_familia();
        	}
    	}
	} while ((strcmp(op,"x")!=0));
}

void menu_in_out(){
    char op[2];
    do{
        system("cls");
        printf("**********************************************\n");
        printf("***** MENU ENTRADAS/SALIDAS DE PRODUCTOS *****\n");
        printf("**********************************************\n");
        printf("a) Entrada por compras\n"); 
        printf("b) Entrada por devoluci%cn de clientes\n",162);
        printf("c) Salidas por ventas\n");
        printf("d) Salidas por devoluci%cn a proveedores\n",162);
        printf("e) Salidas por mermas\n");
        printf("x) Regresar al men%c principal\n\n",163);
        printf("Indica la opci%cn deseada : ",162); gets(op);
        strcpy(op,strlwr(op));
        
        if ((strcmp(op,"a")!=0) && (strcmp(op,"b")!=0) && (strcmp(op,"c")!=0) && (strcmp(op,"d")!=0) && (strcmp(op,"e")!=0) && (strcmp(op,"x")!=0)){
			printf("Error, entrada diferente a las opciones disponibles...\n",162);
			getche();
        }
		else{
            if (strcmp(op,"a")==0){
            	system("cls");
            	entradas(1);
			}	
			if (strcmp(op,"b")==0){
				system("cls");
				entradas(2);	
			}
			if (strcmp(op,"c")==0){
				system("cls");
				entradas(3);
        	}
        	if (strcmp(op,"d")==0){
				system("cls");
				entradas(4);
        	}
        	if (strcmp(op,"e")==0){
				system("cls");
				entradas(5);
        	}
    	}
	} while ((strcmp(op,"x")!=0));
}

void menu_reportes(){
    char op[2];
    do{
        system("cls");
        printf("*************************\n");
        printf("***** MENU REPORTES *****\n");
        printf("*************************\n");
        printf("a) Reporte general de productos ordenado por clave\n"); 
        printf("b) Reporte general de productos ordenado por nombre\n");
        printf("c) Productos por familia\n");
        printf("d) Productos a ordenar ordenado por existencia\n");
        printf("e) Productos a ofertar ordenado por existencia\n");
        printf("f) Listado de movimientos de un producto ordenado por fecha\n");
        printf("x) Regresar al men%c principal\n\n",163);
        printf("Indica la opci%cn deseada : ",162); gets(op);
        strcpy(op,strlwr(op));
        if ((strcmp(op,"a")!=0) && (strcmp(op,"b")!=0) && (strcmp(op,"c")!=0) && (strcmp(op,"d")!=0) && (strcmp(op,"e")!=0) && (strcmp(op,"f")!=0) && (strcmp(op,"x")!=0)){
			printf("Error, entrada diferente a las opciones disponibles...\n",162);
			getche();
        }
		else{
            if (strcmp(op,"a")==0){
            	system("cls");
            	ordenar_reporte(1);
			}
			if (strcmp(op,"b")==0){
				system("cls");
				ordenar_reporte(2);	
			}
			if (strcmp(op,"c")==0){
				system("cls");
				consulta_por_familia();
        	}
        	if (strcmp(op,"d")==0){
				system("cls");
				ordenar_reporte(4);
        	}
        	if (strcmp(op,"e")==0){
				system("cls");
				ordenar_reporte(5);
        	}
        	if (strcmp(op,"f")==0){
        		ordenar_movimientos();
				system("cls");
        	}
    	}
	} while ((strcmp(op,"x")!=0));
}

void menu(){
	char op[2];
	do{
		system("cls");
		printf("**************************\n");
		printf("***** MENU PRINCIPAL *****\n");
		printf("**************************\n");
		printf("a) Archivo de Productos\n");
		printf("b) Entradas/Salidas de Producto\n");
		printf("c) Reportes\n");
		printf("x) Terminar\n\n");
		printf("Indica la opci%cn deseada : ",162); gets(op);
		strcpy(op,strlwr(op));
		if ((strcmp(op,"a")!=0) && (strcmp(op,"b")!=0) && (strcmp(op,"c")!=0) && (strcmp(op,"x")!=0)){
			printf("Error, entrada diferente a las opciones disponibles...\n",162);
			getche();
		}
		else{
			if (strcmp(op,"a")==0){
				system("cls");
				menu_productos();
			}
			if (strcmp(op,"b")==0){
				system("cls");
				menu_in_out();
			}
			if (strcmp(op,"c")==0){
				system("cls");
				menu_reportes();
			}
		}
	} while((strcmp(op,"x")!=0));
}

main(){
	ofstream arch;
	arch.open("productos.txt",ios::app);
	arch.close();
	arch.open("movimientos.txt",ios::app);
	arch.close();
	cargar_productos();
	cargar_movimientos();
	menu();
	descargar_productos();
	descargar_movimientos();
}

