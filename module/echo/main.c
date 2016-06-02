#include <libndls.h>
#include <module.h>

int module_main(int argc, char *argv[]) {
	int nflag = 0;
	// if(1 < argc && *++argv && !strcmp(*argv, "-n")) {	
		// nflag=1;
	// }
	for (int i = 1; i < argc; i++) {
		nio_printf("%s", argv[i]);
		if (i < argc - 1) {
			nio_printf("\x20");
		} else if (nflag == 0) {
			nio_printf("\n");
		}
	}
	return 0;
}
