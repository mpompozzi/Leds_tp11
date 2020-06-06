
/* 
 * File:   main.c
 * Author: magali
 *
 * Created on May 27, 2020, 1:11 PM
 */
/*******************************************************************************
 * HEADERS Y LIBRERIAS
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "PortControl.h"
#include "const.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

/*******************************************************************************
 * PROTOTIPOS
 ******************************************************************************/
void printPort(char puerto);
int input(void);
void init_leds(ALLEGRO_BITMAP *led);
/*******************************************************************************
 * VARIABLES GLOBALES
 ******************************************************************************/
int leds_pos[8]={0,DIST,2*DIST,3*DIST,4*DIST,5*DIST,6*DIST,7*DIST};
/*bool led_actual[8];
bool led_anterior[8];*/
/*******************************************************************************
 * FUNCION MAIN
 ******************************************************************************/
int main(void) 
{
/*VARIABLES */
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_BITMAP *ledOn;
    ALLEGRO_BITMAP *ledOff;
    //ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    //ALLEGRO_BITMAP *led = NULL;

/******************** INICIALIZACIONES DE ALLEGRO  ****************************/
    if (!al_init()) //Primera funcion a llamar antes de empezar a usar allegro.
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
/*INCIALIZO TECLADO*/
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
/*INICIALIZO COLA DE EVENTOS*/
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }
/*INICIALIZO OPERACIONES CON IMAGENES*/
    al_init_image_addon();
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize image addon!\n");
        return -1;
    }

/*INICIALIZO IMAGENES EN VARIABLES*/
    ledOn = al_load_bitmap("led_on.jpeg");

    if (!ledOn) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }
    ledOff = al_load_bitmap("led_off.jpeg");
    if (!ledOn) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }
/*CREACIÓN  EL DISPLAY PRINCIPAL*/
    display = al_create_display(ANCHO, ALTO); // Intenta crear display, si falla devuelve NULL
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
/*CONFIGURACIÓN DEL FONDO DEL DISPLAY*/
    al_clear_to_color(al_map_rgb(200, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)
    al_flip_display();

    //al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

    //al_draw_bitmap(ledOn, 10, 100, 0); //flags(normalmente en cero, ver doc. para rotar etc)

/*INICIALIZACION DE PUERTO A*/
    char puerto = 'a'; //Inicializo en el puerto A
    int mask = 0xFF; //Inicializo la mascara en 11111111b
    int var = -3; //Inicializo la variable con un valor que no interfiera con las funciones
    
    maskOff(mask, puerto); //Apago todos losd  bit del puerto 
    //printPort(puerto); //Imprimo el puerto
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    bool out=0;
    init_leds(ledOff);
    while (!out) 
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            switch (ev.keyboard.keycode) 
            {
                case ALLEGRO_KEY_B:
                    ;
                    break;

                case ALLEGRO_KEY_C:
                    ;
                    break;

                case ALLEGRO_KEY_S:
                    ;
                    break;

                case ALLEGRO_KEY_T:
                    ;
                    break;
                case ALLEGRO_KEY_0:
                    ;
                    break;
                case ALLEGRO_KEY_1:
                    ;
                    break;
                case ALLEGRO_KEY_2:
                    ;
                    break;
                case ALLEGRO_KEY_3:
                    ;
                    break;
                case ALLEGRO_KEY_4:
                    ;
                    break;
                case ALLEGRO_KEY_5:
                    ;
                    break;
                case ALLEGRO_KEY_6:
                    ;
                    break;
                case ALLEGRO_KEY_7:
                    ;
            
                    break;
                case ALLEGRO_KEY_ESCAPE:
                case ALLEGRO_KEY_Q:
                    out = 1;
                    break;



            }
        }
    }
   /* while (var != QUIT) //Mientras no se presiones q
    {
        var = input(); //Consigo el valor del input

        switch (var) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            {
                bitToggle(var, puerto); //Cambio el estado de un bit al contrario
            };
                break;
            case 's':
            case 'S':
            {
                maskOn(mask, puerto); // prendo todos los bits 
            };
                break;
            case 'c':
            case 'C':
            {
                maskOff(mask, puerto); // apago todos los bits
            };
                break;
            case 't':
            case 'T':
            {
                maskToggle(mask, puerto); // prende los bits apagados y apaga los prendidos
            };
                break;
            case 'q':
            case 'Q':
            {
                printf("salgo del programa\n");
            }
        }
       // printPort(puerto); //Imprimo el puerto
    }
 */
/*FINALIZACION DEL PROGRAMA*/
    printf("Termino el programa\n"); //Se presiono q y termina el programa.
    al_destroy_bitmap(ledOn);
    al_destroy_timer(timer);
    al_destroy_display(display); // Destruyo recurso empleados
    return 0;
}

/*******************************************************************************
 *FUNCIONES LOCALES
 ******************************************************************************/
int input(void) {
    int c = 0;
    int conta = 0;
    int out = 0; //Flag para q
    int res = 0; //Para devolver la respuesta


    while ((c = getchar()) != '\n') {
        if ((c >= '0') && (c <= '7')) //Si es uno de los numeros de los bites del puerto
        {
            res *= 10;
            res = (c - '0'); // lo almaceno en res pasandolo a int y aumento el contador  
            conta++;
        }//Si es una de las letras para los comandos
        else if (c == 't' || c == 'T' || c == 'c' || c == 'C' || c == 's' || c == 'S' || c == 'i' || c == 'I') {
            conta++; //Aumento el contador
            res = c; //La almaceno en res
        } else if ((c == 'Q') || (c == 'q')) //En el caso de ser el comando q
        {
            out = 1; //Enciendo el flag de q
            conta++; //Aumento El contador 
        } else {
            conta = -10; //Si no es ninguno de los casos anteriores el contador general en -10
        }
    }

    if (conta <= 0 || conta > 1) //Si el contador es menor a 0 o mayor a 1
    {
        res = ERROR; //Devuelvo error

        printf("Lo ingresado no es valido\n"); //y lo imprimo en pantalla
    }

    if (out == 1 && conta == 1) //Si se presiono q y el contador es 1
    {
        res = QUIT; //Devuelvo QUIT para salir del programa
    }

    return res;
}

/*
void printPort(char puerto) {
    int i = 0;

    printf("|");

    for (i = 0; i <= 7; i++) {

        if (bitGet(i, puerto)) //Si bitGet devuelve 1, porque el bit esta prendido
        {
            printf("*"); // imprimo un *
        } else //Caso contrario (si devuelve un 0) 
        {
            printf(" "); // imprimo un espacio
        }

        printf("|");
    }

    printf("\n");
}
*/
/*void blink_port(void)
{
   int index=0;
   bool blink_flag=false;
   
   
   }
   
   
}
*/

void init_leds(ALLEGRO_BITMAP *led)
{
    int i;
    for(i=0;i<=8;++i)
    {
        al_draw_bitmap(led,leds_pos[i], 100, 0);
    }
    al_flip_display();
}