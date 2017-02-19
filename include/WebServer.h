using namespace std;
namespace GOESDump {
    class WebServer {
        private: 
            int port;
            char * filename;

        public:
            WebServer(int port);
            int ServeFile(char * filename);
    }; 
}