// JAN DARGE

// this was simply just practice.
// i wanted to see if i could manipulate bits in *.c
// the way i would on paper. 
// essentially, automating the process

/*

	ENCRYPT EXAMPLE:
		
		INPUTS
		======
		Key               =       170       (1010 1010) 
		Plaintext         =       240       (1111 0000)
		Shift (circular)  =       2
		
		PROCESS
		=======
		1. Unary the Output for 8 bits   -> (0000 1111) == 15
		2. XOR Ouput and Key for 8 bits  -> (1010 0101) == 165
		3. Circular shift bits for Shift -> (1001 0110) == 150
		
	DECRYPT EXAMPLE:
		
		INPUTS
		======
		Key               =       170       (1010 1010) 
		Plaintext         =       150       (1001 0110)
		Shift (circular)  =       2
		
		PROCESS
		=======
		1. Circular shift bits for Shift -> (1010 0101) == 165
		2. XOR Ouput and Key for 8 bits  -> (0000 1111) == 15
		3. Unary the Ouput for 8 bits    -> (1111 0000) == 240
		
*/

#include <stdio.h>

void encrypt();
void decrypt();

int main(void) {

	// BASIC 8 BIT ECB EXAMPLE

	int x;
	while(1) {
		printf("Options:\n\t 1. Encrypt\n\t 2. Decrypt\n\t-1. Exit\n\nInput -> ");
		scanf("%d",&x);
		if(x == -1) {
			break;
		} else if (x == 1) {
			encrypt();
		} else if (x == 2) {
			decrypt();
		}
		printf("\n=============================================================\n\n");
	}
}

void encrypt() {
	unsigned int key;
	unsigned int input;
	unsigned int shift;
	
	printf("Enter a number key [0-255]:       -> ");
	scanf("%u", &key);
	
	printf("Enter a number plaintext [0-255]: -> ");
	scanf("%u", &input);
	
	printf("Enter a number shift [0-255]:     -> ");
	scanf("%u", &shift);
	
	// FLIP LEAST SIGNIFICANT 8 BITS
	unsigned int encryption_output = ~input & 0xFF;
	
	// XOR OUTPUT AND KEY 
	encryption_output ^= key & 0xFF;
	
	// CIRCULAR SHIFT THE LAST 8 BITS FOR SHIFT
	for(int i = 0; i < shift; i++) {
		if(encryption_output > 128) {
			encryption_output = (encryption_output << 1) & 0xFF;
			encryption_output++;
		} else {
			encryption_output = (encryption_output << 1) & 0xFF;
		}
	}

	printf("ECB encrypted number:             -> %u", encryption_output);
}

void decrypt() {
	unsigned int key;
	unsigned int input;
	unsigned int shift;
	
	printf("Enter a number key [0-255]:       -> ");
	scanf("%u", &key);
	
	printf("Enter a number plaintext [0-255]: -> ");
	scanf("%u", &input);
	
	printf("Enter a number shift [0-255]:     -> ");
	scanf("%u", &shift);
	
	unsigned int decryption_output = input;
	
	// CIRCULAR SHIFT THE LAST 8 BITS FOR SHIFT
	for(int i = 0; i < shift; i++) {
		if(decryption_output & 1) {
			decryption_output = (decryption_output >> 1) & 0xFF;
			decryption_output += 128;
		} else {
			decryption_output = (decryption_output >> 1) & 0xFF;
		}
	}
	
	// XOR OUTPUT AND KEY 
	decryption_output ^= key & 0xFF;
	
	// FLIP LEAST SIGNIFICANT 8 BITS
	decryption_output = ~decryption_output & 0xFF;

	printf("ECB decrypted number:             -> %u", decryption_output);
}
