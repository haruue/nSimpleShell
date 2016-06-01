#include <libndls.h>
#include <module.h>

int module_main(int argc, char *argv[]) {

printf("module echo\n");
	for (int i = 0; i < argc; ++i) {
printf("%d: %s\n", i, argv[i]);
	}
	int nflag = 0;
	// if(1 < argc && *++argv && !strcmp(*argv, "-n")) {	
		// nflag=1;
	// }
	for (int i = 1; i < argc; i++) {
		nio_printf("%s", argv[i]);
		if (i < argc - 1) {
			printf("\x20");
		} else if (nflag == 0) {
			printf("\n");
		}
	}
	return 0;
}
