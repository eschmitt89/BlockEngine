#ifndef GemGenerator_hpp
#define GemGenerator_hpp

#include "Gem.hpp"

class GemGenerator
{
public:
	GemGenerator();
    virtual ~GemGenerator();

	Gem* Generate(int level);

protected:

};

#endif /* GemGenerator_hpp */
