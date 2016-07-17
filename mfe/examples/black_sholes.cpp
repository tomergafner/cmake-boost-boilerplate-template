#include <iostream>

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

#include "mfe_common.h" 

using std::abs; 
using std::cout;
using std::endl;
using std::string;

using boost::program_options::variables_map;
using boost::program_options::value;
using boost::program_options::store;
using boost::program_options::notify;
using boost::program_options::options_description;
using boost::program_options::required_option;
using namespace boost::filesystem;

using namespace mfe::common;

int main(int argc, char* argv[]) {

    try {

        string appName = basename(argv[0]);
        char type = '\0';
        double s0 = 0.0;
        double k = 0.0;
        double t = 0.0;
        double sigma = 0.0;
        double r = 0.0;
        double q = 0.0;

        options_description desc("The following are required flags to the program:");
        desc.add_options()
            // First parameter describes option name/short name
            // The second is parameter to option
            // The third is description
            ("help,h", "print usage message")
            ("option,o", value(&type)->required() , "Type of European Vanilla option c/p")
            ("stock,s", value(&s0)->required(), "The underlying (Stock) price at time 0")
            ("strike,k", value(&k)->required(), "The strike price of the option")
            ("sigma,v", value(&sigma)->required(), "The volatility of the underlying asset e.g. enter 20 for 20%")
            ("interest,r", value(&r)->required(), "The risk free interest rate e.g. enter 3 for 3%")    
            ("expiration,t", value(&t)->required(), "The expiration time of the option in months e.g. enter 6 for 6 months")      
            ("divident,q", value(&q)->required(), "The divident paid by the stock in percent e.g. enter 3 for 3%");        


        variables_map vm;
        try {

            store(parse_command_line(argc, argv, desc), vm);


            if ( vm.count("help")  ) 
            { 
                std::cout << "This program will calculate the price of a plain vanilla European option using the black-scholes formula." << std::endl 
                    << " E.g. (A call option with strike 41, the asset spot price of 40, volatility of 20%. risk free interest rate of 3%, a divident rate of 2% which expires in 6 months)" << std::endl  
                    << "./" << appName << " -o c -s 40 -k 41 -v 20 -r 3 -q 2 -t 6" << std::endl << std::endl; 
                std::cout << desc << std::endl;
                return 0; 
            }        

            notify(vm);    

            t /= 12.0;
            sigma /= 100.0;
            r /= 100.0;
            q /= 100.0;

            std::cout << "S = " << s0 << "; ";
            std::cout << "K = " << k << "; ";
            std::cout << "T = " << t << "; ";
            std::cout << "sigma = " << sigma << "; ";	
            std::cout << "q = " << q << "; ";
            std::cout << "r = " << r << "; " << std::endl;

            std::cout << "The price of the option is " << price_option(type, s0, k, t, sigma, r, q)  << std::endl;
            return 0;
        }
        catch (required_option& e) {
            std::cout << e.what() << std::endl;
            std::cout << desc << std::endl;
            return -1;
        }
    }
    catch(std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
            << e.what() << ", application will now exit" << std::endl; 
        return -2;

    } 

    return 0; 
}
