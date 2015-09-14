#include "systemc.h"
sc_event zen;
sc_event jjk;
SC_MODULE(top) {
    sc_in_clk clk;
    sc_in<int> in_port;
    sc_out<int> out_port;


    SC_CTOR(top) {
        SC_THREAD(topEntry);
        //SC_THREAD(secondEntry);
        sensitive<<clk.pos();
    }
    /*
    void secondEntry() {
      while(true) {

        //wait(2, SC_NS);
       //wait();
        var = var +2;
      }
    }
    */


    void topEntry() {
        while(true) {
            /*
            wait();
            var++;
            wait();
            --var;
            y = y + 1;
            wait();
            var = var *2;
             */
            var = var + 1;
            x=1;
            y=1;
            wait();
            //wait();
        }
    }

public:
    int var;
    int x;
    int y;
};

int sc_main(int argc, char *argv[]){

    sc_clock CLOCK("clock", 5);
    sc_signal<int> output;
    sc_signal<int> input;

    top t2("t2");
    t2.clk(CLOCK);
    t2.in_port(input);
    t2.out_port(output);

    sc_start(10,SC_NS);

    return 0;
}
