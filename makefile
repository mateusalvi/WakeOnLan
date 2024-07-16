############################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#                    Mateus Luiz Salvi                     #
##########################################################*/

wakeonlan.o: wakeonlan.c monitoring.h discovery.h management.h interface.h constants.h
	gcc wakeonlan.c -o wakeonlan monitoring.c discovery.c management.c interface.c -lpthread

clean:
	rm *.o wakeonlan