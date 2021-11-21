# info2_tuner  
TPO Informatica 2 - Afinador Guitarra y Bajo  
Trabajo Final Integrador y Obligatorio realizado en forma individual para la materia Informatica 2 en el año 2014. Nota de aprobación 9.  
Es un afinador de guitarra y bajo mediante del uso de un MCU LPCXpresso LPC1769 y la placa base oficial de Embedded Artists LPCXpresso Baseboard.  
Tambien se tuvo que desarrollar en forma adicional un mini amplificador para recibir la señal, amplificarla y centrarla entre 0V y 3V3 antes de leerla en el ADC.  

Links del hard:   
https://www.embeddedartists.com/products/lpcxpresso-baseboard/  
https://www.embeddedartists.com/products/lpc1769-lpcxpresso/  

-----------------------------------
En lineamientos generales este proyecto consta de un dispositivo cuya función principal es la de interpretar vibraciones y mostrar la nota musical correspondiente a esa frecuencia.  
Esto se traduce en lo que en el mercado se conoce como “afinador cromático” que sirve para ver cuán afinado está un instrumento musical ya sea piano, guitarra, bajo, violín, etc, sin embargo la utilidad de esta aplicación va a estar apuntada enfáticamente a las guitarras criollas, acústicas y eléctricas.
Estas frecuencias serán mostradas en un display OLED junto con la nota correspondiente y junto con unas flechas indicadores del faltante para lograr la afinación lo más precisa posible a la nota deseada.

/////////////////////////////////////////  
// Funcionamiento del programa: //  
////////////////////////////////////////  

El programa va a tener 3 modos:  
-Modo Configuracion  
-Modo Afinacion  
-Modo Metronomo  

En el modo "Configuracion" se van a poder setear distintas opciones que van a influir en el comportamiento del programa, como por ejemplo si optimizar al afinador para guitarras o bajos, o cambiar la norma de afinacion entre A440 (estandard) o A432 (afinacion de conservatorio).  
En el modo "Afinacion" la interfaz va a mostrar en el display OLED una aguja la cual es encargada de mostrar graficamente que tan cerca se esta de la afinacion deseada, a su vez se puede elegir si usar un asistente de afinacion para guitarra o bajo el cual se encarga de asistir en la afinacion deseada cuerda por cuerda, o si se desea un modo libre en el cual se puede tocar cualquier nota que la interfaz se encargara de interpretarla y mostrala.  
Y por ultimo, en el modo "Metronomo" el buzzer emitara un pitido segun el actual "beat" seleccionado.  

La visualizacion del dispositivo es en el display Oled de 96x64px de la placa base conectado mediante el SSP (SPI) del LPC1769.  
La navegacion se realiza mediante el joystick incluido en la placa base, y se confirma o cancela la opcion marcada actualmente mediante dos pulsadores adicionales.   


