/*
* Copyright 2014, Radhika S. Saksena (radhika dot saksena at gmail dot com)
* Licensed under the Apache License, Version 2.0
* http://www.apache.org/licenses/LICENSE-2.0
*/

#include <boost/random.hpp>
#include <boost/random/bernoulli_distribution.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace std;

/*
* Sample from a categorical distribution (1-of-K categories)
* and returns index of the selected category or -1 on error. 
* The Categorical distribution is a generalization of the
* Bernoulli distribution for variables with more than two 
* possible discrete values.
*/
template<typename T,typename U>
int categorical(T& rnd, vector<U> probs)
{
        int numcat = probs.size();
        double tmpProb = 1.0;

        for(int i = 0; i < probs.size(); i++)
        {
            float scaledP = (float)(probs[i] / tmpProb);
            boost::bernoulli_distribution<> bern(scaledP);
            boost::variate_generator<T&, boost::bernoulli_distribution<> > bGen(rnd, bern);
            if(bGen() > 0){
                return i;
            }
                tmpProb -= probs[i];
        }

        return -9;
}
