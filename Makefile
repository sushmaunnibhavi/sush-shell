hash: hash.o cmdlist.o pathvar.o cmdalloc.o extcmd.o redir.o
	gcc -o hash hash.o cmdlist.o pathvar.o cmdalloc.o extcmd.o redir.o

hash.o: hash.c
	gcc -O -Wall -Werror -c hash.c

cmdlist.o: utils/cmdlist.c
	gcc -O -Wall -Werror -c utils/cmdlist.c

pathvar.o: utils/pathvar.c
	gcc -O -Wall -Werror -c utils/pathvar.c

extcmd.o: extcmd/extcmd.c
	gcc -O -Wall -Werror -c extcmd/extcmd.c

cmdalloc.o: extcmd/cmdalloc.c
	gcc -O -Wall -Werror -c extcmd/cmdalloc.c

redir.o: features/redir.c
	gcc -O -Wall -Werror -c features/redir.c

clean:
rm -f hash.o cmdlist.o extcmd.o cmdalloc.o hash
