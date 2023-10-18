#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;

public:
	Pool(int qsize) ;
	void start (int nbthread);
	void submit (Job * job) ;
	void stop() ;
	~Pool() ;

	void poolWorker(Queue<Job>&queue){
		while(true){
			Job *pjob = queue.pop();
			if(pjob == nullptr){
				return;
			}
			pjob -> run();
			delete pjob;

		}
	}
	void stop(){
		queue.setBlocking(false);
		for(auto &t: threads){
			t.join();
		}
		threads.clear();
	}
	void start(int NbThreads){
		threads.reserve(NbThreads);
		for(int i=0;i<NbThreads;i++){
			threads.emplace_back(poolWorker,& queue);
		}
	}

	void submit(Job *job){
		queue.push(job);
	}
};

}
