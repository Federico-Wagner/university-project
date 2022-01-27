#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>
#include <cstring>
using namespace std;

int tecla_continuar;
struct SOCIO{
int ID;
int DNI;
//string NyA;  //No se guardan correctamente las cadenas de caracterres en .dat
char inicial_nombre;
char inicial_apellido;
int ddmmaaaa_nacimiento;
int dto;
char clase;
};
void crear_base_datos();                                    //GENERAL
void target(SOCIO VEC[],int &i);                            //GENERAL
void guardar_base_datos(SOCIO base_datos[],int &len);       //GENERAL
int calculo_edad(int ddmmaaaa_nacimiento);                  //GENERAL
void leer_base_de_datos(SOCIO VEC[],int &largo);            //0 (DEFAULT)
void carga_socio(SOCIO base_datos[],int &len);              //1.0
void menu_administracion(SOCIO base_datos[],int &len);      //2.0
void buscar_ID(SOCIO base_datos[],int &len);                //2.1
void buscar_DNI(SOCIO base_datos[],int &len);               //2.2
void buscar_NyA(SOCIO base_datos[],int &len);               //2.3
void menu_modificacion_socio(SOCIO VEC[],int &len,int &i);  //2.x
void modificacion_datos_socio(SOCIO VEC[],int &i);          //2.x.1
void baja_socio(SOCIO VEC[],int &len,int &i);               //2.x.2
void menu_reportes(SOCIO VEC[],int &len);                   //3.0
void reporte_pob_dem(SOCIO VEC[],int &len);                 //3.1
void reporte_membrecias(SOCIO VEC[],int &len);              //3.2
void reporte_total_socios();                                //3.3

int main(){
SOCIO base_datos[1000]; //REEVER COMO AUTO CONFIGURAR VALOR MAX DE SOCIOS
int len = 0;
leer_base_de_datos(base_datos,len);
bool loop = true;

//MENU PRINCIPAL, Selector de funciones
while(loop){
    system("CLS");
    //cout<<len-1; //DEBUG
    cout << "\n \\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/" << endl;
    cout << "    \\- Registro electronico de socios -/   " << endl;
    cout << "\n MENU PRINCIPAL:" << endl;
    cout << " Seleccione una opcion para continuar..." << endl;
    cout << "\n 1 - CARGAR NUEVO SOCIO" << endl;
    cout << "\n 2 - ADMINISTRAR SOCIO EN BASE DE DATOS" << endl;
    cout << "\n 3 - IMPRIMIR REPORTES POR PANTALLA" << endl;
    cout << "\n 4 - EXIT" << endl;
    int seleccion;
    cin>> seleccion;

    while(seleccion <= 0 || seleccion > 4){
        cout << "\n Has ingresado un valor invalido, por favor vuelve a intentarlo." << endl;
        cin>> seleccion; //Si se ingresa un valor alfabetico, este whilese queda loopinado infinitamente
        }
    switch(seleccion) {
        case 1: //CARGA DE SOCIO
            carga_socio(base_datos,len);
            break;
        case 2: //ADMINISTRACION DE SOCIO
            if(len == 1){
                cout<<"La base de datos no contiene socios para administrar, por favor carge socios al sistema."<<endl;
                system("pause");
                break;
            }
            menu_administracion(base_datos,len);
            break;
        case 3: //  MENU DE REPORTES
            if(len == 1){
                cout<<"La base de datos no contiene socios, por favor carge socios al sistema. "<<endl;
                system("pause");
                break;
            }
            menu_reportes(base_datos,len);
            break;
        case 4: //EXIT
            system("CLS");
            cout << "\n --GRACIAS POR UTILIZAR NUESTROS SERVICIOS--" << endl;
            cout << " \\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/\n" << endl;
            loop = false;
            break;
}}
return 0;
}

void leer_base_de_datos(SOCIO VEC[], int &largo){               //0 (DEFAULT)
//BASE DE DATOS NO EXISTENTE (NUEVA)
FILE * datos;
datos = fopen("SOCIOS_BENAVIDEZ.DAT","rb");
  if (datos==NULL){
    fclose(datos);
    crear_base_datos(); //Crea la base de datos la primera vez que ejecuta el programa
    datos = fopen("SOCIOS_BENAVIDEZ.DAT","rb");
    system("pause");
  }

//BASE DE DATOS EXISTENTE - LECTURA
SOCIO aux;
largo = 0;
fread(&aux,sizeof(struct SOCIO),1,datos);
while(!feof(datos)){
    VEC[largo] = aux;
    largo += 1;
    fread(&aux,sizeof(struct SOCIO),1,datos);
    }
fclose(datos);
}

void crear_base_datos(){                                        //GENERAL
FILE * datos;
datos = fopen("SOCIOS_BENAVIDEZ.DAT","wb");
SOCIO socioCERO;    //crea el primer socio "CERO" dado que el ID de socio se auto genera haciendo auto referencia al valor anterior
socioCERO.ID = 0;   //de ID en el vector de base de datos. Asi el primer socio poseera ID = 1
socioCERO.DNI = 00000000;
//socioCERO.NyA = 'z';
socioCERO.inicial_nombre = '0';
socioCERO.inicial_apellido = '0';
socioCERO.ddmmaaaa_nacimiento = 00000000;
socioCERO.dto = 0;
socioCERO.clase = '0';

fwrite(&socioCERO,sizeof(struct SOCIO),1,datos);
fclose(datos);
cout << " \\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/" << endl;
cout<<"\n LA BASE DE DATOS INICIAL AH SIDO CREADA"<<endl;
}

void guardar_base_datos(SOCIO base_datos[],int &len){           //GENERAL
FILE * save;
save = fopen("SOCIOS_BENAVIDEZ.DAT","wb");
for(int i=0;i<len;i++){
    fwrite(&base_datos[i],sizeof(struct SOCIO),1,save);
    }
fclose(save);
cout<<"\n Los cambios han sido guardados"<<endl;
cout<<endl;
system("pause");
}

void carga_socio(SOCIO base_datos[],int &len){                  //1
    SOCIO nuevo;
    bool loop = true;
    string aux_str;
while(loop){
    system("CLS");
    cout << "\n 1 - MENU DE CARGA DE NUEVO SOCIO" << endl;
    //INGRESO DE DATOS
    nuevo.ID = base_datos[len-1].ID + 1;        //El ID de usuario se genera automaticamente
    cout<<"\n Creando socio ID:"<<nuevo.ID<<endl;
    cout<<"\n Ingrese el DNI: - ";
    cin>>nuevo.DNI;
    //cout<<"Ingrese el nombre y apellido: #SOLO UNA LETRA!  ";
    //cin>>nuevo.NyA;
    cout<<" Ingrese el nombre: - "; //SOLO GUARDAREMOS LA INICIAL
    cin>>aux_str;
    nuevo.inicial_nombre = aux_str[0];
    cout<<" Ingrese el apellido: - "; //SOLO GUARDAREMOS LA INICIAL
    cin>>aux_str;
    nuevo.inicial_apellido = aux_str[0];
    cout<<" Ingrese fecha de nacimiento (FORMATO: DDMMAAAA) - ";
    cin>>nuevo.ddmmaaaa_nacimiento;
    cout<<" Ingrese clase de membresia: [A/B/C] - ";
    cin>>nuevo.clase;
    int edad = calculo_edad(nuevo.ddmmaaaa_nacimiento);     //POLITICA DE DESCUENTO PARA  PERSONAS MAYORES Y MENORES DE EDAD
    if(edad>65){
        nuevo.dto = 15;
    }else if(edad<18){
        nuevo.dto = 20;
    }else{
        nuevo.dto = 0;
    }
    //VALIDACION
    system("CLS");
    cout<<" --CONFIRMACION DE DATOS--"<<endl;
    cout<<" --------------------------------------"<<endl;
    cout<<"\n ID de socio: . . . . . . . . "<<nuevo.ID<<endl;
    cout<<" DNI del socio: . . . . . . . . ."<<nuevo.DNI<<endl;
    cout<<" Inicial del nombre del socio: . "<<nuevo.inicial_nombre<<endl;
    cout<<" Inicial del apellido del socio: "<<nuevo.inicial_apellido<<endl;
    cout<<" Fecha de nacimiento: . . . . . ."<<nuevo.ddmmaaaa_nacimiento<<endl;
    cout<<" Descuento: . . . . . . . . . . ."<<nuevo.dto<<endl;
    cout<<" Clase de membresia:. . . . . . ."<<nuevo.clase<<endl;
    cout<<" La edad actual del socio es de: "<<edad<<endl;
    cout<<"\n DESEA CONFIRMAR ESTOS DATOS? (Y/N)"<<endl;
    char confirmacion = 'N';
    cin>> confirmacion;
    if (confirmacion =='Y' || confirmacion =='y'){
        loop = false;
    }
}
FILE * datos;
datos = fopen("SOCIOS_BENAVIDEZ.DAT","wb");

for(int i=0;i<len;i++){
    fwrite(&base_datos[i],sizeof(struct SOCIO),1,datos);
    }
fwrite(&nuevo,sizeof(struct SOCIO),1,datos);
len += 1;
fclose(datos);
leer_base_de_datos(base_datos,len);
}

void menu_administracion(SOCIO base_datos[],int &len){          //2
    system("CLS");
    cout << " 2 - MENU DE BUSQUEDA DE SOCIO EN BASE DE DATOS" << endl;
    cout << "\n Seleccione el parametro de busqueda:" << endl;
    cout << "\n 1 - ID. de SOCIO:" << endl;
    cout << "\n 2 - DNI:" << endl;
    cout << "\n 3 - NOMBRE Y APELLIDO" << endl;
    cout << "\n 4 - VOLVER" << endl;
    int seleccion2 = 0;
    cin>> seleccion2;
    while(seleccion2 <= 0 || seleccion2 > 4){
        cout << "\n Has ingresado un valor invalido, por favor vuelve a intentarlo." << endl;
        cin>> seleccion2;
        //Si se ingresa un valor alfabetico, se queda loopinado infinitamente este while
        }
        switch(seleccion2) {
            case 1: //BUSQUEDA POR ID. DE SOCIO
                system("CLS");
                buscar_ID(base_datos,len);
                break;
            case 2:
                system("CLS");
                buscar_DNI(base_datos,len);
                break;
            case 3:
                system("CLS");
                buscar_NyA(base_datos,len);
                break;
            case 4:
                break;
}}

void buscar_ID(SOCIO base_datos[],int &len){                    //2.1
cout << "\n BUSQUEDA POR ID. DE SOCIO" << endl;
cout<<" Ingrese el ID de socio a buscar: ";
int ID_busqueda;
cin>>ID_busqueda;
int i = 0;
while(ID_busqueda != base_datos[i].ID && i<len){
    i++;
}
if(ID_busqueda == base_datos[i].ID){
    system("CLS");
    cout<<"---------SOCIO ENCONTRADO---------"<<endl;
    menu_modificacion_socio(base_datos,len,i);
}else{
    cout<<"\n El socio no se ha encontrado"<<endl;
   }}

void buscar_DNI(SOCIO base_datos[],int &len){                   //2.2
    cout << "\n BUSQUEDA POR DNI DE SOCIO" << endl;
    cout<<" Ingrese el DNI del socio a buscar: ";
    int DNI_busqueda;
    cin>>DNI_busqueda;
    int i = 0;
    while(DNI_busqueda != base_datos[i].DNI && i<len){
        i++;
        }
    if(DNI_busqueda == base_datos[i].DNI){
        system("CLS");
        cout<<"---------SOCIO ENCONTRADO---------"<<endl;
        menu_modificacion_socio(base_datos,len,i);
    }else{
        cout<<"\n El socio no se ha encontrado"<<endl;
   }}

void buscar_NyA(SOCIO base_datos[],int &len){                   //2.3

    cout << "\n --------- BUSQUEDA POR NOMBRE Y APELLIDO ----------" << endl;
    cout<<"\n Ingrese el NOMBRE Y APELLIDO del socio a buscar: "<<endl;
    cout<<" (comparacion de iniciales)"<<endl;
    string appellido_long;
    string nombre_long;
    cout<<"\n Ingrese el NOMBRE del socio a buscar: ";
    cin>>nombre_long;
    cout<<" Ingrese el APELLIDO del socio a buscar: ";
    cin>>appellido_long;

    int i = 0;
    while((nombre_long[0] != base_datos[i].inicial_nombre || appellido_long[0] != base_datos[i].inicial_apellido ) && i<len){
        i++;
    }
    if(nombre_long[0] == base_datos[i].inicial_nombre && appellido_long[0] == base_datos[i].inicial_apellido ){
        system("CLS");
        cout<<"---------SOCIO ENCONTRADO---------"<<endl;
        menu_modificacion_socio(base_datos,len,i);
    }else{
        cout<<"\n El socio no se ha encontrado"<<endl;
        system("pause");
    }}

void menu_modificacion_socio(SOCIO VEC[],int &len,int &i){      //2.x
    target(VEC,i);
    cout << "\n Seleccione accion:" << endl;
    cout << "\n 1 - MODIFICACION DE DATOS" << endl;
    cout << "\n 2 - BAJA DE SOCIO" << endl;
    cout << "\n 3 - MOSTRAR DATOS POR PANTALLA" << endl;
    cout << "\n 4 - VOLVER" << endl;
    int seleccion3;
    cin>>seleccion3;

    switch(seleccion3){
        case 1:
            modificacion_datos_socio(VEC,i);
            guardar_base_datos(VEC,len);
            break;
        case 2:
            baja_socio(VEC,len,i);
            guardar_base_datos(VEC,len);
            break;
        case 3:
            system("CLS");
            target(VEC,i);
            system("pause");
            break;
        case 4:
            break;
    }
}

void target(SOCIO VEC[],int &i){                                //GENERAL
    cout<<"\n ------------------------------------"<<endl;
    cout<<" ID de socio: . . . . . . . . . ."<<VEC[i].ID<<endl;
    cout<<" DNI del socio: . . . . . . . . ."<<VEC[i].DNI<<endl;
    cout<<" Inicial del nombre del socio: . "<<VEC[i].inicial_nombre<<endl;
    cout<<" Inicial del apellido del socio: "<<VEC[i].inicial_apellido<<endl;
    cout<<" Fecha de nacimiento: . . . . . ."<<VEC[i].ddmmaaaa_nacimiento<<endl;
    cout<<" Descuento: . . . . . . . . . . ."<<VEC[i].dto<<endl;
    cout<<" Clase de membresia:. . . . . . ."<<VEC[i].clase<<endl;
    cout<<" ------------------------------------"<<endl;
}

void modificacion_datos_socio(SOCIO VEC[],int &i){              //2.x.1
    bool loop = true;
    SOCIO modificado;
    string aux_str;
while(loop){
    system("CLS");
    cout<<" -------MODIFICACION DE DATOS------"<<endl;
    cout<<" ---------DATOS ANTERIORES---------"<<endl;
    target(VEC,i);
    cout<<" Re-ingrese todos los datos del socio"<<endl;
    //INGRESO
    modificado.ID = VEC[i].ID;     //El ID de usuario es INVARIANTE
    cout<<"\n Ingrese el DNI:                                 ";
    cin>>modificado.DNI;
    cout<<" Ingrese el nombre  :                    ";
    cin>>aux_str;
    modificado.inicial_nombre = aux_str[0];
    cout<<" Ingrese el apellido:                    ";
    cin>>aux_str;
    modificado.inicial_apellido = aux_str[0];
    cout<<" Ingrese fecha de nacimiento (Formato: ddmmaaaa): ";
    cin>>modificado.ddmmaaaa_nacimiento;
    cout<<" Ingrese descuento de usuario:                    ";
    cin>>modificado.dto;
    cout<<" Ingrese clase de membresia [A/B/C]:              ";
    cin>>modificado.clase;
    cout<<endl;
    system("pause");
    //VALIDACION
    system("CLS");
    cout<<"----CONFIRMACION DE NUEVOS DATOS----"<<endl;
    cout<<"\n---------DATOS ANTERIORES---------"<<endl;
    target(VEC,i);
    cout<<"\n---------DATOS NUEVOS---------"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"\n ID de socio: . . . . . . . . ."<<modificado.ID<<endl;
    cout<<" DNI del socio: . . . . . . . . ."<<modificado.DNI<<endl;
    cout<<" Inicial del nombre del socio: . "<<modificado.inicial_nombre<<endl;
    cout<<" Inicial del apellido del socio: "<<modificado.inicial_apellido<<endl;
    cout<<" Fecha de afiliacion: . . . . . ."<<modificado.ddmmaaaa_nacimiento<<endl;
    cout<<" Descuento: . . . . . . . . . . ."<<modificado.dto<<endl;
    cout<<" Clase de membresia:. . . . . . ."<<modificado.clase<<endl;
    cout<<" --------------------------------------"<<endl;
    cout<<"\n DESEA CONFIRMAR ESTOS DATOS? (Y/N)"<<endl;
    char confirmacion = 'N';
    cin>> confirmacion;
    if (confirmacion =='Y' || confirmacion =='y'){
        loop = false;
        VEC[i] = modificado;
    }
}}

void baja_socio(SOCIO VEC[],int &len,int &i){                   //2.x.2
    system("CLS");
    cout<<"-----------BAJA DE SOCIO-----------"<<endl;
    target(VEC,i);
    cout << "Confirmacion de baja al socio: (Y/N)" << endl;
    char baja;
    cin >> baja;
    int m = i;
    if(baja == 'Y' || baja =='y'){
        while(i<len){
            VEC[i] = VEC[i+1];
            i++;
        }
    }
    len--;
    cout <<"\n El socio seleccionado ha sido eliminado satisfactoriamente"<<endl;
}

void menu_reportes(SOCIO VEC[],int &len){                       //3.0
    system("CLS");
    cout << "\n 3 - MENU DE REPORTES" << endl;
    cout << "\n Seleccione el Reporte a emitir:" << endl;
    cout << "\n 1 - Poblacion demografica de socios" << endl;
    cout << "\n 2 - Porcentaje de socios por tipo de membrecia:" << endl;
    cout << "\n 3 - Lista completa de socios" << endl;
    cout << "\n 4 - VOLVER" << endl;
    int seleccion3 = 0;
    cin>> seleccion3;
    while(seleccion3 <= 0 || seleccion3 > 4){
        cout << "\n Has ingresado un valor invalido, por favor vuelve a intentarlo." << endl;
        cin>> seleccion3;
        //Si se ingresa un valor alfabetico, se queda loopinado infinitamente este while
        }
        switch(seleccion3) {
            case 1: //REPORTE DE Poblacion demografica de socios
                reporte_pob_dem(VEC,len);
                break;
            case 2: //REPORTE DE Porcentaje de socios por tipo de membrecia
                reporte_membrecias(VEC,len);
                break;
            case 3: //Lista completa de socios
                reporte_total_socios();
                break;
            case 4: //VOLVER
                break;
cout<<endl;
system("pause");
}}

void reporte_pob_dem(SOCIO VEC[],int &len){                     //3.1
    //FECHA DE HOY:
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int ano_actual = 1900 + ltm->tm_year;
    int mes_actual = 1 + ltm->tm_mon;
    int dia_actual = ltm->tm_mday;
    //FECHAS DE NACIMIENTO DE LOS SOCIOS
    int ano_s;  //año de nacimiento del socio
    int mes_s;  //mes de nacimiento del socio
    int dia_s;  //dia de nacimiento del socio
    int no_cumplio = 1;
    int cant_mayores65 = 0;
    int cant_de51a64 = 0;
    int cant_de31a50 = 0;
    int cant_de18a30 = 0;
    int cant_menores = 0;
    for(int i=1;i<len;i++){ //RECORRO BASE DE DATOS
        ano_s = VEC[i].ddmmaaaa_nacimiento % 10000;
        mes_s = (VEC[i].ddmmaaaa_nacimiento / 10000) % 100;
        dia_s = VEC[i].ddmmaaaa_nacimiento / 1000000;
        no_cumplio = 1;
        if(mes_s>mes_actual){
            no_cumplio = 0; //El socio ya cumplio este año
        }else if(mes_s = mes_actual && dia_s>=dia_actual){
                no_cumplio = 0; //El socio ya cumplio este año
            }
        int edad = (ano_actual - ano_s) - no_cumplio;    //calculo edad del socio
        //CONTABILIZO POR GRUPOS
        if(edad>=65){
            cant_mayores65++;
        }else if(edad>=51){
            cant_de51a64++;
        }else if(edad>=31){
            cant_de31a50++;
        }else if(edad>=18){
            cant_de18a30++;
        }else
            cant_menores++;
    }
    int total_socios = cant_mayores65 + cant_de51a64 + cant_de31a50 + cant_de18a30 + cant_menores;
    system("CLS");
    cout << "                                    \\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/" << endl;
    cout<<"\n -----------------------------------REPORTE DE POBLACION DEMOGRAFICA DE SOCIOS-----------------------------------"<<endl;
    cout<<"\n La cantidad total de socios del club es de: "<<total_socios<<endl;
    cout<<"\n La cantidad de socios mayores de 65 años es de: "<<cant_mayores65;
    cout<<"        |  Reprecentando un porcentaje total de socios del: "<<100*cant_mayores65/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios de 51 a 64 años es de: "<<cant_de51a64;
    cout<<"           |  Reprecentando un porcentaje total de socios del: "<<100*cant_de51a64/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios de 31 a 50 años es de: "<<cant_de31a50;
    cout<<"           |  Reprecentando un porcentaje total de socios del: "<<100*cant_de31a50/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios de 18 a 30 años es de: "<<cant_de18a30;
    cout<<"           |  Reprecentando un porcentaje total de socios del: "<<100*cant_de18a30/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios menores de edad es de: "<<cant_menores;
    cout<<"           |  Reprecentando un porcentaje total de socios del: "<<100*cant_menores/total_socios<<"%"<<endl;

system("pause");
}

void reporte_membrecias(SOCIO VEC[],int &len){                  //3.2
    int cant_membrecia_a = 0;
    int cant_membrecia_b = 0;
    int cant_membrecia_c = 0;
    int cant_membrecia_err = 0;
    int total_socios = 0;
    for(int i=1;i<len;i++){         //RECORRO BASE DE DATOS Y CONTABILIZO POR GRUPOS
            total_socios++;
       if(VEC[i].clase=='A' || VEC[i].clase=='a'){
            cant_membrecia_a++;
        }else if(VEC[i].clase=='B' || VEC[i].clase=='b'){
            cant_membrecia_b++;
        }else if(VEC[i].clase=='C' || VEC[i].clase=='c'){
            cant_membrecia_c++;
        }else
            cant_membrecia_err++;
    }
    system("CLS");
    cout << "                                    \\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/" << endl;
    cout<<"\n ----------------------------------------REPORTE DE MEMBRECIAS DE SOCIOS----------------------------------------"<<endl;
    cout<<"\n La cantidad total de socios del club es de: "<<total_socios<<endl;
    cout<<"\n La cantidad de socios de membrecia A es de: "<<cant_membrecia_a;
    cout<<"              |  Reprecentando un porcentaje total de socios del: "<<100*cant_membrecia_a/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios de membrecia B es de: "<<cant_membrecia_b;
    cout<<"              |  Reprecentando un porcentaje total de socios del: "<<100*cant_membrecia_b/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios de membrecia C es de: "<<cant_membrecia_c;
    cout<<"              |  Reprecentando un porcentaje total de socios del: "<<100*cant_membrecia_c/total_socios<<"%"<<endl;
    cout<<" La cantidad de socios con una membrecia erronea es de: "<<cant_membrecia_err;
    cout<<"   |  Reprecentando un porcentaje total de socios del: "<<100*cant_membrecia_err/total_socios<<"%"<<endl;
    system("pause");
}

void reporte_total_socios(){                                    //3.3
system("CLS");
int i = 0;
cout << "\\- CLUB ATLETICO DEFENSORES DE BENAVIDEZ -/" << endl;
cout<<"\n --------REPORTE TOTAL DE SOCIOS--------"<<endl;
SOCIO aux;
FILE * datos;
datos = fopen("SOCIOS_BENAVIDEZ.DAT","rb");
fread(&aux,sizeof(struct SOCIO),1,datos);
while(!feof(datos)){
    if(i!=0){
        cout<<"\n --------------- N:"<<i<<" ----------------"<<endl;
        cout<<" ID de socio: . . . . . . . . . ."<<aux.ID<<endl;
        cout<<" DNI del socio: . . . . . . . . ."<<aux.DNI<<endl;
        cout<<" Inicial del nombre del socio: . "<<aux.inicial_nombre<<endl;
        cout<<" Inicial del apellido del socio: "<<aux.inicial_apellido<<endl;
        cout<<" Fecha de nacimiento: . . . . . ."<<aux.ddmmaaaa_nacimiento<<endl;
        cout<<" Descuento: . . . . . . . . . . ."<<aux.dto<<endl;
        cout<<" Clase de membresia:. . . . . . ."<<aux.clase<<endl;
    }
    fread(&aux,sizeof(struct SOCIO),1,datos);
    i++;
}
fclose(datos);
cout<<endl;
system("pause");
}

int calculo_edad(int ddmmaaaa_nacimiento){                      //GENERAL
    //FECHA DE HOY:
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int ano_actual = 1900 + ltm->tm_year;
    int mes_actual = 1 + ltm->tm_mon;
    int dia_actual = ltm->tm_mday;
    //FECHAS DE NACIMIENTO DE LOS SOCIOS
    int ano_s;  //año de nacimiento del socio
    int mes_s;  //mes de nacimiento del socio
    int dia_s;  //dia de nacimiento del socio
    ano_s = ddmmaaaa_nacimiento % 10000;
    mes_s = (ddmmaaaa_nacimiento / 10000) % 100;
    dia_s = ddmmaaaa_nacimiento / 1000000;
    int no_cumplio = 1;   // 0 = ya cumplio años  |  1 = no cumplio años
    if(mes_s<mes_actual){
        no_cumplio = 0; //El socio todavia NO cumplio este año
    }else if(mes_s == mes_actual && dia_s<=dia_actual){
        no_cumplio = 0; //El socio todavia NO cumplio este año
    }
    int edad = (ano_actual - ano_s) - no_cumplio;    //calculo edad del socio
    return edad;
}
