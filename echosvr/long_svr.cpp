#include <handy/handy.h>
#include <sstream>
#include <unistd.h>

using namespace std;
using namespace handy;

int main(int argc ,const char * argv []){
	
	int nThreads = 1000;
	
	if(argc > 1){
		nThreads = atoi(argv[1]);
	}
	int port = 8081;
	if(argc > 2){
		port=atoi(argv[2]);	
	}
		
	setloglevel("TRACE");
	MultiBase base(100);
	HttpServer echoServer(& base);
	int r = echoServer.bind("",port);
	exitif(r,"bind failed %d %s",errno,strerror(errno));
	echoServer.onGet("/index.html", [](const HttpConnPtr& con) {
        	string v = con.getRequest().version;
        	HttpResponse resp;
		for(int i = 0; i < 10000; i++){
			//sleep(1);
			usleep(1000);
		}		
       	 	resp.body = Slice("");
        	con.sendResponse(resp);
        	if (v == "HTTP/1.0") {
            		con->close();
        	}
    	});
    	Signal::signal(SIGINT, [&]{base.exit();});
    	base.loop();

	return 0;
}
