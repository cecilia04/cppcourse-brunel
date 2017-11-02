#ifndef CORTEX_HPP
#define CORTEX_HPP
#include <iostream>
#include <vector>
#include "neuron.hpp"
#include <fstream>

class Cortex
{
	private:
	
		#ifdef TEST
	FRIEND_TEST (Cortex_Test, Connections);
	FRIEND_TEST (Cortex_Test, UniformDistribution);
		#endif
		
	const unsigned int nb_neurons_ = 12500;
	const unsigned int nb_excitatory_ = 10000;
	const unsigned int nb_inhibitory_ = 2500;
	const unsigned int nb_connections_exc_ = 1000;
	const unsigned int nb_connections_inhib_ = 250;
	
	double g_ = 5;
	double eta_ = 2; /*! nu ext / nu thr */
	
	std::vector<Neuron*> neurons_;
	
	std::vector<std::vector<int>> connections_; /*! matrix to know how many connections there are between each neurons */
	
	public:
	
	Cortex(); /*! constructor */
	
	~Cortex(); /*! destructor */
	
	Cortex(Cortex const& another); /*! copy constructor */
	
	void setG(double g);
	
	void setEta(double eta);
	
	void initNeurons(double time, double h); /*! initialization of the neurons in the cortex */
	
	void initConnections(); /*! initialization of connexions between the neurons */
	
	void fillConnections(std::vector<int> &connections, unsigned int start, unsigned int stop, unsigned int min, unsigned int max);
	
	void updateNeurons(double h, long step_start, long step_stop); /*! updates all the neurons in the cortex */
	
	void printTimeSpikes();
	
	void saveToFile(std::ofstream & file);
	
	void setNeuronInput(size_t i, double input);
	
	int random_uniform(unsigned int start, unsigned int stop); /*! returns a random number between start and stop-1 with a uniform distribution */
	
	void deleteNeurons();
	
};

#endif
