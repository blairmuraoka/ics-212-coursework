/**
 * Name:        Blair Muraoka
 * Homework:    9
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        12-05-2016
 * File:        Homework9.c
 * 
 * Description: This file contains the two functions that will work with JNI
 *              and make them usable within a java interface.
 */
#include <jni.h>
#include <stdio.h>
#include "Homework9.h"

/** 
 * Function name:   Java_Homework9_convertCtoF
 * Description:     Takes an integer value and performs the conversion from
 *                  Celsius to Fahrenheit.
 * Parameters:      num - the number to be converted
 * Return:          The converted value.
 */
JNIEXPORT jfloat JNICALL Java_Homework9_convertCtoF
  (JNIEnv *env, jobject jobj, jint num)
{
    return num * 9/5 + 32;
}

/** 
 * Function name:   Java_Homework9_roundUp
 * Description:     Rounds a number up to the nearest multiple of 5
 * Return:          The converted value.
 */
JNIEXPORT jint JNICALL Java_Homework9_roundUp
  (JNIEnv *env, jobject jobj, jint num)
{
    jint rounded = num;
    
    while (rounded % 5 != 0)
    {
        rounded++; 
    }
    
    return rounded;
}
