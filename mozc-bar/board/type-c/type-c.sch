EESchema Schematic File Version 4
LIBS:type-c-cache
EELAYER 26 0
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
L power:GND #PWR01
U 1 1 5F9AF56B
P 4000 3000
F 0 "#PWR01" H 4000 2750 50  0001 C CNN
F 1 "GND" H 4000 2850 50  0000 C CNN
F 2 "" H 4000 3000 50  0001 C CNN
F 3 "" H 4000 3000 50  0001 C CNN
	1    4000 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F9AF593
P 7150 2900
F 0 "#PWR02" H 7150 2650 50  0001 C CNN
F 1 "GND" H 7150 2750 50  0000 C CNN
F 2 "" H 7150 2900 50  0001 C CNN
F 3 "" H 7150 2900 50  0001 C CNN
	1    7150 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3150 5500 3150
Wire Wire Line
	5100 2000 6750 2000
Wire Wire Line
	6800 1950 5050 1950
Wire Wire Line
	5150 2150 5500 2150
Wire Wire Line
	5100 3350 5500 3350
$Comp
L power:GND #PWR05
U 1 1 5F9AF6FF
P 5350 3650
F 0 "#PWR05" H 5350 3400 50  0001 C CNN
F 1 "GND" H 5350 3500 50  0000 C CNN
F 2 "" H 5350 3650 50  0001 C CNN
F 3 "" H 5350 3650 50  0001 C CNN
	1    5350 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3450 5350 3550
NoConn ~ 6500 2250
Wire Wire Line
	6500 2150 6700 2150
Wire Wire Line
	5500 2250 5450 2250
Wire Wire Line
	5450 2350 5500 2350
Wire Wire Line
	5500 2450 5450 2450
Wire Wire Line
	5450 2550 5500 2550
Wire Wire Line
	5500 2650 5450 2650
Wire Wire Line
	5450 2750 5500 2750
Wire Wire Line
	5500 2850 5450 2850
Wire Wire Line
	5450 2950 5500 2950
Text GLabel 5450 2250 0    60   Input ~ 0
SW1
Text GLabel 5450 2350 0    60   Input ~ 0
SW2
Text GLabel 5450 2450 0    60   Input ~ 0
SW3
Text GLabel 5450 2550 0    60   Input ~ 0
SW4
Text GLabel 5450 2650 0    60   Input ~ 0
SW5
Text GLabel 5450 2750 0    60   Input ~ 0
SW6
$Comp
L power:GND #PWR06
U 1 1 5F9AFACB
P 7150 5350
F 0 "#PWR06" H 7150 5100 50  0001 C CNN
F 1 "GND" H 7150 5200 50  0000 C CNN
F 2 "" H 7150 5350 50  0001 C CNN
F 3 "" H 7150 5350 50  0001 C CNN
	1    7150 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5250 7150 5300
Wire Wire Line
	6650 5300 6900 5300
Wire Wire Line
	6650 5300 6650 5250
Wire Wire Line
	6900 5250 6900 5300
Connection ~ 6900 5300
Connection ~ 7150 5300
Wire Wire Line
	7400 5300 7400 5250
Wire Wire Line
	7650 5300 7650 5250
Connection ~ 7400 5300
Wire Wire Line
	7900 5300 7900 5250
Connection ~ 7650 5300
Wire Wire Line
	8150 5300 8150 5250
Connection ~ 7900 5300
Wire Wire Line
	8400 5300 8400 5250
Connection ~ 8150 5300
$Comp
L power:VCC #PWR07
U 1 1 5F9AFFCA
P 7200 3650
F 0 "#PWR07" H 7200 3500 50  0001 C CNN
F 1 "VCC" H 7200 3800 50  0000 C CNN
F 2 "" H 7200 3650 50  0001 C CNN
F 3 "" H 7200 3650 50  0001 C CNN
	1    7200 3650
	1    0    0    -1  
$EndComp
Text GLabel 5450 2950 0    60   Input ~ 0
SW8
Text GLabel 7400 4750 0    60   Input ~ 0
SW1
Text GLabel 7150 4750 0    60   Input ~ 0
SW2
Text GLabel 6900 4750 0    60   Input ~ 0
SW3
Text GLabel 6650 4750 0    60   Input ~ 0
SW4
Text GLabel 8400 4750 0    60   Input ~ 0
SW5
Text GLabel 8150 4750 0    60   Input ~ 0
SW6
Text GLabel 5450 2850 0    60   Input ~ 0
SW7
Text GLabel 7900 4750 0    60   Input ~ 0
SW7
Text GLabel 7650 4750 0    60   Input ~ 0
SW8
$Comp
L power:PWR_FLAG #FLG08
U 1 1 5F9B078E
P 3800 4050
F 0 "#FLG08" H 3800 4125 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 4200 50  0000 C CNN
F 2 "" H 3800 4050 50  0001 C CNN
F 3 "" H 3800 4050 50  0001 C CNN
	1    3800 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4050 3800 4150
$Comp
L power:PWR_FLAG #FLG09
U 1 1 5F9B08D4
P 4250 4050
F 0 "#FLG09" H 4250 4125 50  0001 C CNN
F 1 "PWR_FLAG" H 4250 4200 50  0000 C CNN
F 2 "" H 4250 4050 50  0001 C CNN
F 3 "" H 4250 4050 50  0001 C CNN
	1    4250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4050 4400 4050
$Comp
L power:VCC #PWR010
U 1 1 5F9B0AC5
P 3950 4150
F 0 "#PWR010" H 3950 4000 50  0001 C CNN
F 1 "VCC" H 3950 4300 50  0000 C CNN
F 2 "" H 3950 4150 50  0001 C CNN
F 3 "" H 3950 4150 50  0001 C CNN
	1    3950 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4150 3950 4150
$Comp
L power:GND #PWR011
U 1 1 5F9B0B68
P 4400 4050
F 0 "#PWR011" H 4400 3800 50  0001 C CNN
F 1 "GND" H 4400 3900 50  0000 C CNN
F 2 "" H 4400 4050 50  0001 C CNN
F 3 "" H 4400 4050 50  0001 C CNN
	1    4400 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5F9B0C77
P 6550 2650
F 0 "C1" H 6575 2750 50  0000 L CNN
F 1 "C" H 6575 2550 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 6588 2500 50  0001 C CNN
F 3 "" H 6550 2650 50  0001 C CNN
	1    6550 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5300 7150 5300
Wire Wire Line
	7150 5300 7150 5350
Wire Wire Line
	7150 5300 7400 5300
Wire Wire Line
	7400 5300 7650 5300
Wire Wire Line
	7650 5300 7900 5300
Wire Wire Line
	7900 5300 8150 5300
Wire Wire Line
	8150 5300 8400 5300
$Comp
L type-c-rescue:74HC165-74xx U1
U 1 1 5FB03AD0
P 6000 2750
F 0 "U1" H 6000 3831 50  0000 C CNN
F 1 "74HC165" H 6000 3740 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 6000 2750 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 6000 2750 50  0001 C CNN
	1    6000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3450 5500 3450
Wire Wire Line
	5550 3750 5550 3550
Wire Wire Line
	5550 3550 5350 3550
Connection ~ 5350 3550
Wire Wire Line
	5350 3550 5350 3650
Wire Wire Line
	6000 1850 6600 1850
$Comp
L power:VCC #PWR04
U 1 1 5F9AF5D4
P 6600 1750
F 0 "#PWR04" H 6600 1600 50  0001 C CNN
F 1 "VCC" H 6600 1900 50  0000 C CNN
F 2 "" H 6600 1750 50  0001 C CNN
F 3 "" H 6600 1750 50  0001 C CNN
	1    6600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1750 6600 1850
$Comp
L power:VCC #PWR0101
U 1 1 5FB8D1CC
P 7050 2100
F 0 "#PWR0101" H 7050 1950 50  0001 C CNN
F 1 "VCC" H 7050 2250 50  0000 C CNN
F 2 "" H 7050 2100 50  0001 C CNN
F 3 "" H 7050 2100 50  0001 C CNN
	1    7050 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2150 6700 2650
$Comp
L Device:R R1
U 1 1 5FBC6DCE
P 5150 1700
F 0 "R1" H 5080 1654 50  0000 R CNN
F 1 "100k" H 5080 1745 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5080 1700 50  0001 C CNN
F 3 "~" H 5150 1700 50  0001 C CNN
	1    5150 1700
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 5FBCB113
P 5150 1550
F 0 "#PWR0102" H 5150 1400 50  0001 C CNN
F 1 "VCC" H 5150 1700 50  0000 C CNN
F 2 "" H 5150 1550 50  0001 C CNN
F 3 "" H 5150 1550 50  0001 C CNN
	1    5150 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2150 5150 1850
Connection ~ 5150 2150
$Comp
L Switch:SW_Push SW2
U 1 1 5FC01AC9
P 6900 5050
F 0 "SW2" V 6946 5002 50  0000 R CNN
F 1 "SW_Push" V 6855 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6900 5250 50  0001 C CNN
F 3 "~" H 6900 5250 50  0001 C CNN
	1    6900 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5FC01D44
P 7150 5050
F 0 "SW3" V 7196 5002 50  0000 R CNN
F 1 "SW_Push" V 7105 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7150 5250 50  0001 C CNN
F 3 "~" H 7150 5250 50  0001 C CNN
	1    7150 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 5FC02175
P 7400 5050
F 0 "SW4" V 7446 5002 50  0000 R CNN
F 1 "SW_Push" V 7355 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7400 5250 50  0001 C CNN
F 3 "~" H 7400 5250 50  0001 C CNN
	1    7400 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW6
U 1 1 5FC02807
P 7900 5050
F 0 "SW6" V 7946 5002 50  0000 R CNN
F 1 "SW_Push" V 7855 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7900 5250 50  0001 C CNN
F 3 "~" H 7900 5250 50  0001 C CNN
	1    7900 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW7
U 1 1 5FC02A93
P 8150 5050
F 0 "SW7" V 8196 5002 50  0000 R CNN
F 1 "SW_Push" V 8105 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8150 5250 50  0001 C CNN
F 3 "~" H 8150 5250 50  0001 C CNN
	1    8150 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 5FC02D04
P 8400 5050
F 0 "SW8" V 8446 5002 50  0000 R CNN
F 1 "SW_Push" V 8355 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 8400 5250 50  0001 C CNN
F 3 "~" H 8400 5250 50  0001 C CNN
	1    8400 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R_Network08_US RN1
U 1 1 5FC139AE
P 7600 3900
F 0 "RN1" H 7988 3946 50  0000 L CNN
F 1 "100k" H 7988 3855 50  0000 L CNN
F 2 "Resistor_THT:R_Array_SIP9" V 8075 3900 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 7600 3900 50  0001 C CNN
	1    7600 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3650 7200 3700
Wire Wire Line
	6600 1850 6600 2350
Wire Wire Line
	6600 2350 6550 2350
Wire Wire Line
	6550 2350 6550 2500
Connection ~ 6600 1850
Wire Wire Line
	6550 2800 6550 3750
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5FD981C4
P 7850 2550
F 0 "J2" H 7822 2432 50  0000 R CNN
F 1 "Conn_01x06_Male" H 7822 2523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Horizontal" H 7850 2550 50  0001 C CNN
F 3 "~" H 7850 2550 50  0001 C CNN
	1    7850 2550
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5FD9930E
P 3100 2550
F 0 "J1" H 2992 2025 50  0000 C CNN
F 1 "Conn_01x06_Female" H 2992 2116 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Horizontal" H 3100 2550 50  0001 C CNN
F 3 "~" H 3100 2550 50  0001 C CNN
	1    3100 2550
	-1   0    0    1   
$EndComp
NoConn ~ 7650 2350
NoConn ~ 3300 2350
$Comp
L power:VCC #PWR03
U 1 1 5F9AF5B3
P 3900 2050
F 0 "#PWR03" H 3900 1900 50  0001 C CNN
F 1 "VCC" H 3900 2200 50  0000 C CNN
F 2 "" H 3900 2050 50  0001 C CNN
F 3 "" H 3900 2050 50  0001 C CNN
	1    3900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2000 5100 2550
Wire Wire Line
	4100 2650 4100 2950
Wire Wire Line
	4100 2950 5150 2950
Wire Wire Line
	5150 2150 5150 2950
Connection ~ 5100 2550
Wire Wire Line
	5100 2550 5100 3350
Wire Wire Line
	7150 2250 7150 2900
Wire Wire Line
	7050 2100 7050 2750
Wire Wire Line
	3900 2050 3900 2750
Wire Wire Line
	4000 2250 4000 3000
Wire Wire Line
	7050 2750 7650 2750
Wire Wire Line
	7150 2250 7650 2250
Text Label 7300 2650 0    50   ~ 0
DATA_OUT
Text Label 7400 2550 0    50   ~ 0
CLK_IN
Text Label 7350 2450 0    50   ~ 0
LOAD_IN
Wire Wire Line
	3300 2250 4000 2250
Wire Wire Line
	3300 2650 4100 2650
Wire Wire Line
	3300 2750 3900 2750
Text Label 3350 2450 0    50   ~ 0
LOAD_OUT
Text Label 3350 2550 0    50   ~ 0
CLK_OUT
Text Label 3350 2650 0    50   ~ 0
DATA_IN
$Comp
L Mechanical:MountingHole H1
U 1 1 618CEE47
P 10100 3850
F 0 "H1" H 10200 3896 50  0000 L CNN
F 1 "MountingHole" H 10200 3805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10100 3850 50  0001 C CNN
F 3 "~" H 10100 3850 50  0001 C CNN
	1    10100 3850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5FC0255B
P 7650 5050
F 0 "SW5" V 7696 5002 50  0000 R CNN
F 1 "SW_Push" V 7605 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 7650 5250 50  0001 C CNN
F 3 "~" H 7650 5250 50  0001 C CNN
	1    7650 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5FC00348
P 6650 5050
F 0 "SW1" V 6696 5002 50  0000 R CNN
F 1 "SW_Push" V 6605 5002 50  0000 R CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 6650 5250 50  0001 C CNN
F 3 "~" H 6650 5250 50  0001 C CNN
	1    6650 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 4850 6650 4300
Wire Wire Line
	6650 4300 7200 4300
Wire Wire Line
	7200 4300 7200 4100
Wire Wire Line
	6900 4850 6900 4350
Wire Wire Line
	6900 4350 7300 4350
Wire Wire Line
	7300 4350 7300 4100
Wire Wire Line
	7150 4850 7150 4400
Wire Wire Line
	7150 4400 7400 4400
Wire Wire Line
	7400 4400 7400 4100
Wire Wire Line
	7400 4850 7400 4500
Wire Wire Line
	7400 4500 7500 4500
Wire Wire Line
	7500 4500 7500 4100
Wire Wire Line
	7650 4850 7650 4500
Wire Wire Line
	7650 4500 7600 4500
Wire Wire Line
	7600 4500 7600 4100
Wire Wire Line
	8400 4850 8400 4300
Wire Wire Line
	8400 4300 7900 4300
Wire Wire Line
	7900 4300 7900 4100
Wire Wire Line
	8150 4850 8150 4400
Wire Wire Line
	8150 4400 7800 4400
Wire Wire Line
	7800 4400 7800 4100
Wire Wire Line
	7900 4850 7900 4450
Wire Wire Line
	7900 4450 7700 4450
Wire Wire Line
	7700 4450 7700 4100
Connection ~ 5050 2450
Wire Wire Line
	5050 2450 5050 3150
Wire Wire Line
	5050 1950 5050 2450
Wire Wire Line
	3300 2450 5050 2450
Wire Wire Line
	3300 2550 5100 2550
Wire Wire Line
	6750 2000 6750 2550
Wire Wire Line
	6800 1950 6800 2450
Connection ~ 6000 3750
Wire Wire Line
	6000 3750 6550 3750
Wire Wire Line
	6000 3750 5550 3750
Wire Wire Line
	6750 2550 7650 2550
Wire Wire Line
	6800 2450 7650 2450
Wire Wire Line
	6700 2650 7650 2650
$Comp
L Mechanical:MountingHole H6
U 1 1 62CF2D41
P 9800 4350
F 0 "H6" H 9900 4396 50  0000 L CNN
F 1 "MountingHole" H 9900 4305 50  0000 L CNN
F 2 "holes:4mm" H 9800 4350 50  0001 C CNN
F 3 "~" H 9800 4350 50  0001 C CNN
	1    9800 4350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H7
U 1 1 62CF2DD5
P 9800 4650
F 0 "H7" H 9900 4696 50  0000 L CNN
F 1 "MountingHole" H 9900 4605 50  0000 L CNN
F 2 "holes:3mm" H 9800 4650 50  0001 C CNN
F 3 "~" H 9800 4650 50  0001 C CNN
	1    9800 4650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H8
U 1 1 62CF2E34
P 9800 4900
F 0 "H8" H 9900 4946 50  0000 L CNN
F 1 "MountingHole" H 9900 4855 50  0000 L CNN
F 2 "holes:4mm" H 9800 4900 50  0001 C CNN
F 3 "~" H 9800 4900 50  0001 C CNN
	1    9800 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H9
U 1 1 62CF2E98
P 9800 5200
F 0 "H9" H 9900 5246 50  0000 L CNN
F 1 "MountingHole" H 9900 5155 50  0000 L CNN
F 2 "holes:3mm" H 9800 5200 50  0001 C CNN
F 3 "~" H 9800 5200 50  0001 C CNN
	1    9800 5200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H10
U 1 1 62CF2F85
P 10550 4350
F 0 "H10" H 10650 4396 50  0000 L CNN
F 1 "MountingHole" H 10650 4305 50  0000 L CNN
F 2 "holes:4mm" H 10550 4350 50  0001 C CNN
F 3 "~" H 10550 4350 50  0001 C CNN
	1    10550 4350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H11
U 1 1 62CF2F8C
P 10550 4650
F 0 "H11" H 10650 4696 50  0000 L CNN
F 1 "MountingHole" H 10650 4605 50  0000 L CNN
F 2 "holes:3mm" H 10550 4650 50  0001 C CNN
F 3 "~" H 10550 4650 50  0001 C CNN
	1    10550 4650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H12
U 1 1 62CF2F93
P 10550 4900
F 0 "H12" H 10650 4946 50  0000 L CNN
F 1 "MountingHole" H 10650 4855 50  0000 L CNN
F 2 "holes:4mm" H 10550 4900 50  0001 C CNN
F 3 "~" H 10550 4900 50  0001 C CNN
	1    10550 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H13
U 1 1 62CF2F9A
P 10550 5200
F 0 "H13" H 10650 5246 50  0000 L CNN
F 1 "MountingHole" H 10650 5155 50  0000 L CNN
F 2 "holes:3mm" H 10550 5200 50  0001 C CNN
F 3 "~" H 10550 5200 50  0001 C CNN
	1    10550 5200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 62CF7C5D
P 9050 4350
F 0 "H2" H 9150 4396 50  0000 L CNN
F 1 "MountingHole" H 9150 4305 50  0000 L CNN
F 2 "holes:4mm" H 9050 4350 50  0001 C CNN
F 3 "~" H 9050 4350 50  0001 C CNN
	1    9050 4350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 62CF7C64
P 9050 4650
F 0 "H3" H 9150 4696 50  0000 L CNN
F 1 "MountingHole" H 9150 4605 50  0000 L CNN
F 2 "holes:3mm" H 9050 4650 50  0001 C CNN
F 3 "~" H 9050 4650 50  0001 C CNN
	1    9050 4650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 62CF7C6B
P 9050 4900
F 0 "H4" H 9150 4946 50  0000 L CNN
F 1 "MountingHole" H 9150 4855 50  0000 L CNN
F 2 "holes:4mm" H 9050 4900 50  0001 C CNN
F 3 "~" H 9050 4900 50  0001 C CNN
	1    9050 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 62CF7C72
P 9050 5200
F 0 "H5" H 9150 5246 50  0000 L CNN
F 1 "MountingHole" H 9150 5155 50  0000 L CNN
F 2 "holes:3mm" H 9050 5200 50  0001 C CNN
F 3 "~" H 9050 5200 50  0001 C CNN
	1    9050 5200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
