src = $(wildcard Source/*.c)
obj = $(src:.c=.o)
CFLAGS=`mysql_config --libs`
build/main: $(obj)
	$(CC) -o $@ $^
.PHONY: clean
clean:
	@echo "Lets clean it..."  
	rm -f $(obj) build/main
