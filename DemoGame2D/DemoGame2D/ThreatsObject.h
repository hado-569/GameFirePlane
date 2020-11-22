#ifndef _THREAT_OBJECT_H_
#define _THREAT_OBJECT_H_

#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 75
#define HEIGHT_THREAT 50


class ThreatObject :public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleINPUTACTION(SDL_Event events);
	void HandleMOVE(const int& x_border,const int& y_border);

	void set_x_val(const int& val) { x_val = val; }
	void set_y_val(const int& val) { y_val = val; }

	int get_x_val()const { return x_val; }
	int get_y_val()const { return y_val; }

	std::vector<AmoObject*> get_amo_list() const { return amo_list_; }
	void set_amo_list(const std::vector<AmoObject*>& amo_list) { amo_list_ = amo_list; }

	void InnitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);

	void Reset(const int& x_border);
	void ResetAMO(AmoObject* p_amo);
private:

	int x_val;
	int y_val;

	std::vector<AmoObject*> amo_list_;


};



#endif // !_THREAT_OBJECT_H_

