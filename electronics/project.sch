EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L teensy:Teensy4.0 U?
U 1 1 5FF0E21C
P 5650 2250
F 0 "U?" H 5650 3865 50  0000 C CNN
F 1 "Teensy4.0" H 5650 3774 50  0000 C CNN
F 2 "" H 5250 2450 50  0001 C CNN
F 3 "" H 5250 2450 50  0001 C CNN
	1    5650 2250
	1    0    0    -1  
$EndComp
Text GLabel 4350 900  0    50   Input ~ 0
GND
Text GLabel 4350 2500 0    50   Input ~ 0
GND
Wire Wire Line
	4350 2500 4550 2500
Wire Wire Line
	4350 900  4550 900 
$Comp
L custom:BMP280 U?
U 1 1 5FF1D2EF
P 9100 1250
F 0 "U?" H 9578 1201 50  0000 L CNN
F 1 "BMP280" H 9578 1110 50  0000 L CNN
F 2 "" H 9250 750 50  0001 C CNN
F 3 "" H 9250 750 50  0001 C CNN
	1    9100 1250
	1    0    0    -1  
$EndComp
$Comp
L custom:GY521 U?
U 1 1 5FF25095
P 9150 2150
F 0 "U?" H 9478 2001 50  0000 L CNN
F 1 "GY521" H 9478 1910 50  0000 L CNN
F 2 "" H 9200 1500 50  0001 C CNN
F 3 "" H 9200 1500 50  0001 C CNN
	1    9150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3300 6750 3300
Text GLabel 6950 3300 2    50   Input ~ 0
GND
Text GLabel 6950 3400 2    50   Input ~ 0
3V3
Wire Wire Line
	6750 3400 6950 3400
Wire Wire Line
	4350 2400 4550 2400
Text GLabel 4350 2400 0    50   Input ~ 0
3V3
Text GLabel 6950 1600 2    50   Input ~ 0
GND
Wire Wire Line
	6750 1600 6950 1600
Text GLabel 8700 1250 0    50   Input ~ 0
GND
Wire Wire Line
	8900 1250 8700 1250
Text GLabel 8700 1050 0    50   Input ~ 0
3V3
Wire Wire Line
	8900 1050 8700 1050
$Comp
L custom:RFM69HCW U?
U 1 1 5FF35928
P 8800 3300
F 0 "U?" H 9125 3625 50  0000 C CNN
F 1 "RFM69HCW" H 9125 3534 50  0000 C CNN
F 2 "" H 9100 2550 50  0001 C CNN
F 3 "" H 9100 2550 50  0001 C CNN
	1    8800 3300
	1    0    0    -1  
$EndComp
$Comp
L custom:W25Q32JVDAIQ U?
U 1 1 5FF38BA5
P 9150 4650
F 0 "U?" H 9175 5025 50  0000 C CNN
F 1 "W25Q32JVDAIQ" H 9175 4934 50  0000 C CNN
F 2 "" H 9150 4400 50  0001 C CNN
F 3 "" H 9150 4400 50  0001 C CNN
	1    9150 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2200 4550 2200
Wire Wire Line
	4150 2100 4550 2100
Wire Wire Line
	4150 2800 4550 2800
Text Label 4150 2100 0    50   ~ 0
MOSI
Text Label 4150 2200 0    50   ~ 0
MISO
Text Label 4150 2800 0    50   ~ 0
SCK
Text GLabel 8050 3200 0    50   Input ~ 0
3V3
Wire Wire Line
	8900 2000 8700 2000
Text GLabel 8700 2000 0    50   Input ~ 0
3V3
Text GLabel 8700 2100 0    50   Input ~ 0
GND
Wire Wire Line
	8900 2100 8700 2100
Text GLabel 8050 3300 0    50   Input ~ 0
GND
Text GLabel 8650 4800 0    50   Input ~ 0
GND
Wire Wire Line
	8850 4800 8650 4800
Wire Wire Line
	4150 3300 4550 3300
Wire Wire Line
	4150 3400 4550 3400
Text Label 4150 3300 0    50   ~ 0
SDA
Text Label 4150 3400 0    50   ~ 0
SCL
Wire Wire Line
	8300 1350 8900 1350
Wire Wire Line
	8300 1550 8900 1550
Text Label 8300 1550 0    50   ~ 0
SDA
Wire Wire Line
	8300 2200 8900 2200
Wire Wire Line
	8300 2300 8900 2300
Text Label 8300 1350 0    50   ~ 0
SCL
Text Label 8300 2200 0    50   ~ 0
SCL
Text Label 8300 2300 0    50   ~ 0
SDA
Wire Wire Line
	7950 3500 8600 3500
Wire Wire Line
	7950 3600 8600 3600
Wire Wire Line
	7950 3700 8600 3700
Wire Wire Line
	7950 3800 8600 3800
Wire Wire Line
	4150 2900 4550 2900
Text Label 4150 2900 0    50   ~ 0
RF-CS
Text Label 4150 3100 0    50   ~ 0
FLASH-CS
Wire Wire Line
	4150 3100 4550 3100
Wire Wire Line
	7150 3200 6750 3200
$Comp
L custom:terminal-2 BAT
U 1 1 5FF75C14
P 2100 1300
F 0 "BAT" V 2188 1172 50  0000 R CNN
F 1 "terminal-2" V 2097 1172 50  0000 R CNN
F 2 "" H 2200 1150 50  0001 C CNN
F 3 "" H 2200 1150 50  0001 C CNN
	1    2100 1300
	0    -1   -1   0   
$EndComp
Text GLabel 1650 1450 0    50   Input ~ 0
GND
Wire Wire Line
	1650 1450 2050 1450
Wire Wire Line
	2050 1450 2050 1400
Wire Wire Line
	7950 3900 8600 3900
Text Label 7950 3900 0    50   ~ 0
RF-RST
Text Label 7950 3800 0    50   ~ 0
RF-CS
Text Label 7950 3700 0    50   ~ 0
MOSI
Text Label 7950 3600 0    50   ~ 0
MISO
Text Label 7950 3500 0    50   ~ 0
SCK
Wire Wire Line
	4150 3000 4550 3000
Text Label 4150 3000 0    50   ~ 0
RF-G0
Wire Wire Line
	10000 3200 9650 3200
Text Label 10000 3200 2    50   ~ 0
RF-G0
Wire Wire Line
	8500 4600 8850 4600
Wire Wire Line
	8500 4500 8850 4500
Wire Wire Line
	9850 4800 9500 4800
Wire Wire Line
	9850 4700 9500 4700
Text Label 9850 4800 2    50   ~ 0
MOSI
Text Label 9850 4700 2    50   ~ 0
SCK
Text Label 8500 4500 0    50   ~ 0
FLASH-CS
Text Label 8500 4600 0    50   ~ 0
MISO
Wire Wire Line
	2450 1450 2150 1450
Wire Wire Line
	2150 1450 2150 1400
Text GLabel 2450 1450 2    50   Input ~ 0
VIN
Wire Wire Line
	7150 3000 7150 3200
Text GLabel 7150 3000 1    50   Input ~ 0
VIN
$Comp
L Device:C C?
U 1 1 5FF27626
P 7300 3200
F 0 "C?" V 7048 3200 50  0000 C CNN
F 1 "100nF" V 7139 3200 50  0000 C CNN
F 2 "" H 7338 3050 50  0001 C CNN
F 3 "~" H 7300 3200 50  0001 C CNN
	1    7300 3200
	0    1    1    0   
$EndComp
Connection ~ 7150 3200
Text GLabel 7450 3200 2    50   Input ~ 0
GND
Wire Wire Line
	8050 3300 8600 3300
Wire Wire Line
	8050 3200 8600 3200
Text GLabel 10150 4500 2    50   Input ~ 0
3V3
$Comp
L Device:R R?
U 1 1 5FF4B056
P 10100 4750
F 0 "R?" V 9893 4750 50  0000 C CNN
F 1 "100k" V 9984 4750 50  0000 C CNN
F 2 "" V 10030 4750 50  0001 C CNN
F 3 "~" H 10100 4750 50  0001 C CNN
	1    10100 4750
	-1   0    0    1   
$EndComp
Text GLabel 10100 4900 3    50   Input ~ 0
GND
$Comp
L Device:R R?
U 1 1 5FF52719
P 8250 4700
F 0 "R?" V 8457 4700 50  0000 C CNN
F 1 "100k" V 8366 4700 50  0000 C CNN
F 2 "" V 8180 4700 50  0001 C CNN
F 3 "~" H 8250 4700 50  0001 C CNN
	1    8250 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8400 4700 8850 4700
Text GLabel 8100 4700 0    50   Input ~ 0
3V3
Text Notes 7400 7500 0    50   ~ 0
Rocket1 flight controller\n
$Comp
L Device:C C?
U 1 1 5FF15A10
P 10000 4350
F 0 "C?" V 9748 4350 50  0000 C CNN
F 1 "22pF" V 9839 4350 50  0000 C CNN
F 2 "" H 10038 4200 50  0001 C CNN
F 3 "~" H 10000 4350 50  0001 C CNN
	1    10000 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4600 10100 4600
Wire Wire Line
	9500 4500 10000 4500
Connection ~ 10000 4500
Wire Wire Line
	10000 4500 10150 4500
$EndSCHEMATC
