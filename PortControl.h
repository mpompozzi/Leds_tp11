/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PortControl.h
 * Author: axel
 *
 * Created on 20 de mayo de 2020, 12:29
 */

#ifndef PORTCONTROL_H
#define PORTCONTROL_H

#include <stdint.h>
/*******************************************************************************
 * Función: bitSet
 * Descripcción: Función que dado un bit especifico  el puerto de dicho bit 
 * y lo pone en 1.
 * Param:numero de bit;puerto al que peternece el bit.
 * Salida:ninguna.
 * 
 ******************************************************************************/
void bitSet (int bit, char puerto);

/*******************************************************************************
 * Función: bitClr
 * Descripcción:Función que dado un bit especifico  el puerto de dicho bit 
 * y lo pone en 0
 * Param:numero de bit;puerto al que peternece el bit,puntero al puerto.
 * Salida:ninguna.
 * 
 ******************************************************************************/
void bitClr (int bit, char puerto);

/*******************************************************************************
 * Función: bitGet
 * Descripcción:Función que dado un bit especifico  el puerto de dicho bit, de-
 * vuelve su estado actual.
 * Param:numero de bit;puerto el que peternece el bit.
 * Salida:estado actual del bit.
 * 
 ******************************************************************************/
int  bitGet (int bit, char puerto);

/*******************************************************************************
 * Función: bitToggle
 * Descripcción:Función que dado un bit especifico  el puerto de dicho bit,pone
 * el estado opuesto al actual.
 * Param:numero de bit;puerto al que peternece el bit.
 * Salida:ninguna.
 * 
 ******************************************************************************/
void bitToggle (int bit, char puerto);
/*******************************************************************************
 * Función: maskOn
 * Descripcción:Dado una mascara y un puerto pone en 1 aquello bit que indique
 * la misma.
 * Param:mascara de dato , puerto seleccionado.
 * Salida:ninguna.
 * 
 ******************************************************************************/
void maskOn ( int mask, char puerto);

/*******************************************************************************
 * Función: maskOff
 * Descripcción: Dado una mascara y un puerto pone en 0 aquellos bits que indi-
 * que la mascara sin alterar el resto.
 * Param:mascara de dato , puerto seleccionado.
 * Salida:
 * 
 ******************************************************************************/
void maskOff (int mask,char puerto);

/*******************************************************************************
 * Función: maskToggle
 * Descripcción: Dado una mascara y un puerto pone en el estado opuesto a aque-
 * llos bits indicado con un 1 mediante la mascara.
 * Param:mascara de dato , puerto seleccionado.
 * Salida:ninguna
 * 
 ******************************************************************************/
void maskToggle (int mask, char puerto);


#endif /* PORTCONTROL_H */

