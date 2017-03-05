//Channel generator

const uint8_t in = A0;
const uint8_t out = A1;
const unsigned long syncTime = 15; //ms, ulong is same as Arduino libraries use for time.
const unsigned long bitTime = 9; //ms
const int trainLength = 4; //Amount of bits in the train

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(in, INPUT);
	pinMode(out, OUTPUT);

	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	OCR1A = (16000000/1024)*15;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	interrupts();

	Serial.begin(2000000); //Baud rate of 2Mbps
	Serial.println("Program initialized");
}

//Timer compare routine for the 1ms timer
ISR(TIMER1_COMPA_vect) {
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

//Basic pulse train
void loop() {
	Serial.print("Start time:");
	Serial.println(micros());
	writeSync(out);
	//Serial.print("Finished writing the sync pulse, current time:");
	//Serial.println(micros());
	for (int i = 0; i < trainLength; i++) {
		write0(out);
		//Serial.print("Finished writing the ");
		//Serial.print(i);
		//Serial.print("th pulse, current time:");
		//Serial.println(micros());
	}
	Serial.print("Finished writing the starting train, end time:");
	Serial.println(micros());
}

//Writes a sync signal, does not handle entry of pins not defined as output.
inline void writeSync(uint8_t pin) {
	digitalWrite(pin, HIGH);
	delay(syncTime); //15ms, TODO(sjon): change to a trap at some point?
	digitalWrite(pin, LOW);
}

//Writes 25% low, 75% high
inline void write0(uint8_t pin) {
	digitalWrite(pin, LOW);
	delay(bitTime / 4);
	digitalWrite(pin, HIGH);
	delay(bitTime - (bitTime / 4));
}

//Writes 75% low, 25% high
inline void write1(uint8_t pin) {
	digitalWrite(pin, LOW);
	delay((bitTime/4) * 3);
	digitalWrite(pin, HIGH);
	delay(bitTime - (bitTime / 4) * 3);
}