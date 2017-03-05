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
}

//Basic pulse train
void loop()
{
	writeSync(out);
	for (int i = 0; i < trainLength; i++) {
		write0(out);
	}
}

//Writes a sync signal, does not handle entry of pins not defined as output.
void writeSync(uint8_t pin) {
	digitalWrite(pin, HIGH);
	delay(syncTime); //15ms, TODO(sjon): change to a trap at some point?
	digitalWrite(pin, LOW);
}

//Writes 25% low, 75% high
void write0(uint8_t pin) {
	digitalWrite(pin, LOW);
	delay(bitTime / 4);
	digitalWrite(pin, HIGH);
	delay(bitTime - (bitTime / 4));
}

//Writes 75% low, 25% high
void write1(uint8_t pin) {
	digitalWrite(pin, LOW);
	delay(bitTime - (bitTime / 4));
	digitalWrite(pin, HIGH);
	delay(bitTime - (bitTime / 4));
}