#ifndef EVENT_H
#define EVENT_H

#include "types.h"

#include "constants/event.h"

extern u32 gEventsTriggered[8];

u32 EventFunction(EventAction action, Event event);

#endif /* EVENT_H */
