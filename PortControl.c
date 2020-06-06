/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/
/*******************************************************************************
* ARCHIVOS HEADERS Y LIBRERIAS.
******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"


/*******************************************************************************
 * ESTRUCTURAS, TYPEDEF Y UNIONES.
 ******************************************************************************/
typedef union
{
    uint16_t D;     //Declaro al puerto D como union de dos puertos de 8 bits
    struct
    {
        //El order de declaracion esta dado por el Enddian (Little Enddia).
        
        uint8_t B;  //Declaro puerto B de 8 bits.
        uint8_t A;  //Declaro puerto A de 8 bits.
    };
    
    
}puerto_t;


/*******************************************************************************
 * VARIABLES.
 ******************************************************************************/
//Tests
#ifdef TESTS
puerto_t port;
#else
static puerto_t port;  
#endif                   

/*******************************************************************************
 * FUNCIONES GLOBALES.
 ******************************************************************************/

void bitSet (int bit,char puerto)
{
    //Verifico que los parametros ingresados sean validos.
    if (((puerto== 'd')||(puerto=='D')) && (bit>=0) && (bit<=15)) 
    {
        uint16_t mask= MASK16 ; //Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask <<= bit;
        //Asigno la mascara para enceder el bit indicado.
        port.D |= mask;
    }
    else if ((bit>=0) && (bit<=7) && ((puerto=='b')||(puerto=='B')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara para enceder el bit indicado.
        port.B |= mask;
        
    }
    else if((bit>=0) && (bit<=7) && ((puerto=='a')||(puerto=='A')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara para enceder el bit indicado.
        port.A |= mask;
    }
    else
    {
        printf("Datos mal ingresados 1\n");
    }
}

void bitClr (int bit, char puerto)
{
    if (((puerto== 'd')||(puerto=='D')) && (bit>=0) && (bit<=15))
    {
        uint16_t mask= MASK16;//Defino una mascara de 16 bits. 
        //Modifico la mascara para poder encerder el bit indicado.
        mask <<= bit;
        //Asigno la mascara para apagar el bit indicado.
        port.D &= ~mask;
    }
    else if ((bit>=0) && (bit<=7) && ((puerto=='b')||(puerto=='B')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara para apagar el bit indicado.
        port.B &= ~mask;
        
    }
    else if((bit>=0) && (bit<=7) && ((puerto=='a')||(puerto=='A')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara para apagar el bit indicado.
        port.A &= ~mask;
    }
    else
    {
        printf("Datos mal ingresados 2\n");
    }
}

int bitGet (int bit, char puerto)
{
    int estado=ERROR;//Inicializo en -1
    
    if (((puerto== 'd')||(puerto=='D')) && (bit>=0) && (bit<=15))
    {
        uint16_t mask= MASK16;//Defino una mascara de 16 bits. 
        //Modifico la mascara para poder encerder el bit indicado.
        mask <<= bit;
        //Verifico el estado actual del bit solicitado.
        if ((port.D) & mask)
        {
            estado=1;
        }
        else 
        {
            estado=0;
        }
    }
    else if ((bit>=0) && (bit<=7) && ((puerto=='b')||(puerto=='B')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 8 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Verifico el estado actual del bit solicitado.
        if((port.B) & mask)
        {
            estado=1;
        }
        else
        {
            estado=0;
        }
        
    }
    else if((bit>=0) && (bit<=7) && ((puerto=='a')||(puerto=='A')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 8 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Verifico el estado actual del bit solicitado.
        if(port.A & mask)
        {
            estado=1;
        }
        else
        {
            estado=0;
        }  
    }
    else
    {
        printf("Datos mal ingresados 3\n");
    }
    return estado;
}

void bitToggle (int bit, char puerto)
{
    if (((puerto== 'd')||(puerto=='D')) && (bit>=0) && (bit<=15))
    {
        uint16_t mask= MASK16;//Defino una mascara de 16 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask <<= bit;
        //Asigno la mascara modificando el bit solicitado a su estado opuesto.
        port.D ^= mask;
    }
    else if ((bit>=0) && (bit<=7) && ((puerto=='b')||(puerto=='B')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 8 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara modificando el bit solicitado a su estado opuesto.
        port.B ^= mask;
        
    }
    else if((bit>=0) && (bit<=7) && ((puerto=='a')||(puerto=='A')))
    {
        uint8_t mask= MASK8;//Defino una mascara de 8 bits.
        //Modifico la mascara para poder encerder el bit indicado.
        mask<<= bit;
        //Asigno la mascara modificando el bit solicitado a su estado opuesto.
        port.A ^= mask;
    }
    else
    {
        printf("Datos mal ingresados 4\n");
    }
}

void maskOn (int mask, char puerto)
{   
    //Verifico que el parametro del puerto sea valido.
    if((puerto=='d')||(puerto == 'D'))
    { 
        //Enciendo los bits que indica la mascara casteando para que sea de 
        //16bits.
        port.D |= (uint16_t)mask; 
    }
    else if((puerto=='a')||(puerto=='A'))
    {
        //Enciendo los bits que indica la mascara casteando para que sea de 
        //8bits.
        port.A |= (uint8_t) mask;
    }
    else if ((puerto=='b')||(puerto=='B'))
    {
        //Enciendo los bits que indica la mascara casteando para que sea de 
        //8bits.
        port.B |= (uint8_t) mask;
    }
    else 
    {
        printf("Datos mal ingresados 5\n");
    } 
}

void maskOff (int mask, char puerto)
{
    if((puerto=='d')||(puerto == 'D'))
    {
        //Apago los bits que indica la mascara casteando para que sea de 
        //16bits.
        port.D &= (uint16_t) (~mask); 
    }
    else if((puerto=='a')||(puerto=='A'))
    {
        //Apago los bits que indica la mascara casteando para que sea de 
        //8bits.
        port.A &= (uint8_t) (~mask);
    }
    else if ((puerto=='b')||(puerto=='B'))
    {
        //Apago los bits que indica la mascara casteando para que sea de 
        //8bits.
        port.B &= (uint8_t) (~mask);
    }
    else 
    {
        printf("Datos mal ingresados 6\n");
    } 
}

void maskToggle (int mask, char puerto)
{
    if((puerto=='d')||(puerto == 'D'))
    {
        //Cambio al estado opuesto los bits que indica la mascara casteando para
        //que sea de 16bits.
        port.D ^= (uint16_t)mask; 
    }
    else if((puerto=='a')||(puerto=='A'))
    {
        //Cambio al estado opuesto los bits que indica la mascara casteando para
        //que sea de 8bits.
        port.A ^=(uint8_t) mask;
    }
    else if ((puerto=='b')||(puerto=='B'))
    {
        //Cambio al estado opuesto los bits que indica la mascara casteando para
        //que sea de 8bits.
        port.B ^=(uint8_t) mask;
    }
    else 
    {
        printf("Datos mal ingresados 7\n");
    } 
}