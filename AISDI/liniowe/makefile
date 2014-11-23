all : asd

asd : asd.cc
	g++ -D _SUNOS asd.cc /materialy/AISDI/liniowe/timer.cc /materialy/AISDI/liniowe/main.cc /materialy/AISDI/tests/ltest_liniowe2.so -o asd 
	
del :
	rm asd
debug : asd.cc
	g++ -g -D _SUNOS asd.cc /materialy/AISDI/liniowe/timer.cc /materialy/AISDI/liniowe/main.cc /materialy/AISDI/tests/ltest_liniowe2.so -o asd_debug
	gdb asd_debug 
	

view:
	lynx /materialy/AISDI/liniowe/info/index.html
