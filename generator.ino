//Channel generator

const uint8_t in = A0;
const uint8_t out = A1;
const unsigned long syncTime = 15; //ms, ulong is same as Arduino libraries use for time.
const unsigned long bitTime = 9; //ms
const int trainLength = 4; //Amount of bits in the train

void setup()
{
	pinMode(in, INPUT);
	pinMode(out, OUTPUT);
	Serial.begin(2000000); //Baud rate of 2Mbps
	Serial.println("Program initialized");
}

//Basic pulse train
void loop()
{
	Serial.print("Start time:");
	Serial.println(millis());
	writeSync(out);
	Serial.print("Finished writing the sync pulse, current time:");
	Serial.println(millis());
	for (int i = 0; i < trainLength; i++) {
		write0(out);
		Serial.print("Finished writing the ");
		Serial.print(i);
		Serial.print("th pulse, current time:");
		Serial.println(millis());
	}
	Serial.print("Finished writing the starting train, end time:");
	Serial.println(millis());
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