#include "stdincludes.h"
#include "Container.h"

class Server {
public:
	Server();
	~Server();
private:
	vector<AppContainer*> containers;
};
