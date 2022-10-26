#include <stdio.h>

//CONSTANTES
#define DISTANCIA_LIMITE 1000 // ... km.
#define IMPORTE_DISTANCIA_LIMITE 300 // ... euros.
#define IMPORTE_FUERA_LIMITE 0.35 // ... euros por km.
#define LIMITE_DIAS 7 // ... dias entre ambas fechas.
#define DESCUENTO 0.60 //Si los vuelos se efectúan en menos de LIMITE_DIAS días.
//PROTOTIPOS
int comprobar_fecha (int dia, int mes);
int dias_transcurridos (int di,int mi,int dv,int mv);
int comparar_fechas (int diaida,int mesida,int diavuelta,int mesvuelta);
int dias_mes (int mes);
void leer_fechas (int *diaida, int *mesida, int *diavuelta, int *mesvuelta);
void leer_distancia (int *km);
void imprimir_resultado (float importe,float descuento);
float calcular_importe (int kms, int duracion, float *descuento);

int main() {
    int dia_ida, mes_ida, dia_vuelta, mes_vuelta, distancia, duracion;
    float importe, descuento;
    leer_distancia(&distancia);
    leer_fechas(&dia_ida,&mes_ida,&dia_vuelta,&mes_vuelta);
    duracion=dias_transcurridos(dia_ida,dia_vuelta,mes_ida,mes_vuelta);
    importe=calcular_importe(distancia,duracion,&descuento);
    imprimir_resultado(importe,descuento);
    return 0;
}

int comprobar_fecha (int dia, int mes){
    int esValida=0;
    if ((mes>0&&mes<=12)&&(dia>0&&dia<= dias_mes(mes)))
        esValida=1;
    return esValida;
}

int dias_transcurridos (int di,int mi,int dv,int mv){
    int dias=0;
    if (mv==mi)
        dias=dv-di;
    else{
        for (int i = mv; i > mi; i--) {
            if (i==mv)
                dias+= dv;
            else if (i==mi)
                dias+= dias_mes(mi)-di;
            else
                dias+= dias_mes(i);
        }
    }
    return dias;
}

int comparar_fechas (int diaida,int mesida,int diavuelta,int mesvuelta){
    int esValido=1;
    if ((mesvuelta<mesida) || (mesvuelta==mesida && diavuelta<diaida))
        esValido=0;
    return esValido;
    }

int dias_mes (int mes){
        int dias;
        switch (mes) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dias=31;
                break;
            case 2:
                dias=28;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dias=30;
                break;
        }
        return dias;
    }

void leer_fechas (int *diaida, int *mesida, int *diavuelta, int *mesvuelta){
    printf("Introduzca la fecha de ida (dd mm): ");
    scanf("%d %d",diaida,mesida);
    fflush(stdin);
    while (comprobar_fecha(*diaida,*mesida)==0){
        printf("Fecha invalida\nIntroduzca la fecha de ida (dd mm): ");
        scanf("%d %d",diaida,mesida);
        fflush(stdin);
    }
    printf("Introduzca la fecha de vuelta (dd mm): ");
    scanf("%d %d",diavuelta,mesvuelta);
    fflush(stdin);
    while (comprobar_fecha(*diavuelta,*mesvuelta)==0){
        printf("Fecha invalida\nIntroduzca la fecha de vuelta (dd mm): ");
        scanf("%d %d",diavuelta,mesvuelta);
        fflush(stdin);
    }
    while (comparar_fechas(*diaida,*mesida,*diavuelta,*mesvuelta)==0){
        printf("Error: Fecha de vuelta anterior a fecha de ida\nIntroduzca la fecha de vuelta (dd mm): ");
        scanf("%d %d",diavuelta,mesvuelta);
        fflush(stdin);
    }
}

void leer_distancia (int *km){
    printf("Introduzca la distancia en km: ");
    scanf("%d",km);
    fflush(stdin);
    while (km<0){
        printf("Los km no pueden ser negativos\nIntroduzca la distancia en km: ");
        scanf("%d",km);
        fflush(stdin);
    }
}

void imprimir_resultado (float importe,float descuento){
    printf("\nImporte bruto: %.2f",importe+descuento);
    printf("\nDescuento: %.2f",descuento);
    printf("\nImporte neto: %.2f",importe);
}

float calcular_importe (int kms, int duracion, float *descuento){
    float coste;
    if (kms<DISTANCIA_LIMITE)
        coste=IMPORTE_DISTANCIA_LIMITE;
    else
        coste=kms*IMPORTE_FUERA_LIMITE;
    if (duracion<LIMITE_DIAS){
        *descuento=DESCUENTO*coste;
        coste=coste-*descuento;
    }
    return coste;
}