/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: magali
 *
 * Created on May 27, 2020, 1:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "PortControl.h"
#include "const.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/*
 * 
 */

void printPort (char puerto);
int input (void);

int main(void) 
{
    ALLEGRO_DISPLAY * display = NULL;
     ALLEGRO_BITMAP *ledOn;
    //ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    //ALLEGRO_TIMER *timer = NULL;
    //ALLEGRO_BITMAP *led = NULL;
    

    if (!al_init())     //Primera funcion a llamar antes de empezar a usar allegro.
    { 
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(ANCHO, ALTO); // Intenta crear display, si falla devuelve NULL
    if (!display) 
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    
    al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)

    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla
    
    al_init_image_addon();
    
    ledOn = al_load_bitmap("ON.jpeg");
    
    if (!ledOn) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
    
    char puerto='a';    //Inicializo en el puerto A
    int mask= 0xFF;     //Inicializo la mascara en 11111111b
    int var= -3;        //Inicializo la variable con un valor que no interfiera con las funciones
    
    
    maskOff(mask, puerto);  //Apago todos los bit del puerto 
   
    printPort(puerto);      //Imprimo el puerto
    
    
    while (var != QUIT)     //Mientras no se presiones q
    {
        var= input();       //Consigo el valor del input
            
        switch (var)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            {
                bitToggle(var, puerto);             //Cambio el estado de un bit al contrario
            }; break;
            case 's':
            case 'S':
            {
                maskOn(mask,puerto);                // prendo todos los bits 
            }; break;
            case 'c':
            case 'C':
            {
                maskOff(mask,puerto);               // apago todos los bits
            };break;
            case 't':
            case 'T':
            {
                maskToggle (mask,puerto);           // prende los bits apagados y apaga los prendidos
            }; break;
            case 'q':
            case 'Q':
            {
                printf("salgo del programa\n");
            }
        }
       
        
        printPort(puerto);                      //Imprimo el puerto
        
    }
    printf("Termino el programa\n");            //Se presiono q y termina el programa
    
    
   al_destroy_bitmap(ledOn);
   //al_destroy_timer(timer);
    al_destroy_display(display); // Destruyo recurso empleados
    
    return 0;
}

int input (void)   
{
    int c=0;
    int conta=0;
    int out=0;          //Flag para q
    int res=0;          //Para devolver la respuesta
    
    
    while ((c=getchar())!='\n')
    {
        if ((c >= '0') && (c <= '7')) //Si es uno de los numeros de los bites del puerto
	{
            res *=10;
            res = (c-'0');            // lo almaceno en res pasandolo a int y aumento el contador  
            conta++;
        }
        //Si es una de las letras para los comandos
        else if ( c == 't' || c == 'T' || c == 'c' || c == 'C' || c == 's' || c == 'S'|| c == 'i' || c == 'I')
        {
            conta++;     //Aumento el contador
            res=c;      //La almaceno en res
        }
        else if ((c=='Q')||(c=='q'))    //En el caso de ser el comando q
        {
            out=1;                //Enciendo el flag de q
            conta++;              //Aumento El contador 
        }
        else
        {
            conta=-10;                  //Si no es ninguno de los casos anteriores el contador general en -10
        }
    }
    
    if (conta<=0 || conta>1)    //Si el contador es menor a 0 o mayor a 1
    {
        res=ERROR;              //Devuelvo error
        
        printf("Lo ingresado no es valido\n");  //y lo imprimo en pantalla
    }
    
    if (out==1 && conta==1)     //Si se presiono q y el contador es 1
    {
        res=QUIT;               //Devuelvo QUIT para salir del programa
    }

	return res;
}	

void printPort (char puerto)
{
    int i=0;
       
    printf("|");
    
    for(i=0; i<=7;i++)
    {
        
        if(bitGet(i,puerto))    //Si bitGet devuelve 1, porque el bit esta prendido
        {
            printf("*");        // imprimo un *
        }
        else                    //Caso contrario (si devuelve un 0) 
        {
            printf(" ");        // imprimo un espacio
        }
        
        printf("|");
    }
    
    printf("\n");
}

