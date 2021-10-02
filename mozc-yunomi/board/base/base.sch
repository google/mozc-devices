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
L Connector:Conn_01x04_Male J13
U 1 1 5DCABE39
P 7550 3250
F 0 "J13" H 7658 3531 50  0000 C CNN
F 1 "Conn_01x04_Male" H 7658 3440 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7550 3250 50  0001 C CNN
F 3 "~" H 7550 3250 50  0001 C CNN
	1    7550 3250
	1    0    0    -1  
$EndComp
Text GLabel 7750 3250 2    50   Input ~ 0
D-
Text GLabel 7750 3350 2    50   Input ~ 0
D+
$Comp
L power:+5V #PWR09
U 1 1 5DCAE395
P 6600 3250
F 0 "#PWR09" H 6600 3100 50  0001 C CNN
F 1 "+5V" H 6615 3423 50  0000 C CNN
F 2 "" H 6600 3250 50  0001 C CNN
F 3 "" H 6600 3250 50  0001 C CNN
	1    6600 3250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DCAE6E0
P 6600 3350
F 0 "#FLG01" H 6600 3425 50  0001 C CNN
F 1 "PWR_FLAG" H 6600 3523 50  0000 C CNN
F 2 "" H 6600 3350 50  0001 C CNN
F 3 "~" H 6600 3350 50  0001 C CNN
	1    6600 3350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5DCAEBC2
P 6900 3350
F 0 "#PWR010" H 6900 3100 50  0001 C CNN
F 1 "GND" H 6905 3177 50  0000 C CNN
F 2 "" H 6900 3350 50  0001 C CNN
F 3 "" H 6900 3350 50  0001 C CNN
	1    6900 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3350 6600 3250
$Comp
L power:+5V #PWR03
U 1 1 5DCB1123
P 3100 1050
F 0 "#PWR03" H 3100 900 50  0001 C CNN
F 1 "+5V" H 3115 1223 50  0000 C CNN
F 2 "" H 3100 1050 50  0001 C CNN
F 3 "" H 3100 1050 50  0001 C CNN
	1    3100 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5DCB198A
P 3000 1050
F 0 "#PWR02" H 3000 900 50  0001 C CNN
F 1 "+5V" H 3015 1223 50  0000 C CNN
F 2 "" H 3000 1050 50  0001 C CNN
F 3 "" H 3000 1050 50  0001 C CNN
	1    3000 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5DCB1D13
P 2900 1050
F 0 "#PWR01" H 2900 900 50  0001 C CNN
F 1 "+5V" H 2915 1223 50  0000 C CNN
F 2 "" H 2900 1050 50  0001 C CNN
F 3 "" H 2900 1050 50  0001 C CNN
	1    2900 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5DCB1F46
P 2150 1250
F 0 "R1" V 2357 1250 50  0000 C CNN
F 1 "10K" V 2266 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 2080 1250 50  0001 C CNN
F 3 "~" H 2150 1250 50  0001 C CNN
	1    2150 1250
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5DCB245E
P 2000 1250
F 0 "#PWR04" H 2000 1100 50  0001 C CNN
F 1 "+5V" V 2015 1378 50  0000 L CNN
F 2 "" H 2000 1250 50  0001 C CNN
F 3 "" H 2000 1250 50  0001 C CNN
	1    2000 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DCB368B
P 2250 1950
F 0 "C1" V 2502 1950 50  0000 C CNN
F 1 "0.1uF" V 2411 1950 50  0000 C CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 2288 1800 50  0001 C CNN
F 3 "~" H 2250 1950 50  0001 C CNN
	1    2250 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5DCB5F52
P 2100 1950
F 0 "#PWR05" H 2100 1700 50  0001 C CNN
F 1 "GND" H 2105 1777 50  0000 C CNN
F 2 "" H 2100 1950 50  0001 C CNN
F 3 "" H 2100 1950 50  0001 C CNN
	1    2100 1950
	1    0    0    -1  
$EndComp
Text GLabel 2400 1550 0    50   Input ~ 0
XTAL1
Text GLabel 2400 1750 0    50   Input ~ 0
XTAL2
Text GLabel 3600 1350 2    50   Input ~ 0
ROW0
Text GLabel 4100 1300 2    50   Input ~ 0
ROW1
Text GLabel 4100 1500 2    50   Input ~ 0
ROW2
Text GLabel 4100 1700 2    50   Input ~ 0
ROW3
Text GLabel 3600 1750 2    50   Input ~ 0
ROW4
Text GLabel 3600 2550 2    50   Input ~ 0
COL0
Text GLabel 3600 2650 2    50   Input ~ 0
COL1
Text GLabel 3600 2750 2    50   Input ~ 0
COL2
Text GLabel 3600 2850 2    50   Input ~ 0
COL3
Text GLabel 3600 2950 2    50   Input ~ 0
COL4
Text GLabel 3600 3050 2    50   Input ~ 0
COL5
NoConn ~ 3600 1850
NoConn ~ 3600 1950
NoConn ~ 3600 2050
NoConn ~ 3600 2250
NoConn ~ 3600 2350
NoConn ~ 3600 3150
NoConn ~ 3600 3250
NoConn ~ 3600 3550
NoConn ~ 3600 3850
NoConn ~ 3600 3950
$Comp
L power:+5V #PWR06
U 1 1 5DCC0F92
P 2400 2150
F 0 "#PWR06" H 2400 2000 50  0001 C CNN
F 1 "+5V" H 2415 2323 50  0000 C CNN
F 2 "" H 2400 2150 50  0001 C CNN
F 3 "" H 2400 2150 50  0001 C CNN
	1    2400 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5DCC2D05
P 2250 2650
F 0 "C2" V 1998 2650 50  0000 C CNN
F 1 "1uF" V 2089 2650 50  0000 C CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 2288 2500 50  0001 C CNN
F 3 "~" H 2250 2650 50  0001 C CNN
	1    2250 2650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5DCC34C8
P 2100 2650
F 0 "#PWR07" H 2100 2400 50  0001 C CNN
F 1 "GND" H 2105 2477 50  0000 C CNN
F 2 "" H 2100 2650 50  0001 C CNN
F 3 "" H 2100 2650 50  0001 C CNN
	1    2100 2650
	1    0    0    -1  
$EndComp
Text GLabel 5000 3100 0    50   Input ~ 0
XTAL1
Text GLabel 5000 3400 0    50   Input ~ 0
XTAL2
$Comp
L Device:Crystal Y1
U 1 1 5DCCC025
P 5350 3250
F 0 "Y1" V 5304 3381 50  0000 L CNN
F 1 "16MHz" V 5395 3381 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 5350 3250 50  0001 C CNN
F 3 "~" H 5350 3250 50  0001 C CNN
	1    5350 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 3100 5350 3100
Wire Wire Line
	5000 3400 5350 3400
$Comp
L Device:C C3
U 1 1 5DCCE1D2
P 5800 3100
F 0 "C3" V 5548 3100 50  0000 C CNN
F 1 "C" V 5639 3100 50  0000 C CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5838 2950 50  0001 C CNN
F 3 "~" H 5800 3100 50  0001 C CNN
	1    5800 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 5DCCE6AD
P 5800 3400
F 0 "C4" V 5548 3400 50  0000 C CNN
F 1 "C" V 5639 3400 50  0000 C CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5838 3250 50  0001 C CNN
F 3 "~" H 5800 3400 50  0001 C CNN
	1    5800 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 3400 5350 3400
Connection ~ 5350 3400
Wire Wire Line
	5350 3100 5650 3100
Connection ~ 5350 3100
$Comp
L power:GND #PWR012
U 1 1 5DCCF18E
P 6150 3400
F 0 "#PWR012" H 6150 3150 50  0001 C CNN
F 1 "GND" H 6155 3227 50  0000 C CNN
F 2 "" H 6150 3400 50  0001 C CNN
F 3 "" H 6150 3400 50  0001 C CNN
	1    6150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3400 5950 3400
Wire Wire Line
	5950 3100 6150 3100
Wire Wire Line
	6150 3100 6150 3400
Connection ~ 6150 3400
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5DCD72B6
P 4900 1400
F 0 "J1" V 4962 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 5053 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4900 1400 50  0001 C CNN
F 3 "~" H 4900 1400 50  0001 C CNN
	1    4900 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5DCD8CDD
P 5800 1400
F 0 "J2" V 5862 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 5953 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5800 1400 50  0001 C CNN
F 3 "~" H 5800 1400 50  0001 C CNN
	1    5800 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5DCD9116
P 6700 1400
F 0 "J3" V 6762 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 6853 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6700 1400 50  0001 C CNN
F 3 "~" H 6700 1400 50  0001 C CNN
	1    6700 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5DCD9433
P 7600 1400
F 0 "J4" V 7662 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 7753 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7600 1400 50  0001 C CNN
F 3 "~" H 7600 1400 50  0001 C CNN
	1    7600 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5DCD9738
P 8500 1400
F 0 "J5" V 8562 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 8653 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8500 1400 50  0001 C CNN
F 3 "~" H 8500 1400 50  0001 C CNN
	1    8500 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5DCDA07A
P 9400 1400
F 0 "J6" V 9462 1444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 9553 1444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9400 1400 50  0001 C CNN
F 3 "~" H 9400 1400 50  0001 C CNN
	1    9400 1400
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 5DCDA4A0
P 4900 2100
F 0 "J7" V 4962 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 5053 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4900 2100 50  0001 C CNN
F 3 "~" H 4900 2100 50  0001 C CNN
	1    4900 2100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J8
U 1 1 5DCDA871
P 5800 2100
F 0 "J8" V 5862 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 5953 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5800 2100 50  0001 C CNN
F 3 "~" H 5800 2100 50  0001 C CNN
	1    5800 2100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 5DCDAC54
P 6700 2100
F 0 "J9" V 6762 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 6853 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6700 2100 50  0001 C CNN
F 3 "~" H 6700 2100 50  0001 C CNN
	1    6700 2100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 5DCDB049
P 7600 2100
F 0 "J10" V 7662 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 7753 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7600 2100 50  0001 C CNN
F 3 "~" H 7600 2100 50  0001 C CNN
	1    7600 2100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 5DCDB4D0
P 8500 2100
F 0 "J11" V 8562 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 8653 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8500 2100 50  0001 C CNN
F 3 "~" H 8500 2100 50  0001 C CNN
	1    8500 2100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 5DCDB9C4
P 9400 2100
F 0 "J12" V 9462 2144 50  0000 L CNN
F 1 "Conn_01x02_Male" V 9553 2144 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9400 2100 50  0001 C CNN
F 3 "~" H 9400 2100 50  0001 C CNN
	1    9400 2100
	0    1    1    0   
$EndComp
Text GLabel 4900 1600 3    50   Input ~ 0
ROW0
Text GLabel 4800 1600 3    50   Input ~ 0
COL0
Text GLabel 5700 1600 3    50   Input ~ 0
COL1
Text GLabel 5800 1600 3    50   Input ~ 0
ROW1
Text GLabel 6600 1600 3    50   Input ~ 0
COL2
Text GLabel 6700 1600 3    50   Input ~ 0
ROW2
Text GLabel 7500 1600 3    50   Input ~ 0
COL3
Text GLabel 7600 1600 3    50   Input ~ 0
ROW3
Text GLabel 8400 1600 3    50   Input ~ 0
COL4
Text GLabel 8500 1600 3    50   Input ~ 0
ROW4
Text GLabel 9300 1600 3    50   Input ~ 0
COL5
NoConn ~ 9400 1600
NoConn ~ 9400 2300
NoConn ~ 8500 2300
NoConn ~ 7600 2300
NoConn ~ 6700 2300
NoConn ~ 5800 2300
NoConn ~ 4900 2300
Text GLabel 4800 2300 3    50   Input ~ 0
COL0
Text GLabel 5700 2300 3    50   Input ~ 0
COL1
Text GLabel 6600 2300 3    50   Input ~ 0
COL2
Text GLabel 7500 2300 3    50   Input ~ 0
COL3
Text GLabel 8400 2300 3    50   Input ~ 0
COL4
Text GLabel 9300 2300 3    50   Input ~ 0
COL5
$Comp
L power:+5V #PWR08
U 1 1 5DD38CC3
P 8050 3150
F 0 "#PWR08" H 8050 3000 50  0001 C CNN
F 1 "+5V" H 8065 3323 50  0000 C CNN
F 2 "" H 8050 3150 50  0001 C CNN
F 3 "" H 8050 3150 50  0001 C CNN
	1    8050 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5DD39183
P 8050 3450
F 0 "#PWR013" H 8050 3200 50  0001 C CNN
F 1 "GND" H 8055 3277 50  0000 C CNN
F 2 "" H 8050 3450 50  0001 C CNN
F 3 "" H 8050 3450 50  0001 C CNN
	1    8050 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 3450 7750 3450
Wire Wire Line
	7750 3150 8050 3150
NoConn ~ 3600 3750
Text GLabel 8750 3200 0    50   Input ~ 0
MISO
Text GLabel 8750 3300 0    50   Input ~ 0
SCK
Text GLabel 8750 3400 0    50   Input ~ 0
RST
Text GLabel 9250 3300 2    50   Input ~ 0
MOSI
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J14
U 1 1 5DCBBCF7
P 8950 3300
F 0 "J14" H 9000 3617 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 9000 3526 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 8950 3300 50  0001 C CNN
F 3 "~" H 8950 3300 50  0001 C CNN
	1    8950 3300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 5DCC3C84
P 9550 3200
F 0 "#PWR0101" H 9550 3050 50  0001 C CNN
F 1 "+5V" H 9565 3373 50  0000 C CNN
F 2 "" H 9550 3200 50  0001 C CNN
F 3 "" H 9550 3200 50  0001 C CNN
	1    9550 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5DCC4385
P 9550 3400
F 0 "#PWR0102" H 9550 3150 50  0001 C CNN
F 1 "GND" H 9555 3227 50  0000 C CNN
F 2 "" H 9550 3400 50  0001 C CNN
F 3 "" H 9550 3400 50  0001 C CNN
	1    9550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 3400 9250 3400
Wire Wire Line
	9250 3200 9550 3200
$Comp
L power:GND #PWR016
U 1 1 5DCB09C1
P 2450 4650
F 0 "#PWR016" H 2450 4400 50  0001 C CNN
F 1 "GND" H 2455 4477 50  0000 C CNN
F 2 "" H 2450 4650 50  0001 C CNN
F 3 "" H 2450 4650 50  0001 C CNN
	1    2450 4650
	1    0    0    -1  
$EndComp
Text GLabel 4100 1400 2    50   Input ~ 0
SCK
Text GLabel 4100 1600 2    50   Input ~ 0
MOSI
Text GLabel 4100 1800 2    50   Input ~ 0
MISO
Wire Wire Line
	4100 1300 3900 1300
Wire Wire Line
	3900 1300 3900 1400
Wire Wire Line
	3900 1450 3600 1450
Wire Wire Line
	4100 1400 3900 1400
Connection ~ 3900 1400
Wire Wire Line
	3900 1400 3900 1450
Wire Wire Line
	4100 1500 3900 1500
Wire Wire Line
	3900 1500 3900 1550
Wire Wire Line
	3900 1600 4100 1600
Wire Wire Line
	3900 1550 3600 1550
Connection ~ 3900 1550
Wire Wire Line
	3900 1550 3900 1600
Wire Wire Line
	3600 1650 3900 1650
Wire Wire Line
	3900 1650 3900 1700
Wire Wire Line
	3900 1800 4100 1800
Wire Wire Line
	4100 1700 3900 1700
Connection ~ 3900 1700
Wire Wire Line
	3900 1700 3900 1800
Text GLabel 2300 1350 0    50   Input ~ 0
RST
Wire Wire Line
	2300 1250 2350 1250
Wire Wire Line
	2350 1250 2350 1350
Wire Wire Line
	2350 1350 2300 1350
Wire Wire Line
	2350 1350 2400 1350
Connection ~ 2350 1350
$Comp
L Connector:Conn_01x01_Male J15
U 1 1 5DCC19AC
P 4900 4100
F 0 "J15" H 5008 4281 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5008 4190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4900 4100 50  0001 C CNN
F 3 "~" H 4900 4100 50  0001 C CNN
	1    4900 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J16
U 1 1 5DCC25FC
P 5600 4100
F 0 "J16" H 5708 4281 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5708 4190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5600 4100 50  0001 C CNN
F 3 "~" H 5600 4100 50  0001 C CNN
	1    5600 4100
	1    0    0    -1  
$EndComp
NoConn ~ 5100 4100
NoConn ~ 5800 4100
$Comp
L Connector:Conn_01x01_Male J17
U 1 1 5DCC9433
P 6300 4100
F 0 "J17" H 6408 4281 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6408 4190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6300 4100 50  0001 C CNN
F 3 "~" H 6300 4100 50  0001 C CNN
	1    6300 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J18
U 1 1 5DCC9439
P 7000 4100
F 0 "J18" H 7108 4281 50  0000 C CNN
F 1 "Conn_01x01_Male" H 7108 4190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7000 4100 50  0001 C CNN
F 3 "~" H 7000 4100 50  0001 C CNN
	1    7000 4100
	1    0    0    -1  
$EndComp
NoConn ~ 6500 4100
NoConn ~ 7200 4100
$Comp
L Connector:Conn_01x01_Male J19
U 1 1 5DCCB27E
P 4900 4450
F 0 "J19" H 5008 4631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5008 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4900 4450 50  0001 C CNN
F 3 "~" H 4900 4450 50  0001 C CNN
	1    4900 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J20
U 1 1 5DCCB284
P 5600 4450
F 0 "J20" H 5708 4631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5708 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5600 4450 50  0001 C CNN
F 3 "~" H 5600 4450 50  0001 C CNN
	1    5600 4450
	1    0    0    -1  
$EndComp
NoConn ~ 5100 4450
NoConn ~ 5800 4450
$Comp
L Connector:Conn_01x01_Male J21
U 1 1 5DCCB28C
P 6300 4450
F 0 "J21" H 6408 4631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6408 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6300 4450 50  0001 C CNN
F 3 "~" H 6300 4450 50  0001 C CNN
	1    6300 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J22
U 1 1 5DCCB292
P 7000 4450
F 0 "J22" H 7108 4631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 7108 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7000 4450 50  0001 C CNN
F 3 "~" H 7000 4450 50  0001 C CNN
	1    7000 4450
	1    0    0    -1  
$EndComp
NoConn ~ 6500 4450
NoConn ~ 7200 4450
$Comp
L Connector:Conn_01x01_Male J23
U 1 1 5DCCC0C3
P 4900 4750
F 0 "J23" H 5008 4931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5008 4840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4900 4750 50  0001 C CNN
F 3 "~" H 4900 4750 50  0001 C CNN
	1    4900 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J24
U 1 1 5DCCC0C9
P 5600 4750
F 0 "J24" H 5708 4931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 5708 4840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5600 4750 50  0001 C CNN
F 3 "~" H 5600 4750 50  0001 C CNN
	1    5600 4750
	1    0    0    -1  
$EndComp
NoConn ~ 5100 4750
NoConn ~ 5800 4750
$Comp
L Connector:Conn_01x01_Male J25
U 1 1 5DCCC0D1
P 6300 4750
F 0 "J25" H 6408 4931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 6408 4840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6300 4750 50  0001 C CNN
F 3 "~" H 6300 4750 50  0001 C CNN
	1    6300 4750
	1    0    0    -1  
$EndComp
NoConn ~ 6500 4750
NoConn ~ 3600 3450
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DCD4AE8
P 6900 3200
F 0 "#FLG0101" H 6900 3275 50  0001 C CNN
F 1 "PWR_FLAG" H 6900 3373 50  0000 C CNN
F 2 "" H 6900 3200 50  0001 C CNN
F 3 "~" H 6900 3200 50  0001 C CNN
	1    6900 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3200 6900 3350
$Comp
L Connector:Conn_01x01_Male J26
U 1 1 5DCF3955
P 7000 4750
F 0 "J26" H 7108 4931 50  0000 C CNN
F 1 "Conn_01x01_Male" H 7108 4840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7000 4750 50  0001 C CNN
F 3 "~" H 7000 4750 50  0001 C CNN
	1    7000 4750
	1    0    0    -1  
$EndComp
NoConn ~ 7200 4750
$Comp
L power:+5V #PWR0103
U 1 1 5DCD7038
P 8150 3950
F 0 "#PWR0103" H 8150 3800 50  0001 C CNN
F 1 "+5V" H 8165 4123 50  0000 C CNN
F 2 "" H 8150 3950 50  0001 C CNN
F 3 "" H 8150 3950 50  0001 C CNN
	1    8150 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5DCD76DF
P 8150 4100
F 0 "C5" H 8265 4146 50  0000 L CNN
F 1 "C" H 8265 4055 50  0000 L CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 8188 3950 50  0001 C CNN
F 3 "~" H 8150 4100 50  0001 C CNN
	1    8150 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5DCD804D
P 8150 4250
F 0 "#PWR0104" H 8150 4000 50  0001 C CNN
F 1 "GND" H 8155 4077 50  0000 C CNN
F 2 "" H 8150 4250 50  0001 C CNN
F 3 "" H 8150 4250 50  0001 C CNN
	1    8150 4250
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5DCD7A57
P 3600 4150
F 0 "TP2" V 3554 4338 50  0000 L CNN
F 1 "TestPoint" V 3645 4338 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 3800 4150 50  0001 C CNN
F 3 "~" H 3800 4150 50  0001 C CNN
	1    3600 4150
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 5DCE171F
P 3600 4250
F 0 "TP3" V 3554 4438 50  0000 L CNN
F 1 "TestPoint" V 3645 4438 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 3800 4250 50  0001 C CNN
F 3 "~" H 3800 4250 50  0001 C CNN
	1    3600 4250
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5DCE269D
P 3600 4050
F 0 "TP1" V 3554 4238 50  0000 L CNN
F 1 "TestPoint" V 3645 4238 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 3800 4050 50  0001 C CNN
F 3 "~" H 3800 4050 50  0001 C CNN
	1    3600 4050
	0    1    1    0   
$EndComp
Text GLabel 2100 2450 0    50   Input ~ 0
D-
Text GLabel 2100 2350 0    50   Input ~ 0
D+
$Comp
L Device:R R3
U 1 1 5DCC40A4
P 2250 2450
F 0 "R3" V 2043 2450 50  0000 C CNN
F 1 "22" V 2134 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 2180 2450 50  0001 C CNN
F 3 "~" H 2250 2450 50  0001 C CNN
	1    2250 2450
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5DCC3CA3
P 2250 2350
F 0 "R2" V 2043 2350 50  0000 C CNN
F 1 "22" V 2134 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 2180 2350 50  0001 C CNN
F 3 "~" H 2250 2350 50  0001 C CNN
	1    2250 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 4650 2900 4650
$Comp
L MCU_Microchip_ATmega:ATmega32U4-AU U1
U 1 1 6155AFF4
P 3000 2850
F 0 "U1" H 3000 961 50  0000 C CNN
F 1 "ATmega32U4-AU" H 3000 870 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 3000 2850 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf" H 3000 2850 50  0001 C CNN
	1    3000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4650 2900 4650
Connection ~ 2900 4650
$EndSCHEMATC
