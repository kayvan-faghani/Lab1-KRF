#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc,argv);
    Vtop* top = new Vtop;
    Verilated:: traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;

    top->trace (tfp,99);
    tfp->open ("top.vcd");


    top->clk = 1;
    top->rst = 1;

    int half = 1;
    for(i=0;i<1000;i++){
        for(clk=0;clk<2;clk++){
            tfp->dump (2*i+clk);
            top->rst = (half == 5);
            top->clk = !top->clk;
            top->eval ();
            half++;
        }
        //Right shifts each value 16,8, 4 and 0 respectively
        //This is then anded with F which is 16, to give us the
        //value of count for each digit
        //vbdPlot(int(top->count), 0, 255);        
        if(Verilated::gotFinish()) exit(0); 
    }

    tfp->close();
    exit(0);
}