#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include "Lista.h"
#pragma once
using namespace std;

struct Nodo{
    char data1[20],data2[9];
    Nodo *sgte;
};

Nodo *primero, *ultimo, *actual, *nuevo;
void menu();

//Cargar el archivo .txt y subirlo a la lista
void Lista::carga_Archivo(){
    ifstream archivo;
    archivo.open("usuarios.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    char data1[20],data2[9]; //actuan como variables y no como nodo
    while (!archivo.eof()){
        archivo>>data1>>data2;
        if (!archivo.eof()){
            nuevo = new Nodo;
            strcpy(nuevo->data1,data1);
            strcpy(nuevo->data2,data2);
            if (primero == NULL){
                primero = nuevo;
                primero->sgte = NULL;
                ultimo = primero;
            }else{
                ultimo->sgte = nuevo;
                nuevo->sgte = NULL;
                ultimo = nuevo;
            }
            //mostrar();
        }
    }archivo.close();
}

//Mostrar elementos de la lista
void Lista::mostrar(){
    system("cls");
    actual=primero;
    int i=1;
    while(actual!=NULL){
        cout<<"Elemento numero "<<i<<": "<<actual->data1<<endl;
        actual=actual->sgte;    
        i++;
    }
    cout<<"Presione enter para continuar..."<<endl;
    getch();
    menu();
}

//Insertar usuarios en la lista
void Lista::insertar(){
    system("cls");
    char data1[20],data2[9];
    char respuesta;

    do {
        nuevo = new Nodo;
        cout << "Ingrese el nombre del usuario: ";
        cin >> data1;
        cout << "Ingrese la clave del usuario: ";
        cin >> data2;

        //Agregar los dato1 y dato2 en el txt
        ofstream archivo;
        archivo.open("usuarios.txt",ios::app);
    
        if(archivo.fail()){
            cout<<"No se pudo abrir el archivo";
            exit(1);
        }
        archivo<<data1<<endl<<data2<<endl;
        archivo.close();

        //Agregar data1 y data2 en la lista
        if (primero == NULL) {
            primero = new (Nodo);
            strcpy(nuevo->data1, data1);
            strcpy(nuevo->data2, data2);
            ultimo = primero;
        } else {
            actual = new (Nodo);
            ultimo->sgte = actual;
            strcpy(actual->data1, data1);
            strcpy(actual->data2, data2);
            ultimo = actual;
        }
        ultimo->sgte = NULL;

        cout<<"Desea ingresar otro usuario? (s/n): "<<endl;
        respuesta= getch();
    }while (respuesta=='s');
    system("Main.exe");
    exit(0);
    getch();
    menu();;
}

//Buscar un usuario por el nombre
void Lista::buscar(){
system("cls");
    char data1[20];
    int bandera=0;

    cout<<"Ingrese el nombre del usuario a buscar: ";
    cin>>data1;
    actual=primero;

    while(actual!=NULL){
        if(strcmp(actual->data1,data1)==0){
            bandera=1;
        }
        actual=actual->sgte;
    }
    if(bandera==1){
        cout<<"Bienvenido (a): "<<data1<<endl;
    }else{
        cout<<"El usuario no existe"<<endl;
    }
    cout<<"Presione enter para continuar..."<<endl;
    getch();
    menu();
}

//Eliminar de la lista enlazada
void Lista::eliminar(){
    system("cls");
    char data1[20],data2[9];
    int bandera=0;

    ofstream archivo;
     archivo.open("temporal.txt",ios::app);
    
        if(archivo.fail()){
            cout<<"No se pudo abrir el archivo";
            exit(1);
        }

        cout<<"Ingrese el nombre del usuario a eliminar: ";
        cin>>data1;
        cout<<"Ingrese la clave del usuario a eliminar: ";
        cin>>data2;
        actual=primero;

    while(actual!=NULL){
        if(strcmp(actual->data1,data1)==0 && strcmp(actual->data2,data1)!=0){
            bandera=1;
        }
        actual=actual->sgte;
    }

    if(bandera==1){
        actual=primero;
        while(actual!=NULL){
            if(strcmp(actual->data1,data1)!=0 && strcmp(actual->data2,data1)!=0){
                archivo<<actual->data1<<endl<<actual->data2<<endl;
            }
            actual=actual->sgte;
        }
        archivo.close();
        remove("usuarios.txt");
        rename("temporal.txt","usuarios.txt");
        cout<<"El usuario ha sido eliminado"<<endl;
    }

    if(bandera==0){
            cout<<"El usuario no existe, intente de nuevo"<<endl;
    }
    getch();
    system("Main.exe");
    exit(0);
    menu();
}

//Menu principal
void Lista::menu(){
    system("cls");
    int opcion;
    cout<<"Proyecto de listas enlazadas en C++"<<endl;
    cout<<"By: Veronica Zapata Vargas"<<endl;
    cout<<"Juan Fernando Romero Rosero"<<endl;
    cout<<""<<endl;
    cout<<"1. Ingresar nuevo usuario"<<endl;
    cout<<"2. Buscar usuario"<<endl;
    cout<<"3. Eliminar usuario existente"<<endl;
    cout<<"4. Mostrar todos los usuarios"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<endl<<endl<<">Ingrese una opcion: ";
    cin>>opcion;

    if(opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4 && opcion!=5){
        cout<<"Opcion no valida"<<endl;
        getch();
        system("Main.exe");
        exit(0);
        menu();
    }

    switch(opcion){
        case 1:
            insertar();
            break;
        case 2:
            buscar();
            break;
        case 3:
            eliminar();
            break;
        case 4:
            mostrar();
            break;
        case 5:
            cout<<"Gracias por usar el programa"<<endl;
            getch();
            exit(0);
            break;
    }
}

