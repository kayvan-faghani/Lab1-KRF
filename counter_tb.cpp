#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc,argv);
    Vcounter* top = new Vcounter;
    Verilated:: traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;

    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    int half = 1;
    for(i=0;i<300;i++){
        for(clk=0;clk<2;clk++){
            tfp->dump (2*i+clk);
            top->rst = (half == 5);
            top->clk =!top->clk;
            top->eval ();
            half++;
        }
        top->en = (i <= 10 | i >= 13);
        if(Verilated::gotFinish()) exit(0); 
    }

    tfp->close();
    exit(0);
}