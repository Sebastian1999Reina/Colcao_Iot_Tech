struct myMillis{ 
	unsigned long offset = 0;
	unsigned long get(){
		return millis() - offset;
	}
	void reset(){
		offset = millis();
	}
	void set(unsigned long value){
		offset = millis() - value;
	}
};
