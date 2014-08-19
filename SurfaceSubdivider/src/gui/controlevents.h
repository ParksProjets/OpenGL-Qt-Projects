#ifndef CONTROLEVENTS_H_
#define CONTROLEVENTS_H_

class ControlEventHandler
{
public:
	virtual ~ControlEventHandler() {};

    virtual void HandleSubdivide() = 0;
    virtual void HandleUndivide() = 0;
};

#endif
