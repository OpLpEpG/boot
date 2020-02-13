/*
 * dev.h
 *
 *  Created on: 28 џэт. 2019 у.
 *      Author: Oleg
 */

#ifndef CORE_INC_DEV_H_
#define CORE_INC_DEV_H_

#include <stdint.h>
#include <string.h>
#include <tools.h>

#ifndef DEV_COUNT
# define DEV_COUNT 16
#endif

void Setup(void);
void Loop(void);

typedef enum {
	DEV_OK,
	DEV_ERR,
    DEV_BUSY,
	DEV_TIMEOUT,
	DEV_ERR_BUFF,
	DEV_TX,
	DEV_RX
} errdev_e;


class dev_c {
public:
	dev_c();
    volatile errdev_e status;
	virtual ~dev_c(){}
    virtual void begin(){}
    virtual void sleep(){}
    virtual void wakeup(){}
    virtual void end(){}
};

/*class bfdev_c: public dev_c {
public:
	const uint16_t buflen;
	const uint16_t rxcnt = cnt;
	const uint8_t* const Buf = this->buf;

	bfdev_c(const uint16_t buflen, uint8_t* const buf) :dev_c(), buflen(buflen), buf(buf){}

	INLINE_FORCE void txcnt(uint16_t c){assert_param(c < buflen); cnt = c; }

	virtual void copy_to_buf(const void* inbuf, uint16_t from, uint16_t c)
	{
		assert_param(from + c < buflen);
		if (from + c < buflen) memcpy(&buf[from], inbuf, c);
	}
protected:
	uint8_t* const buf;
	volatile uint16_t cnt;
};

class rwdev_c: public bfdev_c {
public:
	rwdev_c(const uint16_t buflen, uint8_t* const buf):bfdev_c(buflen, buf){}
	virtual ~rwdev_c(){}

	errdev_e write(const void* buf, uint16_t from, uint16_t cnt)
	{
		if (from + cnt > buflen) return DEV_ERR_BUFF;
		this->copy_to_buf((uint8_t*) buf, from, cnt);
		return write(from + cnt);
	}
	virtual errdev_e write(uint16_t cnt)
	{
		if (cnt > buflen) return DEV_ERR_BUFF;
		this->cnt = cnt;
		return this->status;
	}
	virtual errdev_e read(void)
	{
		return this->status;
	};
protected:
private:
};*/

#ifndef UNUSE_DEVROOT
class dev_root_c {
public:
	//dev_root_c(): cnt(0) {}
	static void add(dev_c* dev){devs[cnt++] = dev;}
	static void begin(void)
	{
		for(uint8_t i = 0; i< cnt; i++) devs[i]->begin();
	}
	static void sleep(void)
	{
		for(uint8_t i = 0; i< cnt; i++) devs[i]->sleep();
	}
	static void wakeup(void)
	{
		for(uint8_t i = 0; i< cnt; i++) devs[i]->wakeup();
	}
	static void end(void)
	{
		for(uint8_t i = 0; i< cnt; i++) devs[i]->end();
	}
public:
    static dev_c* devs[DEV_COUNT];
    static uint8_t cnt;
};
#endif

inline dev_c::dev_c(): status(DEV_OK)
{
#ifndef UNUSE_DEVROOT
	dev_root_c::add(this);
#endif
}


#endif /* CORE_INC_DEV_H_ */
