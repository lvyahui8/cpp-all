#pragma once
class Persion
{
private :
	char * name;
public:
	Persion(void);
	virtual ~Persion(void);
	char * getName() const;
};

