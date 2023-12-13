#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {

class Barrier {
    int cpt;
    const int max;
    std::mutex m;
    std::condition_variable cv;

public :
    Barrier (int max) : cpt(0), max(max) {}

    void done() {
        unique_lock<mutex> ul(m);
        cpt++;
        if (cpt == max) { // tous les jobs sont finis : on débloque
            cv.notify_all();
        }
    }

    void waitFor() {
        unique_lock<mutex> ul(m);
        while (cpt != max) {
            cv.wait(ul);
        }
    }

}


}
