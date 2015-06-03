/*
 * Jenkins.h
 *
 *  Created on: 21/05/2015
 *      Author: emanuel
 */

#ifndef JENKINS_H_
#define JENKINS_H_
#include <string>
using namespace std;

class Jenkins {
private:
	unsigned primo;

public:
	Jenkins(unsigned primo);
	unsigned hash(string word);
	virtual ~Jenkins();
};

#endif /* JENKINS_H_ */
