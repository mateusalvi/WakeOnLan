##########################################################
#INF01151 - Sistemas Operacionais II N - Turma A (2024/1)#
#           Mateus Luiz Salvi - Bianca Pelegrini         #
#        Davi Haas Rodrigues - Adilson Enio Pierog       #
##########################################################

wakeonlan.o: wakeonlan.c monitoring.h discovery.h management.h interface.h
	gcc wakeonlan.c -o wakeonlan monitoring.c discovery.c management.c interface.c -lpthread

clean:
	rm *.o wakeonlan