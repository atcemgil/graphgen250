all: graphgen daggen

daggen: gen_dag_main.cpp sample.o dot_output.o algorithms.o
	g++ -o daggen gen_dag_main.cpp sample.o dot_output.o algorithms.o

graphgen: gen_ug_main.cpp sample.o dot_output.o algorithms.o
	g++ -o graphgen gen_ug_main.cpp sample.o dot_output.o algorithms.o

.o: .cpp graph.h
	g++ -c $<  -o $@

clean:
	rm *.o 
