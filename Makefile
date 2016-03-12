NAME = mirom.gb

Debug:
	rm -f $(NAME)
	lcc -o $(NAME) main.c
clean:
	rm -f $(NAME)