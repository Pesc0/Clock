EESchema Schematic File Version 4
LIBS:clock-cache
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
L MCU_Microchip_ATtiny:ATtiny85-20SU U1
U 1 1 5E06202F
P 3300 4050
F 0 "U1" H 2900 4750 50  0000 R CNN
F 1 "ATtiny85-20SU" H 3150 4650 50  0000 R CNN
F 2 "Package_SO:SOIJ-8_5.3x5.3mm_P1.27mm" H 3300 4050 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3300 4050 50  0001 C CNN
	1    3300 4050
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS3231M U2
U 1 1 5E062847
P 7950 5500
F 0 "U2" H 8900 5200 50  0000 C CNN
F 1 "DS3231M" H 8900 5100 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 7950 4900 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 8220 5550 50  0001 C CNN
	1    7950 5500
	1    0    0    -1  
$EndComp
$Comp
L 7_segment:KW4-56NCWB-P-Y U4
U 1 1 5E064DC8
P 8500 3700
F 0 "U4" V 7650 3600 50  0000 L CNN
F 1 "KW4-56NCWB-P-Y" V 7750 3300 50  0000 L CNN
F 2 "display7seg:7segment" H 8600 3500 50  0001 C CNN
F 3 "" H 8600 3500 50  0001 C CNN
	1    8500 3700
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5E064F5E
P 3300 3450
F 0 "#PWR01" H 3300 3300 50  0001 C CNN
F 1 "+5V" H 3315 3623 50  0000 C CNN
F 2 "" H 3300 3450 50  0001 C CNN
F 3 "" H 3300 3450 50  0001 C CNN
	1    3300 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5E065026
P 7850 4900
F 0 "#PWR011" H 7850 4750 50  0001 C CNN
F 1 "+5V" H 7865 5073 50  0000 C CNN
F 2 "" H 7850 4900 50  0001 C CNN
F 3 "" H 7850 4900 50  0001 C CNN
	1    7850 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5E0650A4
P 9700 1300
F 0 "#PWR013" H 9700 1150 50  0001 C CNN
F 1 "+5V" H 9715 1473 50  0000 C CNN
F 2 "" H 9700 1300 50  0001 C CNN
F 3 "" H 9700 1300 50  0001 C CNN
	1    9700 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5E0650E3
P 3300 4650
F 0 "#PWR02" H 3300 4400 50  0001 C CNN
F 1 "GND" H 3305 4477 50  0000 C CNN
F 2 "" H 3300 4650 50  0001 C CNN
F 3 "" H 3300 4650 50  0001 C CNN
	1    3300 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5E065151
P 7950 6100
F 0 "#PWR012" H 7950 5850 50  0001 C CNN
F 1 "GND" H 7955 5927 50  0000 C CNN
F 2 "" H 7950 6100 50  0001 C CNN
F 3 "" H 7950 6100 50  0001 C CNN
	1    7950 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E0651B7
P 6800 1300
F 0 "#PWR010" H 6800 1050 50  0001 C CNN
F 1 "GND" H 6805 1127 50  0000 C CNN
F 2 "" H 6800 1300 50  0001 C CNN
F 3 "" H 6800 1300 50  0001 C CNN
	1    6800 1300
	1    0    0    -1  
$EndComp
NoConn ~ 8450 5300
NoConn ~ 8450 5600
NoConn ~ 7450 5700
$Comp
L Device:Battery_Cell CR1220
U 1 1 5E0656B3
P 8600 5550
F 0 "CR1220" H 8718 5646 50  0000 L CNN
F 1 "Battery_Cell" H 8718 5555 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_3001_1x12mm" V 8600 5610 50  0001 C CNN
F 3 "~" V 8600 5610 50  0001 C CNN
	1    8600 5550
	1    0    0    -1  
$EndComp
Text GLabel 7200 5400 0    50   Input ~ 0
SDA
Text GLabel 7200 5300 0    50   Input ~ 0
SCL
$Comp
L Device:R R2
U 1 1 5E06601F
P 4450 1850
F 0 "R2" H 4520 1896 50  0000 L CNN
F 1 "10k" H 4520 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4380 1850 50  0001 C CNN
F 3 "~" H 4450 1850 50  0001 C CNN
	1    4450 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E066026
P 5200 1850
F 0 "R1" H 5270 1896 50  0000 L CNN
F 1 "10k" H 5270 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5130 1850 50  0001 C CNN
F 3 "~" H 5200 1850 50  0001 C CNN
	1    5200 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5E06602E
P 5200 1700
F 0 "#PWR03" H 5200 1550 50  0001 C CNN
F 1 "+5V" H 5215 1873 50  0000 C CNN
F 2 "" H 5200 1700 50  0001 C CNN
F 3 "" H 5200 1700 50  0001 C CNN
	1    5200 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5E066034
P 4450 1700
F 0 "#PWR07" H 4450 1550 50  0001 C CNN
F 1 "+5V" H 4465 1873 50  0000 C CNN
F 2 "" H 4450 1700 50  0001 C CNN
F 3 "" H 4450 1700 50  0001 C CNN
	1    4450 1700
	1    0    0    -1  
$EndComp
NoConn ~ 9200 2400
NoConn ~ 9200 2500
NoConn ~ 9200 2600
NoConn ~ 7700 2600
NoConn ~ 7700 2500
NoConn ~ 7700 2400
NoConn ~ 7700 2300
NoConn ~ 7700 2200
NoConn ~ 7700 2100
NoConn ~ 7700 2000
NoConn ~ 7700 1900
Text GLabel 9700 1400 2    50   Input ~ 0
SDA
Text GLabel 9700 1500 2    50   Input ~ 0
SCL
$Comp
L power:GND #PWR05
U 1 1 5E082756
P 3200 2000
F 0 "#PWR05" H 3200 1750 50  0001 C CNN
F 1 "GND" H 3205 1827 50  0000 C CNN
F 2 "" H 3200 2000 50  0001 C CNN
F 3 "" H 3200 2000 50  0001 C CNN
	1    3200 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5E08278D
P 3200 1700
F 0 "#PWR04" H 3200 1550 50  0001 C CNN
F 1 "+5V" H 3215 1873 50  0000 C CNN
F 2 "" H 3200 1700 50  0001 C CNN
F 3 "" H 3200 1700 50  0001 C CNN
	1    3200 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E0828A1
P 3200 1850
F 0 "C1" H 3315 1896 50  0000 L CNN
F 1 "10uF" H 3315 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3238 1700 50  0001 C CNN
F 3 "~" H 3200 1850 50  0001 C CNN
	1    3200 1850
	1    0    0    -1  
$EndComp
Text GLabel 4650 2750 1    50   Input ~ 0
SCL
Text GLabel 4300 2750 1    50   Input ~ 0
SDA
$Comp
L Switch:SW_Push SW3
U 1 1 5E08A25C
P 4900 6050
F 0 "SW3" H 4900 5900 50  0000 C CNN
F 1 "SW_Push" H 4900 6000 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4900 6250 50  0001 C CNN
F 3 "" H 4900 6250 50  0001 C CNN
	1    4900 6050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5E08B3A6
P 4450 6050
F 0 "SW2" H 4450 5900 50  0000 C CNN
F 1 "SW_Push" H 4450 6000 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4450 6250 50  0001 C CNN
F 3 "" H 4450 6250 50  0001 C CNN
	1    4450 6050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5E08B3EE
P 4000 6050
F 0 "SW1" H 4000 5900 50  0000 C CNN
F 1 "SW_Push" H 4000 6000 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4000 6250 50  0001 C CNN
F 3 "" H 4000 6250 50  0001 C CNN
	1    4000 6050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E092618
P 4450 4400
F 0 "#PWR06" H 4450 4150 50  0001 C CNN
F 1 "GND" H 4455 4227 50  0000 C CNN
F 2 "" H 4450 4400 50  0001 C CNN
F 3 "" H 4450 4400 50  0001 C CNN
	1    4450 4400
	1    0    0    -1  
$EndComp
Text GLabel 8950 3450 2    50   Input ~ 0
A
Text GLabel 9200 1600 2    50   Input ~ 0
A
Text GLabel 8950 4050 2    50   Input ~ 0
B
Wire Wire Line
	8950 4050 8950 4200
Text GLabel 9200 1700 2    50   Input ~ 0
B
Text GLabel 8000 3750 0    50   Input ~ 0
C
Text GLabel 9200 1800 2    50   Input ~ 0
C
Text GLabel 8000 3450 0    50   Input ~ 0
D
Text GLabel 9200 1900 2    50   Input ~ 0
D
Text GLabel 8000 3300 0    50   Input ~ 0
E
Text GLabel 9200 2000 2    50   Input ~ 0
E
Text GLabel 8950 3600 2    50   Input ~ 0
F
Text GLabel 9200 2100 2    50   Input ~ 0
F
Text GLabel 8000 3900 0    50   Input ~ 0
G
Text GLabel 9200 2200 2    50   Input ~ 0
G
Text GLabel 8000 3600 0    50   Input ~ 0
DP
Text GLabel 9200 2300 2    50   Input ~ 0
DP
Text GLabel 8950 3300 2    50   Input ~ 0
LED_COM1
Text GLabel 7700 1400 0    50   Input ~ 0
LED_COM1
Text GLabel 8950 3750 2    50   Input ~ 0
LED_COM2
Text GLabel 7700 1500 0    50   Input ~ 0
LED_COM2
Text GLabel 8000 4200 0    50   Input ~ 0
LED_COM_DOT
Text GLabel 7700 1600 0    50   Input ~ 0
LED_COM_DOT
Text GLabel 8950 3900 2    50   Input ~ 0
LED_COM3
Text GLabel 7700 1700 0    50   Input ~ 0
LED_COM3
Text GLabel 8000 4050 0    50   Input ~ 0
LED_COM4
Text GLabel 7700 1800 0    50   Input ~ 0
LED_COM4
$Comp
L Connector:AVR-ISP-6 J3
U 1 1 5E0970D0
P 5350 4050
F 0 "J3" H 5650 4550 50  0000 R CNN
F 1 "AVR-ISP-6" H 5800 4450 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" V 5100 4100 50  0001 C CNN
F 3 " ~" H 4075 3500 50  0001 C CNN
	1    5350 4050
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5E0984F6
P 5450 4450
F 0 "#PWR09" H 5450 4200 50  0001 C CNN
F 1 "GND" H 5455 4277 50  0000 C CNN
F 2 "" H 5450 4450 50  0001 C CNN
F 3 "" H 5450 4450 50  0001 C CNN
	1    5450 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5E098539
P 5450 3550
F 0 "#PWR08" H 5450 3400 50  0001 C CNN
F 1 "+5V" H 5465 3723 50  0000 C CNN
F 2 "" H 5450 3550 50  0001 C CNN
F 3 "" H 5450 3550 50  0001 C CNN
	1    5450 3550
	1    0    0    -1  
$EndComp
Wire Notes Line
	9550 4600 9550 950 
Text Notes 8700 900  2    50   ~ 0
LED display + driver
Wire Wire Line
	7850 5100 7850 4900
Wire Wire Line
	7950 5900 7950 6100
Wire Wire Line
	7200 5300 7450 5300
Wire Wire Line
	7200 5400 7450 5400
Wire Wire Line
	7950 5900 8600 5900
Wire Wire Line
	8600 5900 8600 5650
Connection ~ 7950 5900
Wire Wire Line
	8600 5350 8600 5100
Wire Wire Line
	8600 5100 7950 5100
Wire Notes Line
	7400 5000 9200 5000
Wire Notes Line
	9200 5000 9200 6000
Wire Notes Line
	9200 6000 7400 6000
Wire Notes Line
	7400 6000 7400 5000
Text Notes 8250 4950 0    50   ~ 0
RTC
Wire Wire Line
	3900 3850 4000 3850
Wire Wire Line
	4800 3750 4800 3950
Wire Wire Line
	4800 3950 4950 3950
Wire Wire Line
	4700 3950 4700 4050
Wire Wire Line
	4700 4050 4950 4050
Wire Wire Line
	3900 4250 4700 4250
Wire Wire Line
	4700 4250 4700 4150
Wire Wire Line
	4700 4150 4950 4150
Connection ~ 4000 3850
Wire Wire Line
	4000 3850 4950 3850
Wire Wire Line
	2900 2000 3200 2000
Connection ~ 3200 2000
$Comp
L Device:D D1
U 1 1 5E097D8A
P 3050 1700
F 0 "D1" H 3050 1484 50  0000 C CNN
F 1 "D" H 3050 1575 50  0000 C CNN
F 2 "Diode_SMD:D_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3050 1700 50  0001 C CNN
F 3 "~" H 3050 1700 50  0001 C CNN
	1    3050 1700
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5E0988FA
P 4800 1800
F 0 "J2" V 5000 1800 50  0000 R CNN
F 1 "I2C_conn" V 4900 1900 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4800 1800 50  0001 C CNN
F 3 "~" H 4800 1800 50  0001 C CNN
	1    4800 1800
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5E098AA7
P 2700 1800
F 0 "J1" H 2620 1475 50  0000 C CNN
F 1 "PWR_conn" H 2620 1566 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2700 1800 50  0001 C CNN
F 3 "~" H 2700 1800 50  0001 C CNN
	1    2700 1800
	-1   0    0    1   
$EndComp
Connection ~ 3200 1700
Wire Wire Line
	2900 1800 2900 2000
Text GLabel 4450 2000 3    50   Input ~ 0
SDA
Text GLabel 5200 2000 3    50   Input ~ 0
SCL
Wire Wire Line
	4450 2000 4800 2000
Wire Wire Line
	4900 2000 5200 2000
Wire Notes Line
	2450 6550 5750 6550
Wire Notes Line
	5750 3200 2450 3200
Wire Wire Line
	4650 3050 4650 3950
Wire Wire Line
	4300 3050 4300 3750
Text Notes 2450 3150 0    50   ~ 0
Microcontroller, ISP port, button pins
Wire Wire Line
	6800 1300 7700 1300
Wire Wire Line
	9200 1500 9700 1500
Wire Wire Line
	9200 1400 9700 1400
Wire Wire Line
	9200 1300 9700 1300
$Comp
L HT16K33:HT16K33 U3
U 1 1 5E0938B3
P 8450 1950
F 0 "U3" H 8450 2865 50  0000 C CNN
F 1 "HT16K33" H 8450 2774 50  0000 C CNN
F 2 "ht16k33:HT16K33" H 8150 2300 50  0001 C CNN
F 3 "" H 8150 2300 50  0001 C CNN
	1    8450 1950
	1    0    0    -1  
$EndComp
Wire Notes Line
	6950 950  9550 950 
Wire Notes Line
	9550 4600 6950 4600
Wire Notes Line
	6950 950  6950 4600
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5E0B8CED
P 3650 4900
F 0 "J5" H 3600 4600 50  0000 L CNN
F 1 "Buttons_conn" V 3750 4600 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3650 4900 50  0001 C CNN
F 3 "~" H 3650 4900 50  0001 C CNN
	1    3650 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 4150 4100 4150
Wire Wire Line
	3900 4050 4200 4050
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5E0BBC39
P 3650 5600
F 0 "J4" H 3650 5300 50  0000 C CNN
F 1 "Buttons_conn" V 3750 5550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3650 5600 50  0001 C CNN
F 3 "~" H 3650 5600 50  0001 C CNN
	1    3650 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4900 6250 4450 6250
Connection ~ 4450 6250
Wire Wire Line
	4450 6250 4000 6250
Wire Wire Line
	4900 6250 5100 6250
Connection ~ 4900 6250
$Comp
L Jumper:SolderJumper_2_Bridged JP3
U 1 1 5E0D00DA
P 4000 5300
F 0 "JP3" V 3850 5750 50  0000 L CNN
F 1 "PCB_breakpoint" V 3850 5950 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4000 5300 50  0001 C CNN
F 3 "~" H 4000 5300 50  0001 C CNN
	1    4000 5300
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP4
U 1 1 5E0D0160
P 4100 5300
F 0 "JP4" V 4050 5650 50  0000 L CNN
F 1 "PCB_breakpoint" V 4050 5850 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4100 5300 50  0001 C CNN
F 3 "~" H 4100 5300 50  0001 C CNN
	1    4100 5300
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP5
U 1 1 5E0D01B2
P 4200 5300
F 0 "JP5" V 4250 5550 50  0000 L CNN
F 1 "PCB_breakpoint" V 4250 5750 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4200 5300 50  0001 C CNN
F 3 "~" H 4200 5300 50  0001 C CNN
	1    4200 5300
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP6
U 1 1 5E0D0206
P 4300 5300
F 0 "JP6" V 4450 5500 50  0000 C CNN
F 1 "PCB_breakpoint" V 4450 5950 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4300 5300 50  0001 C CNN
F 3 "~" H 4300 5300 50  0001 C CNN
	1    4300 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 5800 3850 5800
Wire Wire Line
	4100 5700 3850 5700
Wire Wire Line
	4200 5600 3850 5600
Wire Wire Line
	4000 5450 4000 5800
Wire Wire Line
	4100 5450 4100 5700
Wire Wire Line
	4200 5450 4200 5600
Wire Wire Line
	4300 5450 4300 5500
Wire Wire Line
	4300 4400 4450 4400
Wire Wire Line
	4000 3850 4000 5100
Wire Wire Line
	4100 5000 4100 5150
Wire Wire Line
	4100 4150 4100 5000
Connection ~ 4100 5000
Wire Wire Line
	4200 4900 4200 5150
Wire Wire Line
	4200 4050 4200 4900
Connection ~ 4200 4900
Wire Wire Line
	4300 4800 4300 5150
Wire Wire Line
	4300 4400 4300 4800
Connection ~ 4300 4800
Wire Wire Line
	4000 5100 4000 5150
Connection ~ 4000 5100
Wire Notes Line
	5750 3200 5750 6550
Wire Notes Line
	2450 3200 2450 6550
Wire Wire Line
	3850 4800 4300 4800
Wire Wire Line
	3850 4900 4200 4900
Wire Wire Line
	3850 5000 4100 5000
Wire Wire Line
	3850 5100 4000 5100
Wire Wire Line
	3850 5500 4300 5500
Wire Wire Line
	4100 5850 4450 5850
Wire Wire Line
	4200 5750 4900 5750
Wire Wire Line
	4900 5750 4900 5850
Wire Wire Line
	4300 5650 5100 5650
Wire Wire Line
	5100 5650 5100 6250
Connection ~ 4000 5800
Wire Wire Line
	4000 5800 4000 5850
Connection ~ 4100 5700
Connection ~ 4200 5600
Connection ~ 4300 5500
Wire Wire Line
	4100 5700 4100 5850
Wire Wire Line
	4200 5600 4200 5750
Wire Wire Line
	4300 5500 4300 5650
Wire Notes Line
	4300 1400 5450 1400
Wire Notes Line
	5450 1400 5450 2250
Wire Notes Line
	5450 2250 4300 2250
Wire Notes Line
	4300 2250 4300 1400
Text Notes 4350 1350 0    50   ~ 0
I2C breakout and pullups
Wire Notes Line
	2550 1400 3550 1400
Wire Notes Line
	3550 1400 3550 2250
Wire Notes Line
	3550 2250 2550 2250
Wire Notes Line
	2550 2250 2550 1400
Text Notes 2550 1350 0    50   ~ 0
Power connector,\nreverse polarity protection\nand smoothing capacitor
Connection ~ 4300 3750
Wire Wire Line
	4300 3750 4800 3750
Connection ~ 4650 3950
Wire Wire Line
	4650 3950 4700 3950
Wire Wire Line
	3900 3950 4650 3950
Wire Wire Line
	3900 3750 4300 3750
$Comp
L Jumper:SolderJumper_2_Bridged JP1
U 1 1 5F6247A3
P 4300 2900
F 0 "JP1" V 4350 2650 50  0000 L CNN
F 1 "I2C_jmp" V 4250 2500 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4300 2900 50  0001 C CNN
F 3 "~" H 4300 2900 50  0001 C CNN
	1    4300 2900
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP2
U 1 1 5F6247AA
P 4650 2900
F 0 "JP2" V 4700 3000 50  0000 L CNN
F 1 "I2C_jmp" V 4600 3000 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 4650 2900 50  0001 C CNN
F 3 "~" H 4650 2900 50  0001 C CNN
	1    4650 2900
	0    1    1    0   
$EndComp
$EndSCHEMATC
