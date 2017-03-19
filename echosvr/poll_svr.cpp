#include <handy/handy.h>

using namespace std;
using namespace handy;

int main(int argc ,const char * argv []){
	
	int nThreads = 1000;
	
	if(argc > 1){
		nThreads = atoi(argv[1]);
	}
		
	setloglevel("TRACE");
	MultiBase base(100);
	HttpServer echoServer(& base);
	int r = echoServer.bind("",8088);
	exitif(r,"bind failed %d %s",errno,strerror(errno));
	echoServer.onGet("/h5/reply/unread-with-time", [](const HttpConnPtr& con) {
        	string v = con.getRequest().version;
        	HttpResponse resp;
       	 	resp.body = Slice("{\"c\":0,\"t\":-28800}");
        	con.sendResponse(resp);
        	if (v == "HTTP/1.0") {
            		con->close();
        	}
    	});
    	Signal::signal(SIGINT, [&]{base.exit();});
    	base.loop();

	return 0;
}
