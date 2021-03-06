#include <iostream>
#include "HackableCode.h"

HackableCode* hackableCode = nullptr;

int hackableRoutine()
{
	// Pointers to the beginning/end of the hackable code
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;
	int i = 40;

	// This is the code we want to be hackable by the user
	HACKABLE_CODE_BEGIN(assemblyAddressStart, labelStart)
	i += 60;
	HACKABLE_CODE_END(assemblyAddressEnd, labelEnd)

	if (hackableCode == nullptr)
	{
		hackableCode = new HackableCode(assemblyAddressStart, assemblyAddressEnd);
	}

	return i;
}

int main()
{
	// Initialize hackable code (it has to be run once)
	std::cout << hackableRoutine() << "\n";

	// Print original code
	std::cout << hackableCode->assemblyString;

	hackableCode->assemblyString = "nop";

	/*
	// Another example:
	hackableCode->assemblyString = 
		"push eax" "\n"
		"mov eax, 0x40" "\n"
		"pop eax" "\n";
	*/

	if (!hackableCode->applyCustomCode())
	{
		std::cout << "Error compiling assembly!" << "\n";
	}
	else
	{
		std::cout << hackableRoutine() << "\n";
	}
}