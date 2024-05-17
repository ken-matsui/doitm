all: enable_doitm disable_doitm

test: check_rdmsr_installed enable_doitm disable_doitm
	@sudo ./enable_doitm
	@make --no-print-directory ensure_doitm_enabled
	@sudo ./disable_doitm
	@make --no-print-directory ensure_doitm_disabled

check_rdmsr_installed:
	@if command -v rdmsr >/dev/null 2>&1; then \
		echo "rdmsr is installed"; \
	else \
		echo "rdmsr is not installed. You can install it with:"; \
		echo "  sudo pacman -S msr-tools"; \
		exit 1; \
	fi

ensure_doitm_enabled:
	@output=$$($(sudo rdmsr 0x1B01)); \
	if [ "$$output" = "0" ]; then \
		echo 'Err: sudo rdmsr 0x1B01 = 0'; \
		exit 1; \
	else \
		echo 'Ok: sudo rdmsr 0x1B01 = 1'; \
	fi

ensure_doitm_disabled:
	@output=$$($(sudo rdmsr 0x1B01)); \
	if [ "$$output" = "1" ]; then \
		echo 'Err: sudo rdmsr 0x1B01 = 1'; \
		exit 1; \
	else \
		echo 'Ok: sudo rdmsr 0x1B01 = 0'; \
	fi

enable_doitm: enable_doitm.o doitm.o msr.o
	gcc -o enable_doitm enable_doitm.o doitm.o msr.o

disable_doitm: disable_doitm.o doitm.o msr.o
	gcc -o disable_doitm disable_doitm.o doitm.o msr.o

enable_doitm.o: enable_doitm.c
	gcc -c enable_doitm.c -o enable_doitm.o

disable_doitm.o: disable_doitm.c
	gcc -c disable_doitm.c -o disable_doitm.o

doitm.o: doitm.c doitm.h
	gcc -c doitm.c -o doitm.o

msr.o: msr.c msr.h
	gcc -c msr.c -o msr.o

clean:
	rm enable_doitm enable_doitm.o disable_doitm disable_doitm.o doitm.o msr.o
