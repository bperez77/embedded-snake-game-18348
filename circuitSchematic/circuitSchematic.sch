EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:custom_comp
LIBS:circuitSchematic-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Snake Game"
Date "Thu 07 May 2015"
Rev "1.0"
Comp "ECE 348 Final Project"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74LS138 U12
U 1 1 554BBF34
P 3300 3650
F 0 "U12" H 3400 4150 60  0000 R CNN
F 1 "74HCT238" H 3450 3101 60  0000 R CNN
F 2 "" H 3300 3650 60  0000 C CNN
F 3 "" H 3300 3650 60  0000 C CNN
	1    3300 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X30 J1
U 1 1 554BC1E0
P 1350 3350
F 0 "J1" H 1350 4900 50  0000 C CNN
F 1 "MC912C128" V 1350 3350 50  0000 C CNN
F 2 "" H 1350 2850 60  0000 C CNN
F 3 "" H 1350 2850 60  0000 C CNN
	1    1350 3350
	1    0    0    -1  
$EndComp
$Comp
L 74LS138 U10
U 1 1 554BC3B4
P 3300 4950
F 0 "U10" H 3400 5450 60  0000 R CNN
F 1 "74LS138" H 3450 4401 60  0000 R CNN
F 2 "" H 3300 4950 60  0000 C CNN
F 3 "" H 3300 4950 60  0000 C CNN
	1    3300 4950
	1    0    0    -1  
$EndComp
$Comp
L KWM-30881AVB U15
U 1 1 554BE190
P 6200 3650
F 0 "U15" H 6200 4200 60  0000 C CNN
F 1 "KWM-30881AVB" H 6300 3650 60  0000 C CNN
F 2 "" H 6300 3650 60  0000 C CNN
F 3 "" H 6300 3650 60  0000 C CNN
	1    6200 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 554BE7F0
P 2500 5400
F 0 "#PWR?" H 2500 5150 50  0001 C CNN
F 1 "GND" H 2500 5250 50  0000 C CNN
F 2 "" H 2500 5400 60  0000 C CNN
F 3 "" H 2500 5400 60  0000 C CNN
	1    2500 5400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 554BE86B
P 2500 5000
F 0 "#PWR?" H 2500 4850 50  0001 C CNN
F 1 "+5V" H 2500 5140 50  0000 C CNN
F 2 "" H 2500 5000 60  0000 C CNN
F 3 "" H 2500 5000 60  0000 C CNN
	1    2500 5000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 554BE8CB
P 2500 4100
F 0 "#PWR?" H 2500 3850 50  0001 C CNN
F 1 "GND" H 2500 3950 50  0000 C CNN
F 2 "" H 2500 4100 60  0000 C CNN
F 3 "" H 2500 4100 60  0000 C CNN
	1    2500 4100
	1    0    0    -1  
$EndComp
Text Notes 6750 3250 0    60   ~ 0
LED Matrix
$Comp
L Circle H?
U 1 1 554BEC94
P 1850 5900
F 0 "H?" H 1656 5900 60  0001 C CNN
F 1 "PB1 (Project Board)" H 1850 5750 60  0001 C CNN
F 2 "" H 1850 5750 60  0000 C CNN
F 3 "" H 1850 5750 60  0000 C CNN
	1    1850 5900
	1    0    0    -1  
$EndComp
$Comp
L Circle H?
U 1 1 554BEDB1
P 1850 6250
F 0 "H?" H 1656 6250 60  0001 C CNN
F 1 "PB1 (Project Board)" H 1850 6100 60  0001 C CNN
F 2 "" H 1850 6100 60  0000 C CNN
F 3 "" H 1850 6100 60  0000 C CNN
	1    1850 6250
	1    0    0    -1  
$EndComp
Text Notes 1950 5950 0    60   ~ 0
PB1 (Project Board)
Text Notes 1950 6300 0    60   ~ 0
PB2 (Project Board)
$Comp
L OPT101 U14
U 1 1 554BF023
P 3300 2350
F 0 "U14" H 3306 2650 60  0000 C CNN
F 1 "OPT101" H 3300 2000 60  0000 C CNN
F 2 "" H 3300 2000 60  0000 C CNN
F 3 "" H 3300 2000 60  0000 C CNN
	1    3300 2350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 554BF43D
P 4000 2600
F 0 "#PWR?" H 4000 2350 50  0001 C CNN
F 1 "GND" H 4000 2450 50  0000 C CNN
F 2 "" H 4000 2600 60  0000 C CNN
F 3 "" H 4000 2600 60  0000 C CNN
	1    4000 2600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 554BF4EB
P 4000 2100
F 0 "#PWR?" H 4000 1950 50  0001 C CNN
F 1 "+5V" H 4000 2240 50  0000 C CNN
F 2 "" H 4000 2100 60  0000 C CNN
F 3 "" H 4000 2100 60  0000 C CNN
	1    4000 2100
	1    0    0    -1  
$EndComp
Text Notes 3050 1950 0    60   ~ 0
Photodiode
Wire Wire Line
	1600 2300 2800 2300
Wire Wire Line
	850  6250 1800 6250
Wire Wire Line
	850  4500 850  6250
Wire Wire Line
	850  4500 1100 4500
Wire Wire Line
	950  5900 1800 5900
Wire Wire Line
	950  4600 950  5900
Wire Wire Line
	1100 4600 950  4600
Wire Wire Line
	2500 3800 2700 3800
Wire Wire Line
	2500 1600 2500 3800
Wire Wire Line
	800  1600 2500 1600
Wire Wire Line
	800  2300 800  1600
Wire Wire Line
	1100 2300 800  2300
Connection ~ 2500 4000
Wire Wire Line
	2700 3900 2500 3900
Wire Wire Line
	2500 3900 2500 4100
Wire Wire Line
	2700 4000 2500 4000
Wire Wire Line
	2500 5100 2500 5000
Wire Wire Line
	2700 5100 2500 5100
Connection ~ 2500 5300
Wire Wire Line
	2700 5200 2500 5200
Wire Wire Line
	2500 5200 2500 5400
Wire Wire Line
	2700 5300 2500 5300
Wire Wire Line
	1800 3300 2700 3300
Wire Wire Line
	1800 4300 1800 3300
Wire Wire Line
	1600 4300 1800 4300
Wire Wire Line
	1900 3400 2700 3400
Wire Wire Line
	1900 4400 1900 3400
Wire Wire Line
	1600 4400 1900 4400
Wire Wire Line
	2000 3500 2700 3500
Wire Wire Line
	2000 4500 2000 3500
Wire Wire Line
	1600 4500 2000 4500
Wire Wire Line
	1600 4600 2700 4600
Wire Wire Line
	1600 4700 2700 4700
Wire Wire Line
	1600 4800 2700 4800
Wire Wire Line
	6600 5300 6600 4400
Wire Wire Line
	3900 5300 6600 5300
Wire Wire Line
	6500 5200 6500 4400
Wire Wire Line
	3900 5200 6500 5200
Wire Wire Line
	6400 5100 6400 4400
Wire Wire Line
	3900 5100 6400 5100
Wire Wire Line
	6300 5000 6300 4400
Wire Wire Line
	3900 5000 6300 5000
Wire Wire Line
	6200 4900 6200 4400
Wire Wire Line
	3900 4900 6200 4900
Wire Wire Line
	6100 4800 6100 4400
Wire Wire Line
	3900 4800 6100 4800
Wire Wire Line
	6000 4700 6000 4400
Wire Wire Line
	3900 4700 6000 4700
Wire Wire Line
	5900 4600 5900 4400
Wire Wire Line
	3900 4600 5900 4600
Wire Wire Line
	2800 2200 2650 2200
Wire Wire Line
	2650 2200 2650 2300
Connection ~ 2650 2300
Wire Wire Line
	3800 2400 4000 2400
Wire Wire Line
	4000 2300 4000 2600
Wire Wire Line
	3800 2300 4000 2300
Connection ~ 4000 2400
Wire Wire Line
	3800 2200 4000 2200
Wire Wire Line
	4000 2200 4000 2100
$Comp
L R_PACK8 R1
U 1 1 555422F1
P 4700 3650
F 0 "R1" H 4700 4100 50  0000 C CNN
F 1 "270 Ohm" H 4700 3200 50  0000 C CNN
F 2 "" H 4700 3650 60  0000 C CNN
F 3 "" H 4700 3650 60  0000 C CNN
	1    4700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3300 4500 3300
Wire Wire Line
	4900 3300 5500 3300
Wire Wire Line
	3900 3400 4500 3400
Wire Wire Line
	4900 3400 5500 3400
Wire Wire Line
	3900 3500 4500 3500
Wire Wire Line
	4900 3500 5500 3500
Wire Wire Line
	3900 3600 4500 3600
Wire Wire Line
	4900 3600 5500 3600
Wire Wire Line
	4900 3700 5500 3700
Wire Wire Line
	3900 3700 4500 3700
Wire Wire Line
	3900 3800 4500 3800
Wire Wire Line
	4900 3800 5500 3800
Wire Wire Line
	3900 3900 4500 3900
Wire Wire Line
	4900 3900 5500 3900
Wire Wire Line
	3900 4000 4500 4000
Wire Wire Line
	4900 4000 5500 4000
$EndSCHEMATC
