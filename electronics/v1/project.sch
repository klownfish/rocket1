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
Text GLabel 4450 1100 0    50   Input ~ 0
GND
Text GLabel 6800 1300 2    50   Input ~ 0
GND
Wire Wire Line
	6800 1300 6600 1300
Wire Wire Line
	4450 1100 4650 1100
Wire Wire Line
	6800 1400 6600 1400
Text GLabel 6800 1400 2    50   Input ~ 0
3V3
$Comp
L custom:RFM69HCW U2
U 1 1 5FF35928
P 8800 3300
F 0 "U2" H 9125 3625 50  0000 C CNN
F 1 "RFM69HCW" H 9125 3534 50  0000 C CNN
F 2 "custom:Adafruit-RFM69" H 9100 2550 50  0001 C CNN
F 3 "" H 9100 2550 50  0001 C CNN
	1    8800 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2500 6600 2500
Text Label 4300 2300 0    50   ~ 0
MOSI
Text Label 4300 2400 0    50   ~ 0
MISO
Text GLabel 8050 3200 0    50   Input ~ 0
3V3
Text GLabel 8050 3300 0    50   Input ~ 0
GND
Text GLabel 8650 4800 0    50   Input ~ 0
GND
Wire Wire Line
	8850 4800 8650 4800
Wire Wire Line
	7000 2000 6600 2000
Wire Wire Line
	7000 1900 6600 1900
Text Label 7000 2000 2    50   ~ 0
SDA
Text Label 7000 1900 2    50   ~ 0
SCL
Wire Wire Line
	7950 3600 8600 3600
Wire Wire Line
	7950 3700 8600 3700
Wire Wire Line
	7950 3800 8600 3800
Wire Wire Line
	7950 3900 8600 3900
$Comp
L custom:terminal-2 BAT1
U 1 1 5FF75C14
P 2100 1300
F 0 "BAT1" V 2188 1172 50  0000 R CNN
F 1 "terminal-2" V 2097 1172 50  0000 R CNN
F 2 "custom:terminal-small" H 2200 1150 50  0001 C CNN
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
	7950 4000 8600 4000
Text Label 7950 4000 0    50   ~ 0
RF-RST
Text Label 7950 3900 0    50   ~ 0
RF-CS
Text Label 7950 3800 0    50   ~ 0
MOSI
Text Label 7950 3700 0    50   ~ 0
MISO
Text Label 7950 3600 0    50   ~ 0
SCK
Wire Wire Line
	7000 1700 6600 1700
Text Label 7000 1700 2    50   ~ 0
RF-G0
Text Label 7950 3500 0    50   ~ 0
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
	2150 1450 2150 1400
Text GLabel 2450 1450 2    50   Input ~ 0
VIN
Wire Wire Line
	7000 1000 7000 1200
Text GLabel 7000 1000 1    50   Input ~ 0
VIN
$Comp
L Device:C C1
U 1 1 5FF27626
P 7150 1200
F 0 "C1" V 6898 1200 50  0000 C CNN
F 1 "100nF" V 6989 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" H 7188 1050 50  0001 C CNN
F 3 "~" H 7150 1200 50  0001 C CNN
	1    7150 1200
	0    1    1    0   
$EndComp
Connection ~ 7000 1200
Text GLabel 7300 1200 2    50   Input ~ 0
GND
Wire Wire Line
	8050 3300 8600 3300
Wire Wire Line
	8050 3200 8600 3200
Text GLabel 10150 4500 2    50   Input ~ 0
3V3
Wire Wire Line
	8400 4700 8850 4700
Text Notes 7400 7500 0    50   ~ 0
Rocket1 flight controller\n
$Comp
L Device:C C2
U 1 1 5FF15A10
P 10000 4350
F 0 "C2" V 9748 4350 50  0000 C CNN
F 1 "22pF" V 9839 4350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" H 10038 4200 50  0001 C CNN
F 3 "~" H 10000 4350 50  0001 C CNN
	1    10000 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4500 10000 4500
Connection ~ 10000 4500
Wire Wire Line
	10000 4500 10150 4500
Wire Wire Line
	6600 2300 7000 2300
Text Label 7000 2300 2    50   ~ 0
bat_read
$Comp
L Device:R R1
U 1 1 5FF454D8
P 2300 1600
F 0 "R1" V 2507 1600 50  0000 C CNN
F 1 "4.7k" V 2416 1600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 2230 1600 50  0001 C CNN
F 3 "~" H 2300 1600 50  0001 C CNN
	1    2300 1600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5FF468AF
P 2300 2000
F 0 "R2" V 2507 2000 50  0000 C CNN
F 1 "4.7k" V 2416 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 2230 2000 50  0001 C CNN
F 3 "~" H 2300 2000 50  0001 C CNN
	1    2300 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2300 1850 2300 1800
Text GLabel 2300 2150 3    50   Input ~ 0
GND
Wire Wire Line
	2300 1800 2700 1800
Connection ~ 2300 1800
Wire Wire Line
	2300 1800 2300 1750
Text Label 2700 1800 2    50   ~ 0
bat_read
Text GLabel 10000 4200 1    50   Input ~ 0
GND
Wire Wire Line
	7000 1600 6600 1600
Text Label 7000 1600 2    50   ~ 0
RF-RST
Text Label 4200 2200 0    50   ~ 0
FLASH-CS
Wire Wire Line
	7950 3500 8600 3500
Text Label 7000 2500 2    50   ~ 0
SCK
$Comp
L custom:GY91 U3
U 1 1 608CCC88
P 8800 1450
F 0 "U3" V 8949 1878 50  0000 L CNN
F 1 "GY91" V 9040 1878 50  0000 L CNN
F 2 "custom:GY91" H 9000 1950 50  0001 C CNN
F 3 "" H 9000 1950 50  0001 C CNN
	1    8800 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 1300 8700 1300
Text GLabel 8500 1300 0    50   Input ~ 0
3V3
Text GLabel 8500 1450 0    50   Input ~ 0
GND
Wire Wire Line
	8500 1450 8700 1450
Wire Wire Line
	8700 1450 8700 1500
Wire Wire Line
	8300 1600 8700 1600
Wire Wire Line
	8300 1700 8700 1700
Text Label 8300 1600 0    50   ~ 0
SCL
Text Label 8300 1700 0    50   ~ 0
SDA
Wire Wire Line
	2800 3150 2600 3150
Wire Wire Line
	2800 3750 2600 3750
Wire Wire Line
	2800 3650 2600 3650
Wire Wire Line
	2800 2950 2600 2950
Wire Wire Line
	2800 2850 2600 2850
Wire Wire Line
	4500 1200 4650 1200
Wire Wire Line
	4500 1300 4650 1300
Text Label 4500 1200 0    50   ~ 0
RX1
Text Label 4500 1300 0    50   ~ 0
TX1
Text Label 2800 2850 2    50   ~ 0
RX1
Text Label 2800 2950 2    50   ~ 0
TX1
Text GLabel 2800 3650 2    50   Input ~ 0
3V3
Text GLabel 2800 3750 2    50   Input ~ 0
GND
Wire Wire Line
	2800 3250 2600 3250
Wire Wire Line
	2800 3050 2600 3050
Wire Wire Line
	4250 1900 4650 1900
Text Label 4250 1900 0    50   ~ 0
EXT-CS
Text Label 2800 3050 2    50   ~ 0
SCK
Text Label 2800 3250 2    50   ~ 0
MOSI
Text Label 2800 3150 2    50   ~ 0
MISO
Text Label 2900 3350 2    50   ~ 0
EXT-CS
Wire Wire Line
	2900 3350 2600 3350
$Comp
L Connector_Generic:Conn_01x10 J1
U 1 1 6093ABD2
P 2400 3350
F 0 "J1" H 2318 2625 50  0000 C CNN
F 1 "Conn_01x10" H 2318 2716 50  0000 C CNN
F 2 "custom:01x10_header" H 2400 3350 50  0001 C CNN
F 3 "~" H 2400 3350 50  0001 C CNN
	1    2400 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 3550 2600 3550
Wire Wire Line
	2800 3450 2600 3450
Text Label 2800 3550 2    50   ~ 0
SCL
Text Label 2800 3450 2    50   ~ 0
SDA
Text Label 4200 2100 0    50   ~ 0
FLASH-WP
Text Label 4100 2000 0    50   ~ 0
FLASH-HOLD
Text Label 8400 4700 0    50   ~ 0
FLASH-WP
Text Label 10000 4600 2    50   ~ 0
FLASH-HOLD
$Comp
L Device:Buzzer BZ1
U 1 1 609840B9
P 4600 4800
F 0 "BZ1" H 4752 4829 50  0000 L CNN
F 1 "Buzzer" H 4752 4738 50  0000 L CNN
F 2 "custom:buzzer" V 4575 4900 50  0001 C CNN
F 3 "~" V 4575 4900 50  0001 C CNN
	1    4600 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4900 4500 4900
Wire Wire Line
	4300 4700 4500 4700
Text GLabel 4300 4900 0    50   Input ~ 0
GND
Text Label 4300 4700 0    50   ~ 0
BUZZ
Wire Wire Line
	6800 1500 6600 1500
Text Label 6800 1500 2    50   ~ 0
BUZZ
Wire Wire Line
	4350 1400 4650 1400
Text Label 4350 1400 0    50   ~ 0
LED-R
Text Label 4350 1500 0    50   ~ 0
LED-G
Text Label 4350 1600 0    50   ~ 0
LED-B
$Comp
L Device:LED_RGBC D1
U 1 1 609A2A97
P 6300 4700
F 0 "D1" H 6300 5197 50  0000 C CNN
F 1 "LED_RGBC" H 6300 5106 50  0000 C CNN
F 2 "custom:LED_D5.0mm-4_RGB" H 6300 4650 50  0001 C CNN
F 3 "~" H 6300 4650 50  0001 C CNN
	1    6300 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4700 6100 4700
Text GLabel 5900 4700 0    50   Input ~ 0
GND
Wire Wire Line
	7250 4700 6950 4700
Text Label 7600 4300 2    50   ~ 0
LED-R
Text Label 7250 4700 2    50   ~ 0
LED-G
Text Label 7550 5100 2    50   ~ 0
LED-B
Wire Wire Line
	6600 1200 7000 1200
$Comp
L custom:teensy4 U1
U 1 1 608C0A1A
P 5050 1050
F 0 "U1" H 5625 1265 50  0000 C CNN
F 1 "teensy4" H 5625 1174 50  0000 C CNN
F 2 "custom:teensy4" H 5850 1150 50  0001 C CNN
F 3 "" H 5850 1150 50  0001 C CNN
	1    5050 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2000 4650 2000
Wire Wire Line
	4200 2100 4650 2100
Wire Wire Line
	4200 2200 4650 2200
Wire Wire Line
	4300 2400 4650 2400
Wire Wire Line
	4300 2300 4650 2300
Wire Wire Line
	4350 1500 4650 1500
Wire Wire Line
	7000 1800 6600 1800
Text Label 7000 1800 2    50   ~ 0
RF-CS
Wire Wire Line
	4650 1600 4350 1600
$Comp
L Device:R R5
U 1 1 60979944
P 6800 4700
F 0 "R5" V 6593 4700 50  0000 C CNN
F 1 "1000" V 6684 4700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 6730 4700 50  0001 C CNN
F 3 "~" H 6800 4700 50  0001 C CNN
	1    6800 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 60979F50
P 6800 5100
F 0 "R4" V 6593 5100 50  0000 C CNN
F 1 "330" V 6684 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 6730 5100 50  0001 C CNN
F 3 "~" H 6800 5100 50  0001 C CNN
	1    6800 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 4300 7600 4300
Wire Wire Line
	6650 4500 6500 4500
Wire Wire Line
	6650 4700 6500 4700
Wire Wire Line
	6500 4900 6650 4900
Wire Wire Line
	6950 5100 7550 5100
$Comp
L custom:W25Q128JV U4
U 1 1 609A49E2
P 9150 4650
F 0 "U4" H 9175 5025 50  0000 C CNN
F 1 "W25Q128JV" H 9175 4934 50  0000 C CNN
F 2 "Package_SO:SOIC-8_5.275x5.275mm_P1.27mm" H 9150 4400 50  0001 C CNN
F 3 "" H 9150 4400 50  0001 C CNN
	1    9150 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4600 10000 4600
Wire Wire Line
	2450 1450 2300 1450
$Comp
L Device:R R3
U 1 1 609868E1
P 6850 4300
F 0 "R3" V 6643 4300 50  0000 C CNN
F 1 "330" V 6734 4300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 6780 4300 50  0001 C CNN
F 3 "~" H 6850 4300 50  0001 C CNN
	1    6850 4300
	0    1    1    0   
$EndComp
Connection ~ 2300 1450
Wire Wire Line
	2300 1450 2150 1450
Wire Wire Line
	6700 4300 6650 4300
Wire Wire Line
	6650 4300 6650 4500
Wire Wire Line
	6650 4900 6650 5100
Text GLabel 4650 2700 0    50   Input ~ 0
GND
$EndSCHEMATC