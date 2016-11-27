EESchema Schematic File Version 2
LIBS:Abracon
LIBS:ActiveSemi
LIBS:Altera
LIBS:AMS
LIBS:AnalogDevices
LIBS:AOS
LIBS:Atmel
LIBS:Bosch
LIBS:conn-2mm
LIBS:conn-100mil
LIBS:conn-amphenol
LIBS:conn-assmann
LIBS:conn-cui
LIBS:conn-fci
LIBS:conn-jae
LIBS:conn-linx
LIBS:conn-molex
LIBS:conn-tagconnect
LIBS:conn-te
LIBS:conn-test
LIBS:DiodesInc
LIBS:display
LIBS:electomech-misc
LIBS:_electromech
LIBS:Fairchild
LIBS:FTDI
LIBS:Infineon
LIBS:Intersil
LIBS:Lattice
LIBS:_linear
LIBS:LinearTech
LIBS:Littelfuse
LIBS:_logic
LIBS:logic-4000
LIBS:logic-7400
LIBS:logic-7400-new
LIBS:MACOM
LIBS:Macrofab
LIBS:maxim
LIBS:mechanical
LIBS:Microchip
LIBS:Micron
LIBS:Murata
LIBS:NXP
LIBS:OceanOptics
LIBS:onsemi
LIBS:_passive
LIBS:pasv-BelFuse
LIBS:pasv-BiTech
LIBS:pasv-Bourns
LIBS:pasv-cap
LIBS:pasv-ind
LIBS:pasv-Murata
LIBS:pasv-res
LIBS:pasv-TDK
LIBS:pasv-xtal
LIBS:pcb
LIBS:power
LIBS:Recom
LIBS:Richtek
LIBS:_semi
LIBS:semi-diode-DiodesInc
LIBS:semi-diode-generic
LIBS:semi-diode-MCC
LIBS:semi-diode-NXP
LIBS:semi-diode-OnSemi
LIBS:semi-diode-Semtech
LIBS:semi-diode-ST
LIBS:semi-diode-Toshiba
LIBS:semi-opto-generic
LIBS:semi-opto-liteon
LIBS:semi-thyristor-generic
LIBS:semi-trans-AOS
LIBS:semi-trans-DiodesInc
LIBS:semi-trans-EPC
LIBS:semi-trans-Fairchild
LIBS:semi-trans-generic
LIBS:semi-trans-Infineon
LIBS:semi-trans-IRF
LIBS:semi-trans-IXYS
LIBS:semi-trans-NXP
LIBS:semi-trans-OnSemi
LIBS:semi-trans-Panasonic
LIBS:semi-trans-ST
LIBS:semi-trans-TI
LIBS:semi-trans-Toshiba
LIBS:semi-trans-Vishay
LIBS:silabs
LIBS:skyworks
LIBS:ST
LIBS:st_ic
LIBS:supertex
LIBS:symbol
LIBS:TexasInstruments
LIBS:u-blox
LIBS:Vishay
LIBS:Winbond
LIBS:Xilinx
LIBS:wemos_mini
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:actel
LIBS:adc-dac
LIBS:analog_devices
LIBS:analog_switches
LIBS:atmel
LIBS:audio
LIBS:battery_management
LIBS:bbd
LIBS:brooktre
LIBS:cmos4000
LIBS:cmos_ieee
LIBS:conn
LIBS:contrib
LIBS:cypress
LIBS:dc-dc
LIBS:device
LIBS:digital-audio
LIBS:diode
LIBS:dsp
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:intel
LIBS:interface
LIBS:ir
LIBS:linear
LIBS:logo
LIBS:memory
LIBS:microchip
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:microcontrollers
LIBS:motor_drivers
LIBS:motorola
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:opto
LIBS:Oscillators
LIBS:philips
LIBS:powerint
LIBS:Power_Management
LIBS:pspice
LIBS:references
LIBS:regul
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:siliconi
LIBS:stm8
LIBS:stm32
LIBS:switches
LIBS:texas
LIBS:transf
LIBS:transistors
LIBS:ttl_ieee
LIBS:valves
LIBS:video
LIBS:Worldsemi
LIBS:Xicor
LIBS:xilinx
LIBS:Zilog
LIBS:aquarium_light_control-cache
EELAYER 25 0
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
L WeMos_mini U1
U 1 1 58373469
P 2350 3960
F 0 "U1" H 2350 4703 60  0000 C CNN
F 1 "WeMos_mini" H 2350 4597 60  0000 C CNN
F 2 "wemos_d1_mini:D1_mini_board" H 2350 4491 60  0001 C CNN
F 3 "" H 2900 3260 60  0000 C CNN
	1    2350 3960
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 5837420F
P 1560 1530
F 0 "CON1" H 1541 1946 50  0000 C CNN
F 1 "5.5x2.5_BARREL_JACK" H 1541 1855 50  0000 C CNN
F 2 "Connect:BARREL_JACK" H 1541 1764 50  0001 C CNN
F 3 "" H 1560 1530 50  0000 C CNN
	1    1560 1530
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5837429B
P 2030 1760
F 0 "#PWR01" H 2030 1760 30  0001 C CNN
F 1 "GND" H 2030 1690 30  0001 C CNN
F 2 "" H 2030 1760 60  0000 C CNN
F 3 "" H 2030 1760 60  0000 C CNN
	1    2030 1760
	1    0    0    -1  
$EndComp
Wire Wire Line
	1860 1530 2360 1530
Wire Wire Line
	2030 1530 2030 1760
Wire Wire Line
	1860 1630 2030 1630
Connection ~ 2030 1630
$Comp
L +12 #PWR02
U 1 1 5837434A
P 2030 1380
F 0 "#PWR02" H 2030 1430 30  0001 C CNN
F 1 "+12" H 2030 1513 50  0000 C CNN
F 2 "" H 2030 1380 60  0000 C CNN
F 3 "" H 2030 1380 60  0000 C CNN
	1    2030 1380
	1    0    0    -1  
$EndComp
Wire Wire Line
	1860 1430 2360 1430
Wire Wire Line
	2030 1430 2030 1380
$Comp
L Q_NMOS_GSD Q1
U 1 1 5839F0B3
P 5200 1520
F 0 "Q1" H 5391 1566 50  0000 L CNN
F 1 "BSS806NE" H 5391 1475 50  0000 L CNN
F 2 "smd-semi:SOT-23" H 5391 1475 50  0001 L CNN
F 3 "http://www.infineon.com/dgdl/Infineon-BSS806NE-DS-v02_01-en.pdf" H 5391 1429 50  0001 L CNN
	1    5200 1520
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5839F36C
P 5540 1010
F 0 "P3" H 5618 1051 50  0000 L CNN
F 1 "LED_POWER" H 5618 960 50  0000 L CNN
F 2 "conn-100mil:CONN-100MIL-M-1x2" H 5617 914 50  0001 L CNN
F 3 "" H 5540 1010 50  0001 C CNN
	1    5540 1010
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5839F7CD
P 5300 1840
F 0 "#PWR03" H 5300 1840 30  0001 C CNN
F 1 "GND" H 5300 1770 30  0001 C CNN
F 2 "" H 5300 1840 60  0000 C CNN
F 3 "" H 5300 1840 60  0000 C CNN
	1    5300 1840
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1720 5300 1840
Wire Wire Line
	5340 1060 5300 1060
Wire Wire Line
	5300 1060 5300 1320
$Comp
L +12 #PWR04
U 1 1 5839F932
P 5300 880
F 0 "#PWR04" H 5300 930 30  0001 C CNN
F 1 "+12" H 5300 1013 50  0000 C CNN
F 2 "" H 5300 880 60  0000 C CNN
F 3 "" H 5300 880 60  0000 C CNN
	1    5300 880 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 880  5300 960 
Wire Wire Line
	5300 960  5340 960 
NoConn ~ 2850 3610
$Comp
L R-0603 R1
U 1 1 583A04C8
P 4820 1520
F 0 "R1" V 4620 1520 50  0000 C CNN
F 1 "1K" V 4711 1520 50  0000 C CNN
F 2 "IPC7351-Nominal:RESC1608X50" H 4820 1520 50  0001 C CNN
F 3 "" H 4820 1570 60  0000 C CNN
F 4 "RES SMD 1k 5% [0603]" H 5570 2070 60  0001 C CNN "BOM"
	1    4820 1520
	0    1    1    0   
$EndComp
Wire Wire Line
	4920 1520 5000 1520
Text Label 4530 1520 2    60   ~ 0
Q_Gate
Wire Wire Line
	4720 1520 4530 1520
$Comp
L GND #PWR05
U 1 1 583A0D04
P 2190 2350
F 0 "#PWR05" H 2190 2350 30  0001 C CNN
F 1 "GND" H 2190 2280 30  0001 C CNN
F 2 "" H 2190 2350 60  0000 C CNN
F 3 "" H 2190 2350 60  0000 C CNN
	1    2190 2350
	1    0    0    -1  
$EndComp
Text Label 1400 4110 2    60   ~ 0
Q_Gate
Wire Wire Line
	1850 4110 1400 4110
Text Notes 5550 780  0    60   ~ 0
5.5mmx2.5mm barrel plug, center positive
$Comp
L CONN_01X02 P2
U 1 1 583A1ABC
P 2560 1480
F 0 "P2" H 2637 1521 50  0000 L CNN
F 1 "To_5V_Module" H 2637 1430 50  0000 L CNN
F 2 "conn-100mil:CONN-100MIL-M-1x2" H 2637 1384 50  0001 L CNN
F 3 "" H 2560 1480 50  0000 C CNN
	1    2560 1480
	1    0    0    -1  
$EndComp
Connection ~ 2030 1430
Connection ~ 2030 1530
$Comp
L CONN_01X02 P1
U 1 1 583A2300
P 2550 2230
F 0 "P1" H 2469 1865 50  0000 C CNN
F 1 "From_5V_Module" H 2469 1956 50  0000 C CNN
F 2 "conn-100mil:CONN-100MIL-M-1x2" H 2570 2390 50  0001 C CNN
F 3 "" H 2550 2230 50  0000 C CNN
	1    2550 2230
	1    0    0    -1  
$EndComp
$Comp
L +5 #PWR06
U 1 1 583A2B8C
P 1510 3520
F 0 "#PWR06" H 1510 3570 30  0001 C CNN
F 1 "+5" H 1510 3653 50  0000 C CNN
F 2 "" H 1510 3520 60  0000 C CNN
F 3 "" H 1510 3520 60  0000 C CNN
	1    1510 3520
	1    0    0    -1  
$EndComp
Wire Wire Line
	1510 3520 1510 3610
NoConn ~ 2850 3710
NoConn ~ 2850 3810
NoConn ~ 2850 3910
NoConn ~ 2850 4010
NoConn ~ 2850 4110
NoConn ~ 2850 4210
NoConn ~ 2850 4310
NoConn ~ 1850 3810
NoConn ~ 1850 3910
NoConn ~ 1850 4010
NoConn ~ 1850 4210
NoConn ~ 1850 4310
$Comp
L PWR_FLAG #PWR07
U 1 1 583A483E
P 1890 1380
F 0 "#PWR07" H 1890 1380 50  0001 C CNN
F 1 "PWR_FLAG" H 1890 1380 50  0001 C CNN
F 2 "" H 1890 1380 60  0000 C CNN
F 3 "" H 1890 1380 60  0000 C CNN
	1    1890 1380
	1    0    0    -1  
$EndComp
Wire Wire Line
	1890 1380 1890 1430
Connection ~ 1890 1430
$Comp
L PWR_FLAG #PWR08
U 1 1 583A4B1C
P 2060 2120
F 0 "#PWR08" H 2060 2120 50  0001 C CNN
F 1 "PWR_FLAG" H 2060 2120 50  0001 C CNN
F 2 "" H 2060 2120 60  0000 C CNN
F 3 "" H 2060 2120 60  0000 C CNN
	1    2060 2120
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #PWR09
U 1 1 583A4FEA
P 2130 1690
F 0 "#PWR09" H 2130 1690 50  0001 C CNN
F 1 "PWR_FLAG" H 2130 1690 50  0001 C CNN
F 2 "" H 2130 1690 60  0000 C CNN
F 3 "" H 2130 1690 60  0000 C CNN
	1    2130 1690
	1    0    0    -1  
$EndComp
Wire Wire Line
	2130 1690 2130 1710
Wire Wire Line
	2130 1710 2030 1710
Connection ~ 2030 1710
Wire Wire Line
	2350 2280 2190 2280
Wire Wire Line
	2190 2280 2190 2350
$Comp
L +5 #PWR?
U 1 1 583A771A
P 2190 2120
F 0 "#PWR?" H 2190 2170 30  0001 C CNN
F 1 "+5" H 2190 2253 50  0000 C CNN
F 2 "" H 2190 2120 60  0000 C CNN
F 3 "" H 2190 2120 60  0000 C CNN
	1    2190 2120
	1    0    0    -1  
$EndComp
Wire Wire Line
	1510 3610 1850 3610
$Comp
L GND #PWR?
U 1 1 583A7BE5
P 1510 3770
F 0 "#PWR?" H 1510 3770 30  0001 C CNN
F 1 "GND" H 1510 3700 30  0001 C CNN
F 2 "" H 1510 3770 60  0000 C CNN
F 3 "" H 1510 3770 60  0000 C CNN
	1    1510 3770
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3710 1510 3710
Wire Wire Line
	1510 3710 1510 3770
Wire Wire Line
	2060 2180 2350 2180
Wire Wire Line
	2190 2180 2190 2120
Wire Wire Line
	2060 2180 2060 2120
Connection ~ 2190 2180
$EndSCHEMATC
