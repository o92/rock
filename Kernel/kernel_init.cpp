#include <shitio.h>
#include <multiboot.h>
#include <interrupt.h>
#include <graphics.h>
#include <shell.h>
#include <keyboard.h>
#include <paging.h>
#include <process.h>

using namespace standardout;
using namespace MM;

extern "C" void kernel_main() {
    initalize(VGA_WHITE, VGA_BLUE);
    idt_init();

    asm volatile ("sti");

    start_counter(1, 0, 6);

    sprit_draw_main();
    clear_screen();

    s_print(VGA_LIGHT_BLUE, 50, 1, "crepOS 64 bit Dynamic Debugger");

    grab_current_y();
    draw_vline(VGA_MAGENTA, 48, 0, 25);

    page_frame_init(0xf42400);

    block_show();

    process proc(0x2001);
    proc.pmalloc(0x4);
    uint16_t *ptrbruh = (uint16_t*)proc.pmalloc(0x8);
    proc.pfree(ptrbruh);
    uint64_t *ptruh = (uint64_t*)proc.pmalloc(0x4);

    k_print("\n\n\n\n");

    change_text_color(VGA_LIGHT_BLUE);
    k_print("(*ROOT*) > ");
    change_text_color(VGA_BLUE);
    startInput();
    for(;;);
}