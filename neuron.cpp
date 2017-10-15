#include "neuron.hpp"
#include <iostream>
#include <cmath>
#include <fstream>

Neuron::Neuron() //constructor
	: potential_(0), nb_spikes_(0) {};
	
Neuron::Neuron(const Neuron& another) //destructor
	: potential_(another.potential_), nb_spikes_(another.potential_), time_spikes_(another.time_spikes_) {};
	
Neuron::~Neuron() {}; //copy constructor

//getters
double Neuron::getPotential() const {
	return potential_;
}
	
unsigned int Neuron::getNbSpikes() const {
	return nb_spikes_;
}
	
std::vector<double> Neuron::getTimeSpikes()  const {
	return time_spikes_;
}

double Neuron::getDelay() const {
	return delay_;
}

std::vector<double> Neuron::getBuffer() const {
	return ring_buffer_;
}
	

//setters
void Neuron::setClock(double time) {
	clock_ = time;
}

void Neuron::setBuffer(size_t i,double J) {
	ring_buffer_[i] = J;
}

//other functions	
bool Neuron::update(double ext_input, std::ofstream & output, double h, long step) { //update neuron state
	
	bool spike = false;
		
	--refractory_steps_; //update the neuron refractory period
		 
	if (potential_ > threshold_) {
		
		//std::cout << "Potential > threshold" << std::endl;

		refractory_steps_ = refractory_time_ / h; //potential has reached threshold so neuron is refractory
			
		time_spikes_.push_back(clock_); //store spike time
			
		++nb_spikes_; //count up new spike
			
		spike = true;
			
		//std::cout << "New spike ! We now have " << nb_spikes_ << " spikes." << std::endl;
			
	}
		
	if (refractory_steps_ > 0) { //if the neuron is refractory
		potential_ = 0.0;
	} else {
		c1_ = exp(-h/tau_);
		potential_ = c1_ * potential_ + ext_input * resistance_ * (1- c1_) + ring_buffer_[step % (ring_buffer_.size())];
		ring_buffer_[step % ring_buffer_.size()] = 0.0;
			
	}
	
	output << "Time : " << clock_ << " ms; Membrane potential : " << potential_ << " mV" << std::endl;
	clock_ += h; //update the neuron clock
	
	return spike;
}

void Neuron::resizeBuffer(int i) {
	ring_buffer_.resize(i);
}
		
