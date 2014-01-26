#include <cstdlib>
#include <ctime>
#include <opencv2/opencv.hpp>

#include "clients/StreamingClient.h"

int main() {
    srand(time(0)) ;

    StreamingClient* sc = StreamingClient::getInstance() ;
    sc -> start() ;

    return 0 ;
}
