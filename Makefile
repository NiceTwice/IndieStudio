##
## Makefile for indie_studio in /home/debruy_p/projects/tek2/cpp/cpp_indie_studio
## 
## Made by Pierre Debruyne
## Login   <debruy_p@epitech.eu>
## 
## Started on  Mon Apr 25 21:59:19 2016 Pierre Debruyne
## Last update Sun Jun  5 20:30:04 2016 Pierre Debruyne
##

NAME	= indie_studio

all: $(NAME)

$(NAME):
	make -j4 -C src/Client/
	make -j4 -C src/Server/
	cp src/Client/client .
	cp src/Server/server .

clean:
	make -C src/Client/ clean
	make -C src/Server/ clean

fclean:
	make fclean -C src/Client/
	make fclean -C src/Server/
	rm -rf server
	rm -rf client

re:
	make re -C src/Client/
	make re -C src/Server/
	cp src/Client/client .
	cp src/Server/server .
