/*
  position queue
  
*/

#include <stdint.h>
#include <float.h>
#include "datecalc.h"

typedef float gps_float_t;
#define GPS_FLOAT_MAX	FLT_MAX


struct _gps_pos_struct
{
  gps_float latitude;
  gps_float longitude;
};
typedef struct gps_pos_t;

struct _pq_entry_struct
{
  gps_pos_t pos;
  uint32_t timestamp;	/* seconds since 1.1.2000 */
  uint16_t millisecond;	/* milliseconds of the timestamp */
};
typedef struct _pq_entry_struct pq_entry_t;

struct _pq_interface_struct
{
  gps_pos_t pos;
  gps_float speed_in_knots;
  gps_float true_course;
  gps_float magnetic_variation;
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint16_t millisecond;
};
typedef struct _pq_interface_struct pq_interface_t;

#define PQ_LEN 16

struct _pq_struct
{
  pq_interface_t interface;
  pq_entry_t queue[PQ_LEN];
  uint8_t cnt;		/* entries in the queue */	
};
typedef struct _pq_struct pq_t;


void pq_DeleteFirst(pq_t *pq)
{
  uint8_t i;
  if ( pq->cnt > 0 )
  {
    for( i = 1; i < pq->cnt; i++ )
    {
      pq->queue[i-1] = pq->queue[i];
    }
    pq->cnt--;
  }
}

/* add values from the interface to the queue record */
void pq_AddInterfaceValuesToQueue(pq_t *pq)
{
  if ( pq->cnt >= PQ_LEN )
    pq_DeleteFirst(pq);
  pq->queue[pq->cnt].pos = pq->interface.pos;
  pq->cnt++;
}
