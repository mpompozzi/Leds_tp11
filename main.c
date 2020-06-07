
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
#include <time.h>

/*******************************************************************************
 * PROTOTIPOS
 ******************************************************************************/
void printPort(char puerto);
int input(void);
void print_led(void);

/*******************************************************************************
 * VARIABLES GLOBALES
 ******************************************************************************/
int leds_pos[8] = {10,10+DIST,10+ 2 * DIST,10+ 3 * DIST,10+ 4 * DIST,10+ 5 * DIST,10+ 6 * DIST,10+ 7 * DIST};
bool led_actual[8];
bool led_anterior[8];

/*******************************************************************************
 * FUNCION MAIN
 ******************************************************************************/
int main(void) {
    
    /*VARIABLES */
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_BITMAP *ledOn;
    ALLEGRO_BITMAP *ledOff;
    //ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   


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
    ledOn = al_load_bitmap("led_on.jpeg");
    ledOff = al_load_bitmap("led_off.jpeg");
    if (!ledOff) {
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


    maskOff(mask, puerto); //Apago todos los  bit del puerto 
    //printPort(puerto); //Imprimo el puerto
    print_led();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    bool out = 0;

    while (!out) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_B:
                {
                    int c = 0;
                    for (c = 0; c <= 7; ++c) {
                        led_anterior[c] = led_actual[c];
                    }
                    while (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_B) {
                        al_get_next_event(event_queue, &ev);
                    } //Neutralizamos el eco del input de la letra b
                    
                    print_led();
                    
                    al_wait_for_event(event_queue, &ev);
                    
                    while (!(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_B))
                    {
                        
                        int c=0;
                        maskOff(mask, puerto);
                        print_led();
                        
                        al_rest(0.1);   //Espera 5 
                        al_get_next_event(event_queue, &ev);

                        for (c = 0; c <= 7; ++c) 
                        {
                            led_actual[c] = led_anterior[c];
                            if (led_anterior[c]) 
                            {
                                bitSet(c, 'A');
                            }
                        }
                        
                        print_led();
                        
                        al_rest(0.1);
                        
                        al_get_next_event(event_queue, &ev);
                    }
                }
                    break;
                case ALLEGRO_KEY_S:
                    maskOn(mask, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_C:
                    maskOff(mask, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_T:
                    maskToggle(mask, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_0:
                    bitToggle(0, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_1:
                    bitToggle(1, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_2:
                    bitToggle(2, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_3:
                    bitToggle(3, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_4:
                    bitToggle(4, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_5:
                    bitToggle(5, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_6:
                    bitToggle(6, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_7:
                    bitToggle(7, 'A');
                    print_led();
                    break;
                case ALLEGRO_KEY_ESCAPE:
                case ALLEGRO_KEY_Q:
                    out = 1;
                    break;
            }
        }
    }
    /*FINALIZACION DEL PROGRAMA*/
    printf("Termino el programa\n"); //Se presiono q y termina el programa.
    al_destroy_bitmap(ledOn);
    al_destroy_display(display); // Destruyo recurso empleados
    return 0;
}

/*******************************************************************************
 *FUNCIONES LOCALES
 ******************************************************************************/


void print_led(void) {
    ALLEGRO_BITMAP *ledOn = al_load_bitmap("led_on.jpeg");
    ALLEGRO_BITMAP *ledOff = al_load_bitmap("led_off.jpeg");
    int c;
    al_clear_to_color(al_map_rgb(255, 255, 255));
    for (c = 0; c <= 7; ++c) {
        led_actual[c] = (bool) bitGet(c, 'A');
    }
    for (c = 0; c <= 7; ++c) {
        if (led_actual[c] == true) {
            al_draw_bitmap(ledOn, leds_pos[c], 50, 0);
        } else {
            al_draw_bitmap(ledOff, leds_pos[c], 50, 0);
        }
    }
    al_flip_display();
    
    
}


