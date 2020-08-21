#include <kernel/int/apic.h>
#include <kernel/int/idt.h>
#include <lib/asmUtils.h>
#include <lib/output.h>

namespace kernel {

idtEntry_t entries[256];
idtr_t idtr;

extern "C" void isrHandlerMain(regs_t *reg) {
    cout + "[KDEBUG]" << "Hello\n";
    if(reg->isrNumber > 32) {
        uint64_t cr2;
        asm volatile ("cli\n" "mov %%cr2, %0" : "=a"(cr2));
        cout + "[KDEBUG]" << "Congrats: you fucked up with a nice <" << exceptionMessages[reg->isrNumber] << "\n";
        for(;;); 
    }

    apic.lapicWrite(LAPIC_EOI, 0);
}

void idt_t::setIDTentry(uint16_t selector, uint8_t ist, uint8_t attributes, uint64_t offset, uint8_t index) {
    entries[index].offsetLow = (uint16_t)(offset >> 0);
    entries[index].selector = selector;
    entries[index].ist = ist;
    entries[index].attributes = attributes;
    entries[index].offsetMid = (uint16_t)(offset >> 16);
    entries[index].offsetHigh = (uint32_t)(offset >> 32);
    entries[index].zero = 0; 
}

void idt_t::setIDTR() {
    idtr.limit = 256 * sizeof(idtEntry_t) - 1;
    idtr.offset = (uint64_t)&idtr;
    asm volatile ("lidtq %0" : "=m"(idtr));
}

void idt_t::initIDT() {
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr0, 0);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr1, 1);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr2, 2);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr3, 3);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr4, 4);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr5, 5);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr6, 6);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr7, 7);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr8, 8);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr9, 9);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr10, 10);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr11, 11);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr12, 12);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr13, 13);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)errorIsr14, 14);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr15, 15);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr16, 16);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr17, 17);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr18, 18);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr19, 19);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr20, 20);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr21, 21);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr22, 22);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr23, 23);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr24, 24);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr25, 25);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr26, 26);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr27, 27);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr28, 28);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr29, 29);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr30, 30);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr31, 31);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr32, 32);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr33, 33);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr34, 34);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr35, 35);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr36, 36);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr37, 37);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr38, 38);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr39, 39);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr40, 40);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr41, 41);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr42, 42);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr43, 43);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr44, 44);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr45, 45);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr46, 46);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr47, 47);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr48, 48);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr49, 49);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr50, 50);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr51, 51);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr52, 52);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr53, 53);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr54, 54);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr55, 55);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr56, 56);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr57, 57);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr58, 58);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr59, 59);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr60, 60);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr61, 61);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr62, 62);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr63, 63);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr64, 64);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr65, 65);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr66, 66);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr67, 67);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr68, 68);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr69, 69);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr70, 70);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr71, 71);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr72, 72);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr73, 73);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr74, 74);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr75, 75);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr76, 76);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr77, 77);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr78, 78);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr79, 79);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr80, 80);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr81, 81);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr82, 82);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr83, 83);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr84, 84);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr85, 85);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr86, 86);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr87, 87);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr88, 88);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr89, 89);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr90, 90);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr91, 91);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr92, 92);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr93, 93);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr94, 94);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr95, 95);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr96, 96);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr97, 97);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr98, 98);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr99, 99);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr100, 100);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr101, 101);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr102, 102);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr103, 103);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr104, 104);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr105, 105);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr106, 106);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr107, 107);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr108, 108);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr109, 109);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr110, 110);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr111, 111);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr112, 112);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr113, 113);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr114, 114);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr115, 115);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr116, 116);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr117, 117);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr118, 118);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr119, 119);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr120, 120);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr121, 121);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr122, 122);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr123, 123);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr124, 124);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr125, 125);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr126, 126);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr127, 127);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr128, 128);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr129, 129);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr130, 130);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr131, 131);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr132, 132);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr133, 133);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr134, 134);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr135, 135);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr136, 136);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr137, 137);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr138, 138);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr139, 139);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr140, 140);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr141, 141);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr142, 142);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr143, 143);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr144, 144);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr145, 145);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr146, 146);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr147, 147);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr148, 148);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr149, 149);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr150, 150);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr151, 151);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr152, 152);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr153, 153);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr154, 154);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr155, 155);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr156, 156);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr157, 157);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr158, 158);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr159, 159);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr160, 160);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr161, 161);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr162, 162);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr163, 163);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr164, 164);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr165, 165);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr166, 166);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr167, 167);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr168, 168);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr169, 169);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr170, 170);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr171, 171);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr172, 172);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr173, 173);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr174, 174);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr175, 175);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr176, 176);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr177, 177);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr178, 178);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr179, 179);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr180, 180);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr181, 181);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr182, 182);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr183, 183);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr184, 184);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr185, 185);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr186, 186);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr187, 187);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr188, 188);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr189, 189);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr190, 190);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr191, 191);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr192, 192);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr193, 193);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr194, 194);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr195, 195);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr196, 196);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr197, 197);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr198, 198);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr199, 199);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr200, 200);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr201, 201);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr202, 202);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr203, 203);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr204, 204);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr205, 205);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr206, 206);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr207, 207);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr208, 208);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr209, 209);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr210, 210);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr211, 211);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr212, 212);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr213, 213);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr214, 214);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr215, 215);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr216, 216);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr217, 217);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr218, 218);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr219, 219);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr220, 220);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr221, 221);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr222, 222);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr223, 223);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr224, 224);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr225, 225);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr226, 226);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr227, 227);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr228, 228);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr229, 229);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr230, 230);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr231, 231);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr232, 232);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr233, 233);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr234, 234);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr235, 235);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr236, 236);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr237, 237);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr238, 238);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr239, 239);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr240, 240);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr241, 241);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr242, 242);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr243, 243);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr244, 244);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr245, 245);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr246, 246);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr247, 247);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr248, 248);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr249, 249);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr250, 250);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr251, 251);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr252, 252);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr253, 253);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr254, 254);
    setIDTentry(0x8, 0, 0x8e, (uint64_t)isr255, 255);
}

}
