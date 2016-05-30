#include <libndls.h>

int main(void) {
	assert_ndless_rev(877);

	// 初始化 console 
	nio_console csl;
    nio_init(&csl, NIO_MAX_COLS, NIO_MAX_ROWS, 0, 0, BLACK, WHITE, TRUE);
    nio_set_default(&csl);
	

    // 释放 console 
	nio_free(&csl);
	return 0;
}
