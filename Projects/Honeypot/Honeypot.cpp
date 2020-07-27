#include "Honeypot.h"
#include "Honeypot/Context.h"

#include <iostream>

int main(int argc, char** argv)
{
	Honeypot::Context(argc, argv).Run();
}
