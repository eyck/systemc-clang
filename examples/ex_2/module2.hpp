#include "systemc.h"

SC_MODULE(top) {
    sc_in_clk clk;
    sc_in<int> in_port;
    sc_out<int> out_port;


    SC_CTOR(top) {
        SC_THREAD(topEntry);
        sensitive<<clk.pos();
    }


    void topEntry() {
        while(true){
            x = 2;
            wait(1, SC_NS);
            /*
            if (x>5) {
                if(x > 2) {
                    wait(1, SC_NS);
                }
                y++;
            }
             */
        }

    }

public:
    int var;
    int x,y;

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
