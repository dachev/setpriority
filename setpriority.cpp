#include <sys/time.h>
#include <sys/resource.h>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>

#include <iostream>
#include <iterator>

using namespace std;
using namespace boost;
using namespace boost::program_options;

static regex r("\\d\\d\\d-(\\d\\d\\d)");



int main( int argc, char* argv[] ) {
	int ret = 0;
	
	try {
		options_description desc( "Allowed options" );

		desc.add_options( )
    		( "help", "produce help message" )
	    	( "pid", value<int>(), "process ID" )
			( "n", value<int>(), "scheduling priority" )
		;

		variables_map vm;
		store( parse_command_line(argc, argv, desc), vm );
		notify(vm);    

		if (vm.count( "help" )) {
		    cout << desc << "\n";
			return 1;
		}
	
		if (vm.count( "pid" )) {
			cout << "Process ID "
				 << vm["pid"].as<int>( ) << ".\n";
		} else {
			cout << "PID was not set.\n";
		}

		if (vm.count( "n" ) && vm["n"].as<int>( ) >= -20 && vm["n"].as<int>( ) <= 20) {
			cout << "Priority "
				 << vm["n"].as<int>( ) << "\n";
		}
		else if (vm.count( "n" ) && (vm["n"].as<int>( ) < -20 || vm["n"].as<int>( ) > 20)) {
            cout << "Invalid priority: specify a number between -20 and 20\n";
			return 1;
		}
		else {
			cout << "Priority was not set\n";
			return 1;
		}

		ret = setpriority( PRIO_PROCESS, vm["pid"].as<int>( ), vm["n"].as<int>( ) );
	} catch( std::exception &e ) {
		cerr << "error: " << e.what() << "\n";
		return 1;
	}
			
	return ret;
}

