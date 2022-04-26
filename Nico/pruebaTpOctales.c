#include <stdio.h>
#include <stdbool.h>


int clasificarCaracter (char c);
void reiniciarTabla(int matriz[][3]);
//FUNCIONA EL AFD PARA LOS OCTALES, FALTA AGREGAR LOS DEMAS ESTADOS

int main(){

        char c;
        FILE *archivo;
        archivo = fopen("numeros.txt","r");
        if(archivo==NULL)
            printf("No se pudo leer el archivo");
        int e1,e2;
        e1 = e2 = 0;
        int tablaT[3][3] = {{1,2,2},           //TABLA DE TRANSICION PARA OCTALES 
                            {1,1,2},
                            {2,2,2}};

        do{                                    //LEO EL ARCHIVO HASTA EL FINAL
            bool rechazado = false;
            c=fgetc(archivo);
            if(c != ',')                      //muestro los caracteres menos la ','
            {
                e2 = clasificarCaracter(c);
                putchar(c); 
            }
            switch(tablaT[e1][e2]){          //e1 = estado automata (cases del switch), e2 = clasificacion del caracter
                case 1:
                    e1 = tablaT[e1][e2];
                    break;
                case 2:                     //CASO RECHAZO: Salto hasta la coma terminando de leer el numero
                    do{
                        c=fgetc(archivo);
                        if(c != ',')
                            putchar(c);
                        if(feof(archivo))
                            break;      
                    }while(c != ','); 
                    rechazado = true;

                    break;
                default:
                    break;
            }
            if(c == ',' || feof(archivo) ) {
                e1 = 0;   //vuelvo al estado q0
                e2 = 0;
                if(rechazado)
                    printf("  El numero ingresado no es octal \n");
                else
                    printf(" El numero ingresado es octal \n");
            }

        }while(!feof(archivo));    

        fclose(archivo);

        return 0;
}

int clasificarCaracter (char c){

    switch(c){
        case '0':
            return 0;
            break;
        case '1' ... '7':
            return 1;
            break;
        default:
            return 2;
            break;
    }
}
