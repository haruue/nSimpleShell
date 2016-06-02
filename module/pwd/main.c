#include <libndls.h>
#include <module.h>

int module_main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	char *pwdString = getenv("PWD");
	if (pwdString == NULL) {
		char *homeString = getenv("HOME");
		if (homeString == NULL) {
			setenv("PWD", "/", 1);
			setenv("HOME", "/", 1);
		} else {
			setenv("PWD", homeString, 1);
		}
		pwdString = getenv("PWD");
	}
	nio_printf("%s\n", pwdString);
	return 0;
}
