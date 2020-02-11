#if 0
#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <vector>

#define _SC_CB_METHODSTART(x) (x+0x7FFFFF00)
#define SC_CB_STARTONLY 	_SC_CB_METHODSTART(1)
#define SC_CB_STARTEND 		_SC_CB_METHODSTART(2)

#define SC_CB_PERSEC		1
#define SC_CB_PERMIN		60
#define SC_CB_PERHOUR		3600

class ScheduleHandler{
	public:
	void (EventCallback *)(void * data, int hour, int min, int sec);
	typedef struct{
		EventCallback fnCall;
		
		//Value as defined by 
		int cb_method,
		
		int hour_start;
		int min_start;
		int sec_start;
		
		int hour_end;
		int min_end;
		int sec_end;
		
		void * data;
	}ScheduleItem;
	
	private:
	typedef enum{
		
	}
	typedef struct{
		ScheduleItem * item;
		int 
		int loopTag;
		bool completed;
		
	}ScheduleItem_private;
	
	public:
	ScheduleHandler(ScheduleItem[] Items, int size);
	void Update(unsigned long epoch, unsigned int hour, unsigned int min, unsigned int sec);
	
	private:
	ScheduleItem * 	m_items;
	int 			m_itemsSize;
	int 			m_loopCount;
	std::vector<ScheduleItem_private> m_orderedItems;
}

#endif //__SCHEDULE_H__
#endif
