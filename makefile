##########################################################
#INF01151 - Sistemas Operacionais II N - Turma A (2024/1)#
#           Mateus Luiz Salvi - Bianca Pelegrini         #
#        Davi Haas Rodrigues - Adilson Enio Pierog       #
##########################################################

wakeonlan.o: wakeonlan.c
	gcc -o wakeonlan wakeonlan.c monitoring.h discovery.h management.h interface.h
clean:
	rm *.o wakeonlan